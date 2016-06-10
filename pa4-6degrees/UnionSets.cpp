/*
 * UnionSets.cpp
 * Author: <Yihong Zhang, Hao Gai>
 * Date:   <2016.6.3>
 */

#include "UnionSets.hpp"

using namespace std;

UnionSets::UnionSets(void):minyear(9999),maxyear(0) {}

// delete UnionSets
UnionSets::~UnionSets(void) {
    for (auto it=Actors.begin(); it!=Actors.end(); it++)
        delete it->second;
}

// return the root of the ActorNode
ActorNode* UnionSets::Find (ActorNode* x) {
    if (x->parent != x && x->parent)
        x->parent = Find(x->parent);
    return x->parent;
}

// union, merge y into x
void UnionSets::Union (ActorNode* x, ActorNode* y) {
    if (!x->parent)
        x->parent = x;
    if (!y->parent)
        y->parent = y;
    ActorNode* xRoot = Find(x);
    ActorNode* yRoot = Find(y);
    if (xRoot == yRoot)
        return;

    // x and y are not already in the same set, merge them
    yRoot->parent = xRoot;
}

// check whether two ActorNode share the same root
bool UnionSets::sameSet (ActorNode* x, ActorNode* y) {
    ActorNode* xRoot = Find(x);
    ActorNode* yRoot = Find(y);
    return (xRoot && yRoot && (xRoot == yRoot));
}

bool UnionSets::loadFromFile(const char* in_filename) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
    
        // we have an actor/movie relationship, now what?
        // use pair to store actor/movie relationship
        pair<string, int> movieinfo(movie_title, movie_year);
        if (!Actors.count(actor_name))
            Actors[actor_name] = new ActorNode(actor_name);
      
        // contain the actor's information into movie
        if (!movieActor[movieinfo].count(Actors[actor_name])) {
            movieActorvector[movieinfo].push_back(Actors[actor_name]);   
            movieActor[movieinfo].insert(Actors[actor_name]);
        }
    }
    // map movie/year
    map <pair<string, int>, unordered_set<ActorNode*>>::iterator it;
    for (it=movieActor.begin(); it!=movieActor.end(); it++) {
        yearMovie[it->first.second].push_back(it->first.first);
        maxyear = max(maxyear, it->first.second);
        minyear = min(minyear, it->first.second);
    }
        
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

bool UnionSets::loadPairs(const char* in_filename, vector<vector<string>>& v)
{
    // Initialize the file stream
    ifstream infile(in_filename);
    
    bool have_header = false;
    
    // keep reading lines until the end of file is reached
    while (infile)
    {
        string s;
        
        // get the next line
        if (!getline( infile, s )) break;
        
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        
        istringstream ss( s );
        vector <string> record;
        
        while (ss) {
            string next;
            
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
        
        if (record.size() != 2) {
            // we should have exactly 3 columns
            continue;
        }
        
        v.push_back(record);

        // we have an actor/movie relationship, now what?
    }
    
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    
    return true;
}
