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
        Q_PROPERTY_READONLY_AUTO(QVariantList, bangumiList);
    private:
        std::shared_ptr<core::api::client::ApiClient> _apiClient;
        int _cursor = 0;
    public:
        explicit HomePageViewModel(QObject *parent = nullptr);
        VIEW_MODEL_COROUTINE_TASK(LoadSearchSuggest)
        VIEW_MODEL_COROUTINE_TASK(LoadBannerData)
        VIEW_MODEL_COROUTINE_TASK(LoadBangumiList)

    public:
        Q_PROPERTY_READONLY_AUTO(double, ui_listWidth) = 0;

        Q_PROPERTY_READONLY_AUTO(double, ui_listCellHeight) = 100;
        Q_PROPERTY_READONLY_AUTO(double, ui_listCellWidth) = 100;
        Q_PROPERTY_READONLY_AUTO(double, ui_listCellPadding) = 8;

        Q_PROPERTY_READONLY_AUTO(double, ui_listCellContentPadding) = 1;
        Q_PROPERTY_READONLY_AUTO(int, ui_listCellContentHeight) = 100;
        Q_PROPERTY_READONLY_AUTO(int, ui_listCellContentWidth) = 100;
    public:
        Q_INVOKABLE void onPageWidthChanged(double width);
    };

}
