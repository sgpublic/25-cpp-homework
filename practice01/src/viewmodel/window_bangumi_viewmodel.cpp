//
// Created by Haven Madray on 2025/12/12.
//

#include "viewmodel/window_bangumi_viewmodel.h"
#include "core/api/dto/api_dto.h"
#include "core/module/global_signal_module.h"

using namespace biliqt::core::api;
using namespace biliqt::core::module;
using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;

namespace biliqt::viewmodel {

    BangumiWindowViewModel::BangumiWindowViewModel(QObject *parent) : ViewModel(parent) {
        _apiClient = ApiClient::createShared();
        connect(GlobalSignalModule::getInstance(), &GlobalSignalModule::requestBangumiInfo, this, &BangumiWindowViewModel::onLoadBangumiSignal);
    }

    void BangumiWindowViewModel::onLoadBangumi(const QVariantMap &args) {
        const auto& dto = PgcSeasonReq::createShared();
        dto->season_id = seasonId();
        dto->access_key = SettingModule::getInstance()->accessToken().toStdString();
        const auto& result = _apiClient->pgc_season(dto->asSignedParams());
        const auto& body = readRespBody<PgcSeasonResp>(result);
        OATPP_LOGd("BangumiWindowViewModel::onLoadBangumi", "code: {}, message: {}", body->code, body->message);
        if (body->code != 0) {
            return;
        }

        title(body->data->season_title->data());
        cover(body->data->refine_cover->data());
        totalPlay(body->data->stat->views);
        followers(body->data->stat->favorite);
        danmakus(body->data->stat->danmakus);
        pubtime(body->data->publish->release_date_show->data());
        timeLength(body->data->publish->time_length_show->data());
        desc(body->data->evaluate->data());
        if (body->data->rating != nullptr) {
            hasScore(true);
            score(body->data->rating->score);
            ratingCount(body->data->rating->count);
        } else {
            hasScore(false);
        }

        if (body->data->celebrity != nullptr) {
            hasCelebrity(true);
            celebrityList(utils::dtoToQVariant(*body->data->celebrity));
        } else {
            hasCelebrity(false);
            celebrityList(QVariantList());
        }
        loadCelebritySlice();

        const auto& seasonModules = body->data->findModules<PgcSeasonResp::Data::SeasonModule>();
        auto seasonList = QVariantList();
        for (const auto& seasons : *seasonModules) {
            hasSeries(true);
            seriesTitle(seasons->title->data());
            seasonList += utils::dtoToQVariant(*seasons->data->seasons);
        }
        this->seasonList(seasonList);

        const auto& episodeModules = body->data->findModules<PgcSeasonResp::Data::EpisodeModule>();
        auto episodeList = QVariantList();
        for (const auto& episodes : *episodeModules) {
            hasEpisode(true);
            episodeList += utils::dtoToQVariant(*episodes->data->episodes);
        }
        this->episodeList(episodeList);
        loadEpisodeSlice();
    }

    void BangumiWindowViewModel::loadEpisodeSlice() {
        const int pageSize = ui_episodeList_coloumn() * 2;

        const double pageCount = ceil(static_cast<double>(episodeList().size()) / pageSize);
        OATPP_LOGd("BangumiWindowViewModel::loadEpisodeSlice", "pageCount: {}", pageCount);
        if (pageCount <= 0) {
            return;
        }
        episodePageCount(pageCount);

        if (pageCount < episodePageIndex()) {
            episodePageIndex(pageCount);
        }
        const int pageStart = (episodePageIndex() - 1) * pageSize;
        OATPP_LOGd("BangumiWindowViewModel::loadEpisodeSlice", "pageStart: {}, pageSize: {}", pageStart, pageSize);

        currentEpisodeList(episodeList().mid(pageStart, pageSize));
        OATPP_LOGd("BangumiWindowViewModel::loadEpisodeSlice", "episodeList size: {}, currentEpisodeList size: {}", episodeList().size(), currentEpisodeList().size());
    }

    void BangumiWindowViewModel::loadCelebritySlice() {
        const int pageSize = ui_celebrityList_coloumn();

        const double pageCount = ceil(static_cast<double>(celebrityList().size()) / pageSize);
        OATPP_LOGd("BangumiWindowViewModel::loadCelebritySlice", "pageCount: {}", pageCount);
        if (pageCount <= 0) {
            return;
        }
        celebrityPageCount(pageCount);

        if (pageCount < celebrityPageIndex()) {
            celebrityPageIndex(pageCount);
        }
        const int pageStart = (celebrityPageIndex() - 1) * pageSize;
        OATPP_LOGd("BangumiWindowViewModel::loadCelebritySlice", "pageStart: {}, pageSize: {}", pageStart, pageSize);

        currentCelebrityList(celebrityList().mid(pageStart, pageSize));
        OATPP_LOGd("BangumiWindowViewModel::loadCelebritySlice", "celebrityList size: {}, currentCelebrityList size: {}", celebrityList().size(), currentCelebrityList().size());
    }

    void BangumiWindowViewModel::onLoadRecommend(const QVariantMap &args) {
        const auto& dto = PgcSeasonRecommendReq::createShared();
        dto->season_id = seasonId();
        dto->access_key = SettingModule::getInstance()->accessToken().toStdString();
        const auto& result = _apiClient->pgc_season_recommend(dto->asSignedParams());
        const auto& body = readRespBody<PgcSeasonRecommendResp>(result);

        if (body->result != nullptr && body->result->season != nullptr) {
            hasRecommend(true);
            recommendList(utils::dtoToQVariant(*body->result->season));
        } else {
            hasRecommend(false);
            recommendList(QVariantList());
        }
    }

    void BangumiWindowViewModel::onLoadBangumiSignal(const QVariantMap &args) {
        seasonId(args.value("season_id").toInt());
        episodeId(args.value("episode_id").toInt());
        OATPP_LOGd("BangumiWindowViewModel::onLoadBangumiSignal", "seasonId: {}, episodeId: {}", seasonId(), episodeId());
        requestLoadBangumi();
        requestLoadRecommend();
    }

    void BangumiWindowViewModel::onPageWidthChanged(const double width) {
        const int maxWidth = 1300;
        ui_contentWidth(width - 200 > maxWidth ? maxWidth : width - 200);

        const int preEpisodePageLineCount = ui_episodeList_coloumn();
        int newEpisodePageLineCount;
        const double maxEpisodeCellWidth = maxWidth / 6;
        if (const double cellWidth = ui_contentWidth() / 5; cellWidth > maxEpisodeCellWidth) {
            newEpisodePageLineCount = 6;
        } else {
            newEpisodePageLineCount = 5;
        }
        ui_episodeList_cellWidth(ui_contentWidth() / newEpisodePageLineCount);
        ui_episodeList_cellContentWidth(ui_episodeList_cellWidth() - 2 * ui_episodeList_cellPadding());
        ui_episodeList_cellContentCoverHeight(ui_episodeList_cellContentWidth() / 8 * 5);
        ui_episodeList_cellContentHeight(ui_episodeList_cellContentCoverHeight() + 20);
        ui_episodeList_cellHeight(ui_episodeList_cellContentHeight() + 2 * ui_episodeList_cellPadding());
        ui_episodeList_height(ui_episodeList_cellHeight() * 2);
        if (preEpisodePageLineCount != newEpisodePageLineCount) {
            ui_episodeList_coloumn(newEpisodePageLineCount);
            loadEpisodeSlice();
        }

        const int preCelebrityPageLineCount = ui_episodeList_coloumn();
        int newCelebrityPageLineCount;
        const double maxCelebrityCellWidth = maxWidth / 7;
        if (const double cellWidth = ui_contentWidth() / 6; cellWidth > maxCelebrityCellWidth) {
            newCelebrityPageLineCount = 7;
        } else {
            newCelebrityPageLineCount = 6;
        }
        ui_celebrityList_cellWidth(ui_contentWidth() / newCelebrityPageLineCount);
        ui_celebrityList_cellContentWidth(ui_celebrityList_cellWidth() - 2 * ui_celebrityList_cellPadding());
        ui_celebrityList_cellContentCoverHeight(ui_celebrityList_cellContentWidth() / 3 * 4);
        ui_celebrityList_cellContentHeight(ui_celebrityList_cellContentCoverHeight() + 40);
        ui_celebrityList_cellHeight(ui_celebrityList_cellContentHeight() + 2 * ui_celebrityList_cellPadding());
        ui_celebrityList_height(ui_celebrityList_cellHeight() * 2);
        if (preCelebrityPageLineCount != newCelebrityPageLineCount) {
            ui_celebrityList_coloumn(newCelebrityPageLineCount);
            loadCelebritySlice();
        }

        const double maxRecommendCellWidth = maxWidth / 7;
        if (const double cellWidth = ui_contentWidth() / 6; cellWidth > maxRecommendCellWidth) {
            ui_recommendList_coloumn(7);
        } else {
            ui_recommendList_coloumn(6);
        }
        ui_recommendList_cellWidth(ui_contentWidth() / ui_recommendList_coloumn());
        ui_recommendList_cellContentWidth(ui_recommendList_cellWidth() - 2 * ui_recommendList_cellPadding());
        ui_recommendList_cellContentCoverHeight(ui_recommendList_cellContentWidth() / 3 * 4);
        ui_recommendList_cellContentHeight(ui_recommendList_cellContentCoverHeight() + 20);
        ui_recommendList_cellHeight(ui_recommendList_cellContentHeight() + 2 * ui_recommendList_cellPadding());
    }

}
