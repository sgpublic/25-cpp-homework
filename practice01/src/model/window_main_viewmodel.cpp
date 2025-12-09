//
// Created by coder on 12/5/25.
//

#include "model/window_main_viewmodel.h"

#include "core/api/dto/app_dto.h"
#include "core/api/dto/api_dto.h"
#include "core/module/setting_module.h"
#include "utils/string.h"

using namespace biliqt::utils;
using namespace biliqt::core::module;
using namespace biliqt::core::api;
using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;

namespace biliqt::model {

    MainWindowViewModel::MainWindowViewModel(QObject *parent) : ViewModel(parent) {
        _apiClient = ApiClient::createShared();
        _appClient = AppClient::createShared();
        hasLogin(SettingModule::getInstance()->login());
        requestLoadBannerData();
        if (_hasLogin) {
            requestLoadUserInfo();
        }
    }

    void MainWindowViewModel::onLoginSucceed(const QVariantMap& args) {
        hasLogin(true);
        requestLoadUserInfo();
    }

    void MainWindowViewModel::onLoadUserInfo(const QVariantMap& args) {
        const auto dto = MyinfoReq::createShared();
        dto->access_key = qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        const auto result = _appClient->myinfo(dto->asSignedParams());
        const auto body = core::api::readRespBody<MyinfoResp>(result);
        qDebug() << "code:" << body->code << "message:" << body->message->data();
        if (body->code != 0) {
            nick(qtTrId("main_nick_unknown"));
            avatarUrl(nullptr);
        } else {
            nick(body->data->name->data());
            avatarUrl(body->data->face->data());
        }
    }

    void MainWindowViewModel::onLoadBannerData(const QVariantMap& args) {
        const auto dto = PgcPageReq::createShared();
        dto->access_key = qstr_to_oatstr(SettingModule::getInstance()->accessToken());
        const auto result = _apiClient->pgc_page(dto->asSignedParams());
        const auto body = readRespBody(result);
        const int code = body["code"];
        const std::string message = body["message"];
        qDebug() << "code:" << code << "message:" << message;
        if (code != 0) {
            return;
        }
        const auto& banner = findModules<PgcPageResp::ModuleItems>(body, "v_card");
        bannerData(*banner);
    }
}
