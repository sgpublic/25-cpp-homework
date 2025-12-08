//
// Created by coder on 12/8/25.
//

#pragma once
#include <string>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/client/ApiClient.hpp>

#include "core/api/bili_sign_executor.h"

namespace biliqt::core::api::client {
    class BaseApiClient: public oatpp::web::client::ApiClient {
    public:
        BaseApiClient(const std::string& baseUrl, const bool& useHttps) : ApiClient(nullptr, nullptr) {
            m_objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
            m_requestExecutor = std::make_shared<BiliApiExecutor>(baseUrl, useHttps);
        }
    };

    template<typename T>
    static std::shared_ptr<T> createShared() {
        return T::createShared();
    }
}

#define BILI_SIGN_CLIENT_INIT(Class, BASE_URL, USE_HTTPS)                                                      \
public:                                                                                                        \
    Class() : BaseApiClient(BASE_URL, USE_HTTPS) { }                                                       \
                                                                                                               \
    static std::shared_ptr<Class> createShared() {                                                             \
        return std::make_shared<Class>();                                                                      \
    }                                                                                                          \
private:                                                                                                       \
    static oatpp::data::share::StringKeyLabel ___HEADER_KEY_HOST() {                                           \
        return BASE_URL;                                                                                       \
    }


#define BILI_SIGN_DEFAULT_HEADERS                                                                  \
    headers.putOrReplace("User-Agent", "Mozilla/5.0 BiliDroid/7.1.1 (sgpublic2002@gmail.com)");    \
    headers.putOrReplace("Host", ___HEADER_KEY_HOST());


#define BILI_SIGN_POST(NAME)                                                                       \
    API_CALL_HEADERS(NAME) {                                                                       \
        BILI_SIGN_DEFAULT_HEADERS                                                                  \
        headers.putOrReplace("Content-Type", "application/x-www-form-urlencoded");                 \
    }


#define BILI_SIGN_GET(NAME)                                                                        \
    API_CALL_HEADERS(NAME) {                                                                       \
        BILI_SIGN_DEFAULT_HEADERS                                                                  \
    }
