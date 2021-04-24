/**
 *  Linux Completely Fair Scheduler
 *
 *  @author Shreyas Muthkur
 */

#include <iostream>
#include "headers/RBTree.h"

int clocks;
using namespace std;

/*
 * Routine to print RB Tree in Ascending Order
 * */
void redBlackTree::printInOrder(tRedBlackNode *Node) {
    //If we reach a leaf node then return to its parent
    if (Node == Nil)
        return;
    //Make a recursive call with the left child as a parameter
    printInOrder(Node->left);
    //Print the value of current node
    if (Node->nRunTime > 0) {
        if (Node->eColour == BLACK)
            cout << "(" << Node->nRunTime << "," << Node->nID << ")B" << endl;
        if (Node->eColour == RED)
            cout << "(" << Node->nRunTime << "," << Node->nID << ")R" << endl;
    }
    //Make recursive call with right child as a parameter
    printInOrder(Node->right);
}

/*
 * CFS Scheduler:
 * -Every time this routine is called it runs each task in the tree for TIMESLICE units or time.
 * -It then decrements the amount of time required to complete the task by TIMESLICE units for each task.
 * */
/*void redBlackTree::scheduler(tRedBlackNode* Node){
	//If we reach a leaf node then return to its parent
	if(Node == Nil){
		return;
	}
	//Make a recursive call with the left child as a parameter
	Tree->scheduler(Node->left);
	//Reduce the required time for task by TIMESLICE units
	if((Node->nRunTime > 0)){
			cout<<"Executing Task with ID:"<<Node->nID<<" Time Remaining:"<<Node->nRunTime<<" units"<<endl;
			Node->nRunTime -= TIMESLICE;
	}
	//Make recursive call with right child as a parameter
	Tree->scheduler(Node->right);

}*/

//defined in RBTree.h
#ifndef FCFS_SCHEDULER

void redBlackTree::scheduler(tRedBlackNode *Node) {
    //If we reach a leaf node then return to its parent
    if (Node == Nil) {
        return;
    }
    //Make a recursive call with the left child as a parameter
    Tree->scheduler(Node->left);
    //Reduce the required time for task by TIMESLICE units
    if ((Node->nRunTime > 0)) {
        clocks += TIMESLICE;
        cout << "Executing Task with ID:" << Node->nID << " Time Remaining:" << Node->nRunTime << " units" << endl;
        if ((Node->nRunTime - TIMESLICE) >= 0)
            Node->nRunTime -= TIMESLICE;
        else {
            Node->nRunTime = 0;
        }
        if (clocks % PRINT_TIME == 0) {
            cout << endl;
            cout << "In Order Tree at " << clocks << " time units" << endl;
            Tree->printInOrder(Root);                        //Prints the tree In Order
            cout << endl;
        }
    }
    //Make recursive call with right child as a parameter
    Tree->scheduler(Node->right);

}

#endif

#ifdef FCFS_SCHEDULER
void redBlackTree::scheduler(tRedBlackNode* Node){
    cout<<"Executing Task with ID:"<<(Tree->treeMinimum(Root))->nID<<endl;
    //Run the task till it finishes.
    //It gives the CPU away only when it is finished.
    (Tree->treeMinimum(Root))->nRunTime = 0;
    //delete completed task, which is the leftmost node(minimum of the tree).
    Tree->deleteNode(Root,(Tree->treeMinimum(Root)));
}
#endif

