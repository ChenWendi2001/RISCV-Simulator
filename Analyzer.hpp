//
// Created by 12779 on 2020-07-08.
//

#ifndef RISCV_SIMULATOR_ANALYZER_HPP
#define RISCV_SIMULATOR_ANALYZER_HPP

#include "COMMON.h"
#include "Memory.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

class Analyzer{
public:
    void analyze(std::istream& in,Memory & mem){
        std::string str;
        unsigned addr;
        while(in>>str){
            if(str[0]=='@'){
                addr = strtol(str.c_str()+1,NULL,16);
            }
            else{
                mem[addr++] = strtol(str.c_str(), NULL, 16);
            }
        }
    }
};

#endif //RISCV_SIMULATOR_ANALYZER_HPP
