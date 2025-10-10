#ifndef CLUSTER_H
#define CLUSTER_H

#include "Trie.h"
#include "Preprocessor.h"
#include "Graph.h"
#include "HashMap.h"
#include "DisjointSet.h"
#include <bits/stdc++.h>
using namespace std;

class Cluster {
public:
    // Main function to build clusters from emails
    void clusterEmails(Graph &graph);

private:
    // DFS helper: fills commonCount with word-sharing stats
    void clusterFromTrie(TrieNode *node, unordered_map<int, unordered_map<int,int>> &commonCount);
};

#endif // CLUSTER_H
