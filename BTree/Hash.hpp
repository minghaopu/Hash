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
#define LEN 3;

class Hash {
private:
//    class Item {
//    public:
//        Trie* root;
//        string val;
//        bool isWord;
//        Item(): val(""), isWord(false), root(NULL) {};
//    };
    int _len = LEN;
    Trie* _hash = NULL;
    string _path = "";
    int _maxSize = 0;
    int _maxCount = 0;  ///frequency counting
    string _maxCountWord = "";
    int _size = 0;
    int _keySize = 0;
public:
    Hash(string inputFilePath);
    void init();
    int hash(string& word);
    bool search(string word);
    void insert(string word);
    void remove(string word);
    void removeAll(string removalFilePath);
    void fileCheck(string filePath);
    void resetFrequency();
//
    void clear();
    int countKey();
    int getMaxSize();
//
//
//    bool empty();
//    void removeAll(string path);

    ~Hash() {
        clear();
    };
};

#endif /* Hash_hpp */
