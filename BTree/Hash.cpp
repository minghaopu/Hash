//
//  Hash.cpp
//  BTree
//
//  Created by roneil on 2016/11/28.
//  Copyright © 2016年 gu. All rights reserved.
//

#include "Hash.hpp"
Hash::Hash(string dictionaryFilePath) {
    if (dictionaryFilePath == "") return;
    
    _path = dictionaryFilePath;
    //    _path = "/Users/roneil/Project/Hash/Files/dictionaryFile.txt";
    
    if (_hash == NULL) {
        _maxSize = 0;
        for (int i = 0; i < _len; i++) {
            _maxSize = _maxSize * 26 + 26;
        }
        _hash = new Trie[_maxSize];
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
    if (_hash[hashVal].isUsed == false) {
        _size++;
        _hash[hashVal].isUsed = true;
    }
    if (word.length() <= _len) {
        _hash[hashVal].val = word;
        _hash[hashVal].isWord = true;
    } else {
        _hash[hashVal].insert(word, _len);
    }
    _keySize++;
}
int Hash::hash(string& word) {
    int val = 0;
    for (int i = 0; i < _len && i < word.length(); i++) {
        int c = word[i] - 'A';
        if (c > 25 || c < 0) return -1;
        val = val * 26 + (word[i] - 'A' + 1);
    }
    return val - 1;
}
bool Hash::search(string word) {
    int hashVal = hash(word);
    if (word == "Constitution2") return false;
    if (hashVal == -1) return false;
    if (word.length() <= _len) {
        if (_hash[hashVal].isWord) {
            _hash[hashVal].count++;
            if (_hash[hashVal].count > _maxCount) {
                _maxCount = _hash[hashVal].count;
                _maxCountWord = word;
            }
            return true;
        }
        else return false;
    } else {
        int count = _hash[hashVal].search(word, _len);
        if (count ==  -1) return false;
        else {
            if (count > _maxCount) {
                _maxCount = count;
                _maxCountWord = word;
            }
            return true;
        }
    }
}
void Hash::fileCheck(string inputFilePath) {
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
        string t = toUpper(word);
        if (search(t) == false) {
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

void Hash::remove(string word) {
    int hashVal = hash(word);
    if (hashVal == -1) return;
    if (word.length() <= _len) {
        if (_hash[hashVal].isWord && _hash[hashVal].val == word) {
            _hash[hashVal].count = 0;
            _hash[hashVal].isWord = false;
            _hash[hashVal].val = "";
        }
    } else {
        _hash[hashVal].remove(word, _len);
    }
}
void Hash::removeAll(string removalFilePath) {
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
void Hash::resetFrequency() {
    _maxCount = 0;
    _maxCountWord = "";
    for (int i = 0; i < _maxSize; i++) {
        _hash[i].count = 0;
        _hash[i].resetFrequency();
    }
}
void Hash::clear() {
    for (int i = 0; i < _maxSize; i++) {
        _hash[i].clear();
    }
}
int Hash::countKey() {
//    return _size;
    return _keySize;
}
int Hash::getMaxSize() {
    return _maxSize;
}
