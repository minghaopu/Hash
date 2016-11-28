//
//  BTree.hpp
//  BTree
//
//  Created by fanision on 11/1/16.
//  Copyright © 2016 fanision. All rights reserved.
//

#ifndef BTree_hpp
#define BTree_hpp

#include "Header.h"

#define M 4;
#define DEGREE 2;

struct BTNode {
    int num;                                // actually number of nodes

    bool isLeaf;                            // whether the node is a leaf
    pair<string, int>* keys;        // store the word and its frequency
    typedef BTNode* BTNodeChild;
    BTNodeChild* children;
    BTNode(int nodeSize, int childSize) : num(0), isLeaf(true)
        {
            keys=new pair<string, int>[nodeSize];
            for (int i = 0; i < nodeSize; i++) {
                keys[i] = make_pair("", 0);
            }
            children = new BTNodeChild[childSize];
            for (int i = 0; i < childSize; i++) {
                children[i] = NULL;
            }
        }
public:
    ~BTNode(){
        delete []keys;
        delete []children;
    }

};


class BTree {
private:
    int _degree = DEGREE;
    BTNode* _root = NULL;
    int _M = M;
    int _nodeSize = _M - 1; // maximum node size
    int _childSize = _M;    // maximum children size
    int _maxCount = 0;  ///frequency counting
    string _maxCountWord = "";
    string _path = "";      //dictionary file path
public:
    BTree(string inputFilePath);
    void init();
    bool search(string word);
    bool searchNode(BTNode* node, const string word);
    void insert(string word);
    void remove(string word);
    void splitNode(BTNode* node, int index);
    void insertNotFull(BTNode* node, const string word);
    void fileCheck(string filePath);
    void setChildrenNumber(int childrenNumber);     // childrenNumber must be even nubmer
    void clear();
    void recursiveClear(BTNode* node);
    void deleteNode(BTNode* node);
    pair<string, int> getPredecessor(BTNode* node);
    pair<string, int> getSuccessor(BTNode* node);
    void mergeChildren(BTNode* parent, int index);
    bool empty();
    void recursiveRemove(BTNode* node, const string word);
    void removeAll(string path);
    void printTree();
    void findParentNode(BTNode* node);
    void fillNode(BTNode* node, int index);
    void resetFrequency();
    void recursiveReset(BTNode* node);
    ~BTree() {
        clear();
    };
};
#endif /* BTree_hpp */
