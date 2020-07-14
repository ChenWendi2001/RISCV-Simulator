//
// Created by 12779 on 2020-07-07.
//

#ifndef RISCV_SIMULATOR_REGISTER_HPP
#define RISCV_SIMULATOR_REGISTER_HPP

#include "COMMON.h"
#include <cstring>

struct Register{

    Imm prev[32];
    Imm next[32];

    Register(){
        memset(prev,0,sizeof(prev));
        memset(next,0,sizeof(next));
    }

    Imm read(int n){return n? prev[n]:0;}

    void write(int n,Imm x){next[n]= x;}

    void tick(){
        memcpy(prev, next,sizeof(prev));
    }

};
#endif //RISCV_SIMULATOR_REGISTER_HPP
