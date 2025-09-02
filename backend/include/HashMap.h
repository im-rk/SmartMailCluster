#ifndef HASHMAP_H
#define HASHMAP_H
#include<bits/stdc++.h>
#include <string>
using namespace std;

struct Email {
    int email_id;
    int from;
    int to;
    int thread_id;
    string subject;
    string body;
    int parent_id;
};

class HashMap {
private:
    int capacity ;
    int usercount;
    int emailcount;
    const double loadfactor=0.7;
    static const int PRIME = 97;

    vector<Email> table;
    vector<bool> occupied;
    vector<string> tableuser;    // user-email storage
    vector<bool> occupieduser;

    int Hash(int key);
    int PrimeHash(int key);
    int DoubleHash(int key, int attempt);

public:
    HashMap(int initialSize=100);

    void insert(Email email);
    Email* search(int email_id);
    void userinsert(int id, string emailadd);
    string usersearch(int email_id);
    void remove(int email_id);
    void printAll();

    void rehash();

    int getcapacity() const {return capacity;};
    int getusercount() const {return usercount;};
    int getemailcount() const {return emailcount;};
    vector<Email> getAllEmails();
    // Public getters for private members
    // int getSize() const { return SIZE; }
    // bool isOccupied(int index) const { return occupied[index]; }
    // void setOccupied(int index, bool value) { occupied[index] = value; }
    // Email* getTable() { return table; } 

};

#endif
