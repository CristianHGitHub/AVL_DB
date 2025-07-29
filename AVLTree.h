#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <iostream>
#include <algorithm>

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* node, const Record& data);
    AVLNode* minValueNode(AVLNode* node);
    AVLNode* remove(AVLNode* root, int id);
    AVLNode* search(AVLNode* node, int id);
    void inOrder(AVLNode* node);
    void rangeQuery(AVLNode* node, int low, int high);
    int countNodes(AVLNode* node);

public:
    AVLTree();
    void insert(const Record& data);
    void remove(int id);
    Record* search(int id);
    void displayInOrder();
    void rangeQuery(int low, int high);
    int count();
};

#endif
