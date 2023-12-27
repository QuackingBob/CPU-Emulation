cmake_minimum_required(VERSION 3.10)
project(CPUEmulator)

add_library(signals signals.cpp signals.hpp)
add_library(gates gates.cpp gates.hpp)
add_library(switches switches.cpp switches.hpp)
add_library(arithmetics arithmetics.cpp arithmetics.hpp)
add_library(alu alu.cpp alu.hpp
        rom.hpp
        rom.cpp)
add_library(mux mux.cpp mux.hpp)
add_library(mem mem.cpp mem.hpp)
add_library(stats stats.cpp stats.hpp)
add_library(components components.cpp components.hpp
        controller.hpp
        controller.cpp
)
add_library(ram ram.cpp ram.hpp)
add_library(decoder decoder.cpp decoder.hpp)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE signals arithmetics gates alu mux switches stats mem components ram decoder)
