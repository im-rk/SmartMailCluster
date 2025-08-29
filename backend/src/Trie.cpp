#include "Trie.h"
#include<bits/stdc++.h>
using namespace std;

void TrieNode::put(char ch, TrieNode* root)
{
    next[ch]=root;
}

TrieNode* TrieNode::get(char ch)
{
    return next[ch];
}

Trie::Trie(){
    root=new TrieNode();
}

Trie::~Trie()
{
    delete root;
}

void Trie::insertword(const string &word,int emailid)
{
    TrieNode *node=root;
    for(char c: word)
    {
        if(!node->next.count(c))
        {
            node->put(c,new TrieNode());
        }
        node=node->get(c);
    }
    node->end=true;
    if(node->emailids.empty()||node->emailids.back()!=emailid)
    {
        node->emailids.push_back(emailid);
    }
}

TrieNode* Trie::getroot()
{
    return root;
}