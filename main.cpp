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

void test(){
    Thread *thread = new Thread;
    while(true){
        bool flag = thread->tick();
        if(flag) break;
    }
}

int main() {
    test();
    return 0;
}
