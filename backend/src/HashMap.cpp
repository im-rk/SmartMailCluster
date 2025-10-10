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
    tableuserid.assign(capacity, -1);
    PRIME=getLargestPrimeBelow(capacity);
}

void HashMap::rehash() {
    int oldCapacity = capacity;

    // backup old data
    vector<Email> oldTable = table;
    vector<bool> oldOccupied = occupied;
    vector<string> oldTableUser = tableuser;
    vector<bool> oldOccupiedUser = occupieduser;
    vector<int> oldTableUserId = tableuserid;

    // double the capacity
    capacity *= 2;

    // allocate new larger tables
    table.assign(capacity, Email());
    occupied.assign(capacity, false);
    tableuser.assign(capacity, "");
    occupieduser.assign(capacity, false);
    tableuserid.assign(capacity, -1);

    // reset counts
    emailcount = 0;
    usercount = 0;
    PRIME=getLargestPrimeBelow(capacity);

    // reinsert all emails
    for (int i = 0; i < oldCapacity; i++) {
        if (oldOccupied[i]) {
            insert(oldTable[i]);
        }
    }

    // reinsert all user entries
    for (int i = 0; i < oldCapacity; i++) {
        if (oldOccupiedUser[i]) {
            userinsert(oldTableUserId[i], oldTableUser[i]);
        }
    }
    cout << "Rehash complete. New capacity = " << capacity << endl;
}

int HashMap::getLargestPrimeBelow(int n) {
    auto isPrime = [](int x) {
        if (x < 2) return false;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) return false;
        }
        return true;
    };

    for (int i = n - 1; i >= 2; i--) {
        if (isPrime(i)) return i;
    }
    return 2; 
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
    if ((double)emailcount / capacity > loadfactor) rehash();
    int i=0;
    int idx;
    do{
        idx=DoubleHash(email.email_id,i);
        if(!occupied[idx])
        {
            table[idx]=email;
            occupied[idx]=true;
            emailcount++;
            //for(auto x:table){cout<<x.email_id<<"------";}
            return ;
        }
        i++;
    }
    while(i<capacity);
    // for(auto x:table)
    // {
    //     cout<<x.email_id<<"--";
    // }
    cout<<"Hash table full! could not insert email.\n";
}

void HashMap::userinsert(int id, string emailadd)
{
    if ((double)usercount / capacity > loadfactor) rehash();
    int i=0;
    int idx;
    do{
        idx=DoubleHash(id,i);
        if(!occupieduser[idx])
        {
            tableuser[idx]=emailadd;
            tableuserid[idx]=id;
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
        if(tableuserid[idx]==email_id) return tableuser[idx];
        i++;
    }
    return "";
}

vector<Email> HashMap::getAllEmails() {
    vector<Email> emails;
    for (int i = 0; i < capacity; i++) {
        if (occupied[i]) {
            emails.push_back(table[i]);
        }
    }
    return emails;
}
