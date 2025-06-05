//
// Created by noexcept on 2025/6/5.
//

#pragma once

#include <string>

namespace sysinfo {
namespace machine {
    std::string model();
}
namespace cpu {
    std::string model();
    int32_t logical_cpu_count();
    int32_t physical_cpu_count();
    int64_t frequency();
    int64_t frequency_max();
    int64_t frequency_min();

}
}