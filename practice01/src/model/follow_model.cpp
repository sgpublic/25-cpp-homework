//
// Created by Haven Madray on 2025/12/20.
//
#include "model/follow_model.h"

#include "core/api/dto/api_dto.h"
#include "model/dto/follow_dto.h"

using namespace biliqt::core::api;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api::client;
using namespace biliqt::model::dto;
using namespace biliqt::core::module;

namespace biliqt::model {

    FollowModel::FollowModel(QObject *parent): QObject(parent) {
        apiClient = ApiClient::createShared();
    }

    oatpp::Object<MineCurrentWatchingModel> FollowModel::getCurrentWatchingList() {
        const auto& dto = PgcPagePcBangumiTabReq::createShared();
        dto->access_key = utils::qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        const auto& result = apiClient->pgc_page_pc_bangumi_tab(dto->asSignedParams());
        const auto& body = readRespBody<PgcPagePcBangumiTabResp>(result);
        OATPP_LOGd("FollowModel::getCurrentWatchingList", "code: {}, message: {}", body->code, body->message);
        if (body->code != 0) {
            throw std::runtime_error(body->message);
        }
        const auto& followModules = body->data->findModules<PgcPagePcBangumiTabResp::Data::FollowModule>();
        const auto& followListData = oatpp::List<oatpp::Object<MineCurrentWatchingModel::Item>>::createShared();
        for (const auto& followModule: *followModules) {
            for (const auto& followItem : *followModule->items) {
                const auto& item = MineCurrentWatchingModel::Item::createShared();
                item->season_id = followItem->season_id;
                item->cover = followItem->cover;
                item->title = followItem->title;
                item->desc = followItem->desc;
                followListData->emplace_back(item);
            }
        }
        OATPP_LOGd("FollowModel::getCurrentWatchingList", "current watching count: {}", followModules->size());

        const auto& followList = MineCurrentWatchingModel::createShared();
        followList->data = followListData;
        return followList;
    }

    oatpp::Object<MineFollowListModel> FollowModel::getFollowList(const int status, const int page) {
        const auto& dto = PgcFollowBangumiReq::createShared();
        dto->access_key = utils::qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        dto->pn = page;
        dto->status = status;
        const auto& result = apiClient->pgc_follow_bangumi(dto->asSignedParams());
        const auto& body = readRespBody<PgcFollowBangumiResp>(result);
        OATPP_LOGd("FollowModel::getFollowList", "code: {}, message: {}", body->code, body->message);
        if (body->code != 0) {
            throw std::runtime_error(body->message);
        }
        const auto& followList = MineFollowListModel::createShared();
        followList->has_next = body->result->has_next == 1;
        followList->current_page = page;
        const auto& followListData = oatpp::List<oatpp::Object<MineFollowListModel::Item>>::createShared();
        for (const auto& followItem : *body->result->follow_list) {
            const auto& follow = MineFollowListModel::Item::createShared();
            follow->season_id = followItem->season_id;
            follow->cover = followItem->cover;
            follow->title = followItem->title;
            followListData->emplace_back(follow);
        }
        followList->data = followListData;
        return followList;
    }

}
