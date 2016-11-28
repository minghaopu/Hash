//
//  BTree.cpp
//  BTree
//
//  Created by fanision on 11/1/16.
//  Copyright © 2016 fanision. All rights reserved.
//

#include "BTree.hpp"
void printVector(vector<pair<string, int>> v) {
    for (int i = 0; i < v.size(); i++) {
        cout<<v[i].first<<endl;
    }
}

BTree::BTree(string dictionaryFilePath) {
    if (dictionaryFilePath == "") return;
    _path = dictionaryFilePath;
    if (_root == NULL) {
        _root = new BTNode(_nodeSize, _childSize);
    }
    init();
}
/*
 *
 *  init the tree
 *
 */
void BTree::init() {

    ifstream inputData(_path);
    string content((istreambuf_iterator<char>(inputData)),(istreambuf_iterator<char>()));
    replace_if(content.begin() , content.end(),
               [] (const char& c) { return c == '\r' ;},'\n');
    stringstream ss;
    
    string word;
    if (content != "") {
        
        ss.str(content);
        while (getline(ss, word)) {
            if (word != "") {
                insert(toUpper(word));
            }
        }
    }
}
/*
 *
 *  set the max childern number
 *
 */
void BTree::setChildrenNumber(int childrenNumber) {
    if (childrenNumber <= 0|| childrenNumber & 1 ) return;
    //guarantee child number is even
    _childSize = childrenNumber;
    _nodeSize = childrenNumber - 1;
    _degree = _childSize / 2;
    clear();
    _root = new BTNode(_nodeSize, _childSize);
    init();
}
/*
 *
 *  insert a word into the tree
 *
 */
void BTree::insert(string word) {
    if (_root->num == _nodeSize) {
        BTNode* r = _root;
        BTNode* p = new BTNode(_nodeSize, _childSize);
        _root = p;
        p->isLeaf = false;
        p->children[0] = r;
        splitNode(p, 0);
        insertNotFull(p, word);
    } else {
        insertNotFull(_root, word);
    }
}
/*
 *
 *  remove a word from the tree
 *
 */
void BTree::remove(string word) {
    if (!search(word)) return;
    if (_root->num == 1 && _root->isLeaf) {
        clear();
        return;
    }
    recursiveRemove(_root, word);
}
/*
 *
 *  insert a word to an node which is not full
 *
 */
void BTree::insertNotFull(BTNode *node, const string word) {
    int index = node->num-1;
    
    if (node->isLeaf) {
        while (index >= 0 && word < node->keys[index].first) {
            node->keys[index+1] = node->keys[index];
            index--;
        }
        node->keys[index + 1] = {word, 0};
        node->num++;
    } else {
        while (index >= 0 && word < node->keys[index].first) index--;
        index++;
        BTNode *child = node->children[index];
        if (child->num == _nodeSize) {
            splitNode(node, index);
            if (word > node->keys[index].first) index++;
        }
        insertNotFull(node->children[index], word);
    }
}
/*
 *
 *  split a node to 2 nodes
 *
 */
void BTree::splitNode(BTNode *node, int index) {
    BTNode* p = new BTNode(_nodeSize,_childSize);
    BTNode* child = node->children[index];
    p->isLeaf = child->isLeaf;
    p->num = _degree - 1;//degree is half of M
    for (int i = 0; i < _degree - 1; i++) {
        
        p->keys[i] = child->keys[i + _degree];
        child->keys[i + _degree] = {"", 0};
    }
    if (!child->isLeaf) {
        for (int i = 0; i < _degree; i++) {
            p->children[i] = child->children[i + _degree];
            child->children[i + _degree] = NULL;
        }
    }
    child->num = _degree - 1;
    for (int i = node->num; i > index; i--) {
        node->children[i + 1] = node->children[i];
    }
    node->children[index + 1] = p;
    for (int i = node->num - 1; i >= index; i--) {
        node->keys[i+1] = node->keys[i];
    }
    node->keys[index] = child->keys[_degree - 1];
    child->keys[_degree - 1] = {"", 0};
    node->num++;
}
/*
 *
 *  check whether the word is in the tree
 *
 */
bool BTree::search(string word) {
    if (_root == NULL) return false;
    bool res = searchNode(_root, word);
    return res;
}
/*
 *
 *  check whether the word is in the tree start from certain node
 *
 */
bool BTree::searchNode(BTNode* node, const string word) {
    int i = 0;
    while (i < node->num && word > node->keys[i].first) {
        i++;
    }
    if (i < node->num && word == node->keys[i].first) {
        node->keys[i].second++;
        if (node->keys[i].second > _maxCount) {
            _maxCount = node->keys[i].second;
            _maxCountWord = node->keys[i].first;
        }
        return true;
    } else if (node->isLeaf) return false;
    else {
        return searchNode(node->children[i], word);
    }
}
/*
 *
 *  check the misspell of a file
 *
 */
void BTree::fileCheck(string inputFilePath) {
    resetFrequency();
    clock_t timeBegin, timeEnd;
    double totalTime = 0.0;
    timeBegin = clock();
    ifstream inputData(inputFilePath);
    string content((istreambuf_iterator<char>(inputData)),(istreambuf_iterator<char>()));
    
    replace_if(content.begin() , content.end(),
               [] (const char& c) { return ispunct(c) ;},' ');
    replace_if(content.begin() , content.end(),
               [] (const char& c) { return c == '\r' || c == '\n' ;},' ');
    
    stringstream ss;
    string word;
    ss.str(content);
    
    _maxCount = 0;
    _maxCountWord = "";
    
    int misSpell = 0;
    while (getline(ss, word, ' ')) {
        if (word == "") continue;
        if (search(toUpper(word)) == false) {
            misSpell++;
        }
    }
    
    timeEnd = clock();
    totalTime = (double)(timeEnd - timeBegin)/CLOCKS_PER_SEC;
    
    cout << "Total number of misspelled word: " << misSpell << endl
    << "The highest frequency of occurrence: " << _maxCountWord << endl
    << "The highest frequency word: " << _maxCount<<endl;
    cout << "Total (approx) runtime is " << totalTime << endl;
}
/*
 *
 *  erase the whole tree
 *
 */
void BTree::clear() {
    recursiveClear(_root);
    _root = NULL;
}
/*
 *
 *  erase part of the tree from certain node
 *
 */
void BTree::recursiveClear(BTNode* node) {
    if (node != NULL) {
        if (!node->isLeaf) {
            for (int i = 0; i <= node->num; i++) {
                recursiveClear(node->children[i]);
            }
        }
        deleteNode(node);
    }
}
/*
 *
 *  delete certain node of the tree
 *
 */
void BTree::deleteNode(BTNode* node) {
    if (node != NULL) {
        delete node;
        node = NULL;
    }
}
/*
 *
 *  get the predecessor value of the node
 *
 */
pair<string, int> BTree::getPredecessor(BTNode *node) {
    while (!node->isLeaf) {
        node = node->children[node->num];
    }
    return node->keys[node->num - 1];
}
/*
 *
 *  get the successor value of the node
 *
 */
pair<string, int> BTree::getSuccessor(BTNode *node) {
    while (!node->isLeaf) {
        node = node->children[0];
    }
    return node->keys[0];
}
/*
 *
 *  merge children of node
 *
 */
void BTree::mergeChildren(BTNode *node, int index) {
    BTNode* child = node->children[index];
    BTNode* sibling = node->children[index+1];
    child->keys[_degree - 1] = node->keys[index];
    
    for (int i = 0; i < sibling->num; i++) {
        child->keys[i + _degree] = sibling->keys[i];
    }
    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->num; i++) {
            child->children[i + _degree] = sibling->children[i];
        }
    }
    for (int i = index; i < node->num; i++) {
        if (i == _nodeSize - 1) {
            node->keys[i] = {"", 0};
        } else {
            node->keys[i] = node->keys[i+1];
        }
    }
    for (int i = index + 1; i <= node->num; i++) {
        if (i == _nodeSize) {
            node->children[i] = NULL;
        } else {
            node->children[i] = node->children[i+1];
        }
    }
    node->num--;
    child->num += sibling->num + 1;
    delete sibling;
}
/*
 *
 *  recursive remove word from the node
 *
 */
void BTree::recursiveRemove(BTNode *node, const string word) {
    int i = 0;
    while (i < node->num && word > node->keys[i].first) {
        i++;
    }
    
    if (i < node->num && word == node->keys[i].first) {
        // word in this node
        if (node->isLeaf) { //node is a leaf
            
            for (; i < node->num; i++) {
                if (i == _nodeSize - 1) node->keys[i] = {"", 0};
                else node->keys[i] = node->keys[i+1];
            }
            node->num--;
            return;
        } else {    // node is not a leaf
            BTNode* preChild = node->children[i];
            BTNode* sucChild = node->children[i+1];
            if (preChild->num >= _degree) {
                pair<string, int> pre = getPredecessor(preChild);
                node->keys[i] = pre;
                recursiveRemove(preChild, pre.first);
                
                return;
            } else if (sucChild->num >= _degree) {
                pair<string, int> suc = getSuccessor(sucChild);
                node->keys[i] = suc;
                recursiveRemove(sucChild, suc.first);
                return;
            } else {
                mergeChildren(node, i);
                recursiveRemove(node->children[i], word);
                return;
            }
        }
    } else {
        BTNode* child = node->children[i];
        bool flag = i == node->num;
        if (child->num < _degree) {
            fillNode(node, i);
        }
        if (flag && i > node->num) {
            recursiveRemove(node->children[i - 1], word);
        } else {
            recursiveRemove(node->children[i], word);
        }
    }
}
/*
 *
 *  remove all the word contained in a file
 *
 */
void BTree::removeAll(string removalFilePath) {
    ifstream inputData(removalFilePath);
    string content((istreambuf_iterator<char>(inputData)),(istreambuf_iterator<char>()));
    replace_if(content.begin() , content.end(),
               [] (const char& c) { return c == '\r' ;},'\n');
    stringstream ss;
    
    string word;
    if (content != "") {
        ss.str(content);
        while (getline(ss, word)) {
            if (word != "") {
                remove(toUpper(word));
            }
        }
    }
}
/*
 *
 *  print the tree
 *
 */
void BTree::printTree() {
    queue<BTNode*> currentLevel;
    queue<BTNode*> nextLevel;
    currentLevel.push(_root);
    int level = 0;
    string levelString = "";
    while (!currentLevel.empty()) {
        if (levelString == "") {
            levelString += "Level " + to_string(level) + ":";
        }
        BTNode* front = currentLevel.front();
        currentLevel.pop();
        levelString += " [";
        for (int i = 0; i < front->num; i++) {
            if (i == front->num - 1) {
                levelString += front->keys[i].first + "]";
            }
            else levelString += front->keys[i].first + " , ";
        }
        if (!front->isLeaf) {
            for (int i = 0; i <= front->num; i++) {
                nextLevel.push(front->children[i]);
            }
        }
        
        if (currentLevel.empty() && !nextLevel.empty()) {
            cout<<levelString<<endl;
            levelString = "";
            level++;
            swap(currentLevel, nextLevel);
        }
    }
    if (levelString != "") {
        cout<<levelString<<endl;
    }
}
/*
 *
 *  fill the node if the keys in the node is less than degree
 *
 */
void BTree::fillNode(BTNode* node, int index) {
    if (index != 0 && node->children[index - 1]->num >= _degree) {
        
        BTNode* child = node->children[index];
        BTNode* sibling = node->children[index-1];
        
        for (int i = child->num-1; i >= 0; i--) {
            child->keys[i + 1] = child->keys[i];
        }
        
        if (!child->isLeaf) {
            for (int i = child->num; i >= 0; i--) {
                child->children[i + 1] = child->children[i];
            }
        }
        child->keys[0] = node->keys[index -1];
        
        if (!node->isLeaf) {
            child->children[0] = sibling->children[sibling->num];
            sibling->children[sibling->num] = NULL;
        }
        node->keys[index - 1] = sibling->keys[sibling->num - 1];
        sibling->keys[sibling->num - 1] = {"", 0};
        child->num++;
        sibling->num--;
        
    } else if (index != node->num && node->children[index + 1]->num >= _degree) {
        
        BTNode* child = node->children[index];
        BTNode* sibling = node->children[index+1];
        
        child->keys[child->num] = node->keys[index];
        
        if (!child->isLeaf) {
            child->children[child->num + 1] =  sibling->children[0];
        }
        node->keys[index] = sibling->keys[0];
        
        
        for (int i = 0; i < sibling->num; i++) {
            if (i == _nodeSize - 1) sibling->keys[i] = {"",0};
            else sibling->keys[i] = sibling->keys[i + 1];
        }
        
        if (!sibling->isLeaf) {
            for (int i = 0; i <= sibling->num; i++) {
                if (i == _nodeSize) sibling->children[i] = NULL;
                sibling->children[i] = sibling->children[i+1];
            }
        }
        
        child->num++;
        sibling->num--;
        
        
    } else {
        if (index != node->num) {
            mergeChildren(node, index);
        } else {
            mergeChildren(node, index-1);
        }
    }
}
/*
 *
 *  check whether the tree is empty
 *
 */
bool BTree::empty() {
    return _root == NULL || _root->num == 0;
}
void BTree::resetFrequency() {
    recursiveReset(_root);
}
void BTree::recursiveReset(BTNode* node) {
    if (node == NULL) return;
    for (int i = 0; i < _nodeSize; i++) {
        node->keys[i].second = 0;
    }
    for (int i = 0; i < _childSize; i++) {
        recursiveReset(node->children[i]);
    }
}

