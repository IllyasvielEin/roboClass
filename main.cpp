//
// Created by Illyasviel on 2021/9/27.
//
//#include "task1.h"
//#include "task2.h"
#include "task3.h"

int main() {
    behavior p1;
    string s;
    getline(cin, s);
    p1.parseLine(s);
//    p1.show();
    p1.getMySightAng();
    return 0;
}
