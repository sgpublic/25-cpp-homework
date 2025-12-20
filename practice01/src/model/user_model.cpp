//
// Created by Haven Madray on 2025/12/20.
//
#include "model/user_model.h"

#include "core/api/bili_sign_object.h"
#include "core/api/dto/api_dto.h"
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
    }

    oatpp::Object<UserInfoModel> UserModel::getUserInfo() {
        const auto result = apiClient->web_nav();
        const auto body = readRespBody<WebNavResp>(result);
        OATPP_LOGd("MainWindowViewModel::onLoadUserInfo", "code: {}, message: {}", body->code, body->message);
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

}
