//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include "core/api/client/api_client.h"
#include "dto/user_dto.h"

namespace biliqt::model {
    class UserModel: public QObject {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> apiClient;
    public:
        explicit UserModel(QObject *parent = nullptr);

        oatpp::Object<dto::UserInfoModel> getUserInfo();

        void logout();

    };
}
