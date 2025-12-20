//
// Created by Haven Madray on 2025/12/15.
//
#include "viewmodel/page_search_viewmodel.h"

#include <iomanip>

#include "core/api/dto/api_dto.h"
#include "utils/oatpp_dto.h"

using namespace biliqt::core::module;
using namespace biliqt::core::api;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api::client;

namespace biliqt::viewmodel {

    SearchPageViewModel::SearchPageViewModel(QObject *parent): ViewModel(parent) {
        _apiClient = ApiClient::createShared();
    }

    void SearchPageViewModel::onLoadSearchResult(const QVariantMap &args) {
        searchResultList(QVariantList());

        const std::string searchText = (args.contains("search_text") ? args.value("search_text").toString() : this->searchText()).toStdString();
        const int page = args.contains("page") ? args.value("page").toInt() : 1;
        const auto& dto = WebSearchTypeReq::createShared();
        dto->keyword = searchText;
        dto->page = page;
        const auto& result = _apiClient->web_search_type(dto->asWbiParams());
        const auto& body = readRespBody<WebSearchTypeResp>(result);
        OATPP_LOGd("SearchPageViewModel::onLoadSearchResult", "code: {}, message: {}", body->code, body->message);
        if (body->code != 0 || body->data->v_voucher != nullptr) {
            return;
        }

        OATPP_LOGd("SearchPageViewModel::onLoadSearchResult", "search result count: {}", body->data->result->size());

        searchResultList(utils::dtoToQVariant(*body->data->result));
        pageCount(body->data->numPages);
        currentPage(body->data->page);
        numResults(body->data->numResults);
        pagesize(body->data->pagesize);

        OATPP_LOGd("SearchPageViewModel::onLoadSearchResult", "search page count: {}", pageCount());
    }

    QString SearchPageViewModel::timeFromTimestamp(long long timestamp) {
        const std::chrono::system_clock::time_point now_time_t = std::chrono::system_clock::from_time_t(timestamp);
        const std::time_t time_t_val = std::chrono::system_clock::to_time_t(now_time_t);
        const std::tm tm = *std::localtime(&time_t_val);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");
        return oss.str().data();
    }

}
