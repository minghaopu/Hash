//
//  Hash.hpp
//  BTree
//
//  Created by roneil on 2016/11/28.
//  Copyright © 2016年 gu. All rights reserved.
//

#ifndef Hash_hpp
#define Hash_hpp
#include "Trie.hpp"
#define LEN 5;

class Hash {
private:
    class Item {
    public:
        Trie* root;
        string val;
        bool isWord;
        Item(): val(""), isWord(false), root(NULL) {};
    };
    int _len = LEN;
    Item* _hash = NULL;
    string _path;
    int _maxSize;
public:
    Hash(string inputFilePath);
    void init();
    int hash(string word);
//    bool search(string word);
    void insert(string word);
//    void remove(string word);
//
//    void fileCheck(string filePath);
//
//    void clear();
//    
//
//    bool empty();
//    void removeAll(string path);

    ~Hash() {
    };
};

#endif /* Hash_hpp */
