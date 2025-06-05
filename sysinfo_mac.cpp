//
// Created by noexcept on 2025/6/5.
//

#include "sysinfo.h"
#include <sys/sysctl.h>

inline std::string str_from_sysctlbyname(const char* name) {
    size_t len = 0;
    sysctlbyname(name, nullptr, &len, nullptr, 0);
    auto p_str_value = std::make_unique<char[]>(len);
    sysctlbyname(name, p_str_value.get(), &len, nullptr, 0);
    return {p_str_value.get()};
}

template<typename T>
T int_from_sysctlbyname(const char* name) {
    T value;
    size_t len = sizeof(value);
    sysctlbyname(name, &value, &len, nullptr, 0);
    return value;
}

namespace sysinfo {

namespace machine {
    std::string model() {
        return str_from_sysctlbyname("hw.model");
    }
}

namespace cpu {
    std::string model() {
        return str_from_sysctlbyname("machdep.cpu.brand_string");
    }

    int32_t logical_cpu_count() {
        return int_from_sysctlbyname<int32_t>("hw.logicalcpu");
    }

    int32_t physical_cpu_count() {
        return int_from_sysctlbyname<int32_t>("hw.physicalcpu");
    }

    int64_t frequency() {
        return int_from_sysctlbyname<int64_t>("hw.cpufrequency");
    }

    int64_t frequency_max() {
        return int_from_sysctlbyname<int64_t>("hw.cpufrequency_max");
    }

    int64_t frequency_min() {
        return int_from_sysctlbyname<int64_t>("hw.cpufrequency_min");
    }
}
}