/*
 * ActorGraph.cpp
 * Author: <Yihong Zhang, Hao Gai>
 * Date:   <2016.5.27>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"

using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
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
        if (!actorNode.count(actor_name))
            actorNode[actor_name] = new ActorNode(actor_name);
        // use pair to store actor/movie relationship
        pair<string, int> movieinfo(movie_title, movie_year);
        movieActor[movieinfo].insert(actor_name);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    // create graph
    for (auto it=movieActor.begin(); it!=movieActor.end(); it++) {
        for (auto it1=it->second.begin(); it1!=it->second.end(); it1++) {
            for (auto it2=it->second.begin(); it2!=it->second.end(); it2++) {
                if (it1 != it2)
                    actorNode[*it1]->add(actorNode[*it2],it->first);
            }
        }
    }
    for (auto it=actorNode.begin(); it!=actorNode.end(); it++) {
        for(auto it1=it->second->adj.begin(); it1!=it->second->adj.end(); it1++)
            it->second->adjvector.push_back(it1->second);
    }

    return true;
}
