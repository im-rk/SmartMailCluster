#include "Trie.h"

TrieNode::TrieNode() {
    emailIds.clear();
    children.clear();
}

Trie::Trie(DisjointSet* dsPtr) {
    root = new TrieNode();
    ds = dsPtr;
}
void Trie::insertWithPrefixUnion(const string &s, int emailId) {
    TrieNode* node = root;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        char ch = s[i];
        if (node->children.find(ch) == node->children.end()) {
            node->children[ch] = new TrieNode();
        }
        node = node->children[ch];

        if (ch == ' ' || i == n - 1) {
            
            
            for (int otherId : node->emailIds) {
                ds->unionbyRank(otherId, emailId);
            }
            node->emailIds.insert(emailId);
            node = root;  
        }
    }
}



bool Trie::existsPrefix(const string &prefix) {
    TrieNode* node = root;
    for (char ch : prefix) {
        if (node->children.find(ch) == node->children.end()) return false;
        node = node->children[ch];
    }
    return true;
}
