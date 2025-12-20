//
// Created by coder on 12/4/25.
//
#include "viewmodel/page_home_viewmodel.h"

#include "core/api/dto/api_dto.h"
#include "core/module/setting_module.h"
#include "utils/oatpp_dto.h"

using namespace biliqt::utils;
using namespace biliqt::model;
using namespace biliqt::core::module;
using namespace biliqt::core::api;
using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;

namespace biliqt::viewmodel {

    HomePageViewModel::HomePageViewModel(QObject *parent): ViewModel(parent) {
        homePageModel = std::make_shared<HomePageModel>(parent);
    }

    void HomePageViewModel::onLoadBannerData(const QVariantMap& args) {
        try {
            const auto& bannerDataList = homePageModel->getBannerData();
            OATPP_LOGd("HomePageViewModel::onLoadBannerData", "banner image count: {}", bannerDataList->data->size());
            bannerData(dtoToQVariant(*bannerDataList->data));
        } catch (std::runtime_error& e) {
            // TODO: add error message
        }
    }

    void HomePageViewModel::onLoadBangumiList(const QVariantMap &args) {
        if (!_bangumiListHasNext || _isLoadBangumiList) {
            return;
        }
        try {
            _isLoadBangumiList = true;
            const int isRefresh = args.value("is_refresh").toBool() ? 1 : 0;
            const auto& body = homePageModel->getBangumiList(_bangumiListCursor, isRefresh);
            _bangumiListCursor = body->next_cursor;
            _bangumiListHasNext = body->has_next;
            OATPP_LOGd("HomePageViewModel::onLoadBangumiList", "bangumi item count: {}", body->data->size());
            if (isRefresh) {
                emit clearBangumiList();
            }
            for (const auto& item : *body->data) {
                const auto& map = dtoToQVariant(item);
                emit addBangumiData(map);
            }
        } catch (std::runtime_error& e) {
            // TODO: add error message
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
