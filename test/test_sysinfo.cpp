//
// Created by noexcept on 2025/6/5.
//

#include "sysinfo.h"
#include <iostream>

int main() {
    std::cout << sysinfo::machine::model() << std::endl;
    std::cout << sysinfo::cpu::model() << std::endl;
    std::cout << sysinfo::cpu::logical_cpu_count() << std::endl;
    std::cout << sysinfo::cpu::physical_cpu_count() << std::endl;
    std::cout << sysinfo::cpu::frequency() << std::endl;
    std::cout << sysinfo::cpu::frequency_max() << std::endl;
    std::cout << sysinfo::cpu::frequency_min() << std::endl;
    return 0;
}