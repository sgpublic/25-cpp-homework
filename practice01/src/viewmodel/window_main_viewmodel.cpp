//
// Created by coder on 12/5/25.
//

#include "viewmodel/window_main_viewmodel.h"

#include "core/api/dto/api_dto.h"
#include "core/api/dto/search_dto.h"
#include "core/module/global_signal_module.h"
#include "core/module/setting_module.h"
#include "utils/string.h"

using namespace biliqt::utils;
using namespace biliqt::core::module;
using namespace biliqt::core::api;
using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;

namespace biliqt::viewmodel {

    MainWindowViewModel::MainWindowViewModel(QObject *parent) : ViewModel(parent) {
        _apiClient = ApiClient::createShared();
        _searchClient = SearchClient::createShared();
        connect(this, &MainWindowViewModel::searchTextChanged, this, [this] {
            requestLoadSearchSuggest({{ "search_text", searchText() }});
        });
        hasLogin(SettingModule::getInstance()->login());
        if (_hasLogin) {
            requestLoadUserInfo();
        }
    }

    void MainWindowViewModel::onLoginSucceed(const QVariantMap& args) {
        hasLogin(true);
        requestLoadUserInfo();
    }

    void MainWindowViewModel::onLoadUserInfo(const QVariantMap& args) {
        const auto result = _apiClient->web_nav();
        const auto body = core::api::readRespBody<WebNavResp>(result);
        OATPP_LOGd("MainWindowViewModel::onLoadUserInfo", "code: {}, message: {}", body->code, body->message);
        if (body->code != 0) {
            nick(qtTrId("main_nick_unknown"));
            avatarUrl(nullptr);
            SettingModule::getInstance()->wbi_img_key("");
            SettingModule::getInstance()->wbi_sub_key("");
        } else {
            nick(body->data->uname->data());
            avatarUrl(body->data->face->data());
            SettingModule::getInstance()->wbi_img_key(url_to_wbi_key(body->data->wbi_img->img_url));
            SettingModule::getInstance()->wbi_sub_key(url_to_wbi_key(body->data->wbi_img->sub_url));
        }
    }

    void MainWindowViewModel::onLogout(const QVariantMap& args) {
        SettingModule::getInstance()->login(false);
        SettingModule::getInstance()->accessToken("");
        SettingModule::getInstance()->refreshToken("");
        SettingModule::getInstance()->cookie_BiliJct("");
        SettingModule::getInstance()->cookie_DedeUserID("");
        SettingModule::getInstance()->cookie_DedeUserID__ckMd5("");
        SettingModule::getInstance()->cookie_SESSDATA("");
        SettingModule::getInstance()->cookie_sid("");
        SettingModule::getInstance()->wbi_img_key("");
        SettingModule::getInstance()->wbi_sub_key("");
        hasLogin(false);
        emit GlobalSignalModule::getInstance()->loginStatusChanged(false);
    }

    void MainWindowViewModel::onLoadSearchSuggest(const QVariantMap& args) {
        const std::string searchText = args.value("search_text").toString().toStdString();
        const auto dto = SearchSuggestReq::createShared();
        dto->term = searchText;
        const auto result = _searchClient->suggest(dto->asSignedParams());
        const auto body = readRespBody<SearchSuggestResp>(result);
        OATPP_LOGd("MainWindowViewModel::onLoadSearchSuggest", "code: {}", body->code);
        if (body->code != 0) {
            return;
        }
        auto suggests = QVariantList();
        for (const auto& item : *body->result->tag) {
            auto suggestItem = QVariantMap();
            suggestItem["title"] = QString::fromStdString(item->value->data());
            suggests.append(suggestItem);
        }
        OATPP_LOGd("MainWindowViewModel::onLoadSearchSuggest", "search suggests count: {}", suggests.size());
        searchSuggest(suggests);
    }

}
