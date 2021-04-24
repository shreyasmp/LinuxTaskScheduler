
/**
 * Header file declaring all the Red Black Tree class & methods
 *
 * @author Shreyas Muthkur
 */

#ifndef RBTREE_H
#define RBTREE_H

//#define FCFS_SCHEDULER //uncomment for using FCFS scheduler, comment for RR scheduler

#define TRUE 1
#define FALSE 0
#define TIMESLICE 3
#define PRINT_TIME 15

#include <iostream>
#include <vector>
#include <queue>

#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

enum Colour {
    RED = 0,
    BLACK = 1
};

struct tRedBlackNode {
    Colour eColour = BLACK;
    int nID = 0, nStartTime = 0, nRunTime = 0, nTotalTime = 0, nFlag = 0, nActualStart = 0;
    tRedBlackNode *left = nullptr,
            *right = nullptr,
            *parent = nullptr;
};

class redBlackTree {
private:
    tRedBlackNode *Node = new tRedBlackNode();

public:
    redBlackTree() {
        (this->Node)->eColour = BLACK;
        (this->Node)->nID = 0;
        (this->Node)->nStartTime = 0;
        (this->Node)->nRunTime = 0;
        (this->Node)->parent = nullptr;
        (this->Node)->right = nullptr;
        (this->Node)->left = nullptr;
    }

    tRedBlackNode *getRoot() {
        return this->Node;
    }

    void setRoot(tRedBlackNode *tempNode) {
        this->Node = tempNode;
    }

    static int parseInput(ifstream &);

    static tRedBlackNode *treeMinimum(tRedBlackNode *);

    static tRedBlackNode *nodeSuccessor(tRedBlackNode *, tRedBlackNode *);

    static bool leftRotate(tRedBlackNode *, tRedBlackNode *);

    static bool rightRotate(tRedBlackNode *, tRedBlackNode *);

    static bool treeBalance(tRedBlackNode *, tRedBlackNode *);

    static bool insertNode(tRedBlackNode *, tRedBlackNode *);

    static bool deleteBalance(tRedBlackNode *, tRedBlackNode *);

    static bool deleteNode(tRedBlackNode *, tRedBlackNode *);

    static void printBinaryTree(tRedBlackNode *);

    void printInOrder(tRedBlackNode *);

    static tRedBlackNode *inOrderFind(tRedBlackNode *);

    static void scheduler(tRedBlackNode *);

    static void initializeNode(tRedBlackNode *, int, int, int);

    static tRedBlackNode *findNode(tRedBlackNode *, int);
};

extern int clocks;
extern redBlackTree *Tree;
extern tRedBlackNode *Nil;
extern tRedBlackNode *Root;

extern tRedBlackNode *inOrderFind(tRedBlackNode *);

extern void scheduler(tRedBlackNode *);

extern bool insertNode(tRedBlackNode *, tRedBlackNode *);

extern void printBinaryTree(tRedBlackNode *);

extern void printInOrder(tRedBlackNode *);

extern void initializeNode(tRedBlackNode *, int, int, int);

#endif

