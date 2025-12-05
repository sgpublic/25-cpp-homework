//
// Created by coder on 12/5/25.
//
#pragma once

#include <string>
#include <sstream>

namespace biliqt::utils {

    template <typename T>
    std::string to_string(T* ptr) {
        std::ostringstream oss;
        oss << *ptr;
        return oss.str();
    }

    std::string url_encode(const std::string &str);

    std::string md5(const std::string &str);

}