//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include "core/api/client/api_client.h"
#include "core/api/client/passport_client.h"
#include "core/api/dto/passport_dto.h"
#include "dto/user_dto.h"

namespace biliqt::model {
    class UserModel: public QObject {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> apiClient;
        std::shared_ptr<core::api::client::PassportClient> passportClient;
    public:
        explicit UserModel(QObject *parent = nullptr);

        oatpp::Object<dto::UserQrcodeStateModel> getQrcode();
        oatpp::Object<dto::UserQrcodeStateModel> checkQrcode(const std::string &autoCode);

        oatpp::Object<dto::UserInfoModel> getUserInfo();

        void logout();
    private:
        oatpp::Object<dto::UserQrcodeStateModel> createQrcodeState(dto::QrcodeState state, const std::string &url, const std::string &authCode, const std::string &message);
        void postLogin(const oatpp::Object<core::api::dto::LoginQrcodeTvPollResp::Data> &data);
    };
}
