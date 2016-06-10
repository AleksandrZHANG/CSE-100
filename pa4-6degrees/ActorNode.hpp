/*
 * ActorNode.hpp
 * Author: <Yihong Zhang, Hao Gai>
 * Date:   <2016.5.27>
 */

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <limits.h>

// Maybe include some data structures here

using namespace std;

class ActorNode;

struct edge {
    // define a structure with movie's actor, name and year
    ActorNode* node;
    string name;
    int year;
    edge(ActorNode* actor, const string& name, int year):node(actor), name(name), year(year){};
};

class ActorNode {
public:
    string name;
    int dist;
    ActorNode* prev;
    bool done;
    unordered_map<string, edge*> adj;
    vector<edge*> adjvector;
    ActorNode(string name):name(name), dist(INT_MAX), prev(NULL), done(false){};
    void add (ActorNode* actor, const pair<string, int>& info) {
        if (!adj.count(actor->name))
            adj[actor->name] = new edge(actor, info.first, info.second);
    }
    ~ActorNode() {
        for (auto it=adj.begin(); it!=adj.end(); it++)
            delete it->second;
    }
};

#endif // ACTORNODE_HPP
