#include <iostream>
#include "heap.h"
#include "hash.h"
#include <string>
#include <fstream>
#include "graph.h"
#include <algorithm>
#include<chrono>

using namespace std;
int main(int argc, const char * argv[]) {
    string inFile, outFile;
    ifstream input;
    ofstream output;
    graph dij;
    string startV;
    while (!input.is_open()){
        cout << "Enter a valid graph input file : ";
        cin >> inFile;
        input.open(inFile, ifstream::in);
    }
    
    dij.inputGraph(input);
    input.close();
    while(!dij.isVertex(startV)){
        cout << "Enter a valid start vertex : ";
        cin >> startV;
    }
    clock_t begin = clock();
    dij.dijkstra(startV);
    clock_t end = clock();
    float runtime = (float(end - begin))/CLOCKS_PER_SEC;
    cout << "Total Time (in seconds) to apply Dijkstra algorithm :" << runtime << endl;
    while(!output.is_open()){
        cout << "Enter an output file :";
        cin >> outFile;
        output.open(outFile, ofstream::out | ofstream::trunc);
    }
    
    dij.printGraph(output);
    output.close();
    return 0;
}
