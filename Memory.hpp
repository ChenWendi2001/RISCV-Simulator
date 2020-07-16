//
// Created by 12779 on 2020-07-07.
//

#ifndef RISCV_SIMULATOR_MEMORY_HPP
#define RISCV_SIMULATOR_MEMORY_HPP

#include "COMMON.h"
#include <cstring>

struct Memory{ // A Memory Simulator
    unsigned char mem[0x40000];

    Memory(){
        memset(mem,0,sizeof(mem));
    }

    void write(unsigned int addr,Imm imm){
        *(Imm*)(mem+addr) = imm;
    }

    Imm read(unsigned int addr){
        return *(Imm*)(mem+addr);
    }

    void writeShort(unsigned int addr,Imm imm){
        *(short*)(mem+addr) = imm;
    }

    short readShort(unsigned int addr){
        return *(short*)(mem+addr);
    }

    unsigned char & operator[](unsigned int n){
        return mem[n];
    }

};
#endif //RISCV_SIMULATOR_MEMORY_HPP
