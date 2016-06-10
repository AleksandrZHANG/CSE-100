/*
 * UnionSets.hpp
 * Author: <Yihong Zhang, Hao Gai>
 * Date:   <2016.6.3>
 */

#ifndef UnionSets_HPP
#define UnionSets_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

struct ActorNode {

public:
    string name;
    ActorNode* parent;
    bool done;
    set<ActorNode*> adj;
    vector<ActorNode*> adjvector;
    ActorNode(string name):name(name), parent(NULL), done(false){};
};

class UnionSets {
    
public:
    int maxyear, minyear;

    map<pair<string, int>, unordered_set<ActorNode*>> movieActor;

    map<pair<string, int>, vector<ActorNode*>> movieActorvector;
    
    unordered_map<string, ActorNode*> Actors;
    
    map<int, vector<string>> yearMovie;
    
    UnionSets(void);

    ~UnionSets(void);

    ActorNode* Find(ActorNode* x);

    void Union(ActorNode* x, ActorNode* y);

    bool sameSet(ActorNode* x, ActorNode* y);

    bool loadFromFile(const char* in_filename);
    
    bool loadPairs(const char* in_filename,vector<vector<string>>&pairs);
};


#endif // UnionSets_HPP
