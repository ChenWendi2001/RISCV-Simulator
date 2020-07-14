#pragma GCC optimize(3,"Ofast","inline")

#include <iostream>
#include "Thread.h"

void test(const char* str){
    Thread *thread = new Thread(str);
    while(true){
        bool flag = thread->tick();
        if(flag) break;
    }
}

int main() {
    test("testcases2/heart.data");
    return 0;
}
