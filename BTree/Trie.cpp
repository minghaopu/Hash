//
//  Trie.cpp
//  BTree
//
//  Created by roneil on 2016/11/28.
//  Copyright © 2016年 gu. All rights reserved.
//

#include "Trie.hpp"
void Trie::insert(string word, int start) {
    TrieNode* p = root;
    for (int i = 0; i < word.length(); i++) {
        if (p->next[word[i] - 'A'] == NULL) p->next[word[i] - 'A'] = new TrieNode();
        p = p->next[word[i] - 'A'];
    }
    p->isWord = true;
}

bool Trie::search(string word, int start) {
    TrieNode* p = root;
    for (int i = start; i < word.length(); i++) {
        if (p->next[word[i] - 'A'] != NULL) p = p->next[word[i] - 'A'];
        else return false;
    }
    return p != NULL && p->isWord;
}
void Trie::remove(string word, int start) {
    TrieNode* p = root;
    // check whether the node can be found
    for (int i = start; i < word.length(); i++) {
        if (p->next[word[i] - 'A'] != NULL) {
            p = p->next[word[i] - 'A'];
        } else return; // not found
    }
    // if found, set isWord to false;
    if (p != NULL && p->isWord) {
        p->isWord = false;
    }
    // check whether the node can be delete
    removeNode(word, start, root);
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
