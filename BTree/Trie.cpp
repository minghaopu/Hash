//
//  Trie.cpp
//  BTree
//
//  Created by roneil on 2016/11/28.
//  Copyright © 2016年 gu. All rights reserved.
//

#include "Trie.hpp"
void Trie::insert(string word, int start) {
    TrieNode* p = _root;
    for (int i = start; i < word.length(); i++) {
        int c = word[i] - 'A';
        if (c > 25 || c < 0) return;
        if (p->next[c] == NULL) p->next[c] = new TrieNode();
        p = p->next[c];
    }
    p->isWord = true;
}

int Trie::search(string word, int start) {
    if (start >= word.length()) return -1;
    TrieNode* p = _root;
    for (int i = start; i < word.length(); i++) {
        int c = word[i] - 'A';
        if (c > 25 || c < 0) return -1;
        if (p->next[c] != NULL) p = p->next[c];
        else return -1;
    }
    if (p != NULL && p->isWord) {
        p->count++;
        return p->count;
    }
    return -1;
}
void Trie::remove(string word, int start) {
    TrieNode* p = _root;
    // check whether the node can be found
    for (int i = start; i < word.length(); i++) {
        int c = word[i] - 'A';
        if (c > 25 || c < 0) return;
        if (p->next[c] != NULL) {
            p = p->next[c];
        } else return; // not found
    }
    // if found, set isWord to false;
    if (p != NULL && p->isWord) {
        p->isWord = false;
        p->count = 0;
    }
    // check whether the node can be delete
    removeNode(word, start, _root);
}
void Trie::removeNode(string word, int index, TrieNode* node) {
    if (index == word.length()) return;
    if (node != NULL) {
        removeNode(word, index+1, node->next[word[index] - 'A']);
        
        bool hasOhterNode = false;
        for (int i = 0; i < 26; i++) {
            if (node->next[i] != NULL) {
                hasOhterNode = true;
                break;
            }
        }
        // if this node is not the end of a word and it has no childern, then delete
        if (!hasOhterNode && !node->isWord) {
            delete node;
            node = NULL;
        }
    }
}
void Trie::resetFrequency() {
    recursiveReset(_root);
}
void Trie::recursiveReset(TrieNode* node) {
    if (node == NULL) return;
    node->count = 0;
    for (int i = 0; i < 26; i++) {
        if (node->next[i]) recursiveReset(node->next[i]);
    }
}
void Trie::clear() {
    recursiveReset(_root);
}
void Trie::recursiveClear(TrieNode* node) {
    if (node == NULL) return;
    node->count = 0;
    for (int i = 0; i < 26; i++) {
        if (node->next[i]) recursiveReset(node->next[i]);
    }
    delete node;
    node = NULL;
}
