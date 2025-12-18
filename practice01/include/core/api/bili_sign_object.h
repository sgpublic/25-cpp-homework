//
// Created by coder on 12/5/25.
//

#pragma once

#include <QDebug>
#include <oatpp/Types.hpp>
#include <oatpp/web/protocol/http/incoming/Response.hpp>
#include <oatpp/json/ObjectMapper.hpp>
#include <oatpp/data/mapping/ObjectRemapper.hpp>
#include <nlohmann/json.hpp>

#include "utils/oatpp_dto.h"
#include "utils/string.h"

namespace biliqt::core::api {

    template<typename T>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, T>::value,
        std::shared_ptr<T>
    >::type
    readRespBody(const std::shared_ptr<oatpp::web::protocol::http::incoming::Response>& body) {
        const auto objectMapper = std::make_shared<oatpp::json::ObjectMapper>();
        const auto dto = body->readBodyToDto<oatpp::Object<T>>(objectMapper);
        return dto.getPtr();
    }

    nlohmann::json readRespBody(const std::shared_ptr<oatpp::web::protocol::http::incoming::Response>& body);

    template<typename ModuleItemT>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, ModuleItemT>::value,
        std::shared_ptr<std::list<oatpp::Object<ModuleItemT>>>
    >::type
    findModules(const oatpp::List<oatpp::Tree> &modules, const std::string &style = "") {
        const auto& result = oatpp::List<oatpp::Object<ModuleItemT>>::createShared();
        for (const auto& module : *modules) {
            const auto& remapper = utils::createRemapper();
            if (!style.empty() && (!module["style"].isString() || module["style"].getString() != style)) {
                continue;
            }
            for (const auto& items = module["items"].getVector(); const auto& item : items) {
                result->emplace_back(remapper.remap<oatpp::Object<ModuleItemT>>(item));
            }
        }
        return result.getPtr();
    }

    std::string calculateSignValue(const std::unordered_map<std::string, std::string>& params, const std::string& apiSecret);

    template<typename T>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, T>::value,
        oatpp::String
    >::type
    doSignForPostDto(
        T* body, const std::unordered_map<std::string, oatpp::data::type::BaseObject::Property*>& map,
        const std::string& apiSecret, const std::string& signKeyName = "sign"
    ) {
        auto params = std::unordered_map<std::string, std::string>();
        for (const auto &[key, valueRef]: map) {
            oatpp::Void value = valueRef->get(body);
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
        paramsOutput << "&" << signKeyName << "=" << sign;
        return paramsOutput.str();
    }

}

#define BILI_SIGN_REQUEST_DTO(TYPE, API_KEY, API_SECRET, MOBI_APP, PLATFORM, BUILD)                             \
    DTO_INIT(TYPE, DTO)                                                                                         \
    public:                                                                                                     \
        const oatpp::String asSignedParams() {                                                                  \
            return doSignForPostDto(this, TYPE::Z__CLASS_GET_FIELDS_MAP()->getMap(), API_SECRET);               \
        }                                                                                                       \
    DTO_FIELD(String, appkey) = API_KEY;                                                                        \
    DTO_FIELD(String, mobi_app) = MOBI_APP;                                                                     \
    DTO_FIELD(String, platform) = PLATFORM;                                                                     \
    DTO_FIELD(Int64, ts) = std::time(nullptr);                                                                  \
    DTO_FIELD(Int32, build) = BUILD;

#define BILI_SIGN_PASSPORT_REQUEST_DTO(TYPE) \
    BILI_SIGN_REQUEST_DTO(TYPE, "783bbb7264451d82", "2653583c8873dea268ab9386918b1d65", "android", "android", 7010300)
#define BILI_SIGN_API_REQUEST_DTO(TYPE) \
    BILI_SIGN_REQUEST_DTO(TYPE, "1d8b6e7d45233436", "560c52ccd288fed045859ed18bffd973", "android", "android", 7010300)

#define BILI_RESP_SAMPLE_DTO(TYPE)                                                                              \
    DTO_INIT(TYPE, DTO)                                                                                         \
public:                                                                                                         \
    DTO_FIELD(Int32, code);                                                                                     \
    DTO_FIELD(String, message);

#define BILI_RESP_DATA_DTO(TYPE, DATA_TYPE)                                                                     \
    BILI_RESP_SAMPLE_DTO(TYPE)                                                                                  \
    DTO_FIELD(Object<DATA_TYPE>, data);

#define BILI_RESP_LIST_RESULT_DTO(TYPE, DATA_TYPE)                                                              \
    BILI_RESP_SAMPLE_DTO(TYPE)                                                                                  \
    DTO_FIELD(List<Object<DATA_TYPE>>, result);

#define BILI_RESP_RESULT_DTO(TYPE, DATA_TYPE)                                                                   \
    BILI_RESP_SAMPLE_DTO(TYPE)                                                                                  \
    DTO_FIELD(Object<DATA_TYPE>, result);

#define BILI_RESP_MODULE_DTO(TYPE)                                                                              \
    DTO_INIT(TYPE, DTO)                                                                                         \
    DTO_FIELD(List<Tree>, modules);                                                                             \
    public:                                                                                                     \
        template<typename T>                                                                                    \
        typename std::enable_if<                                                                                \
            std::is_base_of<oatpp::DTO, T>::value,                                                              \
            std::shared_ptr<std::list<oatpp::Object<T>>>                                                        \
        >::type                                                                                                 \
        findModules() {                                                                                         \
            return biliqt::core::api::findModules<T>(modules, T::_MODULE_STYLE());                              \
        }

#define BILI_RESP_MODULE_ITEM_DTO(TYPE, NAME)                                                                   \
    DTO_INIT(TYPE, DTO)                                                                                         \
    public:                                                                                                     \
        static std::string _MODULE_STYLE() { return NAME; }
