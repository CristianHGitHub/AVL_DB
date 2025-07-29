#include "AVLTree.h"

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
}

AVLNode* AVLTree::insert(AVLNode* node, const Record& data) {
    if (!node) return new AVLNode(data);
    if (data.id < node->data.id)
        node->left = insert(node->left, data);
    else if (data.id > node->data.id)
        node->right = insert(node->right, data);
    else
        return node; // Duplicate ID not allowed

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && data.id < node->left->data.id)
        return rightRotate(node);
    if (balance < -1 && data.id > node->right->data.id)
        return leftRotate(node);
    if (balance > 1 && data.id > node->left->data.id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && data.id < node->right->data.id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const Record& data) {
    root = insert(root, data);
}

AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

AVLNode* AVLTree::remove(AVLNode* node, int id) {
    if (!node) return node;
    if (id < node->data.id)
        node->left = remove(node->left, id);
    else if (id > node->data.id)
        node->right = remove(node->right, id);
    else {
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else
                *node = *temp;
            delete temp;
        } else {
            AVLNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data.id);
        }
    }

    if (!node) return node;
    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::remove(int id) {
    root = remove(root, id);
}

AVLNode* AVLTree::search(AVLNode* node, int id) {
    if (!node) return nullptr;
    if (id == node->data.id) return node;
    return id < node->data.id ? search(node->left, id) : search(node->right, id);
}

Record* AVLTree::search(int id) {
    AVLNode* node = search(root, id);
    return node ? &node->data : nullptr;
}

void AVLTree::inOrder(AVLNode* node) {
    if (!node) return;
    inOrder(node->left);
    std::cout << "ID: " << node->data.id << ", Name: " << node->data.name << ", Price: $" << node->data.price << "\n";
    inOrder(node->right);
}

void AVLTree::displayInOrder() {
    inOrder(root);
}

void AVLTree::rangeQuery(AVLNode* node, int low, int high) {
    if (!node) return;
    if (node->data.id > low)
        rangeQuery(node->left, low, high);
    if (node->data.id >= low && node->data.id <= high)
        std::cout << "ID: " << node->data.id << ", Name: " << node->data.name << ", Price: $" << node->data.price << "\n";
    if (node->data.id < high)
        rangeQuery(node->right, low, high);
}

void AVLTree::rangeQuery(int low, int high) {
    rangeQuery(root, low, high);
}

int AVLTree::countNodes(AVLNode* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int AVLTree::count() {
    return countNodes(root);
}
