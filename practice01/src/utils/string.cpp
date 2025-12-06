//
// Created by coder on 12/5/25.
//
#include "utils/string.h"

#include <iomanip>
#include <sstream>
#include <boost/url.hpp>
#include <boost/url/rfc/pchars.hpp>
#include <oatpp/core/data/mapping/type/Primitive.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <openssl/evp.h>

using namespace oatpp::data::mapping::type;
using namespace oatpp::parser::json::mapping;

namespace biliqt::utils {

    std::shared_ptr<std::string> void_to_string(const Void& value) {
        if (value.getValueType() == String::Class::getType()) {
            const String& str = value.cast<String>();
            return str.getPtr();
        }
        const std::shared_ptr<ObjectMapper> objMapper = ObjectMapper::createShared();
        const String& str = objMapper->writeToString(value);
        return str.getPtr();
    }

    std::string url_encode(const std::string &str) {
        std::string strVal = str;
        const unsigned long bufferSize = strVal.length() * 3;
        char buf[bufferSize];
        std::size_t size = boost::urls::encode(buf, bufferSize, strVal, boost::urls::pchars);
        buf[size] = '\0';
        return strVal;
    }

    std::string md5(const std::string& input) {
        unsigned char digest[EVP_MAX_MD_SIZE];
        unsigned int length = 0;

        EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
        if (mdctx == nullptr) {
            throw std::runtime_error("Failed to create EVP_MD_CTX");
        }

        if (EVP_DigestInit_ex(mdctx, EVP_md5(), nullptr) != 1) {
            EVP_MD_CTX_free(mdctx);
            throw std::runtime_error("Failed to initialize digest context");
        }

        if (EVP_DigestUpdate(mdctx, input.c_str(), input.length()) != 1) {
            EVP_MD_CTX_free(mdctx);
            throw std::runtime_error("Failed to update digest context");
        }

        if (EVP_DigestFinal_ex(mdctx, digest, &length) != 1) {
            EVP_MD_CTX_free(mdctx);
            throw std::runtime_error("Failed to finalize digest context");
        }

        EVP_MD_CTX_free(mdctx);

        std::ostringstream oss;
        for (unsigned int i = 0; i < length; ++i) {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
        }

        return oss.str();
    }
}
