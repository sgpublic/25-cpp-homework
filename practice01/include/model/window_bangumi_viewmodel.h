//
// Created by Haven Madray on 2025/12/12.
//

#pragma once

#include "base_viewmodel.h"
#include "core/api/client/api_client.h"
#include "utils/stdafx.h"

namespace biliqt::model {
    class BangumiWindowViewModel: public ViewModel {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> _apiClient;
    public:
        explicit BangumiWindowViewModel(QObject *parent = nullptr);
        Q_PROPERTY_READONLY_AUTO(QString, title);
    public:
        VIEW_MODEL_COROUTINE_TASK(LoadBangumi)
    private slots:
        void onLoadBangumiSignal(const QVariantMap &args);
    };
}
