/*
 * pathfinder.cpp
 * Author: <Yihong Zhang, Hao Gai>
 * Date:   <2016.5.27>
 */
 
#include <queue>
#include <string.h>

#include "ActorGraph.hpp"

using namespace std;

class compNode {
    public:
        bool operator() (ActorNode*& one, ActorNode*& other){
            return (one->dist) > (other->dist);
    }
};

int weight(int & Y, bool use_weighted_edges) {
    // weighted path find and unweighted
    int weight = 1;
    if (use_weighted_edges)
        weight = 1 + (2015 - Y);
    return weight;
}

bool loadPairs(const char* in_filename, vector<vector<string>>& v)
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

void Dijkstra(ActorGraph* graph, string from, string end, bool weighted, vector<string>& res) {
    priority_queue<ActorNode*, vector<ActorNode*>, compNode> toExplore;
    for (auto it=graph->actorNode.begin(); it!=graph->actorNode.end(); it++) {
        it->second->prev = NULL;
        it->second->dist = INT_MAX;
        it->second->done = false;
    }
    ActorNode* start = graph->actorNode[from];
    start->dist = 0;
    toExplore.push(start);
    while (!toExplore.empty()) {
        ActorNode* next = toExplore.top();
        toExplore.pop();
        for (int i=0; i<next->adjvector.size(); i++) {
            if (!next->done)
                next->done = true;
            int dist = weight(next->adjvector[i]->year, weighted);
            if (next->dist+dist < next->adjvector[i]->node->dist) {
                next->adjvector[i]->node->dist = next->dist+dist;
                next->adjvector[i]->node->prev = next;
                toExplore.push(next->adjvector[i]->node);
            }
        }
    }
    ActorNode* curr = graph->actorNode[end];
    while (curr->name != from) {
        res.push_back(curr->name);
        res.push_back(to_string(curr->prev->adj[curr->name]->year));
        res.push_back(curr->prev->adj[curr->name]->name);
        curr = curr->prev;
    }
    res.push_back(from);
}

int main(int argc, char *argv[]) {
    // Check for Arguments
    if (argc < 5) {
        cout << "Incorrect number of arguments.\n";
        cout << "./pathfinder movie_casts.tsv w test_pairs.tsv out_paths_weighted.tsv\n";
        return -1;
    }

    bool weighted = false;
    if (!strcmp(argv[2],"w")) {
        weighted = true;
        if (!strcmp(argv[2],"u")) {
            cout << "The third argument should be u or w.\n";
            return -1;
        }
    }
    ActorGraph* graph = new ActorGraph();
    graph->loadFromFile(argv[1], weighted);
    vector<vector<string>> pairs;
    loadPairs(argv[3], pairs);
    ofstream os;
    os.open(argv[4]);

    // write the result into output file
    os << "(actor)--[movie#@year]-->(actor)--..." << endl;
    for(int i=0; i<pairs.size(); i++) {
        vector<string> path;
        Dijkstra(graph, pairs[i][0], pairs[i][1], weighted, path);
        int j = path.size()-1;
        os << "("<<path[j--]<<")";
        for(; j>=0; j-=3)
            os << "--["<<path[j]<<"#@"<<path[j-1]<<"]-->("<<path[j-2]<<")";
        os << endl;
    }
    os.close();

    delete graph;
    return 0;
}
