//
// Created by Haven Madray on 2025/12/20.
//
#include "model/home_model.h"

#include "core/api/dto/api_dto.h"

using namespace biliqt::core::api;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api::client;
using namespace biliqt::model::dto;
using namespace biliqt::core::module;

namespace biliqt::model {

    HomeModel::HomeModel(QObject *parent): QObject(parent) {
        apiClient = ApiClient::createShared();
    }

    oatpp::Object<HomeBannerModel> HomeModel::getBannerData() {
        const auto dto = PgcPageReq::createShared();
        dto->access_key = utils::qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        const auto result = apiClient->pgc_page(dto->asSignedParams());
        const auto body = readRespBody<PgcPageResp>(result);
        OATPP_LOGd("HomeModel::getBannerData", "code: {}, message: {}", body->code, body->message);
        if (body->code != 0) {
            throw std::runtime_error(body->message);
        }
        const auto& bannerDataList = oatpp::List<oatpp::Object<HomeBannerModel::Item>>::createShared();
        const auto& moduleData = body->result->findModules<PgcPageResp::Result::TopicModule>();
        for (const auto& module : *moduleData) {
            for (const auto& item : *module->items) {
                const auto banner = HomeBannerModel::Item::createShared();
                banner->cover = item->cover;
                banner->title = item->title;
                bannerDataList->emplace_back(banner);
            }
        }
        const auto bannerData = HomeBannerModel::createShared();
        bannerData->data = bannerDataList;
        return bannerData;
    }

    oatpp::Object<HomeBangumiModel> HomeModel::getBangumiList(std::string cursor, bool isRefresh) {
        const auto dto = PgcPageBangumiReq::createShared();
        dto->access_key = utils::qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        dto->cursor = cursor;
        dto->is_refresh = isRefresh;
        const auto result = apiClient->pgc_page_bangumi(dto->asSignedParams());
        const auto body = readRespBody<PgcPageBangumiResp>(result);
        if (body->code != 0) {
            throw std::runtime_error(body->message);
        }
        const auto& bangnumiDataList = oatpp::List<oatpp::Object<HomeBangumiModel::Item>>::createShared();
        const auto& list = body->result->findModules<PgcPageBangumiResp::Result::DoubleFeedModule>();
        OATPP_LOGd("HomeModel::getBangumiList", "bangumi item count: {}", list->size());
        for (const auto& module : *list) {
            for (const auto& item : *module->items) {
                const auto bangumi = HomeBangumiModel::Item::createShared();
                bangumi->season_id = item->season_id;
                bangumi->episode_id = item->episode_id;
                bangumi->cover = item->cover;
                bangumi->title = item->title;
                bangumi->desc = item->desc;
                bangumi->type = item->type;
                bangnumiDataList->emplace_back(bangumi);
            }
        }
        const auto bangumiList = HomeBangumiModel::createShared();
        bangumiList->has_next = body->result->has_next == 1;
        bangumiList->next_cursor = body->result->next_cursor;
        bangumiList->data = bangnumiDataList;
        return bangumiList;
    }

}
