/*
 * ActorGraph.hpp
 * Author: <Yihong Zhang, Hao Gai>
 * Date:   <2016.5.27>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "ActorNode.hpp"

// Maybe include some data structures here

using namespace std;

class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here
    map<pair<string,int>, unordered_set<string>> movieActor;

public:
    ActorGraph(void);

    // Maybe add some more methods here

    // a hash table with key=actor name, content=ActorVertex*
    unordered_map<string, ActorNode*> actorNode;
    bool weighted;
    ~ActorGraph() {
        for (auto it=actorNode.begin(); it!=actorNode.end(); it++)
            delete it->second;
    }
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */

    bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  
};


#endif // ACTORGRAPH_HPP
