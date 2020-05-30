//
//  heap.cpp
//  heap
//
//  Created by Crystal Wang on 10/19/19.
//  Copyright © 2019 Crystal Wang. All rights reserved.
//

#include <stdio.h>
#include<iostream>
#include "heap.h"
#include<string.h>
using namespace std;

heap::heap(int capacity){
    data.resize(capacity + 1);
    mapping = new hashTable(capacity * 2);
    this -> capacity = capacity;
    size = 0;
    //initializing the chart
}

int heap::insert(const std::string &id, int key,void *pv){
    if (size == capacity - 1){
        return 1;
    }
    if (mapping ->contains(id) == false){
        size++;
        data[size].id = id;
        data[size].key = key;
        data[size].pData = pv;
        mapping ->insert(id, &data[size]);
        percolateUp(size);
    }
    else{
        return 2;
    }
    return 0;
}

int heap::deleteMin(const std::string *pId, int *pKey, void *pData){
    if(size == 0){
        return 1;
    }
    mapping -> remove(data[1].id);
    if(pId != NULL)
        pId = &data[1].id;
    if(pKey != NULL){
        *pKey = data[1].key;
    }
    if(pData != NULL){
        *(static_cast<void **>(pData)) = data[1].pData;
    }
    data[1] = data[size --];
    percolateDown(1);
    return 0;
}

int heap::remove(const std:: string &id, int *pKey, void *pData){
    if(mapping -> contains(id) == false){
        return 1;
    }
    node *pn = static_cast<node *>(mapping->getPointer(id));
    if(pKey != NULL){
        *pKey = pn -> key;
    }
    if(pData != NULL)
    {
        *(static_cast<void **>(pData)) = pn ->pData;
    }
    setKey(id,INT_MIN);
    deleteMin();
    return 0;
}

int heap::setKey(const std::string &id, int key){
    if(mapping -> contains(id) == false){
        return 1;
    }
    node *pn = static_cast<node *>(mapping ->getPointer(id));
    int cur = getPos(pn);
    pn->key = key;
    int pre = pn -> key;
    if (key > pre){
        percolateDown(cur);
    }
    else if (key < pre){
        percolateUp(cur);
    }
    return 0;
}

void heap::percolateUp(int posCur){
    node inserted = data[posCur];
    for(; inserted.key < data[posCur/2].key && posCur >1; posCur = posCur/2){
        data[posCur] = data[posCur/2];
        mapping ->setPointer(data[posCur].id, &data[posCur]);
    }
    data[posCur] = inserted;
    mapping ->setPointer(data[posCur].id, &data[posCur]);
    
}

void heap::percolateDown(int posCur){
    node removed = data[posCur];
    int child;
    for(; posCur *2 <= size; posCur = child){
        child = posCur *2;
        if(child != size && data[child+1].key < data[child].key){
            child ++;
        }
        if (data[child].key < removed.key){
            data[posCur] = data[child];
            mapping -> setPointer(data[posCur].id, &data[posCur]);
        }
        else {
            break;
        }
    }
    data[posCur] = removed;
    mapping -> setPointer(data[posCur].id, &data[posCur]);
}

int heap:: getPos(node *pn){
    return (pn - &data[0]);
}

void heap:: printHeap(){
    cout << "Start:";
    for (int i = 1; i <= size; i++){
        cout << i<<":"<<data[i].id << "  &  " << data[i].key<< "\n";
    }
    cout << "End"<<endl;
}

