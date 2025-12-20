//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include "core/api/client/api_client.h"
#include "dto/bangumi_dto.h"

namespace biliqt::model {
    class BangumiModel: public QObject {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> apiClient;
    public:
        explicit BangumiModel(QObject *parent = nullptr);

        oatpp::Object<dto::BangumiInfoModel> getBangumiInfo(int seasonId);

        oatpp::Object<dto::BangumiRecommendModel> getBangumiRecommend(int seasonId);
    };
}
