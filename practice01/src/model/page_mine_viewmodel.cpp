//
// Created by Haven Madray on 2025/12/12.
//
#include "model/page_mine_viewmodel.h"

#include "core/api/dto/api_dto.h"
#include "core/module/setting_module.h"
#include "utils/oatpp_dto.h"

using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api;
using namespace biliqt::core::module;
using namespace biliqt::utils;

namespace biliqt::model {

    MinePageViewModel::MinePageViewModel(QObject *parent): ViewModel(parent) {
        _apiClient = ApiClient::createShared();
        requestLoadCurrentWatching();
        requestLoadFollowWant();
        requestLoadFollowWatched();
        requestLoadFollowWatching();
    }

    void MinePageViewModel::onLoadCurrentWatching(const QVariantMap &args) {
        const auto dto = PgcPagePcBangumiTabReq::createShared();
        dto->access_key = qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        const auto result = _apiClient->pgc_page_pc_bangumi_tab(dto->asSignedParams());
        const auto body = readRespBody<PgcPagePcBangumiTabResp>(result);
        qDebug() << "code:" << body->code << "message:" << body->message->data();
        if (body->code != 0) {
            return;
        }
        const auto follow = body->data->findModules<PgcPagePcBangumiTabResp::Data::FollowModule>();
        qDebug() << "current watching count:" << follow->size();
        currentWatching(dtoToQVariant(*follow));
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
        const auto dto = PgcFollowBangumiReq::createShared();
        dto->access_key = qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        dto->pn = state.currentPage + 1;
        dto->status = state.status;
        const auto result = _apiClient->pgc_follow_bangumi(dto->asSignedParams());
        const auto body = readRespBody<PgcFollowBangumiResp>(result);
        qDebug() << "code:" << body->code << "message:" << body->message->data();
        if (body->code != 0) {
            return;
        }
        const auto followList = body->result;
        if (isRefresh) {
            clearSignal();
        }
        for (const auto& item : *body->result->follow_list) {
            addSignal(dtoToQVariant(item));
        }
        state.currentPage = dto->pn;
        state.hasNext = body->result->has_next;
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
