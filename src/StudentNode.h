//
// Created by invad on 9/29/2023.
//

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#ifndef PROJECT1_STUDENTNODE_H
#define PROJECT1_STUDENTNODE_H

struct Node{
    string name;
    string ufid;

    Node* left;
    Node* right;
    int balanceFactor;

    Node(string& name, string& ufid){
        this->name = name;
        this->ufid = ufid;
        left = nullptr;
        right = nullptr;
    }

    Node(){
        name = "";
        ufid = "";
        left = nullptr;
        right = nullptr;
    }
};

#endif //PROJECT1_STUDENTNODE_H
