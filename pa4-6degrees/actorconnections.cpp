/*
 * actorconnection.cpp
 * Author: <Yihong Zhang, Hao Gai>
 * Date:   <2016.6.3>
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "UnionSets.hpp"

using namespace std;

bool BFS (UnionSets* us, ActorNode* begin, ActorNode* end) {
/* Initialize queue, set dist to INFINITY and prev to null for all nodes
 * Add S to queue and set S.dist to 0
 * while queue is not empty:
 *   dequeue node curr from head of queue
 *   for each of curr's neighbors, n:
 *   if n.dist == INFINITY:
 *     set n.dist to curr.dist+1
 *     set n's prev to curr
 *     enqueue n to the queue
 */
    queue<ActorNode*> toExplore;
    for(auto it=us->Actors.begin(); it!=us->Actors.end(); it++)
        (*it).second->done = false;
    toExplore.push(begin);
    begin->done = true;
    while (!toExplore.empty()) {
        ActorNode* next = toExplore.front();
        toExplore.pop();
        for (auto it=next->adjvector.begin(); it!=next->adjvector.end(); it++) {
            if (*it == end)
                return true;
            if ((*it)->done == false) {
                (*it)->done = true;
            toExplore.push(*it);                
            }
        }
    }
    return false;
}

void BFSFind (UnionSets* us, vector<vector<ActorNode*>>& pairs, vector<int>& ret, int count) {
    int maxyear = us->maxyear;
    int minyear = us->minyear;
    // traverse all years in increasing order
    while (minyear <= maxyear) {       
        // pair actors which have the same movie in current year
        vector<string>* v = &us->yearMovie[minyear];
        for (int i=0; i<v->size(); i++) {
            vector<ActorNode*>* actors = &(us->movieActorvector[make_pair((*v)[i], minyear)]);
            // traverse all actors, insert them to the adj as each other
            for (auto it1=(*actors).begin(); it1!=(*actors).end(); it1++)
                for (auto it2=(*actors).begin(); it2!=(*actors).end(); it2++)
                    if (it1!=it2 && !(*it1)->adj.count(*it2)) {
			  (*it1)->adjvector.push_back(*it2);
			  (*it2)->adjvector.push_back(*it1);
                    }
        }
        // repeat BFS until all pairs have been done
        for (int i=0; i<pairs.size(); i++) {
            // if two actors are connected in current year
            if (ret[i] == 9999 && BFS(us,pairs[i][0],pairs[i][1])) {
                ret[i] = minyear;
                count--;
                if (!count)
                    return;
            }
        }
        minyear++;
    }
}

void UnionFind (UnionSets* us, vector<vector<ActorNode*>>& pairs, vector<int>& ret, int count) {
    int maxyear = us->maxyear;
    int minyear = us->minyear;
    // traverse all years in increasing order
    while (minyear <= maxyear) {       
        // pair actors which have the same movie in current year
        vector<string>* v = &us->yearMovie[minyear];
        for (int i=0; i<v->size(); i++) {
            unordered_set<ActorNode*>* actors = &(us->movieActor[make_pair((*v)[i],minyear)]);
            unordered_set<ActorNode*>::iterator it = (*actors).begin();
            // check for root
            if(!(*it)->parent)
                (*it)->parent = (*it);
            // make (*it)->parent as root
            ActorNode* root = (*it)->parent;
            it++;
            for(; it!=(*actors).end(); it++)
                us->Union(root,(*it));
        }
        
        // repeat check for sameset until all pairs have been done
        for(int i=0; i<pairs.size(); i++) {
            // if two actors are in the same set
            if(ret[i] == 9999 && us->sameSet(pairs[i][0],pairs[i][1])) {
                ret[i] = minyear;
                count--;
                if (!count)
                    return;
            }
        }
        minyear++;
    }  
}

int main(int argc, char *argv[]) {
    // Check for Arguments
    if (argc < 4) {
        cout << "Incorrect number of arguments.\n";
        std::cout << "movie_casts.tsv test_pairs.tsv out_connections_bfs.tsv bfs (or ufind)\n";
        return -1;
    }

    UnionSets* us = new UnionSets();
    us->loadFromFile(argv[1]);
    vector<vector<string>> pairs;
    us->loadPairs(argv[2], pairs);
    // contain in each line an actor pair followed by the year after which the corresponding actor pair became connected
    vector<vector<ActorNode*>> actorpairs;
    for (int i=0; i<pairs.size(); i++) {
        actorpairs.push_back(vector<ActorNode*>());
        if(!us->Actors.count(pairs[i][0]))
            actorpairs.back().push_back(NULL);
        else
            actorpairs.back().push_back(us->Actors[pairs[i][0]]);
        if(!us->Actors.count(pairs[i][1]))
            actorpairs.back().push_back(NULL);
        else
            actorpairs.back().push_back(us->Actors[pairs[i][1]]);
    }
    vector<int> res;
    res = vector<int>(pairs.size(),9999);
    int count = pairs.size();
    for (int i=0; i<pairs.size(); i++) {
        if (!actorpairs[i][0] || !actorpairs[i][1]) {
            res[i] = -1;
            count--;
        }
    }
    if (!strcmp(argv[4],"bfs"))
        BFSFind(us, actorpairs, res, count);
    else
        UnionFind(us, actorpairs, res, count);
    
    // If they never became connected even after adding all the movies from in the movie cast file to your graph, you should output 9999 on that line.
    for (int i=0; i<res.size(); i++) {
        if (res[i] == -1)
            res[i] = 9999;
    }

    // write the result into output file
    ofstream os;
    os.open(argv[3]);
    os << "Actor1\tActor2\tYear\n";
    for (int i=0; i<pairs.size(); i++)
        os << pairs[i][0] << "\t" << pairs[i][1] << "\t" << res[i] << endl;
    os.close();

    delete us;
    return 0;
}
