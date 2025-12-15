//
// Created by coder on 12/5/25.
//
#pragma once

#include <QString>
#include <string>
#include <oatpp/core/Types.hpp>

namespace biliqt::utils {

    std::shared_ptr<std::string> void_to_string(const oatpp::Void& value);

    oatpp::String qstr_to_oatstr(const QString& str);

    std::string url_encode(const std::string &str);

    std::string md5(const std::string &str);

    std::string sha256(const std::string &str);

    std::string concat(const std::string &str, const std::string &sep);

    QString url_to_wbi_key(const oatpp::String& url);

}
