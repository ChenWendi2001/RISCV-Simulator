//
// Created by 12779 on 2020-07-12.
//

#ifndef RISCV_SIMULATOR_MEM_H
#define RISCV_SIMULATOR_MEM_H
#include "../Thread.h"
#include <queue>
#include "../Instruction.hpp"
class Thread;

class MemAccessor{

    Thread* thread;

public:
    std::queue<Imm> rd;

    MemAccessor(Thread* th);

    Instruction* inst;

    Instruction instTemp;

    void tick();

    void get();
};
#endif //RISCV_SIMULATOR_MEM_H
