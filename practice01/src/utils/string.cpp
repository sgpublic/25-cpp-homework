//
// Created by coder on 12/5/25.
//
#include "utils/string.h"

#include <iomanip>
#include <QCryptographicHash>
#include <QString>
#include <sstream>
#include <boost/url/encode.hpp>
#include <boost/url/rfc/pchars.hpp>
#include <openssl/evp.h>

#include <oatpp/json/ObjectMapper.hpp>

using namespace oatpp;
using namespace oatpp::json;

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

    oatpp::String qstr_to_oatstr(const QString& str) {
        oatpp::String result = str.toStdString();
        return result;
    }

    std::string url_encode(const std::string &str) {
        std::string strVal = str;
        const unsigned long bufferSize = strVal.length() * 3;
        char buf[bufferSize];
        std::size_t size = boost::urls::encode(buf, bufferSize, strVal, boost::urls::pchars);
        buf[size] = '\0';
        return strVal;
    }

    std::string md5(const std::string& str) {
        QByteArray hash = QCryptographicHash::hash(str, QCryptographicHash::Md5);
        return hash.toHex().toStdString();
    }

    std::string sha256(const std::string &str) {
        QByteArray hash = QCryptographicHash::hash(str, QCryptographicHash::Sha256);
        return hash.toHex().toStdString();
    }

    std::string concat(const std::string &str, const std::string &sep) {
        return str + sep;
    }
}
