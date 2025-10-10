#include "DisjointSet.h"
#include<bits/stdc++.h>
using namespace std;

DisjointSet::DisjointSet(int n)
{
    parent.resize(n+1);
    rank.resize(n+1,0);
    //size.resize(n+1);
    for(int i=0;i<=n;i++)
    {
        parent[i]=i;
    }
}

int DisjointSet::findUPar(int node)
{
    if(node==parent[node])
    {
        return node;
    }
    return parent[node]=findUPar(parent[node]);
}

void DisjointSet::unionbyRank(int u,int v)
{
    int ulp_u=findUPar(u);
    int ulp_v=findUPar(v);
    if(ulp_u==ulp_v)
    {
        return;
    }
    if(rank[ulp_u]<rank[ulp_v])
    {
        parent[ulp_u]=ulp_v;
    }
    else if(rank[ulp_v]<rank[ulp_u])
    {
        parent[ulp_v]=ulp_u;
    }
    else
    {
        parent[ulp_v]=ulp_u;
        rank[ulp_u]++;
    }
}

// void DisjointSet::unionbySize(int u,int v)
// {
//     int ulp_u=findUPar(u);
//     int ulp_v=findUPar(v);
//     if(ulp_u==ulp_v)
//     {
//         return ;
//     }
//     if(size[ulp_u]<size[ulp_v])
//     {
//         parent[ulp_u]=ulp_v;
//         size[ulp_v]+=size[ulp_u];
//     }
//     else
//     {
//         parent[ulp_v]=ulp_u;
//         size[ulp_u]+=size[ulp_v];
//     }
// }

