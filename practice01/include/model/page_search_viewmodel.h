//
// Created by Haven Madray on 2025/12/15.
//
#pragma once

#include "base_viewmodel.h"
#include "core/api/client/api_client.h"
#include "utils/stdafx.h"


namespace biliqt::model {

    class SearchPageViewModel: public ViewModel {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> _apiClient;
    public:
        explicit SearchPageViewModel(QObject *parent = nullptr);
        Q_PROPERTY_AUTO(QString, searchText);
        Q_PROPERTY_AUTO(QVariantList, searchResultList);
        Q_PROPERTY_AUTO(int, currentPage) = 1;
        Q_PROPERTY_AUTO(int, pageCount) = 0;
        Q_PROPERTY_AUTO(int, numResults) = 0;
        Q_PROPERTY_AUTO(int, pagesize) = 0;
    public:
        VIEW_MODEL_COROUTINE_TASK(LoadSearchResult)
    public:
        Q_INVOKABLE QString timeFromTimestamp(long long timestamp);
    };

}
