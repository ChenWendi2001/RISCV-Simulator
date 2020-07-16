
//
// Created by 12779 on 2020-07-12.
//

#ifndef RISCV_SIMULATOR_ID_H
#define RISCV_SIMULATOR_ID_H
#include "../Instruction.hpp"
#include "../Thread.h"

class Thread;

class Decoder{

    Thread* thread;

    Imm inst;

    unsigned int addr;

public:
    Imm pc;

    Imm origin;

    Instruction* instruction;

    Decoder(Thread* th);

    ~Decoder();

    bool tick();

    void flush();

    void getAddr(unsigned int x);
};
#endif //RISCV_SIMULATOR_ID_H
