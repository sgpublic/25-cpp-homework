//
// Created by Haven Madray on 2025/12/15.
//
#pragma once
#include <string>
#include <oatpp/web/protocol/http/Http.hpp>

#include "core/module/setting_module.h"

namespace biliqt::core::api {

    std::string mixin_key();

    std::string mixin_key(const std::string& img_key, const std::string& sub_key) ;

    void add_cookies_header(oatpp::web::protocol::http::Headers& headers, const std::string& cookieItem);

    void add_cookies_header(oatpp::web::protocol::http::Headers& headers, const std::string& key, const QString& cookie);

}

#define _BILI_WBI_REQUEST_DTO_DEFAULT(TYPE)                                                                     \
    EXPOSE_PROPERTY_DTO(TYPE)                                                                                   \
    DTO_FIELD(Int32, wts) = std::time(nullptr);

#define BILI_WBI_REQUEST_DTO(TYPE)                                                                              \
    public:                                                                                                     \
        const oatpp::String asWbiParams() {                                                                     \
            return doSignForPostDto(this, biliqt::core::api::mixin_key(), "w_rid");                             \
        }                                                                                                       \
    _BILI_WBI_REQUEST_DTO_DEFAULT(TYPE)

#define _BILI_WBI_REQUEST_DTO_CUSTOM(TYPE, IMG_KEY, SUB_KEY)                                                     \
    public:                                                                                                     \
        const oatpp::String asWbiParams() {                                                                     \
            return doSignForPostDto(this, biliqt::core::api::mixin_key(IMG_KEY, SUB_KEY), "w_rid");             \
        }                                                                                                       \
    _BILI_WBI_REQUEST_DTO_DEFAULT(TYPE)

#define BILI_WBI_SEARCH_REQUEST_DTO(TYPE) \
    _BILI_WBI_REQUEST_DTO_CUSTOM(TYPE, "76e91e21c4df4e16af9467fd6f3e1095", "ddfca332d157450784b807c59cd7921e")


#define BILI_WBI_DEFAULT_HEADERS                                                                                \
    BILI_SIGN_DEFAULT_HEADERS

#define BILI_WBI_GET(NAME)                                                                                      \
    API_CALL_HEADERS(NAME) {                                                                                    \
        BILI_WBI_DEFAULT_HEADERS                                                                                \
    }

#define BILI_WBI_ADD_COOKIE(NAME)                                                                               \
    add_cookies_header(headers, #NAME, biliqt::core::module::SettingModule::getInstance()->cookie_##NAME());

#define BILI_WBI_COOKIE_SESSDATA                                                                                \
    BILI_WBI_ADD_COOKIE(SESSDATA)
#define BILI_WBI_COOKIE_sid                                                                                     \
    BILI_WBI_ADD_COOKIE(sid)
