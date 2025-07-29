#ifndef AVLNODE_H
#define AVLNODE_H

#include <string>

struct Record {
    int id;
    std::string name;
    double price;
};

struct AVLNode {
    Record data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Record& r)
        : data(r), left(nullptr), right(nullptr), height(1) {}
};

#endif
