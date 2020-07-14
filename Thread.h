//
// Created by 12779 on 2020-07-12.
//

#ifndef RISCV_SIMULATOR_THREAD_H
#define RISCV_SIMULATOR_THREAD_H
#include <iostream>
#include <fstream>
#include "COMMON.h"
#include "PCounter.hpp"
#include "Analyzer.hpp"
#include "Register.hpp"
#include "Pipeline/IF.h"
#include "Pipeline/ID.h"
#include "Pipeline/EX.h"
#include "Pipeline/MEM.h"
#include "Pipeline/WB.h"

class Fetcher;
class Decoder;
class Executor;
class MemAccessor;
class Writer;

class Thread{
    std::ifstream in;
    Analyzer ana; // a parser
public:
    Memory mem;
    Register r;
    Fetcher * f;
    Decoder * d;
    Executor * e;
    MemAccessor *m;
    Writer *w;
    PCounter* PC;

    Thread();
    Thread(const char* path);
    ~Thread();
    bool tick();
};
#endif //RISCV_SIMULATOR_THREAD_H
