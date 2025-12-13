//
// Created by coder on 12/5/25.
//
#pragma once

#include "base_viewmodel.h"
#include "utils/stdafx.h"
#include "core/api/client/search_client.h"
#include "core/api/client/app_client.h"

namespace biliqt::model {

    class MainWindowViewModel: public ViewModel {
        Q_OBJECT

        Q_PROPERTY_READONLY_AUTO(bool, hasLogin) = false;
        Q_PROPERTY_READONLY_AUTO(QString, nick);
        Q_PROPERTY_READONLY_AUTO(QString, avatarUrl);

        Q_PROPERTY_AUTO(QString, searchText);
        Q_PROPERTY_READONLY_AUTO(QVariantList, searchSuggest);
    private:
        std::shared_ptr<core::api::client::AppClient> _appClient;
        std::shared_ptr<core::api::client::SearchClient> _searchClient;
    public:
        explicit MainWindowViewModel(QObject *parent = nullptr);

        VIEW_MODEL_COROUTINE_TASK(LoginSucceed)
        VIEW_MODEL_COROUTINE_TASK(LoadUserInfo)
        VIEW_MODEL_COROUTINE_TASK(Logout)
        VIEW_MODEL_COROUTINE_TASK(LoadSearchSuggest)
        VIEW_MODEL_COROUTINE_TASK(Search)
    };

}
