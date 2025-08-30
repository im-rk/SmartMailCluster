#include "../include/HashMap.h"
#include <bits/stdc++.h>
using namespace std;

HashMap::HashMap(int initialSize) {
    capacity = initialSize;
    usercount = 0;
    emailcount = 0;
    table.assign(capacity, Email());
    occupied.assign(capacity, false);
    tableuser.assign(capacity, "");
    occupieduser.assign(capacity, false);
}

void HashMap::rehash() {
    int oldCapacity = capacity;
    capacity *= 2;  // double the table size
    vector<Email> oldTable = table;
    vector<bool> oldOccupied = occupied;
    vector<string> oldTableUser = tableuser;
    vector<bool> oldOccupiedUser = occupieduser;

    // reset new bigger arrays
    table.assign(capacity, Email());
    occupied.assign(capacity, false);
    tableuser.assign(capacity, "");
    occupieduser.assign(capacity, false);
    emailcount = 0;
    usercount=0;                                              // this for rehashing the tableuser too....
    // reinsert emails
    for (int i = 0; i < oldCapacity; i++) {
        if (oldOccupied[i]) {
            insert(oldTable[i]);
        }
    }
    // reinsert users
    for (int i = 0; i < oldCapacity; i++) {
        if (oldOccupiedUser[i]) {
            userinsert(i, oldTableUser[i]);
        }
    }
}


int HashMap::Hash(int key)
{
    return key%capacity;
}

int HashMap::PrimeHash(int key)
{
    return PRIME-(key%PRIME);
}

int HashMap::DoubleHash(int key,int attempt)
{
    return (Hash(key)+attempt*PrimeHash(key))%capacity;
}

void HashMap::insert(Email email)
{
    int i=0;
    int idx;
    do{
        idx=DoubleHash(email.email_id,i);
        if(!occupied[idx])
        {
            table[idx]=email;
            occupied[idx]=true;
            emailcount++;
            return ;
        }
        i++;
    }
    while(i<capacity);
    cout<<"Hash table full! could not insert email.\n";
}

void HashMap::userinsert(int id, string emailadd)
{
    int i=0;
    int idx;
    do{
        idx=DoubleHash(id,i);
        if(!occupieduser[idx])
        {
            tableuser[idx]=emailadd;
            occupieduser[idx]=true;
            usercount++;
            return ;
        }
        i++;
    }while(i<capacity);
    cout<<"Hash table full! could not insert emailaddress.\n";
}

Email * HashMap::search(int email_id)
{
    int i=0;
    int idx;
    while(i<capacity)
    {
        idx=DoubleHash(email_id,i);
        if(!occupied[idx]) return nullptr;
        if(table[idx].email_id==email_id) return &table[idx];
        i++;
    }
    return nullptr;
}


string HashMap::usersearch(int email_id)
{
    int i=0;
    int idx;
    while(i<capacity)
    {
        idx=DoubleHash(email_id,i);
        if(!occupieduser[idx]) return "";
        else
        {
            return tableuser[idx];
        }
        i++;
    }
    return nullptr;
}

