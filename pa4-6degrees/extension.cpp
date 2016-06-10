/*
 * extension.cpp
 * Author: <Yihong Zhang, Hao Gai>
 * Date:   <2016.6.3>
 * Outputs the average distance to Kevin Bacon and the biggest path to Kevin Bacon 
 */

#include "ActorGraph.hpp"
#include "ActorNode.hpp"

using namespace std;

class compNode {
    public:
        bool operator() (ActorNode*& one, ActorNode*& other) {
            return (one->dist) > (other->dist);
    }
};

double averagepath (ActorGraph* graph, string begin, int& maxpath, int& minpath, pair<string,string>& res) {
/* Initialize queue, set dist to INFINITY and prev to null for all nodes
 * Add S to queue and set S.dist to 0
 * while queue is not empty:
 *   dequeue node curr from head of queue
 *   for each of curr's neighbors, n:
 *   if n.dist == INFINITY:
 *     something different from BFS
 *     set n to curr.dist+1
 *     set n's prev to curr
 *     enqueue n to the queue
 */
    int sum = 0;
    int count = 0;
    queue<ActorNode*> toExplore;
    for (auto it=graph->actorNode.begin(); it!=graph->actorNode.end(); it++) {
        it->second->prev = NULL;
        it->second->dist = INT_MAX;
        it->second->done = false;
    }   
    ActorNode* start = graph->actorNode[begin];
    toExplore.push(start);
    start->dist = 0;
    while (!toExplore.empty()) {
        ActorNode* next = toExplore.front();
        toExplore.pop();
        if (!next->done) {
            next->done = true;
            // something different from BFS
            count++;
            sum += next->dist+1;
            // update the biggest shortest path
            if (maxpath < next->dist) {
                maxpath = next->dist;
                res.first = begin;
                res.second = next->name;
            }
            int dist=next->dist+1;
            for (auto it=next->adj.begin(); it!=next->adj.end(); it++)
                if (!it->second->node->done && dist<graph->actorNode[it->first]->dist) {
                graph->actorNode[it->first]->dist = dist;
                toExplore.push(graph->actorNode[it->first]);
            }
        }
    }
    return 1.0*sum/count;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "Incorrect number of arguments.";
        std::cout << "./extension movie_casts.tsv\n";
    }

    ActorGraph* graph = new ActorGraph();
    graph->loadFromFile(argv[1], false);
    int sum, max, min;
    sum = max = min = 0;
    int count = graph->actorNode.size();
    pair<string, string> pair;
    unordered_map<string, ActorNode*>::iterator it;
    double result = averagepath(graph, "BACON, KEVIN (I)", max, min, pair);
    cout << "The average distance to Kevin Bacon = " << result << endl;
    cout << "The biggest path to Kevin Bacon is " << max << " from " << pair.second << endl;
    delete graph;
    return 0;
}
