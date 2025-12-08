//
// Created by coder on 12/5/25.
//

#pragma once

#include <QDebug>
#include <oatpp/core/Types.hpp>
#include <oatpp/web/protocol/http/incoming/Response.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <nlohmann/json.hpp>

#include "utils/string.h"

namespace biliqt::core::api {

    template<typename T>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, T>::value,
        std::shared_ptr<T>
    >::type
    readRespBody(const std::shared_ptr<oatpp::web::protocol::http::incoming::Response>& body) {
        const auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        const auto bodyStr = body->readBodyToString();
        const auto dto = objectMapper->readFromString<oatpp::Object<T>>(bodyStr);
        return dto.getPtr();
    }

    nlohmann::json readRespBody(const std::shared_ptr<oatpp::web::protocol::http::incoming::Response>& body);

    template<typename T>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, T>::value,
        std::shared_ptr<T>
    >::type
    findModules(const nlohmann::json& body, const std::string style) {
        // TODO
    }

    std::string calculateSignValue(const std::unordered_map<std::string, std::string>& params, const std::string& apiSecret);

    template<typename T>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, T>::value,
        oatpp::String
    >::type
    doSignForPostDto(T* body, const std::string& apiSecret) {
        auto map = T::getProperties()->getMap();
        auto params = std::unordered_map<std::string, std::string>();
        for (const auto &[key, valueRef]: map) {
            oatpp::data::mapping::type::Void value = valueRef->get(body);
            params[key] = *utils::void_to_string(value);
        }
        std::string sign = calculateSignValue(params, apiSecret);
        std::ostringstream paramsOutput;
        bool isFirst = true;
        for (const auto &[key, value]: params) {
            if (isFirst) {
                isFirst = false;
            } else {
                paramsOutput << "&";
            }
            paramsOutput << key << "=" << utils::url_encode(value);
        }
        paramsOutput << "&" << "sign=" << sign;
        return paramsOutput.str();
    }

}

#define BILI_SIGN_REQUEST_DTO(TYPE, API_KEY, API_SECRET, MOBI_APP, PLATFORM, BUILD)                             \
    DTO_INIT(TYPE, DTO)                                                                                         \
    public:                                                                                                     \
        static const oatpp::data::mapping::type::BaseObject::Properties* getProperties() {                      \
            return Z__CLASS_GET_FIELDS_MAP();                                                                   \
        }                                                                                                       \
                                                                                                                \
        const oatpp::String asSignedParams() {                                                                  \
            return doSignForPostDto(this, API_SECRET);                                                          \
        }                                                                                                       \
    DTO_FIELD(String, appkey) = API_KEY;                                                                        \
    DTO_FIELD(String, mobi_app) = MOBI_APP;                                                                     \
    DTO_FIELD(String, platform) = PLATFORM;                                                                     \
    DTO_FIELD(Int32, ts) = std::time(nullptr);                                                                  \
    DTO_FIELD(Int32, build) = BUILD;

#define BILI_SIGN_PASSPORT_REQUEST_DTO(TYPE) \
    BILI_SIGN_REQUEST_DTO(TYPE, "783bbb7264451d82", "2653583c8873dea268ab9386918b1d65", "android", "android", 7010300)
#define BILI_SIGN_API_REQUEST_DTO(TYPE) \
    BILI_SIGN_REQUEST_DTO(TYPE, "1d8b6e7d45233436", "560c52ccd288fed045859ed18bffd973", "android", "android", 7010300)

#define BILI_RESP_SAMPLE_DTO(TYPE)                                                                              \
DTO_INIT(TYPE, DTO)                                                                                             \
public:                                                                                                         \
    DTO_FIELD(Int32, code);                                                                                     \
    DTO_FIELD(String, message);

#define BILI_RESP_DTO(TYPE, DATA_TYPE)                                                                          \
    BILI_RESP_SAMPLE_DTO(TYPE)                                                                                  \
    DTO_FIELD(Object<DATA_TYPE>, data);
