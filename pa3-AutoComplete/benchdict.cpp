/**
 *  CSE 100 PA3
 *  Authors: Yihong Zhang, Hao Gai
 *  Date: 5.11.2016 
*/

#include "util.hpp"
#include "DictionaryTrie.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void benchdict_trie(int min_size, int step_size, int num_iterations, std::string dict_filename){

    ifstream in;
    in.open(dict_filename, std::ios::binary);


    // Testing student's trie
    DictionaryTrie* dictionary_trie = new DictionaryTrie();

    Timer T;
    long long time_duration;
    int i = 0;
    int j = 0;
    int times = 100;

    cout << "DictionaryTrie" << endl;

    for (i=0; i<num_iterations; i++){
        Utils::load_dict(*dictionary_trie, in, min_size+i*step_size);
        T.begin_timer();
        for (j=0; j<times; j++){
            dictionary_trie->find("YihongZhang1");
            dictionary_trie->find("ZhangYihong2");
            dictionary_trie->find("HaoGai3");
            dictionary_trie->find("GaiHao4");
            dictionary_trie->find("YanYi5");
            dictionary_trie->find("YiYan6");
            dictionary_trie->find("RuiGuo7");
            dictionary_trie->find("GuoRui8");
            dictionary_trie->find("ZhengYi9");
            dictionary_trie->find("YiZheng10");
        }
        time_duration = T.end_timer();
        cout << min_size+i*step_size << "\t" << time_duration/times << endl;
    }
    cout << endl;
    delete dictionary_trie;


}

void benchdict_bst(int min_size, int step_size, int num_iterations, std::string dict_filename){

    ifstream in;
    in.open(dict_filename, std::ios::binary);


    // Testing student's bst
    DictionaryBST* dictionary_bst = new DictionaryBST();

    Timer T;
    long long time_duration;
    int i = 0;
    int j = 0;
    int times = 100;

    cout << "DictionaryBST" << endl;
    
    for (i=0; i<num_iterations; i++){
        Utils::load_dict(*dictionary_bst, in, min_size+i*step_size);
        T.begin_timer();
        for (j=0; j<times; j++){
            dictionary_bst->find("YihongZhang1");
            dictionary_bst->find("ZhangYihong2");
            dictionary_bst->find("HaoGai3");
            dictionary_bst->find("GaiHao4");
            dictionary_bst->find("YanYi5");
            dictionary_bst->find("YiYan6");
            dictionary_bst->find("RuiGuo7");
            dictionary_bst->find("GuoRui8");
            dictionary_bst->find("ZhengYi9");
            dictionary_bst->find("YiZheng10");
        }
        time_duration = T.end_timer();
        cout << min_size+i*step_size << "\t" << time_duration/times << endl;
    }
    cout << endl;
    delete dictionary_bst;
}

void benchdict_hashtable(int min_size, int step_size, int num_iterations, std::string dict_filename){

    ifstream in;
    in.open(dict_filename, std::ios::binary);


    // Testing student's hashtable
    DictionaryHashtable* dictionary_hashtable = new DictionaryHashtable();

    Timer T;
    long long time_duration;
    int i = 0;
    int j = 0;
    int times = 100;

    cout << "DictionaryHashtable" << endl;

    for (i=0; i<num_iterations; i++){
        Utils::load_dict(*dictionary_hashtable, in, min_size+i*step_size);
        T.begin_timer();
        for (j=0; j<times; j++){
            dictionary_hashtable->find("YihongZhang1");
            dictionary_hashtable->find("ZhangYihong2");
            dictionary_hashtable->find("HaoGai3");
            dictionary_hashtable->find("GaiHao4");
            dictionary_hashtable->find("YanYi5");
            dictionary_hashtable->find("YiYan6");
            dictionary_hashtable->find("RuiGuo7");
            dictionary_hashtable->find("GuoRui8");
            dictionary_hashtable->find("ZhengYi9");
            dictionary_hashtable->find("YiZheng10");
        }
        time_duration = T.end_timer();
        cout << min_size+i*step_size << "\t" << time_duration/times << endl;
    }
    cout << endl;
    delete dictionary_hashtable;
}

int main(int argc, char *argv[]) {

    if(argc != 5){
        std::cout << "Incorrect number of arguments." << std::endl;
        std::cout << "\t Correct Format:  ./benchdict min_size step_size num_iterations dictfile." << std::endl;
        std::cout << std::endl;
        exit(-1);
    }

    stringstream s1;
    int minsize;
    s1 << argv[1];
    s1 >> minsize;
    stringstream s2;
    int stepsize;
    s2 << argv[2];
    s2 >> stepsize;
    stringstream s3;
    int numiterations;
    s3 << argv[3];
    s3 >> numiterations; 
    benchdict_trie(minsize,stepsize,numiterations,argv[4]);
    benchdict_bst(minsize,stepsize,numiterations,argv[4]);
    benchdict_hashtable(minsize,stepsize,numiterations,argv[4]);


}
