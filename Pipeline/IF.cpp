//
// Created by 12779 on 2020-07-12.
//
#include "IF.h"
#include <iomanip>
Fetcher::Fetcher(Thread *th){thread = th;}

void Fetcher::tick(){
    instruction = thread->mem.read(thread->PC->read());
#ifdef Debug
    std::clog<<"---------------------------------"<<std::endl;
    std::clog<<"PC = 0x"<<std::hex<<thread->PC->read()<<std::endl;
#endif
}

Imm Fetcher::getIns(){return instruction;}