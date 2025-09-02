#include "Cluster.h"

void Cluster::clusterEmails(Graph &graph) {
    auto allEmails = graph.getEmailStore().getAllEmails();
    if (allEmails.empty()) {
        cout << "No emails to cluster.\n";
        return;
    }

    Preprocessor preproc;
    Trie trie;
    DisjointSet dsu(10000); // assume max 10k emails for now

    for (auto &e : allEmails) {
        string content = e.subject + " " + e.body;
        auto tokens = preproc.preprocessEmail(content);

        for (auto &token : tokens) {
            trie.insertword(token, e.email_id);
        }
    }

    clusterFromTrie(trie.getroot(), dsu);

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

void Cluster::clusterFromTrie(TrieNode *node, DisjointSet &dsu) {
    if (!node) return;

    if (node->emailids.size() > 1) {
        int first = node->emailids[0];
        if(dsu.findUPar(first)==first)
        {
            for (size_t i = 1; i < node->emailids.size(); i++) {
                if(node->emailids[i]==dsu.findUPar(node->emailids[i]))
                {
                    dsu.unionbyRank(first, node->emailids[i]);
                }
            }
        }
    }

    // Recurse for children
    for (auto &p : node->next) {
        clusterFromTrie(p.second, dsu);
    }
}
