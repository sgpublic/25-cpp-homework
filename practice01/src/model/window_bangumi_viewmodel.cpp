//
// Created by Haven Madray on 2025/12/12.
//

#include "model/window_bangumi_viewmodel.h"
#include "core/api/dto/api_dto.h"
#include "core/module/global_signal_module.h"

using namespace biliqt::core::api;
using namespace biliqt::core::module;
using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;

namespace biliqt::model {

    BangumiWindowViewModel::BangumiWindowViewModel(QObject *parent) : ViewModel(parent) {
        _apiClient = ApiClient::createShared();
        connect(GlobalSignalModule::getInstance(), &GlobalSignalModule::requestBangumiInfo, this, &BangumiWindowViewModel::requestLoadBangumi);
    }

    void BangumiWindowViewModel::onLoadBangumi(const QVariantMap &args) {
        const int seasonId = args.value("season_id").toInt();
        const int episodeId = args.value("episode_id").toInt();
        qDebug() << "seasonId:" << seasonId << "episodeId:" << episodeId;

        const auto& dto = PgcSeasonReq::createShared();
        dto->season_id = seasonId;
        dto->access_key = SettingModule::getInstance()->accessToken().toStdString();
        const auto& result = _apiClient->pgc_season(dto->asSignedParams());
        const auto& body = readRespBody<PgcSeasonResp>(result);
        qDebug() << "code:" << body->code << "message:" << body->message->data();
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
    }

    void BangumiWindowViewModel::onLoadBangumiSignal(const QVariantMap &args) {
        requestLoadBangumi(args);
    }

}
