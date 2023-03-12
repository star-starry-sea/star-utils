#pragma once
#ifndef UTILS_FILESYSTEM_HPP
#define UTILS_FILESYSTEM_HPP

#include <filesystem>

namespace star::filesystem {
    inline bool remove(const std::filesystem::path &path) noexcept {
        std::error_code temp_ec{};
        bool result = std::filesystem::remove(path, temp_ec);
        return result;
    }
}

#endif //UTILS_FILESYSTEM_HPP
