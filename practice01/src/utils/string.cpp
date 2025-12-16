//
// Created by coder on 12/5/25.
//
#include "utils/string.h"

#include <QCryptographicHash>
#include <QString>
#include <sstream>
#include <oatpp/encoding/Url.hpp>

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

using namespace oatpp;
using namespace oatpp::encoding;
using namespace oatpp::parser::json::mapping;

namespace biliqt::utils {

    std::shared_ptr<std::string> void_to_string(const Void& value) {
        if (value.getValueType() == String::Class::getType()) {
            const String& str = value.cast<String>();
            return str.getPtr();
        }
        const std::shared_ptr<ObjectMapper> objMapper = std::make_shared<ObjectMapper>();
        const String& str = objMapper->writeToString(value);
        return str.getPtr();
    }

    String qstr_to_oatstr(const QString& str) {
        String result = str.toStdString();
        return result;
    }

    std::string url_encode(const std::string &str) {
        const Url::Config config;
        const String strVal = str;
        return Url::encode(strVal, config);
    }

    std::string md5(const std::string& str) {
        const QByteArray hash = QCryptographicHash::hash(str, QCryptographicHash::Md5);
        return hash.toHex().toStdString();
    }

    std::string sha256(const std::string &str) {
        const QByteArray hash = QCryptographicHash::hash(str, QCryptographicHash::Sha256);
        return hash.toHex().toStdString();
    }

    std::string concat(const std::string &str, const std::string &sep) {
        return str + sep;
    }

    QString url_to_wbi_key(const String &url) {
        const auto& key = url->substr(url->length() - 32 - 4, 32);
        return QString::fromStdString(key);
    }

}
