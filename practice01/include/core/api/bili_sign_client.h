#pragma once

#include <QDebug>
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
    doSign(T* body, const std::string& apiSecret) {
        auto map = T::getProperties()->getMap();
        std::priority_queue<std::string, std::vector<std::string>, std::greater<>> keys;
        for (const auto &field: map) {
            keys.push(field.first);
        }
        std::ostringstream secretCalculate;
        bool isFirst = true;
        while (!keys.empty()) {
            auto key = keys.top();
            keys.pop();
            if (isFirst) {
                isFirst = false;
            } else {
                secretCalculate << "&";
            }
            oatpp::data::mapping::type::Void value = map[key]->get(body);
            std::shared_ptr<std::string> strVal = utils::void_to_string(value);
            secretCalculate << key << "=" << utils::url_encode(*strVal);
        }
        secretCalculate << apiSecret;
        qDebug() << "secretCalculate:" << secretCalculate.str();
        std::string sign = utils::md5(secretCalculate.str());

        std::ostringstream paramsOutput;
        isFirst = true;
        for (const auto &field: map) {
            if (isFirst) {
                isFirst = false;
            } else {
                paramsOutput << "&";
            }
            auto value = map[field.first]->get(body);
            std::shared_ptr<std::string> strVal = utils::void_to_string(value);
            paramsOutput << field.first << "=" << utils::url_encode(*strVal);
        }
        paramsOutput << "&" << "sign=" << sign;

        qDebug() << "paramsOutput:" << paramsOutput.str();

        return paramsOutput.str();
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
        headers.putOrReplace("User-Agent", "Mozilla/5.0 BiliDroid/7.1.1 (sgpublic2002@gmail.com)");\
        headers.putOrReplace("Content-Type", "application/x-www-form-urlencoded");                 \
    }
