//
// Created by 12779 on 2020-07-12.
//

#ifndef RISCV_SIMULATOR_EX_H
#define RISCV_SIMULATOR_EX_H

#include "../Thread.h"
#include "../Instruction.hpp"
#include "../COMMON.h"
#include <queue>
class Thread;

class Executor{
    Thread* thread;
    Imm addr;
public:
    bool ifJump;
    Instruction instTemp;
    Instruction* inst;
    std::queue<Imm> rd;
    std::queue<Imm> pc;
    Executor(Thread* th);
    void get();
    void tick();
    void flush();
    void getAddr(unsigned int x);
};
#endif //RISCV_SIMULATOR_EX_H
