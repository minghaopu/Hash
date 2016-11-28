//
//  Header.h

//
//  Created by fanision on 11/1/16.
//  Copyright © 2016年 fanision. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <stack>
#include <queue>
#include <sstream>
#include <fstream>
using namespace std;
static std::string toUpper(std::string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] =  toupper(s[i]);
    }
    return s;
}

#endif /* Header_h */



