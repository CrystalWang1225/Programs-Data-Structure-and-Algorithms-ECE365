#ifndef graph_h
#define graph_h

#include "heap.h"
#include "hash.h"
#include <fstream>
#include <list>
#include <string>

using namespace std;

class graph{
public:
    graph();
    bool isVertex(const string &);
    bool dijkstra(const string &);
    bool inputGraph(ifstream &);
    void insert(const string &, const string &, int);
    void printGraph(ofstream &);
    class edge;
    class vertex;
    int capacity;
    list<vertex *> vertexList;
    hashTable *vertices;
    class edge{
    public:
        int cost;
        vertex *destination;
    };
    class vertex{
    public:
        string name;
        list<edge> adjacent;
        // for dijkstras algorithm parameters
        bool known;
        int distance;
        list<string> path;
    };
};
#endif /* graph_h */
