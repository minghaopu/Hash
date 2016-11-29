//
//  Trie.hpp
//  BTree
//
//  Created by roneil on 2016/11/28.
//  Copyright © 2016年 gu. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include "Header.h"
class Trie {
private:
    class TrieNode {
    public:
        TrieNode* next[26];
        int count;
        bool isWord;
        TrieNode() {
            count = 0;
            memset(next, NULL, sizeof(next));
            isWord = false;
        }
    };
    TrieNode* _root;
public:
    string val;
    bool isWord;
    int count;
    bool isUsed;
    Trie() {
        val = "";
        count = 0;
        isWord = false;
        _root = new TrieNode();
    }
    void insert(string word, int start);
    int search(string word, int start);
    void remove(string word, int start);
    void removeNode(string word, int index, TrieNode* node);
    void clear();
    void recursiveClear(TrieNode* node);
    void resetFrequency();
    void recursiveReset(TrieNode* node);
    ~Trie() {
        clear();
        _root = NULL;
    }
};

#endif /* Trie_hpp */
