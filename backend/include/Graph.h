#ifndef GRAPH_H
#define GRAPH_H
#include "HashMap.h"
#include<bits/stdc++.h>
using namespace std;

struct EmailEdge{
    int to;
    int weight ;
    int thread_id;
};

struct ThreadEdge{
    int toEmailId;
    string relation;
};


class Graph{
    private:
    vector<vector<EmailEdge>> adjList;
    vector<vector<int>> adjMatrix;
    vector<vector<ThreadEdge>> threadGraph;
    HashMap emailStore;
    int numUsers;
    int nextEmailId;
    int nextThreadId;

    public:
    Graph(int n);
    void addEdge(int fromEmail,int toEmail,int threadId);

    void sendEmail(int from ,int to ,string subject, string body);
    void replyEmail(int email_id,int from,int to,string body);
    void forwardEmail(int email_id,int from,int to,string body);
    void viewThread(int email_id);

    int getNextThreadId();
};

#endif