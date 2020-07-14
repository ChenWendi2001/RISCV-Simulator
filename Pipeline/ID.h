
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

public:
    Instruction* instruction;

    Decoder(Thread* th);

    ~Decoder();

    void tick();
};
#endif //RISCV_SIMULATOR_ID_H
