//
//  hash.cpp
//  Hashtable
//
//  Created by Crystal Wang on 9/22/19.
//  Copyright © 2019 Crystal Wang. All rights reserved.
//

#include <stdio.h>
#include "hash.h"

using namespace std;

int primos[] ={17,10003,20003,400009,800011,1600033,320003,6400013};
unsigned int hashTable:: getPrime(int size){
    unsigned int prime = 0;
    int limit = sizeof(primos)/sizeof(int);
    for (int i = 0; i < limit; i++){
        if(primos[i] >=(2 *size) ){
            prime = primos[i];
            break;
        }
    }
    return prime;
}

hashTable::hashTable(int size){
    //for null
    capacity = getPrime(size);
    filled = 0;
    //entries
    data.resize(capacity);
    for(int i=0; i < data.size(); i++){
        data[i].isDeleted = false;
        data[i].isOccupied = false;
    }
}


int hashTable::insert(const std::string &key, void *pv){
   //insert function part and also detects whether the hashtable is too small.
    int detect = 0;
    if((filled *2) >= capacity){
        detect = rehash();
    }
    if (detect == 2){
        return 2;
    }
    int pos = hash(key);
    if(contains(key) == true){
        return 1;
    }
    
    while (data[pos].isOccupied == true){
        pos = pos + 1;
        if (pos == capacity){
            pos = 0;
        }
    }
    filled++;
    data[pos].isDeleted = false;
    data[pos].isOccupied = true;
    data[pos].key = key;
    data[pos].pv = pv;
    
    return 0;
}

bool hashTable:: contains(const string &key){
    //to check if the value already exsits in the hashtable
    if (findPos(key) > 0){
        return true;
    }
    else {
        return false;
    }
}

int hashTable::findPos(const std:: string &key){
     //find the posision of a value
    int pos = hash(key);
    while(data[pos].isOccupied == true){
        if(data[pos].key == key){
            return pos;
        }
        else{
            pos++;
            if (pos == capacity){
                pos = 0;
            }
        }
        
 }
    return -1;
}


int hashTable:: hash(const string &key){
    //the hashing funciton part
    unsigned int hash = 0, length = key.length();
    for (int i = 0; i< length; i++){
        hash = key[i] + (hash << 6) + (hash << 16) - hash;
    }
    return hash % capacity;
    //source from : http://www.cse.yorku.ca/~oz/hash.html, it was created for sbdm
}


bool hashTable::rehash(){
    /*using linear probing for rehashing, trnasfer old data to a temp hashtable, then resize and expand the current hashtable, and move the old data back to the new hashtable */
    vector<hashItem> old = data;
    int newSize = getPrime(capacity);
    try
    {
        data.resize(newSize);
    }
    catch (const bad_alloc)
    {
        return 2;
    }
    filled = 0;
    capacity = newSize;
    for (int i = 0; i < data.size(); i++)
    {
        data[i].key = "";
        data[i].isOccupied = false;
        data[i].isDeleted = false;
    }

    for (int i = 0; i < old.size(); i++)
    {
        hashItem oldPtr = old[i];
        if (oldPtr.isOccupied && !oldPtr.isDeleted)
        {
            insert(oldPtr.key, oldPtr.pv);
        }
    }
    return 1;
}

 


