
#ifndef heap_h
#define heap_h

#include "hash.h"
using namespace std;
#include<string>
#include<vector>


class heap{
public:
    //maximum number of items capacity
    heap(int capacity);
    int insert(const std::string &id, int key,void *pt = NULL);
    int deleteMin(const std::string *pId = NULL, int *pKey = NULL, void *pData = NULL);
    int remove(const std:: string &id, int *pKey = NULL, void *pData = NULL);
    int setKey(const std::string &id, int key);
    void printHeap();
private:
    class node { // An inner class within heap
    public:
      std::string id; // The id of this node
      int key; // The key of this node
      void *pData; // A pointer to the actual data
    };
    std::vector<node> data; // The actual binary heap
    hashTable *mapping; // maps ids to node pointers
    int capacity, size;
    void percolateUp(int posCur);
    void percolateDown(int posCur);
    int getPos(node *pn);

};


#endif /* heap_h */

