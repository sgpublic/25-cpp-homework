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
        bangumiModel = std::make_shared<model::BangumiModel>(parent);
        connect(GlobalSignalModule::getInstance(), &GlobalSignalModule::requestBangumiInfo, this, &BangumiWindowViewModel::onLoadBangumiSignal);
    }

    void BangumiWindowViewModel::onLoadBangumi(const QVariantMap &args) {
        try {
            const auto& data = bangumiModel->getBangumiInfo(seasonId());

            title(data->metaData->title->data());
            cover(data->metaData->cover->data());
            totalPlay(data->metaData->totalPlay);
            followers(data->metaData->followers);
            danmakus(data->metaData->danmakus);
            pubtime(data->metaData->pubtime->data());
            timeLength(data->metaData->state->data());
            desc(data->metaData->desc->data());

            if (data->rating != nullptr) {
                score(data->rating->score);
                ratingCount(data->rating->count);
                hasScore(true);
            } else {
                hasScore(false);
            }

            if (data->celebrity != nullptr) {
                celebrityList(utils::dtoToQVariant(*data->celebrity));
                hasCelebrity(true);
            } else {
                hasCelebrity(false);
            }
            loadCelebritySlice();

            if (data->series != nullptr) {
                seriesTitle(data->series->title->data());
                seriesList(utils::dtoToQVariant(*data->series->seasons));
                hasSeries(true);
            } else {
                hasSeries(false);
            }

            if (data->episodes != nullptr) {
                episodeList(utils::dtoToQVariant(*data->episodes));
                hasEpisode(true);
            } else {
                hasEpisode(false);
            }
            loadEpisodeSlice();
        } catch (std::runtime_error& e) {
            emit GlobalSignalModule::getInstance()->showToastOnBangumiWindow(false, qtTrId("err_bangumiInfo_load").arg(e.what()));
        }
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

        if (ui_episodeList_coloumn() > episodeList().size()) {
            ui_episodeList_height(ui_episodeList_cellHeight());
        } else {
            ui_episodeList_height(ui_episodeList_cellHeight() * 2);
        }
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
        try {
            if (const auto& result = bangumiModel->getBangumiRecommend(seasonId()); result->data != nullptr) {
                recommendList(utils::dtoToQVariant(*result->data));
                hasRecommend(true);
            } else {
                hasRecommend(false);
            }
        } catch (std::runtime_error& e) {
            // TODO: add error message
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
        if (preEpisodePageLineCount != newEpisodePageLineCount) {
            ui_episodeList_coloumn(newEpisodePageLineCount);
            loadEpisodeSlice();
        }

        const double maxSeriesCellWidth = maxWidth / 7;
        if (const double cellWidth = ui_contentWidth() / 6; cellWidth > maxSeriesCellWidth) {
            ui_seriesList_coloumn(7);
        } else {
            ui_seriesList_coloumn(6);
        }
        ui_seriesList_cellWidth(ui_contentWidth() / ui_seriesList_coloumn());
        ui_seriesList_cellContentWidth(ui_seriesList_cellWidth() - 2 * ui_seriesList_cellPadding());
        ui_seriesList_cellContentCoverHeight(ui_seriesList_cellContentWidth() / 3 * 4);
        ui_seriesList_cellContentHeight(ui_seriesList_cellContentCoverHeight() + 20);
        ui_seriesList_cellHeight(ui_seriesList_cellContentHeight() + 2 * ui_seriesList_cellPadding());

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
