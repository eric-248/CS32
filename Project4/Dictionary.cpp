// Dictionary.cpp


#include "Dictionary.h"
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

void removeNonLetters(string& s);

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl(int maxBuckets) :m_list(maxBuckets) {}
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
private:
    vector<vector<string>> m_list;

    unsigned long int sortedHash(string s) const {
        sort(s.begin(), s.end());
        unsigned long int hash;
        int c;

        hash = 5381;
        for (auto x : s) {
            c = x;
            hash = ((hash << 5) + hash) + c;
        }
        return hash % m_list.size();
    }
};

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);

    if (word.empty()) {
        return;
    }
   
    int key = sortedHash(word);
    m_list[key].push_back(word);
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr) {
        return;
    }

    string sLetters = letters;
    removeNonLetters(sLetters);

    if (sLetters.empty()) {
        return;
    }

    sort(sLetters.begin(), sLetters.end());
    int key = sortedHash(sLetters);

    for (const string& word : m_list[key]) {
        string sortedWord = word;
        sort(sortedWord.begin(), sortedWord.end());

        if (sLetters == sortedWord) {
            callback(word);
        }

    }
 
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
