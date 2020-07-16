//
// Created by 12779 on 2020-07-12.
//

#ifndef RISCV_SIMULATOR_IF_H
#define RISCV_SIMULATOR_IF_H

#include "../Thread.h"
#include "../Instruction.hpp"

class Thread;

class Fetcher{

    Thread* thread;



    Imm instruction;

public:

    Fetcher(Thread *th);

    void tick();

    Imm getIns();

    Imm addr;
};

#endif //RISCV_SIMULATOR_IF_H
