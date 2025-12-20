//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include "core/api/client/api_client.h"
#include "dto/follow_dto.h"

namespace biliqt::model {
    class FollowModel: public QObject {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> apiClient;
    public:
        explicit FollowModel(QObject *parent = nullptr);

        oatpp::Object<dto::MineCurrentWatchingModel> getCurrentWatchingList();

        oatpp::Object<dto::MineFollowListModel> getFollowList(int status, int page);
    };
}
