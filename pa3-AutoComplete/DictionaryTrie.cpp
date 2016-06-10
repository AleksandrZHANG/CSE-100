#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <queue>
#include <utility>

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie():root(nullptr) {}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
    bool flag = false;
    if (word.empty()) {
        return flag;
    }
    if (root == nullptr) {
        root = new TSTNode(word[0]);
    }
    TSTNode* curr = root;
    int l = word.length();
    int i = 0;
    while(i < l) {
<<<<<<< HEAD
        if (freq > curr->max_freq)
            curr->max_freq = freq;
        if (word[i] == curr->letter) {
=======
        if (freq > curr->max_freq) {
            curr->max_freq = freq;
        }
        if (word[i] == curr->letter) {

>>>>>>> 3ad7d27656ae8f5923a8c90c9dd3a79f2be20dc5
            if (i == (l-1)) {
                if (curr->freq == 0) {
                    curr->freq = freq;
                    flag = true;
                }
                return flag;
            }
            if (curr->middle == 0) {
                curr->middle = new TSTNode(word[i+1]);
                flag = true;
            }
            curr = curr->middle;
            i++;
        }
        else if (word[i] < curr->letter) {
            if (curr->left == 0) {
                curr->left = new TSTNode(word[i]);
                flag = true;
            }
            curr = curr->left;
        }
<<<<<<< HEAD
        else {
=======
        else if (word[i] > curr->letter) {
>>>>>>> 3ad7d27656ae8f5923a8c90c9dd3a79f2be20dc5
            if (curr->right == 0) {
                curr->right = new TSTNode(word[i]);
                flag = true;
            }
            curr = curr->right;
        }
    }
    return flag;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
    TSTNode* curr = root;
    if (root == 0) {
        return false;
    }
    int l = word.length();
    for (int i = 0; i < l; i++) {
        while (curr->letter != word[i]) {
            if (word[i] < curr->letter)
                curr = curr->left;
            else if (word[i] > curr->letter)
                curr = curr->right;
            if (curr == 0)
                return false;
        }
        if ((i == (l-1)) && (curr->freq == 0))
            return false;
        curr = curr->middle;
    }
    return true;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
    std::priority_queue<std::pair<unsigned int, std::string>,std::vector<std::pair<unsigned int, std::string> >, compare> pq;
    std::vector<std::string> words;
    TSTNode* curr = root;
    if (root == 0) {
        return words;
    }
    // Find the last letter of prefix
    int l = prefix.length();
    for (int i = 0; i < l; i++) {
        while (curr->letter != prefix[i]) {
<<<<<<< HEAD
            if (prefix[i] < curr->letter)
=======
            if (prefix[i] < curr->letter) {
>>>>>>> 3ad7d27656ae8f5923a8c90c9dd3a79f2be20dc5
                curr = curr->left;
            }
            else if (prefix[i] > curr->letter) {
                curr = curr->right;
<<<<<<< HEAD
            if (curr == 0)
                return words;
=======
            }
            if (curr == 0) {
                return words;
            }
>>>>>>> 3ad7d27656ae8f5923a8c90c9dd3a79f2be20dc5
        }
        if ((i == (l-1)) && (curr->freq != 0)) {
            pq.push(make_pair(curr->freq, prefix));
        }
        curr = curr->middle;
    }
    // Depth first search on TSTtrie root from curr.
    dfs(prefix, curr, pq, num_completions);
<<<<<<< HEAD
    words.resize(pq.size());
    for (unsigned int i = 0; i < pq.size(); i++) {
        words[pq.size()-1-i] = pq.top().second;
=======
    unsigned int size = pq.size();
    words.resize(size);
    for (unsigned int i = 0; i < size; i++) {
        words[size-1-i] = pq.top().second;
>>>>>>> 3ad7d27656ae8f5923a8c90c9dd3a79f2be20dc5
        pq.pop();
    }
    return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){}
