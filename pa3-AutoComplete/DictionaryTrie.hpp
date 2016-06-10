/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include <queue>
#include <iostream>

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class compare {
public:
    bool operator()(std::pair<unsigned int, std::string>& a,
                    std::pair<unsigned int, std::string>& b) const {
<<<<<<< HEAD
        if (a.first > b.first)
            return true;
        else if (a.first < b.first)
            return false;
=======
        if (a.first > b.first) {
            return true;
        }
        else if (a.first < b.first) {
            return false;
        }
>>>>>>> 3ad7d27656ae8f5923a8c90c9dd3a79f2be20dc5
        return a.second < b.second;
    }
};
class DictionaryTrie
{
public:
    
    /* Create a new Dictionary that uses a Trie back end */
    DictionaryTrie();
    
    /* Insert a word with its frequency into the dictionary.
     * Return true if the word was inserted, and false if it
     * was not (i.e. it was already in the dictionary or it was
     * invalid (empty string) */
    bool insert(std::string word, unsigned int freq);
    
    /* Return true if word is in the dictionary, and false otherwise */
    bool find(std::string word) const;
    
    /* Return up to num_completions of the most frequent completions
     * of the prefix, such that the completions are words in the dictionary.
     * These completions should be listed from most frequent to least.
     * If there are fewer than num_completions legal completions, this
     * function returns a vector with as many completions as possible.
     * If no completions exist, then the function returns a vector of size 0.
     * The prefix itself might be included in the returned words if the prefix
     * is a word (and is among the num_completions most frequent completions
     * of the prefix)
     */
    std::vector<std::string>
    predictCompletions(std::string prefix, unsigned int num_completions);
    
    /* Destructor */
    ~DictionaryTrie();
    
private:
    // Add your own data members and methods here
    class TSTNode{
    public:
        unsigned int freq;
        unsigned int max_freq;
        const char letter;
        TSTNode* left;
        TSTNode* right;
        TSTNode* middle;
        TSTNode(const char & c): freq(0),max_freq(0),letter(c),left(0),right(0),middle(0) {};
        // If freq == 0, this node is not an terminal node.
    };
    TSTNode* root;
    
    void dfs(std::string & prefix, TSTNode* node,
<<<<<<< HEAD
std::priority_queue<std::pair<unsigned int,std::string>, std::vector<std::pair<unsigned int, std::string> >, compare> & pq,
unsigned int num) {
        if (node == 0)
=======
             std::priority_queue<std::pair<unsigned int, std::string>,std::vector<std::pair<unsigned int, std::string> >, compare> & pq,
             unsigned int num) {
        if (node == 0) {
>>>>>>> 3ad7d27656ae8f5923a8c90c9dd3a79f2be20dc5
            return;
        }
        std::string tmp = prefix;
        tmp.push_back(node->letter);
<<<<<<< HEAD
        if ((node->freq != 0) && (pq.size() < num))
            pq.push(make_pair(node->freq, tmp));
        else if ((node->freq != 0) && (node->freq > pq.top().first)) {
            pq.push(make_pair(node->freq, tmp));
            pq.pop();
        }
        dfs(prefix, node->left, pq, num);
        dfs(prefix, node->right, pq, num);
        if ((pq.size() < num) || (node->max_freq > pq.top().first)) {
=======
        if ((node->freq != 0)&&(pq.size() < num)) {
            pq.push(make_pair(node->freq, tmp));
        }
        else if ((node->freq != 0)&&(node->freq > pq.top().first)) {
            pq.push(make_pair(node->freq, tmp));
            pq.pop();
        }
        if ((pq.size() < num)||(node->max_freq > pq.top().first)) {
            dfs(prefix, node->left, pq, num);
            dfs(prefix, node->right, pq, num);
>>>>>>> 3ad7d27656ae8f5923a8c90c9dd3a79f2be20dc5
            dfs(tmp, node->middle, pq, num);
        }
    }
};

#endif // DICTIONARY_TRIE_HPP
