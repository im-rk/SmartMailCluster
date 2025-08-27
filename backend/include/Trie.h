#ifndef TRIE_H
#define TRIE_H
#include<bits/stdc++.h>
using namespace std;
struct TrieNode
{
    unordered_map<char,TrieNode*> next;
    vector<int> emailids;
    bool end=false;

    void put(char ch, TrieNode* node);
    TrieNode *get(char ch);
};

class Trie{
    private:
        TrieNode* root;

    public:
        Trie();
        ~Trie();

        void insertword(const string &word,int emailid);

        TrieNode* getroot();
};

#endif