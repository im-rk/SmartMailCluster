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

void Graph::BFS(int startEmail)
{
    vector<bool> visited(numEmails,false);
    queue<int> q;
    visited[startEmail]=false;
    q.push(startEmail);

    while(!q.empty())
    {
        int email=q.front();
        q.pop();
        cout<<email<<" ";

        for(auto x:adj[email])
        {
            if (!visited[x])
            {
                q.push(x);
                visited[x]=true;
            }
        }
    }
    cout<<"\n";
}

void Graph::DFS(int startEmail)
{
    vector<bool> visited(numEmails, false);

    function<void(int)> DFSHELPER = [&](int email) {
        visited[email] = true;
        cout << email << " ";

        for (auto x : adj[email]) {
            if (!visited[x]) {
                DFSHELPER(x);
            }
        }
    };

    DFSHELPER(startEmail);
    cout << "\n";
}
