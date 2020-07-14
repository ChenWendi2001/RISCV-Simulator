//
// Created by 12779 on 2020-07-12.
//

#ifndef RISCV_SIMULATOR_MEM_H
#define RISCV_SIMULATOR_MEM_H
#include "../Thread.h"
#include <queue>

class Thread;

class MemAccessor{

    Thread* thread;

public:
    std::queue<Imm> rd;

    MemAccessor(Thread* th);

    void tick();
};
#endif //RISCV_SIMULATOR_MEM_H
