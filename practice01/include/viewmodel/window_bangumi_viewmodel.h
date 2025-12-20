//
// Created by Haven Madray on 2025/12/12.
//

#pragma once

#include "base_viewmodel.h"
#include "core/api/client/api_client.h"
#include "utils/stdafx.h"

namespace biliqt::viewmodel {
    class BangumiWindowViewModel: public ViewModel {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> _apiClient;
    public:
        explicit BangumiWindowViewModel(QObject *parent = nullptr);
        Q_PROPERTY_READONLY_AUTO(int, seasonId) = -1;
        Q_PROPERTY_READONLY_AUTO(int, episodeId) = -1;

        Q_PROPERTY_READONLY_AUTO(QString, title);
        Q_PROPERTY_READONLY_AUTO(QString, cover);
        Q_PROPERTY_READONLY_AUTO(int, totalPlay) = 0;
        Q_PROPERTY_READONLY_AUTO(int, followers) = 0;
        Q_PROPERTY_READONLY_AUTO(int, danmakus) = 0;
        Q_PROPERTY_READONLY_AUTO(QString, pubtime);
        Q_PROPERTY_READONLY_AUTO(QString, timeLength);
        Q_PROPERTY_READONLY_AUTO(QString, desc);
        Q_PROPERTY_READONLY_AUTO(float, score) = 0;
        Q_PROPERTY_READONLY_AUTO(int, ratingCount) = 0;
        Q_PROPERTY_READONLY_AUTO(QVariantList, celebrity);

        Q_PROPERTY_READONLY_AUTO(bool, hasSeries) = false;
        Q_PROPERTY_READONLY_AUTO(QString, seriesTitle);
        Q_PROPERTY_READONLY_AUTO(QVariantList, seasonList);

        Q_PROPERTY_READONLY_AUTO(bool, hasEpisode) = false;
        Q_PROPERTY_READONLY_AUTO(QVariantList, episodeList);
    public:
        VIEW_MODEL_COROUTINE_TASK(LoadBangumi)
        VIEW_MODEL_COROUTINE_TASK(LoadRecommend)
    private slots:
        void onLoadBangumiSignal(const QVariantMap &args);
    };
}
