//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include "core/api/client/api_client.h"
#include "core/api/dto/api_dto.h"
#include "dto/page_search_dto.h"

namespace biliqt::model {
    class SearchPageModel: public QObject {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> apiClient;
    public:
        explicit SearchPageModel(QObject *parent = nullptr);

        oatpp::Object<dto::SearchResultModel> search(std::string keyword, int page);
    };
}
