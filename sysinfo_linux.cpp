//
// Created by noexcept on 6/9/25.
//


#include "sysinfo.h"
#include <fstream>
#include <algorithm>
#include <unistd.h>

inline int64_t get_number_from_file(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return 0;
    }
    std::string line;
    std::getline(file, line);
    if (line.empty()) {
        return 0;
    }
    return static_cast<int64_t>(std::stoll(line));
}

inline std::string find_str_from_file(const std::string& file_path, const std::string& search_for) {

}

namespace sysinfo {

namespace machine {
    std::string model() {
        std::string product_name;
        std::ifstream file("/sys/class/dmi/id/product_name");
        if (!file.is_open()) {
            return product_name;
        }

        std::getline(file, product_name);
        if (!product_name.empty() && product_name.back() == '\n') {
            product_name.pop_back();
        }
        return product_name;
    }
}

namespace cpu {
    std::string brand_string() {
        std::string model_name;
        std::ifstream file("/proc/cpuinfo");
        if (!file.is_open()) {
            return model_name;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.find("model name") != std::string::npos) {
                if (const size_t colon_pos = line.find(':'); colon_pos != std::string::npos) {
                    model_name = line.substr(colon_pos + 1);
                }

                model_name.erase(model_name.begin(),
                    std::find_if(model_name.begin(), model_name.end(),
                        [](const int c) { return !std::isspace(c); }));

                model_name.erase(std::find_if(model_name.rbegin(), model_name.rend(),
                        [](const int c) { return !std::isspace(c); }).base(),
                        model_name.end());
                return model_name;
            }
        }
        return model_name;
    }

    std::string vendor()
    {
        std::string vendor_id;
        std::ifstream file("/proc/cpuinfo");
        if (!file.is_open()) {
            return vendor_id;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.find("vendor_id") != std::string::npos) {
                if (const size_t colon_pos = line.find(':'); colon_pos != std::string::npos) {
                    vendor_id = line.substr(colon_pos + 1);
                }

                vendor_id.erase(vendor_id.begin(),
                    std::find_if(vendor_id.begin(), vendor_id.end(),
                        [](const int c) { return !std::isspace(c); }));

                vendor_id.erase(std::find_if(vendor_id.rbegin(), vendor_id.rend(),
                        [](const int c) { return !std::isspace(c); }).base(),
                        vendor_id.end());
                return vendor_id;
            }
        }
        return vendor_id;
    }

    int32_t logical_cpu_count() {
        int32_t count = static_cast<int32_t>(sysconf(_SC_NPROCESSORS_ONLN));
        return count;
    }

    int32_t physical_cpu_count() {
        std::string cpu_cores;
        int32_t cpu_cores_count = 0;
        std::ifstream file("/proc/cpuinfo");
        if (!file.is_open()) {
            cpu_cores_count;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.find("cpu cores") != std::string::npos) {
                if (const size_t colon_pos = line.find(':'); colon_pos != std::string::npos) {
                    cpu_cores = line.substr(colon_pos + 1);
                }

                cpu_cores.erase(cpu_cores.begin(),
                    std::find_if(cpu_cores.begin(), cpu_cores.end(),
                        [](const int c) { return !std::isspace(c); }));

                cpu_cores.erase(std::find_if(cpu_cores.rbegin(), cpu_cores.rend(),
                        [](const int c) { return !std::isspace(c); }).base(),
                        cpu_cores.end());
                cpu_cores_count = std::atoi(cpu_cores.c_str());
                return cpu_cores_count;
            }
        }
        return cpu_cores_count;
    }
    int64_t frequency() {
        int64_t freq_khz = get_number_from_file("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");
        return freq_khz * 1000;
    }

    int64_t frequency_max() {
        int64_t freq_khz = get_number_from_file("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq");
        return freq_khz * 1000;
    }

    int64_t frequency_min() {
        int64_t freq_khz = get_number_from_file("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq");
        return freq_khz * 1000;
    }
}


namespace memory {
    uint64_t physical_size() {
        std::ifstream file("/proc/meminfo");
        if (!file.is_open()) {
            return 0;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.find("MemTotal") != std::string::npos) {
                size_t colon = line.find(':');
                if (colon == std::string::npos) {
                    return 0;
                }

                std::string value = line.substr(colon + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value = value.substr(0, value.find(' '));

                char* end;
                unsigned long long kb = std::strtoull(value.c_str(), &end, 10);
                return (end != value.c_str()) ? kb * 1024 : 0;
            }
        }
        return 0;
    }
}

namespace kernel {
    std::string osrelease() {
        std::string osrelease;
        std::ifstream file("/proc/version");
    }

    std::string osversion();
    std::string version();
}
}
