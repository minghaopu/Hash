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
        bool isWord;
        TrieNode() {
            memset(next, NULL, sizeof(next));
            isWord = false;
        }
    };
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    void insert(string word, int start);
    bool search(string word, int start);
    void remove(string word, int start);
    void removeNode(string word, int index, TrieNode* node);
    void clear();
    void recursiveClear(Trie* root);
};

#endif /* Trie_hpp */
