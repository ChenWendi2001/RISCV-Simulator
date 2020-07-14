//
// Created by 12779 on 2020-07-12.
//
#include "EX.h"

Executor::Executor(Thread* th):thread(th){ifJump=false;}

void Executor:: tick(){
    inst = thread->d->instruction;
    if(inst->t == Instruction::type::R){
        if(inst->funct7==0b0000000&&inst->funct3==0b000){//ADD
            rd.push(thread->r.read(inst->rs1)+thread->r.read(inst->rs2));
#ifdef Debug
            std::clog<<"ADD"<<std::endl;
#endif
        }
        else if(inst->funct7==0b0100000&&inst->funct3==0b000){//SUB
            rd.push(thread->r.read(inst->rs1)-thread->r.read(inst->rs2));
#ifdef Debug
            std::clog<<"SUB"<<std::endl;
#endif
        }
        else if(inst->opcode==0b0110011&&inst->funct7==0b0000000&&inst->funct3==0b001){//SLL
            rd.push(thread->r.read(inst->rs1)<<(thread->r.read(inst->rs2)&(unsigned)0x1f));
#ifdef Debug
            std::clog<<"SLL"<<std::endl;
#endif
        }
        else if(inst->funct7==0b0000000&&inst->funct3==0b010){//SLT
            rd.push((sImm)thread->r.read(inst->rs1)<(sImm)thread->r.read(inst->rs2)?1:0);
#ifdef Debug
            std::clog<<"SLT"<<std::endl;
#endif
        }
        else if(inst->funct7==0b0000000&&inst->funct3==0b011){//SLTU
            rd.push(thread->r.read(inst->rs1)<thread->r.read(inst->rs2)?1:0);
#ifdef Debug
            std::clog<<"SLTU"<<std::endl;
#endif
        }
        else if(inst->funct7==0b0000000&&inst->funct3==0b100){//XOR
            rd.push(thread->r.read(inst->rs1)^thread->r.read(inst->rs2));
#ifdef Debug
            std::clog<<"XOR"<<std::endl;
#endif
        }
        else if(inst->opcode==0b0110011&&inst->funct7==0b0000000&&inst->funct3==0b101){//SRL
            rd.push(thread->r.read(inst->rs1)>>(thread->r.read(inst->rs2)&(unsigned)0x1f));
#ifdef Debug
            std::clog<<"SRL"<<std::endl;
#endif
        }
        else if(inst->opcode==0b0110011&&inst->funct7==0b0100000&&inst->funct3==0b101){//SRA
            rd.push((sImm)thread->r.read(inst->rs1)>>(thread->r.read(inst->rs2)&(unsigned)0x1f));
#ifdef Debug
            std::clog<<"SRA"<<std::endl;
#endif
        }
        else if(inst->funct7==0b0000000&&inst->funct3==0b110){//OR
            rd.push(thread->r.read(inst->rs1)|(thread->r.read(inst->rs2)));
#ifdef Debug
            std::clog<<"OR"<<std::endl;
#endif
        }
        else if(inst->funct7==0b0000000&&inst->funct3==0b111){//AND
            rd.push(thread->r.read(inst->rs1)&(thread->r.read(inst->rs2)));
#ifdef Debug
            std::clog<<"AND"<<std::endl;
#endif
        }
        else if(inst->opcode==0b0010011&&inst->funct3==0b001){//SLLI
            rd.push(thread->r.read(inst->rs1)<<(inst->rs2 & (unsigned)0x1f));
#ifdef Debug
            std::clog<<"SLLI"<<std::endl;
#endif
        }
        else if(inst->opcode==0b0010011&&inst->funct7==0b0000000&&inst->funct3==0b101){//SRLI
            rd.push(thread->r.read(inst->rs1)>>(inst->rs2 & (unsigned)0x1f));
#ifdef Debug
            std::clog<<"SRLI"<<std::endl;
#endif
        }
        else if(inst->opcode==0b0010011&&inst->funct7==0b0100000&&inst->funct3==0b101){//SRAI
            rd.push((sImm)thread->r.read(inst->rs1)>>(inst->rs2 & (unsigned)0x1f));
#ifdef Debug
            std::clog<<"SRAI"<<std::endl;
#endif
        }
    }
    else if(inst->t == Instruction::type::I && inst->opcode==0b0010011){
        if(inst->funct3 == 0b000){//ADDI
            rd.push(thread->r.read(inst->rs1)+(inst->imm));
#ifdef Debug
            std::clog<<"ADDI"<<std::endl;
#endif
        }
        else if(inst->funct3 == 0b010){//STLI
            rd.push((sImm)thread->r.read(inst->rs1)<(sImm)(inst->imm)?1:0);
#ifdef Debug
            std::clog<<"STLI"<<std::endl;
#endif
        }
        else if(inst->funct3 == 0b011){//STLIU
            rd.push(thread->r.read(inst->rs1)<(inst->imm)?1:0);
#ifdef Debug
            std::clog<<"STLTU"<<std::endl;
#endif
        }
        else if(inst->funct3 == 0b100){//XORI
            rd.push(thread->r.read(inst->rs1)^(inst->imm));
#ifdef Debug
            std::clog<<"XORI"<<std::endl;
#endif
        }
        else if(inst->funct3 == 0b110){//ORI
            rd.push(thread->r.read(inst->rs1)|(inst->imm));
#ifdef Debug
            std::clog<<"ORI"<<std::endl;
#endif
        }
        else if(inst->funct3 == 0b111){//ANDI
            rd.push(thread->r.read(inst->rs1)&(inst->imm));
#ifdef Debug
            std::clog<<"ADDI"<<std::endl;
#endif
        }
    }
    else if(inst->t == Instruction::type::SB){
        if(inst->funct3 == 0b000){//BEQ
            if(thread->r.read(inst->rs1) == thread->r.read(inst->rs2)){
                pc.push(thread->PC->read()+inst->imm);
#ifdef Debug
                std::clog<<"BEQ"<<std::endl;
#endif
                ifJump=true;
            }
        }
        else if(inst->funct3 == 0b001){//BNE
            if(thread->r.read(inst->rs1) != thread->r.read(inst->rs2)){
                pc.push(thread->PC->read()+inst->imm);
#ifdef Debug
                std::clog<<"BNE"<<std::endl;
#endif
                ifJump=true;
            }
        }
        else if(inst->funct3 == 0b100){//BLT
            if(((sImm)thread->r.read(inst->rs1)) < ((sImm)thread->r.read(inst->rs2))){
                pc.push(thread->PC->read()+inst->imm);
#ifdef Debug
                std::clog<<"BLT"<<std::endl;
#endif
                ifJump=true;
            }
        }
        else if(inst->funct3 == 0b101){//BGE
            if(((sImm)thread->r.read(inst->rs1)) >= ((sImm)thread->r.read(inst->rs2))){
                pc.push(thread->PC->read()+inst->imm);
#ifdef Debug
                std::clog<<"BGE"<<std::endl;
#endif
                ifJump=true;
            }
        }
        else if(inst->funct3 == 0b110){//BLTU
            if(thread->r.read(inst->rs1) < thread->r.read(inst->rs2)){
                pc.push(thread->PC->read()+inst->imm);
#ifdef Debug
                std::clog<<"BLTU"<<std::endl;
#endif
                ifJump=true;
            }
        }
        else if(inst->funct3 == 0b111){//BGEU
            if(thread->r.read(inst->rs1) >= thread->r.read(inst->rs2)){
                pc.push(thread->PC->read()+inst->imm);
#ifdef Debug
                std::clog<<"BGEU"<<std::endl;
#endif
                ifJump=true;
            }
        }

    }
    else if(inst->t == Instruction::type::UJ){//JAL
        rd.push(thread->PC->read()+4);
        pc.push(thread->PC->read()+inst->imm);
        ifJump=true;
#ifdef Debug
        std::clog<<"JAL"<<std::endl;
#endif
    }
    else if(inst->t == Instruction::type::I && inst->opcode == 0b1100111){//JALR
        rd.push(thread->PC->read()+4);
        pc.push((thread->r.read(inst->rs1) + inst->imm) & (~0x1));
        ifJump=true;
#ifdef Debug
        std::clog<<"JALR"<<std::endl;
#endif
    }
    else if(inst->opcode == 0b0110111){//LUI
        rd.push(inst->imm);
#ifdef Debug
        std::clog<<"LUI"<<std::endl;
#endif
    }
    else if(inst->opcode == 0b0010111){//AUIPC
        rd.push(thread->PC->read()+inst->imm);
#ifdef Debug
        std::clog<<"AUIPC"<<std::endl;
#endif
    }
}
