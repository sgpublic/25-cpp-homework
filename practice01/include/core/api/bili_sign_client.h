#pragma once

#include <queue>
#include <oatpp/network/tcp/client/ConnectionProvider.hpp>
#include <oatpp/web/client/HttpRequestExecutor.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/codegen/ApiClient_define.hpp>
#include <oatpp/core/data/mapping/ObjectMapper.hpp>

#include "bili_sign_executor.h"
#include "utils/string.h"


namespace biliqt::core::api {
    template<typename T>
    std::shared_ptr<T> createShared(const std::string& baseUrl, const bool& useHttps) {
        auto jsonObjectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        // auto address = oatpp::network::Address(baseUrl, 443);
        // auto connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared(address);
        // auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);
        auto requestExecutor = std::make_shared<BiliApiExecutor>(baseUrl, useHttps);
        return T::createShared(requestExecutor, jsonObjectMapper);
    }

    template<typename T>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, T>::value,
        oatpp::String
    >::type
    doSign(T* body, std::string apiSecret) {
        oatpp::parser::json::mapping::ObjectMapper objectMapper;

        auto map = T::getProperties()->getMap();
        std::priority_queue<std::string> keys;
        for (const auto &field: map) {
            keys.push(field.first);
        }
        std::ostringstream oss;
        bool isFirst = true;
        while (!keys.empty()) {
            auto key = keys.top();
            keys.pop();
            if (isFirst) {
                isFirst = false;
            } else {
                oss << "&";
            }
            oatpp::data::mapping::type::Void value = map[key]->get(body);
            std::string strVal = objectMapper.writeToString(value);
            oss << key << "=" << strVal;
        }
        oss << apiSecret;
        std::string sign = utils::md5(oss.str());

        oss.clear();
        isFirst = true;
        for (const auto &field: map) {
            if (isFirst) {
                isFirst = false;
            } else {
                oss << "&";
            }
            auto value = map[field.first]->get(body);
            std::string strVal = objectMapper.writeToString(value);
            oss << field.first << "=" << utils::url_encode(strVal);
        }
        oss << "&" << "sign=" << sign;

        return oss.str();
    }
}

#define BILI_SIGN_CLIENT_INIT(Class, BASE_URL, USE_HTTPS)                                          \
    API_CLIENT_INIT(Class)                                                                         \
public:                                                                                            \
    static std::shared_ptr<Class> createShared() {                                                 \
        return biliqt::core::api::createShared<Class>(BASE_URL, USE_HTTPS);                        \
    }


#define BILI_SIGN_CALL(NAME)                                                                       \
    API_CALL_HEADERS(NAME) {                                                                       \
        headers.put("User-Agent", "Mozilla/5.0 BiliDroid/7.1.1 (sgpublic2002@gmail.com)");         \
    }
