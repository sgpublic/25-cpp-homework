//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include "core/api/client/api_client.h"
#include "core/api/client/search_client.h"
#include "dto/search_dto.h"

namespace biliqt::model {
    class SearchModel: public QObject {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> apiClient;
        std::shared_ptr<core::api::client::SearchClient> searchClient;
    public:
        explicit SearchModel(QObject *parent = nullptr);

        oatpp::Object<dto::SearchResultModel> search(const std::string &keyword, int page);

        oatpp::Object<dto::SearchSuggestModel> suggest(const std::string &keyword);
    };
}
