#include "util.hpp"
#include "DictionaryHashtable.hpp"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
    if (find(word)) {
        return false;
    }
    dict_hashtable.insert(word);
    return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
    if (dict_hashtable.find(word) == dict_hashtable.end()) {
        return false;
    }
    return true;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
