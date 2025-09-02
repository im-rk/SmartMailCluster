#include "Graph.h"
#include<bits/stdc++.h>
using namespace std;



Graph::Graph(int n)
{
    numUsers=n;
    adjList.resize(n+1);
    adjMatrix.resize(n+1,vector<int> (n+1,0));
    threadGraph.resize(1000);
    nextEmailId=0;
    nextThreadId=100;
}

int Graph::getNextThreadId()
{
    return nextThreadId++;
}

void Graph::addUserAddress(int id,string email)
{
    emailStore.userinsert(id,email);
}

void Graph::addEdge(int fromEmail,int toEmail,int thread_id)    
{
    bool found=false;
    for(auto &edge: adjList[fromEmail])
    {
        if (edge.to==toEmail)
        {
            edge.weight++;
            found=true;
            break;
        }
    }
    if(!found)
    {
        adjList[fromEmail].push_back({toEmail,1,thread_id});
    }
    adjMatrix[fromEmail][toEmail]+=1;
    
}

void Graph::sendEmail(int from,int to,string subject, string body)
{
    int threadId=getNextThreadId();
    addEdge(from,to,threadId);
    Email newEmail = {nextEmailId++, from, to, threadId, subject, body,-1};
    emailStore.insert(newEmail);
    cout<< "Email sent "
            << " | From: " << from
            << " | To: " << to
            << " | Subject: " << subject
            << " | EmailId: " << newEmail.email_id
            << "\n";
    cout<<"\n";
}

void Graph::replyEmail(int email_id, int from, int to, string body)
{
    Email* original = emailStore.search(email_id);
    if (!original) {
        cout << "Error: Email ID " << email_id << " not found.\n";
        cout<<"\n";
        return;
    }

    if (from != original->from && from != original->to) {
        cout << "Error: User " << from << " is not allowed to reply to Email ID " << email_id << ".\n";
        cout<<"\n";
        return;
    }

    addEdge(from, to, original->thread_id);

    string reply_subject = "RE: " + original->subject;
    Email reply = {nextEmailId++, from, to, original->thread_id, reply_subject, body,email_id};
    emailStore.insert(reply);
    threadGraph[original->email_id].push_back({reply.email_id,"reply"});
    cout << "Reply sent to Email ID " << email_id
            << " | From: " << from
            << " | To: " << to
            << " | Subject: " << body
            <<"|Email id:"<<reply.email_id
            << "\n";
    cout<<"\n";
}


void Graph::forwardEmail(int email_id,int from,int to,string body)
{
    Email* original = emailStore.search(email_id);  
    if (!original) {
        cout << "Error: Email ID " << email_id << " not found.\n";
        cout<<"\n";
        return;
    }

    if (from != original->from && from != original->to) {
        cout << "Error: User " << from << " is not allowed to forward Email ID " << email_id << ".\n";
        cout<<"\n";
        return;
    }

    addEdge(from, to, original->thread_id);

    string fwd_sub = "FWD: " + original->subject;
    string finalbody;
    if(body.empty())
    {
        finalbody=original->body;
    }
    else
    {
        finalbody=body+original->body;
    }
    Email fwd = {nextEmailId++, from, to, original->thread_id, fwd_sub, finalbody,email_id};
    emailStore.insert(fwd);
    threadGraph[original->email_id].push_back({fwd.email_id,"forward"});
    cout << "Email forwarded from Email ID " << email_id
            << " | From: " << from
            << " | To: " << to
            << " | Subject: " << body
            <<"|Email id:"<< fwd.email_id
            << "\n";;
    cout<<"\n";
}


void Graph::viewThread(int rootEmailId) {
    cout << "Viewing thread starting from Email ID " << rootEmailId << ":\n";
    Email *e=emailStore.search(rootEmailId);

    int rootid=rootEmailId;
    while(e && e->parent_id!=-1)
    {
        rootid=e->parent_id;
        e=emailStore.search(rootid);
    }

    queue<int> q;
    unordered_set<int> visited;

    q.push(rootid);
    visited.insert(rootid);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        Email *e = emailStore.search(curr);
        cout << "Email ID: " << e->email_id
             << " From: " << e->from
             << " To: " << e->to
             << " Subject: " << e->subject
             << " Body: " << e->body << "\n";

        for (auto &edge : threadGraph[curr]) {
            if (!visited.count(edge.toEmailId)) {
                q.push(edge.toEmailId);
                visited.insert(edge.toEmailId);
            }
        }
    }
    cout << "\n";
}


// void Graph::BFS(int startEmail)
// {
//     vector<bool> visited(numUsers,false);
//     queue<int> q;
//     visited[startEmail]=false;
//     q.push(startEmail);

//     while(!q.empty())
//     {
//         int email=q.front();
//         q.pop();
//         cout<<email<<" ";

//         for(auto x:adjList[email])
//         {
//             if (!visited[x])
//             {
//                 q.push(x);
//                 visited[x]=true;
//             }
//         }
//     }
//     cout<<"\n";
// }

// void Graph::DFS(int startEmail)
// {
//     vector<bool> visited(numUsers, false);

//     function<void(int)> DFSHELPER = [&](int email) {
//         visited[email] = true;
//         cout << email << " ";

//         for (auto x : adjList[email]) {
//             if (!visited[x]) {
//                 DFSHELPER(x);
//             }
//         }
//     };

//     DFSHELPER(startEmail);
//     cout << "\n";
// }

// void Graph::printAdjMatrix()
// {
//     for (int i = 0; i < numUsers; i++)
//     {
//         for (int j = 0; j < numUsers; j++)
//         {
//             cout << adjMatrix[i][j] << " ";
//         }
//         cout << "\n";
//     }
// }
