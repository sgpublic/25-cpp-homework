//
// Created by Haven Madray on 2025/12/20.
//
#include "model/user_model.h"

#include "core/api/bili_sign_object.h"
#include "core/api/dto/api_dto.h"
#include "core/api/dto/passport_dto.h"
#include "core/module/global_signal_module.h"

using namespace biliqt::core::api;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api::client;
using namespace biliqt::model::dto;
using namespace biliqt::core::module;
using namespace biliqt::utils;

namespace biliqt::model {

    UserModel::UserModel(QObject *parent): QObject(parent) {
        apiClient = ApiClient::createShared();
        passportClient = PassportClient::createShared();
    }

    oatpp::Object<UserQrcodeStateModel> UserModel::getQrcode() {
        const auto dto = LoginQrcodeTvReq::createShared();
        const auto result = passportClient->qrcodeTv(dto->asSignedParams());
        if (result->getStatusCode() != 200) {
            return createQrcodeState(QrcodeState::Error, "", "", result->getStatusDescription());
        }
        const auto body = readRespBody<LoginQrcodeTvResp>(result);
        if (body->code != 0) {
            return createQrcodeState(QrcodeState::Error, "", "", body->message);
        }
        return createQrcodeState(QrcodeState::Loaded, body->data->url, body->data->auth_code, "");
    }

    oatpp::Object<UserQrcodeStateModel> UserModel::checkQrcode(const std::string& autoCode) {
        const oatpp::Object<LoginQrcodeTvPollReq>& dto = LoginQrcodeTvPollReq::createShared();
        dto->auth_code = autoCode;
        const auto& result = passportClient->qrcodeTvPoll(dto->asSignedParams());
        if (result->getStatusCode() != 200) {
            return createQrcodeState(QrcodeState::Error, "", "", result->getStatusDescription());
        }
        switch (const auto body = readRespBody<LoginQrcodeTvPollResp>(result); body->code) {
            case 0:
                postLogin(body->data);
                return createQrcodeState(QrcodeState::Success, "", "", "");
            case 86039:
                return createQrcodeState(QrcodeState::Waiting, "", "", "");
            case 86090:
                return createQrcodeState(QrcodeState::Scanned, "", "", "");
            case 86038:
                return createQrcodeState(QrcodeState::Expired, "", "", "");
            default:
                return createQrcodeState(QrcodeState::Error, "", "", body->message);
        }
    }

    oatpp::Object<UserInfoModel> UserModel::getUserInfo() {
        const auto result = apiClient->web_nav();
        const auto body = readRespBody<WebNavResp>(result);
        OATPP_LOGd("UserModel::getUserInfo", "code: {}, message: {}", body->code, body->message);
        const auto& userInfo = UserInfoModel::createShared();
        if (body->code != 0) {
            userInfo->nick = nullptr;
            userInfo->avatar = nullptr;
            SettingModule::getInstance()->wbi_img_key("");
            SettingModule::getInstance()->wbi_sub_key("");
        } else {
            userInfo->nick = body->data->uname;
            userInfo->avatar = body->data->face;
            SettingModule::getInstance()->wbi_img_key(url_to_wbi_key(body->data->wbi_img->img_url));
            SettingModule::getInstance()->wbi_sub_key(url_to_wbi_key(body->data->wbi_img->sub_url));
        }
        return userInfo;
    }

    void UserModel::logout() {
        SettingModule::getInstance()->login(false);
        SettingModule::getInstance()->accessToken("");
        SettingModule::getInstance()->refreshToken("");
        SettingModule::getInstance()->cookie_BiliJct("");
        SettingModule::getInstance()->cookie_DedeUserID("");
        SettingModule::getInstance()->cookie_DedeUserID__ckMd5("");
        SettingModule::getInstance()->cookie_SESSDATA("");
        SettingModule::getInstance()->cookie_sid("");
        SettingModule::getInstance()->wbi_img_key("");
        SettingModule::getInstance()->wbi_sub_key("");
        emit GlobalSignalModule::getInstance()->loginStatusChanged(false);
    }

    oatpp::Object<UserQrcodeStateModel> UserModel::createQrcodeState(const QrcodeState state, const std::string &url, const std::string &authCode, const std::string &message) {
        const auto& stateDto = UserQrcodeStateModel::createShared();
        stateDto->state = state;
        stateDto->url = url;
        stateDto->authCode = authCode;
        stateDto->message = message;
        return stateDto;
    }

    void UserModel::postLogin(const oatpp::Object<LoginQrcodeTvPollResp::Data> &data) {
        const auto& setting = SettingModule::getInstance();
        setting->accessToken(data->token_info->access_token->data());
        setting->refreshToken(data->token_info->refresh_token->data());
        const auto& cookies = data->cookie_info->cookies;
        for (const auto& cookieItem : *cookies) {
            const auto& value = cookieItem->value->data();
            if (cookieItem->name == "bili_jct") {
                setting->cookie_BiliJct(value);
            } else if (cookieItem->name == "DedeUserID") {
                setting->cookie_DedeUserID(value);
            } else if (cookieItem->name == "DedeUserID__ckMd5") {
                setting->cookie_DedeUserID__ckMd5(value);
            } else if (cookieItem->name == "sid") {
                setting->cookie_sid(value);
            } else if (cookieItem->name == "SESSDATA") {
                setting->cookie_SESSDATA(value);
            }
        }
        setting->login(true);
        emit GlobalSignalModule::getInstance()->loginStatusChanged(true);
    }
}
