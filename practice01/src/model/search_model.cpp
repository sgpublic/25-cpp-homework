//
// Created by Haven Madray on 2025/12/20.
//
#include "model/search_model.h"

#include "core/api/dto/api_dto.h"
#include "core/api/dto/search_dto.h"

using namespace biliqt::core::api;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api::client;
using namespace biliqt::model::dto;
using namespace biliqt::core::module;

namespace biliqt::model {

    SearchModel::SearchModel(QObject *parent): QObject(parent) {
        apiClient = ApiClient::createShared();
        searchClient = SearchClient::createShared();
    }

    oatpp::Object<SearchResultModel> SearchModel::search(const std::string &keyword, const int page) {
        const auto& dto = WebSearchTypeReq::createShared();
        dto->keyword = keyword;
        dto->page = page;
        const auto& result = apiClient->web_search_type(dto->asWbiParams());
        const auto& body = readRespBody<WebSearchTypeResp>(result);
        OATPP_LOGd("SearchModel::search", "code: {}, message: {}", body->code, body->message);
        if (body->code != 0) {
            throw std::runtime_error(body->message);
        }
        if (body->data->v_voucher != nullptr) {
            throw std::runtime_error("risk control triggered!");
        }
        const auto& searchResult = SearchResultModel::createShared();
        searchResult->totalCount = body->data->numResults;
        searchResult->pageCount = body->data->numResults;
        searchResult->pageSize = body->data->pagesize;
        searchResult->currentPage = body->data->page;
        const auto& resultList = oatpp::List<oatpp::Object<SearchResultModel::Item>>::createShared();
        if (body->data->result != nullptr) {
            for (const auto& resultItem : *body->data->result) {
                const auto& resultDto = SearchResultModel::Item::createShared();
                resultDto->season_id = resultItem->season_id;
                resultDto->title = resultItem->title;
                resultDto->desc = resultItem->desc;
                resultDto->cover = resultItem->cover;
                resultDto->styles = resultItem->styles;
                resultDto->pubtime = resultItem->pubtime;
                resultDto->index_show = resultItem->index_show;
                resultList->emplace_back(resultDto);
            }
        }
        searchResult->data = resultList;
        OATPP_LOGd("SearchModel::search", "search result count: {}", resultList->size());
        return searchResult;
    }

    oatpp::Object<SearchSuggestModel> SearchModel::suggest(const std::string &keyword) {
        const auto& dto = SearchSuggestReq::createShared();
        dto->term = keyword;
        const auto& result = searchClient->suggest(dto->asSignedParams());
        const auto& body = readRespBody<SearchSuggestResp>(result);
        OATPP_LOGd("MainWindowViewModel::onLoadSearchSuggest", "code: {}", body->code);
        if (body->code != 0) {
            throw std::runtime_error("error");
        }

        const auto& suggests = SearchSuggestModel::createShared();
        const auto& suggestList = oatpp::List<oatpp::Object<SearchSuggestModel::Item>>::createShared();
        for (const auto& suggestItem : *body->result->tag) {
            const auto& suggestDto = SearchSuggestModel::Item::createShared();
            suggestDto->title = suggestItem->name;
            suggestList->emplace_back(suggestDto);
        }
        suggests->data = suggestList;
        return suggests;
    }
}
