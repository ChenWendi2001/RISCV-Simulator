//
// Created by 12779 on 2020-07-08.
//

#ifndef RISCV_SIMULATOR_PCOUNTER_HPP
#define RISCV_SIMULATOR_PCOUNTER_HPP

#include "COMMON.h"

class PCounter{ // A Program Counter
    Imm prev,next;
public:
    PCounter():prev(0),next(0){}

    Imm read(){return prev;}
    void write(Imm imm){next = imm;}

    Imm readNext(){return next;}
    void tick(){prev = next;}

};

#endif //RISCV_SIMULATOR_PCOUNTER_HPP
