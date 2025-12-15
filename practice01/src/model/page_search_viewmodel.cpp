//
// Created by Haven Madray on 2025/12/15.
//
#include "model/page_search_viewmodel.h"

#include "core/api/dto/api_dto.h"

using namespace biliqt::core::module;
using namespace biliqt::core::api;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api::client;

namespace biliqt::model {

    SearchPageViewModel::SearchPageViewModel(QObject *parent): ViewModel(parent) {
        _apiClient = ApiClient::createShared();
    }

    void SearchPageViewModel::onLoadSearchResult(const QVariantMap &args) {
        const std::string searchText = args.value("search_text").toString().toStdString();
        const auto& dto = WebSearchTypeReq::createShared();
        dto->keyword = searchText;
        dto->page = currentPage();
        const auto& result = _apiClient->web_search_type(dto->asWbiParams());
        const auto& body = readRespBody<WebSearchTypeResp>(result);
        qDebug() << "code:" << body->code << "message:" << body->message->data();
        if (body->code != 0) {
            return;
        }
    }

}
