/**
 *  Tree class with all Red black tree methods
 *
 *  @author Shreyas Muthkur
 */

#include <iostream>
#include <queue>
#include <string>

#include "headers/RBTree.h"

using namespace std;

redBlackTree *Tree = new redBlackTree();
tRedBlackNode *Nil = new tRedBlackNode();
tRedBlackNode *Root = Nil;

/*
 * This routine returns the left most node from the tree
 * */

tRedBlackNode *redBlackTree::treeMinimum(tRedBlackNode *Node) {
    while ((Node->left) != Nil) {
        Node = Node->left;
    }
    return Node;
}

/*
 * This routine returns the next largest value in the tree from the current node
 * */

tRedBlackNode *redBlackTree::nodeSuccessor(tRedBlackNode *treeRoot, tRedBlackNode *Node) {
    tRedBlackNode *y;
    if ((Node->right) != Nil) {
        return treeMinimum(Node->right);
    }
    y = Node->parent;
    while ((y != Nil) && (Node == y->right)) {
        Node = y;
        y = y->parent;
    }
    return y;
}

/*
 * rotate left along 2 nodes
 * */

bool redBlackTree::leftRotate(tRedBlackNode *treeRoot, tRedBlackNode *Node) {
    tRedBlackNode *y = Node->right;
    Node->right = y->left;
    if (y->left != Nil)
        (y->left)->parent = Node;
    if (y != Nil)
        y->parent = Node->parent;
    //if Node is at root then y becomes root
    if ((Node->parent) == Nil) {
        Root = y;
    } else {
        //if Node is a left child then adjust Node's parent's left child or..
        if (Node == (Node->parent)->left) {
            (Node->parent)->left = y;
        } else {
            //adjust Node's parent's right child
            (Node->parent)->right = y;
        }
    }
    //the left child of y is now Node
    y->left = Node;
    //the parent of Node is now y
    if (Node != Nil)
        Node->parent = y;
    return TRUE;
}

/*
 * rotate right along 2 nodes
 * */
bool redBlackTree::rightRotate(tRedBlackNode *treeRoot, tRedBlackNode *Node) {
    tRedBlackNode *y = Node->left;
    Node->left = y->right;
    if (y->right != Nil)
        (y->right)->parent = Node;
    if (y != Nil)
        y->parent = Node->parent;
    //if Node is at root then y becomes root
    if ((Node->parent)->nID == 0) {
        Root = y;
    } else {
        // if Node is a left child then adjust Node's parent's left child or...
        if (Node == (Node->parent)->left) {
            (Node->parent)->left = y;
        } else {
            // adjust Node's parent's right child
            (Node->parent)->right = y;
        }
    }
    //the right child of y is now Node
    y->right = Node;
    //the parent of Node is now y
    if (Node != Nil)
        Node->parent = y;
    return TRUE;
}

/*
 * Routine to balance the RB Tree after Insert
 * The insert node routine disturbs the 3rd property of RB Tree
 * i.e, A red node cannot have a red child
 * This routine balances the tree in such a way that this property is retained
 * after inserting the node.
 * Case1: y is x's uncle. Executed when both p[x] & y are RED.
 * 		Both are made BLACK & grandparent is made RED. Now the parent of
 * 		grandparent might be RED hence the issue is pushed up one level
 * 		and while loop is repeated.
 * Case2: if x is right child we use left rotation & convert it to Case3.
 * Case3: where x is left child. Both x and p[x] are RED it doesn't affect
 * Black Height. We make color changes & right rotate to preserve property 4.
 * */
bool redBlackTree::treeBalance(tRedBlackNode *treeRoot, tRedBlackNode *Node) {
    tRedBlackNode *y;
    while ((Node != Root) && ((Node->parent)->eColour == RED)) {    //3
        //if x's parent is a left child
        if (((Node->parent)->parent)->left == Node->parent) {        //4
            y = ((Node->parent)->parent)->right;                //5
            if (y->eColour == RED) {                                //6
                (Node->parent)->eColour = BLACK;                //7-> Case 1
                y->eColour = BLACK;                                //8-> Case 1
                ((Node->parent)->parent)->eColour = RED;        //9-> Case 1
                Node = (Node->parent)->parent;                    //10->Case 1
            } else {
                if (Node == (Node->parent)->right) {                //11
                    Node = Node->parent;                        //12->Case 2
                    leftRotate(Root, Node);                        //13->Case 2
                }
                (Node->parent)->eColour = BLACK;                //14->Case 3
                ((Node->parent)->parent)->eColour = RED;        //15->Case 3
                rightRotate(Root, ((Node->parent)->parent));        //16->Case 3
            }
        }
            //Above steps are repeated if x's parent is right child
        else {
            y = ((Node->parent)->parent)->left;
            if (y->eColour == RED) {
                (Node->parent)->eColour = BLACK;
                y->eColour = BLACK;
                ((Node->parent)->parent)->eColour = RED;
                Node = ((Node->parent)->parent);
            } else {
                if (Node == (Node->parent)->left) {
                    Node = Node->parent;
                    rightRotate(Root, Node);
                }
                (Node->parent)->eColour = BLACK;
                ((Node->parent)->parent)->eColour = RED;
                leftRotate(Root, ((Node->parent)->parent));
            }
        }
        Root->eColour = BLACK;
    }
    return TRUE;
}

/*
 * Routine to insert a node into the RB Tree
 * */
bool redBlackTree::insertNode(tRedBlackNode *treeRoot, tRedBlackNode *z) {
    tRedBlackNode *x, *y;
    y = Nil;
    x = treeRoot;
    //This while runs until we find the place to insert the node
    while (x != Nil) {
        //y is always maintained as the parent of x
        y = x;
        //If current task arrived before
        if (z->nStartTime < x->nStartTime) {
            x = x->left;
        }
            //If current task arrived at same time but requires lesser time of CPU
        else if ((z->nStartTime == x->nStartTime) && (z->nRunTime < x->nRunTime)) {
            x = x->left;
        }
            //If current task arrived later
        else {
            x = x->right;
        }
    }
    //The following steps are used to setup the node and completely associate it with the Tree
    z->parent = y;
    if (y == Nil) {
        cout << "first insert" << endl;
        Root = z;
        z->left = Nil;
        z->right = Nil;
        z->eColour = BLACK;
        Root->parent = Nil;
    } else {
        if (z->nStartTime < y->nStartTime) {
            y->left = z;
            z->left = Nil;
            z->right = Nil;
            z->eColour = RED;
        } else if ((z->nStartTime == x->nStartTime) && (z->nRunTime < x->nRunTime)) {
            y->left = z;
            z->left = Nil;
            z->right = Nil;
            z->eColour = RED;
        } else {
            y->right = z;
            z->left = Nil;
            z->right = Nil;
            z->eColour = RED;
        }
    }

    //Call the RB-Tree balancing routine to maintain the RB Tree properties
    treeBalance(Root, z);
    return TRUE;
}

/*
 * Routine to balance the RB Tree after deleting a node
 * Case1: when node w, the sibling of node x, is RED. Since w must have BLACK
 * 		children, we can switch the colors of w and its parent and then perform a
 * 		left rotation on p[x] without violating any red black properties.
 * Case2: when node 2 is BLACK, both its children are BLACK. We take one black from
 * 		x and w and make w RED and add an extra BLACK to p[x]. Then repeat with p[x]
 * 		as new node.
 * Case3: when w is black, its left child is RED and right is BLACK. Switch colors
 * 		of w and left child and perform right rotation on w. The new sibling of
 * 		is a BLACK node with a RED right child. Transformed into Case 4.
 * Case4: when w's right child is RED. make some color changes and perform left rotate
 * 		on p[x]. Setting x to the root terminates the loop.
 * */
bool redBlackTree::deleteBalance(tRedBlackNode *treeRoot, tRedBlackNode *x) {
    tRedBlackNode *y;
    while ((x != Root) && (x->eColour == BLACK)) {                                //1
        //if x is a left child
        if ((x->parent)->left == x) {                                                //2
            y = (x->parent)->right;                                                //3
            if (y->eColour == RED) {                                                //4
                y->eColour = BLACK;                                                //5->Case 1
                (x->parent)->eColour = RED;                                        //6->Case 1
                leftRotate(Root, x->parent);                                        //7->Case 1
                y = (x->parent)->right;                                            //8->Case 1
            }
            if (((y->left)->eColour == BLACK) && ((y->right)->eColour == BLACK)) {//9-
                y->eColour = RED;                                                //10->Case 2
                x = x->parent;                                                    //11->Case 1
            } else {
                if ((y->right)->eColour == BLACK) {                                //12
                    (y->left)->eColour = BLACK;                                    //13->Case 3
                    y->eColour = RED;                                            //14->Case 3
                    rightRotate(Root, y);                                        //15->Case 3
                    y = (x->parent)->right;                                        //16->Case 3
                }
                y->eColour = (x->parent)->eColour;                                    //17->Case 4
                (x->parent)->eColour = BLACK;                                        //18->Case 4
                (y->right)->eColour = BLACK;                                        //19->Case 4
                leftRotate(Root, x->parent);                                            //20->Case 4
                x = Root;                                                            //21->Case 4
            }
        }
            //if x is a right child
        else {
            y = (x->parent)->left;
            if (y->eColour == RED) {                                                //4
                y->eColour = BLACK;                                                //5
                (x->parent)->eColour = RED;                                        //6
                leftRotate(Root, x->parent);                                        //7
                y = (x->parent)->left;                                            //8
            }
            if (((y->right)->eColour == BLACK) && ((y->left)->eColour == BLACK)) {//9
                y->eColour = RED;                                                //10
                x = x->parent;                                                    //11
            } else {
                if ((y->left)->eColour == BLACK) {                                //12
                    (y->right)->eColour = BLACK;                                //13
                    y->eColour = RED;                                            //14
                    leftRotate(Root, y);                                            //15
                    y = (x->parent)->left;                                        //16
                }
                y->eColour = (x->parent)->eColour;                                //17
                (x->parent)->eColour = BLACK;                                    //18
                (y->left)->eColour = BLACK;                                        //19
                rightRotate(Root, x->parent);                                    //20
                x = Root;                                                        //21
            }
        }
    }
    x->eColour = BLACK;
    return TRUE;
}

/*
 * Routine to delete a node from the RB Tree
 * */
bool redBlackTree::deleteNode(tRedBlackNode *treeRoot, tRedBlackNode *Node) {
    tRedBlackNode *x, *y;
    x = Nil;
    if ((Node->left == Nil) || (Node->right == Nil)) {
        y = Node;
    } else {
        y = nodeSuccessor(Root, Node);
    }
    if ((y->left) != Nil) {
        x = y->left;
    } else {
        x = y->right;
    }
    x->parent = y->parent;//7
    if ((y->parent) == Nil) {//8
        Root = x;//9
    } else if (y == (y->parent)->left) {//10
        (y->parent)->left = x;//11
    } else {
        (y->parent)->right = x;//12
    }
    if (y != Node) {//13
        Node->nID = y->nID;
        Node->nRunTime = y->nRunTime;
        Node->nStartTime = y->nStartTime;//15
    }
    if (y->eColour == BLACK) {
        deleteBalance(Root, x);
    }
    return TRUE;
}

/*
 * Routine to print binary tree in level order
 * */
void redBlackTree::printBinaryTree(tRedBlackNode *Node) {
    queue<tRedBlackNode *> bfsQueue;
    if (Node != Nil) {
        bfsQueue.push(Node);
    }
    while (!bfsQueue.empty()) {
        tRedBlackNode *tempNode = bfsQueue.front();
        bfsQueue.pop();
        cout << "(" << tempNode->nRunTime << "," << tempNode->nID << ")";
        if (tempNode->eColour == BLACK)
            cout << "B" << " ";
        if (tempNode->eColour == RED)
            cout << "R" << " ";
        if ((tempNode->left)->nRunTime) {
            bfsQueue.push(tempNode->left);
        }
        if ((tempNode->right)->nRunTime) {
            bfsQueue.push(tempNode->right);
        }
    }
}

/*
 * Routine to initialize a node before inserting it into the tree
 * */
void redBlackTree::initializeNode(tRedBlackNode *x, int id, int time1, int time2) {
    x->eColour = BLACK;
    x->nID = id;
    x->nStartTime = time1;
    x->nRunTime = time2;
    x->parent = Nil;
    x->left = Nil;
    x->right = Nil;
}

/*
 * Routine to find a node based on its run time
 * */
tRedBlackNode *redBlackTree::findNode(tRedBlackNode *Node, int time) {
    while (Node != Nil) {
        if (time < Node->nRunTime) {
            Node = Node->left;
        } else if (time > Node->nRunTime) {
            Node = Node->right;
        } else {
            break;
        }
    }
    return Node;
}

/*
 * Routine to find the Task that has just completed execution
 * */
tRedBlackNode *redBlackTree::inOrderFind(tRedBlackNode *Node) {

    //If we reach a leaf node then return to its parent
    if (Node == Nil)
        return Nil;
    //Make a recursive call with the left child as a parameter
    Tree->inOrderFind(Node->left);
    //If we find a Node that can be deleted the return it
    if (Node->nRunTime == 0) {
        return Node;
    }
    //Make recursive call with right child as a parameter
    Tree->inOrderFind(Node->right);
}

