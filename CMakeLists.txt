cmake_minimum_required(VERSION 3.10)
project(RISCV_Simulator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++11 -g")

add_executable(code main.cpp Register.hpp COMMON.h Instruction.hpp Memory.hpp Analyzer.hpp PCounter.hpp Thread.h Thread.cpp Pipeline/IF.h Pipeline/IF.cpp Pipeline/ID.h Pipeline/ID.cpp Pipeline/EX.h Pipeline/EX.cpp Pipeline/MEM.h Pipeline/MEM.cpp Pipeline/WB.h Pipeline/WB.cpp Predictor.hpp)