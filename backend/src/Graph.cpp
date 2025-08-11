#include "Graph.h"
#include<bits/stdc++.h>
using namespace std;

Graph::Graph(int n)
{
    numEmails=n;
    adj.resize(n);
}

void Graph::addEdge(int fromEmail,int toEmail)
{
    adj[fromEmail].push_back(toEmail);
}

vector<int> Graph::getNeighbours(int EmailId)
{
    return adj[EmailId];
}