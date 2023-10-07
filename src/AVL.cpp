#include "AVL.h"
#include <regex>

AVLTree::AVLTree(){
    root = nullptr;
}

Node *AVLTree::getRoot() {
    return root;
}

void AVLTree::Insert(string name, string ufid){
    this->root = InsertHelper(this->root, name, ufid);
}

Node *AVLTree::InsertHelper(Node* currentRoot, string name, string ufid){
    // Normal BST Insertion

    if (currentRoot == nullptr)
    {
        Node* temp = new Node(name, ufid);
        cout << "successful" << endl;
        return temp;
    }

    else if (currentRoot->ufid < ufid) {
        currentRoot->right = InsertHelper(currentRoot->right, name, ufid);
    }

    else if (currentRoot->ufid > ufid) {
        currentRoot->left = InsertHelper(currentRoot->left, name, ufid);
    }

    else {
        cout << "unsuccessful" << endl;
        return currentRoot;
    }

    // Balancing the BST after Insertion

    currentRoot->balanceFactor = calculateBalanceFactor(currentRoot);

    if (currentRoot->balanceFactor > 1){
        if (ufid < currentRoot->left->ufid){
            return rotateRight(currentRoot);
        }

        else if(ufid > currentRoot->left->ufid){
            return rotateLeftRight(currentRoot);
        }
    }

    else if (currentRoot->balanceFactor < -1){
        if (ufid > currentRoot->right->ufid){
            return rotateLeft(currentRoot);
        }

        else if(ufid < currentRoot->right->ufid){
            return rotateRightLeft(currentRoot);
        }
    }

    return currentRoot;
}

void AVLTree::Remove(string ufid) {
    this->root = RemoveHelper(this->root, ufid);
}

Node *AVLTree::RemoveHelper(Node *currentRoot, string ufid){
    if (currentRoot == nullptr){
        cout << "unsuccessful" << endl;
        return nullptr;
    }

    if (ufid < currentRoot->ufid){
        currentRoot->left = RemoveHelper(currentRoot->left, ufid);
    }

    else if (ufid > currentRoot->ufid){
        currentRoot->right = RemoveHelper(currentRoot->right, ufid);
    }

    else{
        // Node with only one child or no child
        if (currentRoot->left == nullptr){
            Node* temp = currentRoot->right;
            delete currentRoot;
            cout << "successful" << endl;
            return temp;
        }

        else if(currentRoot->right == nullptr){
            Node* temp = currentRoot->left;
            delete currentRoot;
            cout << "successful" << endl;
            return temp;
        }

        // Node with two children, get the inorder successor (smallest in the right subtree)
        Node* temp = findSmallestNode(currentRoot->right);

        // Copy the inorder successor's data to this node
        currentRoot->name = temp->name;
        currentRoot->ufid = temp->ufid;

        // Delete the inorder successor
        currentRoot->right = RemoveHelper(currentRoot->right, temp->ufid);
    }

    return currentRoot;
}

Node *AVLTree::findSmallestNode(Node *node) {
    Node* temp = node;

    while(temp->left != nullptr) {
        temp = temp->left;
    }

    return temp;
}

Node *AVLTree::rotateLeft(Node *node) {
    Node* grandChild = node->right->left;
    Node* newParent = node->right;

    newParent->left = node;
    node->right = grandChild;

    return newParent;
}

Node *AVLTree::rotateRight(Node *node) {
    Node* grandChild = node->left->right;
    Node* newParent = node->left;

    newParent->right = node;
    node->left = grandChild;

    return newParent;
}

Node *AVLTree::rotateRightLeft(Node *node) {
    Node* newChild = node->right->left;
    Node* grandChild = node->right;
    Node* greatGrandChild = node->right->left->right;

    node->right = newChild;
    newChild->right = grandChild;
    grandChild->left = greatGrandChild;
    Node* newParent = rotateLeft(node);

    return newParent;
}

Node *AVLTree::rotateLeftRight(Node *node) {
    Node* newChild = node->left->right;
    Node* grandChild = node->left;
    Node* greatGrandChild = node->left->right->left;

    node->left = newChild;
    newChild->left = grandChild;
    grandChild->right = greatGrandChild;
    Node* newParent = rotateRight(node);

    return newParent;
}

int AVLTree::height(Node *currentRoot) {
    if (currentRoot == nullptr){
        return 0;
    }

    // Recursive call that goes to the bottom of tree

    int left = height(currentRoot->left);
    int right = height(currentRoot->right);
    int height = 1 + max(left, right);

    return height;
}


int AVLTree::calculateBalanceFactor(Node *currentRoot) {
    if (currentRoot == nullptr){
        return 0;
    }

    else{
        // Formula to calculate the Balance Factor
        return (height(currentRoot->left)) - (height(currentRoot->right));
    }
}

void AVLTree::SearchIDHelper(Node* currentRoot, string ufid) {
    // Terminal case: When ID does not exist within the tree, print “unsuccessful”.
    if (currentRoot == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }

    // When ID does exist
    if (currentRoot->ufid == ufid) {
        cout << currentRoot->name << endl;
        return;
    }
    else if (ufid < currentRoot->ufid) {
        SearchIDHelper(currentRoot->left, ufid);
    }
    else if (ufid > currentRoot->ufid) {
        SearchIDHelper(currentRoot->right, ufid);
    }
}

void AVLTree::SearchID(string ufid) {
    SearchIDHelper(this->root, ufid);
}

void AVLTree::SearchNameHelper(Node *currentRoot, string name, bool &found) {
    if (currentRoot == nullptr) {
        return;
    }

    if (currentRoot->name == name) {
        cout << currentRoot->ufid << endl;
        found = true; // Update the found flag
    }

    // Continue to search in both left and right subtrees
    SearchNameHelper(currentRoot->left, name, found);
    SearchNameHelper(currentRoot->right, name, found);
}

void AVLTree::SearchName(string name) {
    bool found = false; // Use a flag to track if the name was found
    SearchNameHelper(this->root, name, found);
    if (!found) {
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::preOrder(Node *currentRoot, vector<Node*> &tempNodes) {
    if (currentRoot == nullptr){
        return;
    }

    tempNodes.push_back(currentRoot);
    preOrder(currentRoot->left, tempNodes);
    preOrder(currentRoot->right, tempNodes);
}

void AVLTree::postOrder(Node *currentRoot, vector<Node *> &tempNodes) {
    if (currentRoot == nullptr){
        return;
    }

    postOrder(currentRoot->left, tempNodes);
    postOrder(currentRoot->right, tempNodes);
    tempNodes.push_back(currentRoot);
}

void AVLTree::inOrder(Node *currentRoot, vector<Node *> &tempNodes, vector<string> &keys) {
    if (currentRoot == nullptr){
        return;
    }

    inOrder(currentRoot->left, tempNodes, keys);
    tempNodes.push_back(currentRoot);
    keys.push_back(currentRoot->ufid);
    inOrder(currentRoot->right, tempNodes, keys);
}

vector<string> AVLTree::inOrderUFIDs() {
    Node* currentRoot = this->root;

    vector<Node*> tempNodes;
    vector<string> keys;
    inOrder(currentRoot, tempNodes, keys);

    return keys;
}


void AVLTree::PrintPreOrder() {
    vector<Node*> tempNodes;
    preOrder(root, tempNodes);
    printNames(tempNodes);
}

void AVLTree::PrintPostOrder() {
    vector<Node*> tempNodes;
    postOrder(root, tempNodes);
    printNames(tempNodes);
}

void AVLTree::PrintInOrder() {
    Node* currentRoot = this->root;

    vector<Node*> tempNodes;
    vector<string> keys;
    inOrder(currentRoot, tempNodes, keys);
    printNames(tempNodes);
}

void AVLTree::PrintLevelCount() {
    int levelCount = height(this->root);
    cout << levelCount << endl;
}

void AVLTree::printNames(vector<Node *> tempNodes) {
    for (auto it = tempNodes.begin(); it != tempNodes.end(); ++it) {
        cout << (*it)->name;
        if (next(it) != tempNodes.end()) {
            cout << ", ";
        }
    }

    cout << endl;
}

Node *AVLTree::RemoveInOrderHelper(Node *currentRoot, int n) {
    if (currentRoot == nullptr){
        cout << "unsuccessful" << endl;
        return currentRoot;
    }

    vector<Node*> tempNodes;
    vector<string> keys;
    inOrder(currentRoot, tempNodes, keys);
    int size = tempNodes.size();

    if (n > size - 1){
        cout << "unsuccessful" << endl;
        return currentRoot;
    }

    else{
        Node* temp = RemoveHelper(currentRoot, tempNodes[n]->ufid);
        return temp;
    }
}

void AVLTree::RemoveInOrder(int n) {
    this->root = RemoveInOrderHelper(this->root, n);
}

int AVLTree::countNodes(Node *currentRoot) {
    if (currentRoot == nullptr){
        return 0;
    }

    return 1 + countNodes(currentRoot->left) + countNodes(currentRoot->right);
}