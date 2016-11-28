//
//  main.cpp
//  BTree
//
//  Created by fanision on 11/1/16.
//  Copyright © 2016 fanision. All rights reserved.
//


#include "List.hpp"
#include "BTree.hpp"
#include "Hash.hpp"
int main(int argc, const char * argv[]) {
//    string inputFilePath = argv[1];
//    string dictionaryFilePath = argv[2];
//    string removalFilePath = argv[3];
//
//    BTree tree(dictionaryFilePath);
//    
//
//    cout<<"---------------- B Tree ----------------"<<endl;
//    if (tree.empty()) {
//        cout<<"The dictionary file path is wrong"<<endl;
//    } else{
//        cout<<"\n---------------- file check before removal with M=4 ----------------"<<endl;
//        tree.fileCheck(inputFilePath);
//        tree.setChildrenNumber(10);
//        cout<<"\n----- file check before removal with M=10 which is my choice after experiment -----"<<endl;
//        tree.fileCheck(inputFilePath);
//        tree.setChildrenNumber(50);
//        cout<<"\n----- file check before removal with M=50(experimental value)  -----"<<endl;
//        tree.fileCheck(inputFilePath);
//        tree.setChildrenNumber(100);
//        cout<<"\n----- file check before removal with M=100(experimental value -----"<<endl;
//        tree.fileCheck(inputFilePath);
//        tree.removeAll(removalFilePath);
//        cout<<"\n---------------- file check after removal ----------------"<<endl;
//        tree.fileCheck(inputFilePath);
//    }
//    
//    cout<<"\n\n---------------- link list ----------------\n"<<endl;
//    
//    List list(dictionaryFilePath);
//    if (list.empty()) {
//        cout<<"The dictionary file path is wrong"<<endl;
//    } else{
//        cout<<"\n---------------- file check before removal ----------------"<<endl;
//        list.fileCheck(inputFilePath);
//        list.removeAll(removalFilePath);
//        cout<<"\n---------------- file check after removal ----------------"<<endl;
//        list.fileCheck(inputFilePath);
//    }
    Hash h("");
//    string s[235886];
//    ifstream inputData("/Users/roneil/Project/zlP3/Project3/BTree/Files/dictionaryFile.txt");
//    string content((istreambuf_iterator<char>(inputData)),(istreambuf_iterator<char>()));
//    replace_if(content.begin() , content.end(),
//               [] (const char& c) { return c == '\r' ;},'\n');
//    stringstream ss;
//    
//    string word;
//    int i = 0;
//    if (content != "") {
//        
//        ss.str(content);
//        while (getline(ss, word)) {
//            if (word != "") {
//                s[i++] = toUpper(word);
//            }
//        }
//    }
    return 0;
}
