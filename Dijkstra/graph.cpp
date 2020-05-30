#include <stdio.h>
#include "heap.h"
#include "hash.h"
#include "graph.h"
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;
//constructor
graph::graph(){
    vertices = new hashTable(1000000);
    capacity = 0;
}

bool graph::inputGraph(ifstream &input){
    int distance;
    string v1, v2;
    while (input >> v1 >> v2 >> distance){
        insert(v1, v2, distance);
    }
    return true;
}

void graph::printGraph(ofstream &out){
    for(list<vertex *>::const_iterator it = vertexList.begin(),end= vertexList.end(); it!= end; ++it){
        out << (*it)->name << ":";
        if ((*it)->distance == INT_MAX){
            out << "NO PATH" << endl;
        }
        else {
            out << (*it) ->distance << "  [";
            for (list<string>::const_iterator i = (*it) ->path.begin(), e = (*it) ->path.end(); i!= e; ++i){
                out << *i;
                if (next(i,1)!= e){
                    out << ",";
                }
            }
            out << "]" << endl;
        }
    }
}

void graph::insert( const string &v1, const string &v2, int distance){
    edge newEdge;
    vertex *temp1;
    vertex *temp2;
    
    if (!vertices -> contains(v1)){
        temp1 = new vertex;
        temp1 -> name = v1;
        temp1 -> known = false;
        temp1 -> distance = INT_MAX;
        vertexList.push_back(temp1);
        vertices -> insert(v1, temp1);
        capacity ++;
    }
    else {
        temp1 = (vertex*)vertices -> getPointer(v1);
    }
    if (!vertices -> contains(v2)){
             temp2 = new vertex;
              temp2 -> name = v2;
              temp2 -> known = false;
              temp2 -> distance = INT_MAX;
                vertexList.push_back(temp2);
                vertices -> insert(v2, temp2);
                capacity ++;
    }
    else {
        temp2 = (vertex *)vertices -> getPointer(v2);
    }
    newEdge.destination = temp2;
    newEdge.cost = distance;

    temp1 -> adjacent.push_back(newEdge);
}

bool graph::dijkstra(const string &startV){
    vertex *start = (vertex *)vertices -> getPointer(startV);
    start -> distance = 0;
    start -> path.push_back(startV);
    heap disHeap(capacity);
    //insert the starting vert into the heap
    disHeap.insert(startV, start->distance, start);
    for (list<vertex*>::const_iterator it = vertexList.begin(), end = vertexList.end();
         it != end; ++it){
        if ((*it)-> name != startV){
            disHeap.insert((*it)->name, (*it)->distance, *it);
        }
    }
    vertex *temporary;
    for (int i = 0; i < capacity; ++i){
        disHeap.deleteMin(nullptr, nullptr, &temporary);
        for (list<edge>::const_iterator it = temporary->adjacent.begin(), end = temporary->adjacent.end(); it != end && temporary->distance != INT_MAX; ++it){
            if (!it -> destination->known && it->destination->distance > (it ->cost + temporary -> distance)){
                it ->destination->path.clear();
                it->destination->path.insert(it->destination->path.begin(), temporary->path.begin(), temporary->path.end());
                it->destination->path.push_back(it->destination->name);
                it->destination->distance = it->cost + temporary ->distance;
                disHeap.setKey(it->destination->name, (it->cost + temporary->distance));
            }
        }
        temporary-> known = true;
    }
    return true;
}

bool graph::isVertex(const string &v){
    return (vertices -> contains(v));
}
