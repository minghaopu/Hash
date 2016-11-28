//
//  List.cpp
//  BTree
//
//  Created by fanision on 11/1/16.
//  Copyright © 2016 fanision. All rights reserved.
//

#include "List.hpp"

List::List(string dictionaryFilePath) {
    ifstream inputData(dictionaryFilePath);
    string content((istreambuf_iterator<char>(inputData)),(istreambuf_iterator<char>()));
    replace_if(content.begin() , content.end(),
               [] (const char& c) { return c == '\r' ;},'\n');
    stringstream ss;
    string word;
    ss.str(content);
    _head = new ListNode("");
    ListNode* p = _head;
    while (getline(ss, word)) {
        if (word != "") {
            
            p->next = new ListNode(toUpper(word));
            p = p->next;
            
            _total++;
        }
    }
    _last = p;
}
bool List::search(string word) {
    ListNode* p = _head->next;
    ListNode* pre = _head;
    while (p) {
        if (p->val == word) {
            pre->next = p->next;
            p->next = _head->next;
            _head->next = p;
            if (pre->next == NULL) {
                _last = pre;
            }
            p->count++;
            if (p->count > _maxCount) {
                _maxCount = p->count;
                _maxCountWord = p->val;
            }
            return true;
        }
        p = p->next;
        pre = pre->next;
    }
    return false;
}
void List::add(string word) {
    _last->next = new ListNode(word);
    _last = _last->next;
    _total++;
}

void List::remove(string word) {
    ListNode* p = _head->next;
    ListNode* pre = _head;
    while (p) {
        if (p->val == word) {
            pre->next = p->next;
            delete p;
            if (pre->next == NULL) {
                _last = pre;
            }
            _total--;
            return;
        }
        p = p->next;
        pre = pre->next;
    }
}
int List::size() {
    return _total;
}
bool List::empty() {
    return _total == 0;
}
void List::fileCheck(string inputFilePath) {
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
        string t =toUpper(word);
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
void List::removeAll(string removalFilePath) {

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
void List::resetFrequency() {
    ListNode* p = _head->next;
    while (p) {
        p->count = 0;
        p = p->next;
    }
}
