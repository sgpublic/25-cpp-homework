//
// Created by Haven Madray on 2025/12/15.
//
#pragma once

#include "base_viewmodel.h"
#include "model/page_search_model.h"
#include "utils/stdafx.h"


namespace biliqt::viewmodel {

    class SearchPageViewModel: public ViewModel {
        Q_OBJECT
    private:
        std::shared_ptr<model::SearchPageModel> searchPageModel;
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
