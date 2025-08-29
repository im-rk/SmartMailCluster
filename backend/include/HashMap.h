#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
using namespace std;

struct Email {
    int email_id;
    int from;
    int to;
    int thread_id;
    string subject;
    string body;
};

class HashMap {
private:
    static const int SIZE = 100;
    static const int PRIME = 97;

    Email table[SIZE];
    bool occupied[SIZE];

    int Hash(int key);
    int PrimeHash(int key);
    int DoubleHash(int key, int attempt);

public:
    HashMap();

    void insert(Email email);
    Email* search(int email_id);
    void remove(int email_id);
    void printAll();

    // Public getters for private members
    int getSize() const { return SIZE; }
    bool isOccupied(int index) const { return occupied[index]; }
    void setOccupied(int index, bool value) { occupied[index] = value; }
    Email* getTable() { return table; } 
};

#endif
