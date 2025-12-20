//
// Created by Haven Madray on 2025/12/12.
//

#pragma once

#include "base_viewmodel.h"
#include "core/api/client/api_client.h"
#include "model/bangumi_model.h"
#include "utils/stdafx.h"

namespace biliqt::viewmodel {
    class BangumiWindowViewModel: public ViewModel {
        Q_OBJECT
    private:
        std::shared_ptr<model::BangumiModel> bangumiModel;
    public:
        explicit BangumiWindowViewModel(QObject *parent = nullptr);
        Q_PROPERTY_READONLY_AUTO(int, seasonId) = -1;
        Q_PROPERTY_READONLY_AUTO(int, episodeId) = -1;

        Q_PROPERTY_READONLY_AUTO(QString, title);
        Q_PROPERTY_READONLY_AUTO(QString, cover);
        Q_PROPERTY_READONLY_AUTO(int, totalPlay) = 0;
        Q_PROPERTY_READONLY_AUTO(int, followers) = 0;
        Q_PROPERTY_READONLY_AUTO(int, danmakus) = 0;
        Q_PROPERTY_READONLY_AUTO(QString, pubtime);
        Q_PROPERTY_READONLY_AUTO(QString, timeLength);
        Q_PROPERTY_READONLY_AUTO(QString, desc);
        Q_PROPERTY_READONLY_AUTO(bool, hasScore) = false;
        Q_PROPERTY_READONLY_AUTO(float, score) = 0;
        Q_PROPERTY_READONLY_AUTO(int, ratingCount) = 0;

        Q_PROPERTY_READONLY_AUTO(bool, hasEpisode) = false;
        Q_PROPERTY_READONLY_AUTO(QVariantList, episodeList);
        Q_PROPERTY_AUTO(int, episodePageIndex) = 1;
        Q_PROPERTY_READONLY_AUTO(int, episodePageCount) = 0;
        Q_PROPERTY_READONLY_AUTO(QVariantList, currentEpisodeList);
        Q_PROPERTY_READONLY_AUTO(double, ui_contentWidth) = 0;
        Q_PROPERTY_READONLY_AUTO(int, ui_episodeList_coloumn) = 1;
        Q_PROPERTY_READONLY_AUTO(double, ui_episodeList_height) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_episodeList_cellPadding) = 8;
        Q_PROPERTY_READONLY_AUTO(double, ui_episodeList_cellWidth) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_episodeList_cellHeight) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_episodeList_cellContentWidth) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_episodeList_cellContentHeight) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_episodeList_cellContentCoverHeight) = 0;

        Q_PROPERTY_READONLY_AUTO(bool, hasSeries) = false;
        Q_PROPERTY_READONLY_AUTO(QString, seriesTitle);
        Q_PROPERTY_READONLY_AUTO(QVariantList, seriesList);
        Q_PROPERTY_READONLY_AUTO(int, ui_seriesList_coloumn) = 1;
        Q_PROPERTY_READONLY_AUTO(double, ui_seriesList_cellPadding) = 8;
        Q_PROPERTY_READONLY_AUTO(double, ui_seriesList_cellWidth) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_seriesList_cellHeight) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_seriesList_cellContentWidth) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_seriesList_cellContentHeight) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_seriesList_cellContentCoverHeight) = 0;

        Q_PROPERTY_READONLY_AUTO(bool, hasCelebrity) = false;
        Q_PROPERTY_READONLY_AUTO(QVariantList, celebrityList);
        Q_PROPERTY_AUTO(int, celebrityPageIndex) = 1;
        Q_PROPERTY_READONLY_AUTO(int, celebrityPageCount) = 0;
        Q_PROPERTY_READONLY_AUTO(QVariantList, currentCelebrityList);
        Q_PROPERTY_READONLY_AUTO(int, ui_celebrityList_coloumn) = 1;
        Q_PROPERTY_READONLY_AUTO(double, ui_celebrityList_height) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_celebrityList_cellPadding) = 8;
        Q_PROPERTY_READONLY_AUTO(double, ui_celebrityList_cellWidth) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_celebrityList_cellHeight) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_celebrityList_cellContentWidth) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_celebrityList_cellContentHeight) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_celebrityList_cellContentCoverHeight) = 0;

        Q_PROPERTY_READONLY_AUTO(bool, hasRecommend) = false;
        Q_PROPERTY_READONLY_AUTO(QVariantList, recommendList);
        Q_PROPERTY_READONLY_AUTO(int, ui_recommendList_coloumn) = 1;
        Q_PROPERTY_READONLY_AUTO(double, ui_recommendList_cellPadding) = 8;
        Q_PROPERTY_READONLY_AUTO(double, ui_recommendList_cellWidth) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_recommendList_cellHeight) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_recommendList_cellContentWidth) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_recommendList_cellContentHeight) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_recommendList_cellContentCoverHeight) = 0;
    public:
        VIEW_MODEL_COROUTINE_TASK(LoadBangumi)
        VIEW_MODEL_COROUTINE_TASK(LoadRecommend)
    public:
        Q_INVOKABLE void onPageWidthChanged(double width);
        Q_INVOKABLE void loadEpisodeSlice();
        Q_INVOKABLE void loadCelebritySlice();
    private slots:
        void onLoadBangumiSignal(const QVariantMap &args);
    };
}
