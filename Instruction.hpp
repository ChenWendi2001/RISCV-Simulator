//
// Created by 12779 on 2020-07-07.
//

#ifndef RISCV_SIMULATOR_INSTRUCTION_HPP
#define RISCV_SIMULATOR_INSTRUCTION_HPP

#include "COMMON.h"
#include <iostream>
#include <iomanip>
struct Instruction{
    enum type{R , I , S , SB , U , UJ };

    unsigned int opcode, rd, funct3, rs1, rs2, funct7;
    Imm imm;
    type t;

    unsigned int getDig(unsigned int x,unsigned int start,unsigned int end){
        return (x>>start) & ((1<<(end-start+1))-1);
    }

    unsigned int expend(int flag,int index){
        return flag?(0xffffffff)<<index:0;
    }
};

struct InstructionR : Instruction{
    InstructionR(const unsigned int& x ){
        opcode = getDig(x,0,6);
        rd = getDig(x,7,11);
        funct3 = getDig(x,12,14);
        rs1 = getDig(x,15,19);
        rs2 = getDig(x,20,24);
        funct7 = getDig(x,25,31);
        t = R;
    }
};

struct InstructionI : Instruction{
    InstructionI(const unsigned int& x ){
        opcode = getDig(x,0,6);
        rd = getDig(x,7,11);
        funct3 = getDig(x,12,14);
        rs1 = getDig(x,15,19);
        imm = getDig(x,20,31)|expend(getDig(x,31,31),11);
        t = I;
        if(funct3==0b001||funct3==0b101){
            imm=0;
            t = R;
            rs2 = getDig(x,20,24);
            funct7 = getDig(x,25,31);
        }

#ifdef Debug
        else
            std::clog<<"imm = 0x"<<imm<<std::endl;
#endif
    }
};

struct InstructionS : Instruction{
    InstructionS(const unsigned int& x ){
        opcode = getDig(x,0,6);
        imm = getDig(x,7,11);
        funct3 = getDig(x,12,14);
        rs1 = getDig(x,15,19);
        rs2 = getDig(x,20,24);
        imm+= getDig(x,25,31)<<5;
        imm |= expend(getDig(x,31,31),11);
        t = S;
#ifdef Debug

            std::clog<<"imm = 0x"<<imm<<std::endl;
#endif
    }
};

struct InstructionSB : Instruction{
    InstructionSB(const unsigned int& x ){
        opcode = getDig(x,0,6);
        imm = getDig(x,8,11)<<1;
        funct3 = getDig(x,12,14);
        rs1 = getDig(x,15,19);
        rs2 = getDig(x,20,24);
        imm+= (getDig(x,25,30)<<5)
              + (getDig(x,7,7)<<11)
              + (getDig(x,31,31)<<12);
        imm |= expend(getDig(x,31,31),12);
        t = SB;
#ifdef Debug

            std::clog<<"imm = 0x"<<imm<<std::endl;
#endif
    }
};

struct InstructionU : Instruction{
    InstructionU(const unsigned int& x ){
        opcode = getDig(x,0,6);
        rd = getDig(x,7,11);
        imm = getDig(x,12,31)<<12;
        t = U;
#ifdef Debug

            std::clog<<"imm = 0x"<<imm<<std::endl;
#endif
    }
};

struct InstructionUJ : Instruction{
    InstructionUJ(const unsigned int& x ){
        opcode = getDig(x,0,6);
        rd = getDig(x,7,11);
        imm = getDig(x,21,30)<<1;
        imm+= (getDig(x,20,20)<<11)
              + (getDig(x,12,19)<<12)
              + (getDig(x,31,31)<<20);
        imm|=expend(getDig(x,31,31),20);
        t = UJ;
#ifdef Debug

            std::clog<<"imm = 0x"<<imm<<std::endl;
#endif
    }
};


#endif //RISCV_SIMULATOR_INSTRUCTION_HPP
