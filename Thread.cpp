//
// Created by 12779 on 2020-07-12.
//

#include "Thread.h"
#include <iostream>

Thread::Thread() {
    ana.analyze(std::cin,mem);
    PC = new PCounter;
    f = new Fetcher(this);
    d = new Decoder(this);
    e = new Executor(this);
    m = new MemAccessor(this);
    w = new Writer(this);
}

Thread::Thread(const char* path){
    in.open(path);
    ana.analyze(in,mem);
    PC = new PCounter;
    f = new Fetcher(this);
    d = new Decoder(this);
    e = new Executor(this);
    m = new MemAccessor(this);
    w = new Writer(this);
}

Thread::~Thread(){
    in.close();
    delete PC;
    delete f;
    delete d;
    delete e;
    delete m;
    delete w;
}

bool Thread::tick(){

    //std::clog<<"---------"<<std::hex<<mem.read(0x8)<<std::endl;
    PC->tick();
    r.tick();
    f->tick();
    d->tick();
    e->tick();
    m->tick();
    w->tick();
    if(f->getIns() == 0xff00513){
        std::cout<<(r.read(e->inst->rd)&255u);
        return true;
    }
    return false;
}

