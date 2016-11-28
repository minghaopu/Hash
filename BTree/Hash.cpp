//
//  Hash.cpp
//  BTree
//
//  Created by roneil on 2016/11/28.
//  Copyright © 2016年 gu. All rights reserved.
//

#include "Hash.hpp"
Hash::Hash(string dictionaryFilePath) {
//    if (dictionaryFilePath == "") return;
    
//    _path = dictionaryFilePath;
    _path = "/Users/roneil/Project/zlP3/Project3/BTree/Files/dictionaryFile.txt";

    if (_hash == NULL) {
        _maxSize = 0;
        for (int i = 0; i < _len; i++) {
            _maxSize = _maxSize * 26 + 26;
        }
        _hash = new Item[_maxSize];
    }
    init();
}
void Hash::init() {
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
void Hash::insert(string word) {
    int hashVal = hash(word);
    if (word.length() <= _len) {
        _hash[hashVal].val = word;
        _hash[hashVal].isWord = true;
    } else {
        if (_hash[hashVal].root == NULL) _hash[hashVal].root = new Trie();
        _hash[hashVal].root->insert(word, _len);
    }
    
}
int Hash::hash(string word) {
    int val = 0;
    for (int i = 0; i < _len && i < word.length(); i++) {
        val = val * 26 + (word[i] - 'A' + 1);
    }
    return val - 1;
}
//bool Hash::search(string word) {
//    
//}
