#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "StudentNode.h"
using namespace std;

class AVLTree{
private:
    Node* root;

    // Helper Functions

    Node* InsertHelper(Node* currentRoot, string name, string ufid);
    Node* RemoveHelper(Node* currentRoot, string ufid);
    Node* RemoveInOrderHelper(Node* currentRoot, int n);
    void SearchIDHelper(Node* currentRoot, string ufid);
    void SearchNameHelper(Node* currentRoot, string name, bool &found);

    // Rotations

    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* findSmallestNode(Node* node);

    // Preorder, Postorder, and Inorder Functions

    void preOrder(Node* currentRoot, vector<Node*> &tempNodes);
    void postOrder(Node* currentRoot, vector<Node*> &tempNodes);
    void inOrder(Node* currentRoot, vector<Node*> &tempNodes, vector<string> &keys);
    void printNames(vector<Node*> tempNodes);

public:
    void Insert(string name, string ufid);
    void Remove(string ufid);
    void SearchID(string ufid);
    void SearchName(string name);
    void PrintPreOrder();
    void PrintPostOrder();
    void PrintInOrder();
    void PrintLevelCount();
    void RemoveInOrder(int n);

    // Used to verify if inOrder works for Test Cases

    vector<string> inOrderUFIDs();

    int height(Node* currentRoot);
    int calculateBalanceFactor(Node* currentRoot);

    // Getters and Setters

    int countNodes(Node *currentRoot);
    Node* getRoot();

    // Constructors

    AVLTree();

};

