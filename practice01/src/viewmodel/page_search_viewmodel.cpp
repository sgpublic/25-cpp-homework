//
// Created by Haven Madray on 2025/12/15.
//
#include "viewmodel/page_search_viewmodel.h"

#include <iomanip>

#include "core/module/global_signal_module.h"
#include "utils/oatpp_dto.h"

using namespace biliqt::core::module;
using namespace biliqt::core::api;
using namespace biliqt::model;
using namespace biliqt::core::api::client;

namespace biliqt::viewmodel {

    SearchPageViewModel::SearchPageViewModel(QObject *parent): ViewModel(parent) {
        searchModel = std::make_shared<SearchModel>(parent);
    }

    void SearchPageViewModel::onLoadSearchResult(const QVariantMap &args) {
        searchResultList(QVariantList());
        pageCount(0);
        currentPage(1);
        numResults(0);
        pagesize(0);

        try {
            const std::string searchText = (args.contains("search_text") ? args.value("search_text").toString() : this->searchText()).toStdString();
            const int page = args.contains("page") ? args.value("page").toInt() : 1;
            const auto& result = searchModel->search(searchText, page);

            searchResultList(utils::dtoToQVariant(*result->data));
            pageCount(result->pageCount);
            currentPage(result->currentPage);
            numResults(result->totalCount);
            pagesize(result->pageSize);

            OATPP_LOGd("SearchPageViewModel::onLoadSearchResult", "search page count: {}", pageCount());
        } catch (std::runtime_error &e) {
            emit GlobalSignalModule::getInstance()->showToastOnMainWindow(false, qtTrId("err_search_load").arg(e.what()));
        }
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
