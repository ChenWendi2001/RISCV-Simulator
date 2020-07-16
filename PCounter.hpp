//
// Created by 12779 on 2020-07-08.
//

#ifndef RISCV_SIMULATOR_PCOUNTER_HPP
#define RISCV_SIMULATOR_PCOUNTER_HPP

#include "COMMON.h"

class PCounter{ // A Program Counter
    Imm prev,next;

public:
    Imm origin;

    PCounter():prev(0),next(0){}

    Imm read(){return prev;}
    void write(Imm imm){next = imm;}

    Imm readNext(){return next;}

    void tick(){prev = next; next = prev+4;}

    void reGet(){prev = origin;next = prev+4;}
};

#endif //RISCV_SIMULATOR_PCOUNTER_HPP
