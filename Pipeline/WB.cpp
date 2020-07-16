//
// Created by 12779 on 2020-07-12.
//
#include "WB.h"

Writer::Writer(Thread* th):thread(th){}
void Writer:: tick(){
    if(!thread->e->pc.empty()) thread->PC->write(thread->e->pc.front()),thread->e->pc.pop();
    /*
    if(!thread->e->ifJump){
        thread->PC->write(thread->PC->readNext()+4);
    }
    thread->e->ifJump=false;
     */
    if(!thread->e->rd.empty()) thread->r.write(rd,thread->e->rd.front()),thread->Reg.erase(rd),thread->e->rd.pop();
    if(!thread->m->rd.empty()) thread->r.write(rd,thread->m->rd.front()),thread->Reg.erase(rd),thread->m->rd.pop();

}