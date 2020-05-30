//
//  main.cpp
//  Project1
///Users/crystalwang/Documents/Xcode/Project1/Project1
//  Created by Crystal Yuecen Wang on 3/27/19.
//  Copyright © 2019 Crystal Wang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
using namespace std;

vector<string> split(string line){ //the vector<string>function splits the string word by word
    string del = " ";
    vector<string> thisline;//create a vector that stores words in each line
    size_t pos = 0;
    string sub;
    while ((pos = line.find(del)) != string::npos)//if it reaches the end of each line, stop
    {
        sub = line.substr(0, pos);
        thisline.push_back(sub);
        line.erase(0, pos + del.length());
    }
    thisline.push_back(line);
    return thisline;
}

// a base class of simpleList
template <typename T> // using template so that base class and derived class can only be written once
class SimpleList{
private:
    string name;
    T input;
    class Node  //a nested class which contains one field for data and another to point to the next node
    {
        Node* next;
    public:
        T* data;
        Node(){ // constructor of the node
            data = nullptr;
            next = nullptr;
        }
        void changeNext(Node* next){ // change the next node
            this->next = next;
        }
        void changeData(T* data){// change the value of the node
            this->data = data;
        }
        Node* getNext(){// get the next node
            return this->next;
        }
        T* getData(){
            return data;
        }
    };
protected:
    Node* head;
    Node* end;
    SimpleList(string name){ //constructor
        this->head = nullptr;
        this->end = head;
        this->name = name;
    }
    virtual void startInsert(T* input){
        // start insert node in front of the current head node
        Node* dummy = new Node();
        dummy->changeData(input);
        dummy->changeNext(head);
        head = dummy;
    }
    virtual void endInsert(T* input){
        //insert node at the end of the linkedlist
        if (end != nullptr){
        Node* trailer = new Node();
        end-> changeNext(trailer);
        trailer-> changeData(input);
        end = trailer;
        }
        else { // check if the list is empty
            end = new Node;
            end->changeNext(nullptr);
            end->changeData(input);
            head = end;
        }
    }
    virtual T* remove(){
        if(head == nullptr){ // check if the list is empty, return a null pointer
            return nullptr;
        }
        else {
        Node* dummy;
        dummy = head; //use dummy node to store th calue of the head
        head = head->getNext();
        return dummy->getData();
        }
    }
public:
    string getName(){
        return this->name;
    }
    virtual void push(T* data) = 0; // pure virtual function
    virtual T* pop() = 0;
    ~SimpleList();//destructor
};

template <typename T>
class Stack : public SimpleList<T>{ // derived class Stack
public:
    Stack(string name) : SimpleList<T>(name) // define the constructor of stack as the constructor of the simpleList
    {
    }
    void push(T* data){
        SimpleList<T>::startInsert(data);
    }
    T* pop(){
        return SimpleList<T>::remove();
    }
};

template <typename T>
class Queue : public SimpleList<T>{
public:
    Queue(string name) : SimpleList<T>(name){
    }
    // define the constructor of queue as the constructor of the simpleList
    void push(T* data){
        SimpleList<T>::endInsert(data);
    }
    T* pop(){
        return SimpleList<T>::remove();
    }
};

// a search function that searches if the specifeid stacks or queues
template<typename T>
SimpleList<T>* search(string name, list<SimpleList<T>*> list){
    while(list.empty() != 1)
    {
        if ((list.front()->getName()).compare(name) == 0)
        {
            // if the name has already exists in the List
            return list.front();//pop the first element name out of the list (the name of the existed list)
        }
    else{
        list.pop_front();
    }
}
    return NULL; // if can't find the name, return a null pointer
}



int main(int argc, const char * argv[]) {
    vector<vector<string>> lines;
    ifstream inFile;
    ofstream outFile;
    
    cout << "Enter the name of the input file: ";
    string input;
    cin >> input; // enter the file name
    inFile.open("/Users/crystalwang/Documents/Xcode/Project1/Project1/command1.txt");
    //open using the file name(input), change according to your location of your file
    if (!inFile) {
        cout << "Unable to open file\n";
        exit(9); // terminate with errorcode 9
    }
 
    cout << "Enter the name of the output file:";
    string output;
    cin >> output; // enter the output file name
    outFile.open("/Users/crystalwang/Documents/Xcode/Project1/Project1/output.txt");
    //open using the file name(input), change according to your location of your file
    //shorten the string names
    string c = "create";
    string po = "pop";
    string pu = "push";
    string s = "stack";
    string q = "queue";
 
    //initialization of the lists
    list<SimpleList<int> *> listSLi; // all integer stacks and queues
    list<SimpleList<double> *> listSLd; // all double stacks and queues
    list<SimpleList<string> *> listSLs; // all string stacks and queues
    
    vector<string> eachline; // a vector that stores each line to a vector
    string e1; // the first string element of each line
    string e2; // the second string element of each line
    string e3; // the thrid string element of each line
    
    
   
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line))
        {
            outFile << "PROCESSING COMMAND :" << line <<'\n';
            // printing the processing command message everytime it gets a new line in the output file
            eachline = split(line);
            e1 = eachline[0];
            // the first element of the line is stored at the first vector element of the vector
            //"create", "pop", "push"
            e2 = eachline[1];
            // the second element of the line is stored at the second vector element of the vector
            // if the first word is "create"
            if(eachline[0].compare(c) == 0 || eachline[0].compare(pu) == 0){
                //only pop and create command have the thrid word
                e3 = eachline[2];
            }
            //"create" case
             if(eachline[0].compare(c) == 0)
            {
            if(eachline[1].substr(0,1).compare("i") == 0)
            { // case of an integer
               if(search(e2, listSLi) != NULL)
                {
                    outFile << "ERROR: This name already exists!" << '\n';
                }
                else
                {
                SimpleList<int> *pi;// initialize a int simplelist pointer
                if(e3.compare(s) == 0)
                {// for the stack case
                    pi = new Stack<int>(eachline[1]);
                    // assign the pointer to the int stack, with the name of the second element
                    listSLi.push_front(pi);
                }
               if(e3.compare(q) == 0)
                {// for the queue case
                    pi = new Queue<int>(eachline[1]);
                    // assign the pointer to the int queue, with the name of the second element
                    listSLi.push_front(pi);
                }
                }
            }
            
            if(eachline[1].substr(0,1).compare("d") == 0){ // case of a double
                if(search(e2, listSLd) != NULL)
                {
                    outFile << "ERROR: This name already exists!" << endl;
                }
                else {
                    SimpleList<double> *pd;// initialize a int simplelist pointer
                    if(e3.compare(s)==0) {// for stack
                            pd = new Stack<double>(eachline[1]);
                    // assign the pointer to the double stack, with the name of the second element
                            listSLd.push_front(pd);
                        
                    }
                    if(e3.compare(q)==0) {// for the queue case
                            pd = new Queue<double>(eachline[1]);
                        // assign the pointer to the int queue, with the name of the second element
                        listSLd.push_front(pd);
                        
                        }
                }
            }
            if(eachline[1].substr(0,1).compare("s") == 0){ // case of a string
                if(search(e2, listSLd) != NULL)
                {
                    outFile << "ERROR: This name already exists!" << endl;
                }
                else{
                    SimpleList<string> *ps;// initialize a string simplelist pointer
                if(e3.compare(s)==0) { // for the stack
                        ps = new Stack<string>(eachline[1]);
                    // assign the pointer to the string stack, with the name of the second element
                        listSLs.push_front(ps);
                }
                    if(e3.compare(q)==0) {// for the queue case
                            ps = new Queue<string>(eachline[1]);
                        // assign the pointer to the string queue, with the name of the second element
                            listSLs.push_front(ps);
                    }
                }
            }// string
            }// create
            
          if(eachline[0].compare(po) == 0){ // pop case
              if(eachline[1].substr(0,1).compare("i") == 0){//integer case
                  SimpleList<int> *pi = search(e2,listSLi);
                  if(pi == NULL){
                      outFile << "ERROR: This name does not exist!" << '\n';
                  }
                  else{
                      int* pvalue = pi->pop();
                      if(pvalue == nullptr){ // empty list
                          outFile << "ERROR: This list is empty!" << '\n';
                      }
                      else {
                          outFile << "Value popped: " << *pvalue <<'\n';
                  }
                  }// integer case
              }
               if(eachline[1].substr(0,1).compare("d") == 0){//double case
                   SimpleList<double> *pd = search(e2,listSLd);
                   if(pd == NULL){
                       outFile << "ERROR: This name does not exist!" << '\n';
                   }
                   else{
                       double* pvalue = pd->pop();
                       if(pvalue == nullptr){ // empty list
                           outFile << "ERROR: This list is empty!" << '\n';
                       }
                       else {
                           outFile << "Value popped: " << *pvalue <<'\n';
                       }
                   }
               }// double case
              
              if(eachline[1].substr(0,1).compare("s") == 0){//string case
                   SimpleList<string> *ps = search(e2,listSLs);
                   if(ps == NULL){
                       outFile << "ERROR: This name does not exist!" << '\n';
                   }
                   else{
                       string* pvalue = ps->pop();
                       if(pvalue == nullptr){ // empty list
                           outFile << "ERROR: This list is empty!" << '\n';
                       }
                       else {
                           outFile << "Value popped: " << *pvalue <<'\n';
                       }
                   }
               }// string case
       }//pop class
         
            
            if(eachline[0].compare(pu) ==0){ //push case
                if(eachline[1].substr(0,1).compare("i") == 0){//integer case
                       SimpleList<int> *pi;
                        if(search(e2, listSLi) == NULL){
                            outFile << "ERROR: This name does not exist!" << '\n';
                        }
                        else {
                            pi = search<int>(e2,listSLi);
                            int x = 0;
                            stringstream value(e3); // convert a string value to an integer
                            value>>x;
                            int* p = new int(x);
                            pi->push(p);
                            }
                    
                       }//interger case
                
                if(eachline[1].substr(0,1).compare("d") == 0){ // double case
                    SimpleList<double> *pd;
                    if(search(e2, listSLd) == NULL){
                        outFile << "ERROR: This name does not exist!" << '\n';
                    }
                    else {
                        pd = search<double>(e2,listSLd);
                        double y = 0.00;
                        stringstream value(e3); // convert a string value to an integer
                        value >> y;
                        double* p1 = new double(y);
                        pd->push(p1);
                    }
                }//double case
                
                if(eachline[1].substr(0,1).compare("s") == 0){ // string case
                    SimpleList<string> *ps;
                    if(search(e2, listSLs) == NULL){
                        outFile << "ERROR: This name does not exist!" << '\n';
                    }
                    else {
                        ps = search<string>(e2,listSLs);
                        string* s = new string(e3);
                        //stringstream value(e3);
                        //value >> s;
                        
                        ps->push(s); //no need to convert string to other data type
                }
            }//string case
            }//push case
    }
        
            
    }// while
    

    inFile.close();
    outFile.close();
    
    return 0;
    }
