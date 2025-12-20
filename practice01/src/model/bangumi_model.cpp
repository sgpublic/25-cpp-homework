//
// Created by Haven Madray on 2025/12/20.
//
#include "model/bangumi_model.h"

#include "core/api/dto/api_dto.h"

using namespace biliqt::core::api;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api::client;
using namespace biliqt::model::dto;
using namespace biliqt::core::module;

namespace biliqt::model {

    BangumiModel::BangumiModel(QObject *parent): QObject(parent) {
        apiClient = ApiClient::createShared();
    }

    oatpp::Object<BangumiInfoModel> BangumiModel::getBangumiInfo(const int seasonId) {
        const auto& dto = PgcSeasonReq::createShared();
        dto->season_id = seasonId;
        dto->access_key = SettingModule::getInstance()->accessToken().toStdString();
        const auto& result = apiClient->pgc_season(dto->asSignedParams());
        const auto& body = readRespBody<PgcSeasonResp>(result);
        OATPP_LOGd("BangumiModel::getBangumiInfo", "code: {}, message: {}", body->code, body->message);
        if (body->code != 0) {
            throw std::runtime_error(body->message);
        }
        const auto& bangumiInfo = BangumiInfoModel::createShared();
        bangumiInfo->metaData = BangumiInfoModel::MetaData::createShared();
        bangumiInfo->metaData->title = body->data->season_title;
        bangumiInfo->metaData->cover = body->data->refine_cover;
        bangumiInfo->metaData->desc = body->data->evaluate;
        bangumiInfo->metaData->pubtime = body->data->publish->release_date_show;
        bangumiInfo->metaData->state = body->data->publish->time_length_show;
        bangumiInfo->metaData->followers = body->data->stat->favorite;
        bangumiInfo->metaData->danmakus = body->data->stat->danmakus;
        bangumiInfo->metaData->totalPlay = body->data->stat->views;
        bangumiInfo->rating = BangumiInfoModel::Rating::createShared();
        bangumiInfo->rating->count = body->data->rating->count;
        bangumiInfo->rating->score = body->data->rating->score;

        if (const auto& seasonModules = body->data->findModules<PgcSeasonResp::Data::SeasonModule>(); seasonModules->size() > 0) {
            bangumiInfo->series = BangumiInfoModel::Series::createShared();
            bangumiInfo->series->title = body->data->season_title;
            bangumiInfo->series->seasons = oatpp::List<oatpp::Object<BangumiInfoModel::Series::Season>>::createShared();
            for (const auto& seasons : *seasonModules) {
                for (const auto season : *seasons->data->seasons) {
                    const auto& seasonItem = BangumiInfoModel::Series::Season::createShared();
                    seasonItem->season_id = season->season_id;
                    seasonItem->title = season->title;
                    seasonItem->cover = season->cover;
                    bangumiInfo->series->seasons->emplace_back(seasonItem);
                }
            }
        }

        if (const auto& episodeModules = body->data->findModules<PgcSeasonResp::Data::EpisodeModule>(); episodeModules->size() > 0) {
            bangumiInfo->episodes = oatpp::List<oatpp::Object<BangumiInfoModel::Episode>>::createShared();
            for (const auto& episodes : *episodeModules) {
                for (const auto& episode : *episodes->data->episodes) {
                    const auto& episodeItem = BangumiInfoModel::Episode::createShared();
                    episodeItem->title = episode->show_title;
                    episodeItem->cover = episode->cover;
                    episodeItem->episode_id = episode->ep_id;
                    bangumiInfo->episodes->emplace_back(episodeItem);
                }
            }
        }

        if (body->data->celebrity != nullptr) {
            bangumiInfo->celebrity = oatpp::List<oatpp::Object<BangumiInfoModel::Celebrity>>::createShared();
            for (const auto celebrity : *body->data->celebrity) {
                const auto& celebrityItem = BangumiInfoModel::Celebrity::createShared();
                celebrityItem->avatar = celebrity->avatar;
                celebrityItem->desc = celebrity->desc;
                celebrityItem->name = celebrity->name;
                bangumiInfo->celebrity->emplace_back(celebrityItem);
            }
        }

        return bangumiInfo;
    }

    oatpp::Object<BangumiRecommendModel> BangumiModel::getBangumiRecommend(const int seasonId) {
        const auto& dto = PgcSeasonRecommendReq::createShared();
        dto->season_id = seasonId;
        dto->access_key = SettingModule::getInstance()->accessToken().toStdString();
        const auto& result = apiClient->pgc_season_recommend(dto->asSignedParams());
        const auto& body = readRespBody<PgcSeasonRecommendResp>(result);
        OATPP_LOGd("BangumiModel::getBangumiRecommend", "code: {}, message: {}", body->code, body->message);
        if (body->code != 0) {
            throw std::runtime_error(body->message);
        }
        const auto& recommendList = BangumiRecommendModel::createShared();
        if (body->result != nullptr && body->result->season != nullptr) {
            recommendList->data = oatpp::List<oatpp::Object<BangumiRecommendModel::Season>>::createShared();
            for (const auto& recommend : *body->result->season) {
                const auto& recommendItem = BangumiRecommendModel::Season::createShared();
                recommendItem->season_id = recommend->season_id;
                recommendItem->title = recommend->title;
                recommendItem->cover = recommend->cover;
                recommendList->data->emplace_back(recommendItem);
            }
        }
        return recommendList;
    }
}
