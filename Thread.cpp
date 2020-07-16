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

bool Thread::serial(){

    //std::clog<<"---------"<<std::hex<<mem.read(0x8)<<std::endl;
    PC->tick();
    r.tick();
    f->tick();
    d->tick();
    e->get();
    e->tick();
    m->tick();
    w->tick();
    if(f->getIns() == 0xff00513){
        std::cout<<(r.read(e->inst->rd)&255u);
        return true;
    }
    return false;
}

bool Thread::parallel() {

    w->tick();
    r.tick();

    m->tick();

    //e->get();

    if(e->inst && (Reg.count(e->inst->rs1)||Reg.count(e->inst->rs2))){//data hazard
        w->tick();
        r.tick();
    }

    e->tick();

    if(e->ifJump){//control hazard / Stall
        w->tick();
        r.tick();

        w->tick();
        r.tick();

        e->flush();
        d->flush();

        PC->write(PC->readNext()-4);
        PC->tick();
        f->tick();

        return false;
    }

    if(e->inst && e->inst->inst == 0xff00513){ //end

        w->tick();

        //m->tick();
        w->tick();

        std::cout<<(r.read(e->inst->rd)&255u);
        return true;
    }

    d->tick();

    PC->tick();
    f->tick();
    return false;
}

bool Thread::parallel_with_predictor() {

    w->tick();
    r.tick();

    m->tick();

    //e->get();

    if(e->inst && (Reg.count(e->inst->rs1)||Reg.count(e->inst->rs2))){//data hazard
        w->tick();
        r.tick();
    }

    e->tick();

    if(e->ifJump && e->inst &&(e->inst->t == Instruction::type::UJ||e->inst->t == Instruction::type::I)){//control hazard / Stall
        w->tick();
        r.tick();

        w->tick();
        r.tick();

        e->flush();
        d->flush();

        PC->write(PC->readNext()-4);
        PC->tick();
        f->tick();

        return false;
    }

    bool flag;

    if(e->inst && e->inst->t && e->inst->t == Instruction::type::SB){
        pre.countAll++;
        flag = pre.ifJump(e->inst->addr);
    }

    if(e->ifJump &&e->inst&&(!flag)){//control hazard / Stall
        pre.change(e->inst->addr,1);
        w->tick();
        r.tick();

        w->tick();
        r.tick();

        e->flush();
        d->flush();

        PC->write(PC->readNext()-4);
        PC->tick();
        f->tick();

        return false;
    }
    else if((!e->ifJump)&&e->inst && e->inst->t == Instruction::type::SB &&(!flag)){
        pre.change(e->inst->addr,0);
    }
    else if((e->ifJump)&&e->inst && e->inst->t == Instruction::type::SB &&(flag)){
        e->pc.pop();
        pre.change(e->inst->addr,1);
    }
    else if((!e->ifJump)&&e->inst && e->inst->t == Instruction::type::SB &&(flag)){
        pre.change(e->inst->addr,0);
        PC->reGet();
        f->tick();
    }

    if(e->inst && e->inst->inst == 0xff00513){ //end

        w->tick();

        //m->tick();
        w->tick();

        std::cout<<(r.read(e->inst->rd)&255u)<<std::endl;
        return true;
    }

    if(d->tick()&&pre.ifJump(d->instruction->addr)){
        PC->write(d->pc);
        PC->origin=d->origin;
    }

    PC->tick();
    f->tick();
    return false;
}