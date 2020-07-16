
#include <iostream>
#include "Thread.h"

void serial_test(const char* str){
    Thread *thread = new Thread(str);
    while(true){
        bool flag = thread->serial();
        if(flag) break;
    }
}

void serial_test(){
    Thread *thread = new Thread;
    while(true){
        bool flag = thread->serial();
        if(flag) break;
    }
}

void parallel_test(const char* str){
    Thread *thread = new Thread(str);
    while(true){
        bool flag = thread->parallel();
        if(flag) break;
    }
}

void parallel_test_with_predictor(const char* str){
    Thread *thread = new Thread(str);
    while(true){
        bool flag = thread->parallel_with_predictor();
        if(flag) break;
    }
    thread->pre.printAcc();
}

int main() {
    //serial_test("testcases2/array_test1.data");
    //parallel_test("testcases2/bulgarian.data");
    parallel_test_with_predictor("testcases2/bulgarian.data");
    return 0;
}
