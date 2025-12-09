//
// Created by coder on 12/4/25.
//
#include "model/base_viewmodel.h"
#include "model/page_home_viewmodel.h"

#include "core/api/dto/api_dto.h"
#include "core/module/setting_module.h"

using namespace biliqt::utils;
using namespace biliqt::core::module;
using namespace biliqt::core::api;
using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;

namespace biliqt::model {

    HomePageViewModel::HomePageViewModel(QObject *parent): ViewModel(parent) {
        _apiClient = ApiClient::createShared();
        requestLoadBannerData();
    }

    void HomePageViewModel::onLoadSearchSuggest(const QVariantMap& args) {

    }

    void HomePageViewModel::onLoadBannerData(const QVariantMap& args) {
        const auto dto = PgcPageReq::createShared();
        dto->access_key = qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        const auto result = _apiClient->pgc_page(dto->asSignedParams());
        const auto body = readRespBody(result);
        const int code = body["code"];
        const std::string message = body["message"];
        if (code != 0) {
            return;
        }
        const auto& banner = findModules<PgcPageResp::ModuleItems>(body, "topic");
        sleep(2);
        qDebug() << "banner image count:" << banner->size();
        bannerData(*banner);
    }
}
