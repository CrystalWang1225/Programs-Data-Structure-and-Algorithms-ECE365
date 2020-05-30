//
//  main.cpp
//  Hashtable
//
//  Created by Crystal Wang on 9/22/19.
//  Copyright © 2019 Crystal Wang. All rights reserved.
//

#include <iostream>
#include "hash.h"
#include<string>
#include<string.h>
#include<fstream>
#include<ctime>
using namespace std;

int main() {
    string dicFile;
    hashTable *dicHash = new hashTable(50000);
    cout << "Please enter the name of the dictionary: ";
    cin >> dicFile;
    ifstream input, dictionary;
    clock_t begin = clock();
    dictionary.open(dicFile);
    string line;
    if (dictionary.fail()){
        cout << "failed to open the dictionary"<< endl;
    }
    else if (!dictionary.fail()){
        while(getline(dictionary,line)){
            // converting all upper cases to lower once open
            for(int i = 0; i <= line.length(); i++){
                line[i] = tolower(line[i]);
            }
            dicHash -> insert(line, NULL);
        }
        dictionary.close();
    }
    clock_t end = clock();
    cout << "Total time (in seconds)  to load dictionary : " << ((double)(end-begin))/CLOCKS_PER_SEC << endl;
    
    string inFile,outFile;
    cout<< "Enter name of input file: ";
    cin >> inFile;

    cout<< "Enter name of output file: ";
    cin >> outFile;
    begin = clock();
    input.open(inFile);
    if (input.fail()){
        cout << "failed to open input file" << endl;
    }
    ofstream output;
    output.open(outFile);
    if(output.fail()){
        cout << "failed to open the output file" << endl;
    }
    unsigned long pos = 0;
    char content ;
    string word;
    bool ignore;
    while(getline(input, line)){

        pos ++;
        for (int j = 0; j <= line.length(); j++){
            //converting everything to lower case
            content = tolower(line[j]);
            if (isalnum(content) == true || (content == 45) || (content == 39)){
                //if the char is a decminal digit or "-" or a uppercase or a lower case character or "'" after taking diff for the sample output with my own output
                word += content;
                if(isdigit(content) == true){
                    ignore = true;
                    //if its a number then ignore
                }
            }
            else if ((word.length() > 0) && (ignore == false)){

                    if(word.length() > 20){
                        output << "Long word at line " << pos << "starts " << word.substr(0,20) << endl;
                    }
                   else if (!dicHash -> contains(word)){
                       output << "Unknown word at line" << pos << ":" << word << endl;
                    }
                    word = "";
                }
                   else {
                       ignore = false;
                       word = "";
                   }
                }
        }
    input.close();
    output.close();
    end = clock();
    
    cout << "Total time (in seconds) to check document: " << ((double)(end - begin))/CLOCKS_PER_SEC << endl;
    return 0;
}

   
