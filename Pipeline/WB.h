//
// Created by 12779 on 2020-07-12.
//

#ifndef RISCV_SIMULATOR_WB_H
#define RISCV_SIMULATOR_WB_H
#include "../Thread.h"
class Thread;

class Writer{
    Thread * thread;
public:
    Writer(Thread* th);
    void tick();
};
#endif //RISCV_SIMULATOR_WB_H
