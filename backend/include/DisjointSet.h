#ifndef DISJOINTSET_H
#define DISJOINTSET_H
#include<bits/stdc++.h>
using namespace std;
class DisjointSet{
    private:
    vector<int> parent;
    vector<int> rank;
    vector<int> size;
    int n;

    public:
    DisjointSet(int size);

    int findUPar(int x);
    void unionbyRank(int u,int v);
    void unionbySize(int u,int v);
};

#endif
