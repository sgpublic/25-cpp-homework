//
// Created by Haven Madray on 2025/12/12.
//
#include "viewmodel/page_mine_viewmodel.h"

#include "core/module/setting_module.h"
#include "utils/oatpp_dto.h"

using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api;
using namespace biliqt::core::module;
using namespace biliqt::utils;
using namespace biliqt::model;

namespace biliqt::viewmodel {

    MinePageViewModel::MinePageViewModel(QObject *parent): ViewModel(parent) {
        minePageModel = std::make_shared<MinePageModel>(parent);
        requestLoadCurrentWatching();
        requestLoadFollowWant();
        requestLoadFollowWatched();
        requestLoadFollowWatching();
    }

    void MinePageViewModel::onLoadCurrentWatching(const QVariantMap &args) {
        try {
            const auto followData = minePageModel->getCurrentWatchingList();
            OATPP_LOGd("MinePageViewModel::onLoadCurrentWatching", "current watching count: {}", followData->data->size());
            currentWatching(dtoToQVariant(*followData->data));
        } catch (std::runtime_error& e) {
            // TODO: add error message
        }
    }

    void MinePageViewModel::onLoadFollowWatching(const QVariantMap &args) {
        requestLoadFollow(
            args, followWatchingState,
            [this] {
                emit clearFollowWatching();
            },
            [this](const QVariantMap& data) {
                emit addFollowWatching(data);
            }
        );
    }

    void MinePageViewModel::onLoadFollowWatched(const QVariantMap &args) {
        requestLoadFollow(
            args, followWatchedState,
            [this] {
                emit clearFollowWatched();
            },
            [this](const QVariantMap& data) {
                emit addFollowWatched(data);
            }
        );
    }

    void MinePageViewModel::onLoadFollowWant(const QVariantMap &args) {
        requestLoadFollow(
            args, followWantState,
            [this] {
                emit clearFollowWant();
            },
            [this](const QVariantMap& data) {
                emit addFollowWant(data);
            }
        );
    }

    void MinePageViewModel::requestLoadFollow(
        const QVariantMap &args, PageState& state,
        const std::function<void()> &clearSignal,
        const std::function<void(const QVariantMap&)> &addSignal
    ) {
        const int isRefresh = args.value("is_refresh").toBool();
        if ((!isRefresh && !state.hasNext) || state.loading) {
            return;
        }
        state.loading = true;
        try {
            const auto& followList = minePageModel->getFollowList(state.status, state.currentPage + 1);
            if (isRefresh) {
                clearSignal();
            }
            for (const auto& item : *followList->data) {
                addSignal(dtoToQVariant(item));
            }
            state.currentPage = followList->current_page;
            state.hasNext = followList->has_next;
        } catch (std::runtime_error& e) {
            // TODO: add error message
        }
        state.loading = false;
    }

    void MinePageViewModel::onPageWidthChanged(double width) {
        constexpr int maxWidth = 1700;
        ui_listWidth(width > maxWidth ? maxWidth : width);

        const double maxCellWidth = maxWidth / 7;
        if (const double cellWidth = ui_listWidth() / 6; cellWidth > maxCellWidth) {
            ui_listCellWidth(ui_listWidth() / 7);
        } else {
            ui_listCellWidth(cellWidth);
        }
        ui_listCellContentWidth(ui_listCellWidth() - 2 * ui_listCellPadding());

        ui_listCellContentCoverHeight(ui_listCellContentWidth() / 3 * 4);
        ui_listCellContentHeight(ui_listCellContentCoverHeight() + 20);
        ui_listCellHeight(ui_listCellContentHeight() + 2 * ui_listCellPadding());
    }
}
