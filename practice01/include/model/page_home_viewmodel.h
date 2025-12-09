//
// Created by coder on 12/4/25.
//
#pragma once

#include "base_viewmodel.h"
#include "core/api/client/api_client.h"
#include "utils/stdafx.h"

namespace biliqt::model {

    class HomePageViewModel: public ViewModel {
        Q_OBJECT
    public:
        Q_PROPERTY_AUTO(QString, searchText);
        Q_PROPERTY_READONLY_AUTO(QVariantList, bannerData);
    private:
        std::shared_ptr<core::api::client::ApiClient> _apiClient;
    public:
        explicit HomePageViewModel(QObject *parent = nullptr);
        VIEW_MODEL_COROUTINE_TASK(LoadSearchSuggest)
        VIEW_MODEL_COROUTINE_TASK(LoadBannerData)
    };

}
