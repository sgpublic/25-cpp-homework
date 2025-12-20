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
        score(body->data->rating->score);
        ratingCount(body->data->rating->count);

        celebrity(utils::dtoToQVariant(*body->data->celebrity));

        auto seasonList = QVariantList();
        for (const auto& seasons : *body->data->findModules<PgcSeasonResp::Data::SeasonModule>()) {
            hasSeries(true);
            seriesTitle(seasons->title->data());
            seasonList += utils::dtoToQVariant(*seasons->data->seasons);
        }
        this->seasonList(seasonList);

        auto episodeList = QVariantList();
        for (const auto& episodes : *body->data->findModules<PgcSeasonResp::Data::EpisodeModule>()) {
            hasEpisode(true);
            episodeList += utils::dtoToQVariant(*episodes->data->episodes);
        }
        this->episodeList(episodeList);
    }

    void BangumiWindowViewModel::onLoadRecommend(const QVariantMap &args) {
        const auto& dto = PgcSeasonRecommendReq::createShared();
        dto->season_id = seasonId();
        dto->access_key = SettingModule::getInstance()->accessToken().toStdString();
        const auto& result = _apiClient->pgc_season_recommend(dto->asSignedParams());
    }

    void BangumiWindowViewModel::onLoadBangumiSignal(const QVariantMap &args) {
        seasonId(args.value("season_id").toInt());
        episodeId(args.value("episode_id").toInt());
        OATPP_LOGd("BangumiWindowViewModel::onLoadBangumiSignal", "seasonId: {}, episodeId: {}", seasonId(), episodeId());
        requestLoadBangumi();
        requestLoadRecommend();
    }

}
