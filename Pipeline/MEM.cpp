//
// Created by 12779 on 2020-07-12.
//
#include "MEM.h"

void MemAccessor::get(){
    if(thread->e->inst){
        instTemp = *thread->e->inst;
        inst = &instTemp;
    }
    else{
        inst = NULL;
    }
}

MemAccessor::MemAccessor(Thread* th):thread(th){ inst = NULL;}
void MemAccessor:: tick(){
    if(inst==NULL) return;
    if(inst->opcode == 0b0000011){
        unsigned int addr =  thread->r.read(inst->rs1) + inst->imm;
        switch(inst->funct3){
            case 0b000://LB
                rd.push((char)thread->mem[addr]);
                thread->w->rd = inst->rd;
                thread->Reg.insert(inst->rd);
#ifdef Debug
                std::clog<<"LB"<<std::endl;
#endif
                break;
            case 0b001://LH
                rd.push((short)thread->mem.readShort(addr));
                thread->w->rd = inst->rd;
                thread->Reg.insert(inst->rd);
#ifdef Debug
                std::clog<<"LH"<<std::endl;
#endif
                break;
            case 0b010://LW
                rd.push(thread->mem.read(addr));
                thread->w->rd = inst->rd;
                thread->Reg.insert(inst->rd);
#ifdef Debug
                std::clog<<"LW"<<std::endl;
#endif
                break;
            case 0b100://LBU
                rd.push(thread->mem[addr]);
                thread->w->rd = inst->rd;
                thread->Reg.insert(inst->rd);
#ifdef Debug
                std::clog<<"LBU"<<std::endl;
#endif
                break;
            case 0b101://LHU
                rd.push(thread->mem.readShort(addr));
                thread->w->rd = inst->rd;
                thread->Reg.insert(inst->rd);
#ifdef Debug
                std::clog<<"LHU"<<std::endl;
#endif
                break;
        }
    }
    else if(inst->opcode == 0b0100011){
        unsigned int addr =  thread->r.read(inst->rs1)+inst->imm ;
        switch(inst->funct3){
            case 0b000://SB
                thread->mem[addr] = thread->r.read(inst->rs2);
#ifdef Debug
                std::clog<<"SB"<<std::endl;
#endif
                break;
            case 0b001://SH
                thread->mem.writeShort(addr,thread->r.read(inst->rs2));
#ifdef Debug
                std::clog<<"SH"<<std::endl;
#endif
                break;
            case 0b010://SW
                thread->mem.write(addr,thread->r.read(inst->rs2));
#ifdef Debug
                std::clog<<"SW"<<std::endl;
#endif
                break;
        }
    }
}