#include "util.hpp"
#include "DictionaryBST.hpp"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
    if (find(word)) {
        return false;
    }
    dict_bst.insert(word);
    return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
    if (dict_bst.find(word) == dict_bst.end()) {
        return false;
    }
    return true;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
