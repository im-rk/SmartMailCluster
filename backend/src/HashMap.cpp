#include "../include/HashMap.h"
#include <iostream>
using namespace std;

HashMap::HashMap()
{
    for(int i=0;i<SIZE;i++)
    {
        occupied[i]=false;
    }
}

int HashMap::Hash(int key)
{
    return key%SIZE;
}

int HashMap::PrimeHash(int key)
{
    return PRIME-(key%PRIME);
}

int HashMap::DoubleHash(int key,int attempt)
{
    return (Hash(key)+attempt*PrimeHash(key))%SIZE;
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
            return ;
        }
        i++;
    }
    while(i<SIZE);
    cout<<"Hash table full! could not insert email.\n";
}

Email * HashMap::search(int email_id)
{
    int i=0;
    int idx;
    while(i<SIZE)
    {
        idx=DoubleHash(email_id,i);
        if(!occupied[idx]) return nullptr;
        if(table[idx].email_id==email_id) return &table[idx];
        i++;
    }
    return nullptr;
}

