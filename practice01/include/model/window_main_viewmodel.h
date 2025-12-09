//
// Created by coder on 12/5/25.
//
#pragma once

#include "base_viewmodel.h"
#include "utils/stdafx.h"
#include "core/api/client/api_client.h"
#include "core/api/client/app_client.h"

namespace biliqt::model {

    class MainWindowViewModel: public ViewModel {
        Q_OBJECT

        Q_PROPERTY_READONLY_AUTO(bool, hasLogin) = false;
        Q_PROPERTY_READONLY_AUTO(QString, nick);
        Q_PROPERTY_READONLY_AUTO(QString, avatarUrl);
        Q_PROPERTY_READONLY_AUTO(QList<QVariantMap>, bannerData);
    private:
        std::shared_ptr<core::api::client::ApiClient> _apiClient;
        std::shared_ptr<core::api::client::AppClient> _appClient;
    public:
        explicit MainWindowViewModel(QObject *parent = nullptr);

        VIEW_MODEL_COROUTINE_TASK(LoginSucceed)
        VIEW_MODEL_COROUTINE_TASK(LoadUserInfo)
        VIEW_MODEL_COROUTINE_TASK(LoadBannerData)
    };

}
