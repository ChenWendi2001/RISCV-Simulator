//
// Created by 12779 on 2020-07-16.
//

#ifndef RISCV_SIMULATOR_PREDICTOR_HPP
#define RISCV_SIMULATOR_PREDICTOR_HPP

#include <iostream>
#include <cstring>
#include "COMMON.h"

class Predictor{
    unsigned char mem[0x20000];

    int countAcc;
public:
    int countAll;
    Predictor(){
        memset(mem,0,sizeof(mem));
        countAcc = countAll = 0;
    }

    void write(unsigned int addr,unsigned char x){
        mem[addr]=x;
    }

    unsigned char read(unsigned int addr){
        return mem[addr];
    }

    void change(unsigned int addr, bool flag){
        unsigned char temp = read(addr);
        switch (temp) {
            case 0:
                if(flag) {
                    write(addr,1);
                    //countAcc++;
                }
                else {
                    write(addr,0);
                    countAcc++;
                }
                break;
            case 1:
                if(flag) {
                    write(addr,2);
                    //countAcc++;
                }
                else {
                    write(addr,0);
                    countAcc++;
                }
                break;
            case 2:
                if(flag) {
                    write(addr,3);
                    countAcc++;
                }
                else {
                    write(addr,1);
                    //countAcc++;
                }
                break;
            case 3:
                if(flag) {
                    write(addr,3);
                    countAcc++;
                }
                else {
                    write(addr,2);
                    //countAcc++;
                }
                break;
        }
    }

    bool ifJump(unsigned int addr){
        Imm temp = read(addr);
        return !(temp == 0 || temp == 1);
    }

    void printAcc(){
        std::cout<<"countAll = "<<countAll<<" countAcc = "<<countAcc<<" Accuracy = "<<double(countAcc)/countAll<<std::endl;
    }

};


#endif //RISCV_SIMULATOR_PREDICTOR_HPP
