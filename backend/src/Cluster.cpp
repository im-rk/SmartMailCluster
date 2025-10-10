#include "Cluster.h"
void Cluster::clusterEmails(Graph &graph) {
    auto allEmails = graph.getEmailStore().getAllEmails();
    if (allEmails.empty()) {
        cout << "No emails to cluster.\n";
        return;
    }

    Preprocessor preproc;
    Trie trie;
    DisjointSet dsu(1000);

    //  Build Trie
    for (auto &e : allEmails) {
        string content = e.subject + " " + e.body;
        auto tokens = preproc.preprocessEmail(content);
        for (auto &token : tokens) {
            trie.insertword(token, e.email_id);
        }
    }

    // Count common words between email pairs
    unordered_map<int, unordered_map<int,int>> commonCount;
    clusterFromTrie(trie.getroot(), commonCount);

    // Step 3: Apply threshold
    const int THRESHOLD = 5; 
    for (auto &[id1, mp] : commonCount) {
        for (auto &[id2, cnt] : mp) {
            if (cnt >= THRESHOLD) {
                dsu.unionbyRank(id1, id2);
            }
        }
    }

    //  Build clusters
    unordered_map<int, vector<int>> clusters;
    for (auto &e : allEmails) {
        int root = dsu.findUPar(e.email_id);
        clusters[root].push_back(e.email_id);
    }

    cout << "\nEmail Clusters:\n";
    for (auto &[root, members] : clusters) {
       cout << "Cluster -> ";
        for (int id : members) cout << id << " ";
        cout << "\n";
    }
    cout << "\n";
}


void Cluster::clusterFromTrie(TrieNode *node, unordered_map<int, unordered_map<int,int>> &commonCount) {
    if (!node) return;

    auto &ids = node->emailids;
    if (ids.size() > 1) {
        for (size_t i = 0; i < ids.size(); i++) {
            for (size_t j = i+1; j < ids.size(); j++) {
                commonCount[ids[i]][ids[j]]++;
                commonCount[ids[j]][ids[i]]++;
            }
        }
    }

    for (auto &p : node->next) {
        clusterFromTrie(p.second, commonCount);
    }
}
