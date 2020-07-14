//
// Created by 12779 on 2020-07-12.
//
# include "ID.h"

Decoder::Decoder(Thread* th):thread(th),instruction(NULL){}

Decoder::~Decoder(){if(instruction) delete instruction;}

void Decoder::tick(){
    if(instruction) delete instruction;
    inst = thread->f->getIns();
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
}