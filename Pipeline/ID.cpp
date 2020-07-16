//
// Created by 12779 on 2020-07-12.
//
# include "ID.h"

Decoder::Decoder(Thread* th):thread(th),instruction(NULL){}

void Decoder::flush() {if(instruction) delete instruction;instruction=NULL;}

Decoder::~Decoder(){if(instruction) delete instruction;}

void Decoder::getAddr(unsigned int x) {
    addr = x;
}

bool Decoder::tick(){
    if(instruction) delete instruction,instruction=NULL;
    inst = thread->f->getIns();
    if(inst==0)return false;
    getAddr(thread->f->addr);
    switch (inst & 0b1111111){
        case 0b0110011:
            instruction = new InstructionR(inst);
            break;
        case 0b0010011:
            instruction = new InstructionI(inst);
            break;
        case 0b0100011:
            instruction = new InstructionS(inst);
            break;
        case 0b1100011:
            instruction = new InstructionSB(inst);
            break;
        case 0b0000011:
            instruction = new InstructionI(inst);
            break;
        case 0b1100111:
            instruction = new InstructionI(inst);
            break;
        case 0b1101111:
            instruction = new InstructionUJ(inst);
            break;
        case 0b0110111:
            instruction = new InstructionU(inst);
            break;
        case 0b0010111:
            instruction = new InstructionU(inst);
            break;
    }
    instruction->addr = addr;
    thread->e->get();
    thread->m->get();

    if(instruction->t == Instruction::type::SB) {
        if (instruction->funct3 == 0b000) {//BEQ
            pc = thread->PC->read() + instruction->imm;
            origin = thread->PC->read();
        } else if (instruction->funct3 == 0b001) {//BNE
            pc = thread->PC->read() + instruction->imm;
            origin = thread->PC->read();
        } else if (instruction->funct3 == 0b100) {//BLT
            pc = thread->PC->read() + instruction->imm;
            origin = thread->PC->read();
        } else if (instruction->funct3 == 0b101) {//BGE
            pc = thread->PC->read() + instruction->imm;
            origin = thread->PC->read();
        } else if (instruction->funct3 == 0b110) {//BLTU
            pc = thread->PC->read() + instruction->imm;
            origin = thread->PC->read();
        } else if (instruction->funct3 == 0b111) {//BGEU
            pc = thread->PC->read() + instruction->imm;
            origin = thread->PC->read();
        }
        return true;
    }
    return false;
}