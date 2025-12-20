//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include "core/api/client/api_client.h"
#include "core/api/dto/api_dto.h"
#include "dto/page_mine_dto.h"

namespace biliqt::model {
    class MinePageModel: public QObject {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> apiClient;
    public:
        explicit MinePageModel(QObject *parent = nullptr);

        oatpp::Object<dto::MineCurrentWatchingModel> getCurrentWatchingList();

        oatpp::Object<dto::MineFollowListModel> getFollowList(int status, int page);
    };
}
