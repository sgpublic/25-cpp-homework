//
// Created by coder on 12/4/25.
//
#include "model/page_home_viewmodel.h"

#include "core/api/dto/api_dto.h"
#include "core/module/setting_module.h"

using namespace biliqt::utils;
using namespace biliqt::core::module;
using namespace biliqt::core::api;
using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;

namespace biliqt::model {

    HomePageViewModel::HomePageViewModel(QObject *parent): ViewModel(parent) {
        _apiClient = ApiClient::createShared();
    }

    void HomePageViewModel::onLoadSearchSuggest(const QVariantMap& args) {

    }

    void HomePageViewModel::onLoadBannerData(const QVariantMap& args) {
        const auto dto = PgcPageReq::createShared();
        dto->access_key = qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        const auto result = _apiClient->pgc_page(dto->asSignedParams());
        const auto body = readRespBody(result);
        const int code = body["code"];
        const std::string message = body["message"];
        if (code != 0) {
            return;
        }
        const auto& banner = findModules<PgcPageResp::ModuleItems>(body["result"], "topic");
        qDebug() << "banner image count:" << banner->size();
        bannerData(*banner);
    }

    void HomePageViewModel::onLoadBangumiList(const QVariantMap &args) {
        if (!_bangumiListHasNext || _isLoadBangumiList) {
            return;
        }
        _isLoadBangumiList = true;
        const int isRefresh = args.value("is_refresh").toBool() ? 1 : 0;
        const auto dto = PgcPageBangumiReq::createShared();
        dto->access_key = qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        dto->cursor = _bangumiListCursor;
        dto->is_refresh = isRefresh;
        const auto result = _apiClient->pgc_page_bangumi(dto->asSignedParams());
        const auto body = readRespBody(result);
        const int code = body["code"];
        const std::string message = body["message"];
        qDebug() << "onLoadBangumiList" << "code:" << code << ", messasge:" << message;
        if (code != 0) {
            _isLoadBangumiList = false;
            return;
        }
        const auto& list = findModules<PgcPageBangumiResp::ModuleItems>(body["result"], "double_feed");
        _bangumiListCursor = body["result"]["next_cursor"];
        _bangumiListHasNext = body["result"]["has_next"] == 1;
        qDebug() << "bangumi item count:" << list->size();
        if (isRefresh) {
            emit clearBangumiList();
        }
        for (const auto& item : *list) {
            const auto& map = qvariant_cast<QVariantMap>(item);
            emit addBangumiData(map);
        }
        _isLoadBangumiList = false;
    }

    void HomePageViewModel::onPageWidthChanged(const double width) {
        constexpr int maxWidth = 1700;
        ui_listWidth(width > maxWidth ? maxWidth : width);

        const double maxCellWidth = maxWidth / 5;
        if (const double cellWidth = ui_listWidth() / 4; cellWidth > maxCellWidth) {
            ui_listCellWidth(ui_listWidth() / 5);
        } else {
            ui_listCellWidth(cellWidth);
        }
        ui_listCellContentWidth(ui_listCellWidth() - 2 * ui_listCellPadding());

        ui_listCellContentCoverHeight(ui_listCellContentWidth() / 8 * 5);
        ui_listCellContentHeight(ui_listCellContentCoverHeight() + 40);
        ui_listCellHeight(ui_listCellContentHeight() + 2 * ui_listCellPadding());
    }
}
