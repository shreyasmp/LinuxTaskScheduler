/**
 *  Class file to parse the input file and read the data into the RB Tree
 *
 *  @author Shreyas Muthkur
 */

#include <iostream>
#include <algorithm>

#include "headers/RBTree.h"

using namespace std;

int redBlackTree::parseInput(ifstream &inFile) {

    if (!inFile) {
        cout << "File not found in argument. Please check again...." << endl;
        return -1;
    }

    string fileContents;
    getline(inFile, fileContents);

    size_t first;
    size_t second;
    size_t third;
    size_t fourth;

    first = fileContents.find("");
    second = fileContents.find(' ');

    third = fileContents.find(' ');
    fourth = fileContents.find('\n');

    // Parse input file for Total Tasks and Total CPU cycles

    string totalTasks = fileContents.substr(first, second - first);
    cout << "Total Tasks: " << totalTasks << endl;

    string totalCPUCycles = fileContents.substr(third + 1, fourth - third);
    cout << "Total CPU Cycles: " << totalCPUCycles << endl;

    if (Root->nID == 0) {
        cout << "Building Tree Starting Now" << endl << endl;
    }

    while (getline(inFile, fileContents)) {

        tRedBlackNode *ins;
        cout << fileContents << endl;

        istringstream tokenizer(fileContents);
        string token;

        getline(tokenizer, token, ',');
        istringstream tokenizeID(token);
        int taskID;
        tokenizeID >> taskID;
        cout << "TASKID: " << taskID << " ";

        getline(tokenizer, token, ',');
        int sTime;
        sTime = atoi(token.c_str());
        cout << "STARTTIME: " << sTime << " ";

        getline(tokenizer, token, ',');
        istringstream tokenizeTTime(token);
        int tTime;
        tokenizeTTime >> tTime;
        cout << "TOTALTIME: " << tTime << endl;

        ins = new tRedBlackNode();
        Tree->initializeNode(ins, taskID, sTime, tTime);
        Tree->insertNode(Root, ins);
        cout << "Level Order Tree View after current insert" << endl;
        Tree->printBinaryTree(Root);
        cout << endl << endl;

    }
    inFile.close();

    Tree->printInOrder(Root);
    cout << endl;
    cout << "Level Order Traversal after inserting last task:" << endl;
    Tree->printBinaryTree(Root);
    cout << endl << endl;


    //We call the scheduler from here

    cout << "Beginning Execution........." << endl << endl;

    while (Root != Nil) {
        //defined in RBTree.h
#ifdef FCFS_SCHEDULER
        clocks += Tree->treeMinimum(Root)->nRunTime;
            Tree->scheduler(Root);								//Calling the CFS scheduler
            cout<<endl;
            if(clocks%PRINT_TIME == 0){
                cout<<"In Order Tree after "<<clocks<<" time units"<<endl;
                Tree->printInOrder(Root);							//Prints the tree In Order
            }
            cout<<endl;
#endif

#ifndef FCFS_SCHEDULER
        Tree->scheduler(Root);
        if (Tree->treeMinimum(Root)->nRunTime == 0) {
            Tree->deleteNode(Root, Tree->treeMinimum(Root));    //Delete the completed task from Tree
        }
#endif
    }
    cout << endl << "Execution Terminated..... at " << clocks << " cycles" << endl;
    return 0;
}

