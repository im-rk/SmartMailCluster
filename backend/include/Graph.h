#ifndef GRAPH_H
#define GRAPH_H

#include<bits/stdc++.h>
using namespace std;

class Graph{
    private:
    vector<vector<int>> adj;
    int numEmails;

    public:
    Graph(int n);
    void addEdge(int fromEmail,int toEmail);
    vector<int> getNeighbours(int emialId);

};

#endif