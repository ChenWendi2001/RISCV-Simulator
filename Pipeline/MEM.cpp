//
// Created by 12779 on 2020-07-12.
//
#include "MEM.h"

MemAccessor::MemAccessor(Thread* th):thread(th){}
void MemAccessor:: tick(){
    if(thread->e->inst->opcode == 0b0000011){
        unsigned int addr =  thread->r.read(thread->e->inst->rs1) + thread->e->inst->imm;
        switch(thread->e->inst->funct3){
            case 0b000://LB
                rd.push((char)thread->mem[addr]);
                std::clog<<"LB"<<std::endl;
                break;
            case 0b001://LH
                rd.push((short)thread->mem.readShort(addr));
                std::clog<<"LH"<<std::endl;
                break;
            case 0b010://LW
                rd.push(thread->mem.read(addr));
                std::clog<<"LW"<<std::endl;
                break;
            case 0b100://LBU
                rd.push(thread->mem[addr]);
                std::clog<<"LBU"<<std::endl;
                break;
            case 0b101://LHU
                rd.push(thread->mem.readShort(addr));
                std::clog<<"LHU"<<std::endl;
                break;
        }
    }
    else if(thread->e->inst->opcode == 0b0100011){
        unsigned int addr =  thread->r.read(thread->e->inst->rs1)+thread->e->inst->imm ;
        switch(thread->e->inst->funct3){
            case 0b000://SB
                thread->mem[addr] = thread->r.read(thread->e->inst->rs2);
                std::clog<<"SB"<<std::endl;
                break;
            case 0b001://SH
                thread->mem.writeShort(addr,thread->r.read(thread->e->inst->rs2));
                std::clog<<"SH"<<std::endl;
                break;
            case 0b010://SW
                thread->mem.write(addr,thread->r.read(thread->e->inst->rs2));
                std::clog<<"SW"<<std::endl;
                break;
        }
    }
}