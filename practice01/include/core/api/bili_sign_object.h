//
// Created by coder on 12/5/25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/web/protocol/http/incoming/Response.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

namespace biliqt::core::api {

    template<typename T>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, T>::value,
        std::shared_ptr<T>
    >::type
    readRespBody(std::shared_ptr<oatpp::web::protocol::http::incoming::Response> body) {
        auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        auto dto = body->readBodyToDto<oatpp::Object<T>>(objectMapper);
        return dto.getPtr();
    }

}

#define BILI_SIGN_REQUEST_DTO(TYPE, API_KEY, API_SECRET, MOBI_APP, PLATFORM, BUILD)                             \
DTO_INIT(TYPE, DTO)                                                                                             \
public:                                                                                                         \
    static const oatpp::data::mapping::type::BaseObject::Properties* getProperties() {                          \
        return Z__CLASS_GET_FIELDS_MAP();                                                                       \
    }                                                                                                           \
                                                                                                                \
    const oatpp::String signedBody() {                                                                          \
        return doSign(this, API_SECRET);                                                                        \
    }                                                                                                           \
DTO_FIELD(String, appkey) = API_KEY;                                                                            \
DTO_FIELD(String, mobi_app) = MOBI_APP;                                                                         \
DTO_FIELD(String, platform) = PLATFORM;                                                                         \
DTO_FIELD(Int32, ts) = std::time(nullptr);                                                                      \
DTO_FIELD(Int32, build) = BUILD;

#define BILI_SIGN_PASSPORT_REQUEST_DTO(TYPE) \
    BILI_SIGN_REQUEST_DTO(TYPE, "783bbb7264451d82", "2653583c8873dea268ab9386918b1d65", "android", "android", 7010300)
#define BILI_SIGN_API_REQUEST_DTO(TYPE) \
    BILI_SIGN_REQUEST_DTO(TYPE, "1d8b6e7d45233436", "560c52ccd288fed045859ed18bffd973", "android", "android", 7010300)

#define BILI_RESP_DTO(TYPE, DATA_TYPE)                                                                          \
DTO_INIT(TYPE, DTO)                                                                                             \
public:                                                                                                         \
    DTO_FIELD(Int32, code);                                                                                     \
    DTO_FIELD(String, message);                                                                                 \
    DTO_FIELD(Object<DATA_TYPE>, data);
