//
// Created by coder on 12/5/25.
//
#pragma once

#include <string>
#include <oatpp/core/data/mapping/type/Type.hpp>

namespace biliqt::utils {

    std::shared_ptr<std::string> void_to_string(const oatpp::data::mapping::type::Void& value);

    std::string url_encode(const std::string &str);

    std::string md5(const std::string &str);

}
