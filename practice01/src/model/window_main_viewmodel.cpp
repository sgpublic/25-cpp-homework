//
// Created by coder on 12/5/25.
//

#include "model/window_main_viewmodel.h"

#include "core/api/dto/app_dto.h"
#include "core/api/dto/search_dto.h"
#include "core/module/global_signal_model.h"
#include "core/module/setting_module.h"
#include "utils/string.h"

using namespace biliqt::utils;
using namespace biliqt::core::module;
using namespace biliqt::core::api;
using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;

namespace biliqt::model {

    MainWindowViewModel::MainWindowViewModel(QObject *parent) : ViewModel(parent) {
        _appClient = AppClient::createShared();
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

    void MainWindowViewModel::onLogout(const QVariantMap& args) {
        SettingModule::getInstance()->login(false);
        SettingModule::getInstance()->accessToken("");
        SettingModule::getInstance()->refreshToken("");
        SettingModule::getInstance()->cookie_BiliJct("");
        SettingModule::getInstance()->cookie_DedeUserID("");
        SettingModule::getInstance()->cookie_DedeUserID__ckMd5("");
        SettingModule::getInstance()->cookie_SESSDATA("");
        SettingModule::getInstance()->cookie_sid("");
        hasLogin(false);
        emit GlobalSignalModule::getInstance()->loginStatusChanged(false);
    }

    void MainWindowViewModel::onLoadSearchSuggest(const QVariantMap& args) {
        const std::string searchText = args.value("search_text").toString().toStdString();
        const auto dto = SearchSuggestReq::createShared();
        dto->term = searchText;
        const auto result = _searchClient->suggest(dto->asSignedParams());
        // const auto result = _searchClient->suggest(searchText);
        const auto body = readRespBody<SearchSuggestResp>(result);
        qDebug() << "onLoadSearchSuggest" << "code:" << body->code;
        if (body->code != 0) {
            return;
        }
        auto suggests = QVariantList();
        for (const auto& item : *body->result->tag) {
            auto suggestItem = QVariantMap();
            suggestItem["title"] = QString::fromStdString(item->value->data());
            suggests.append(suggestItem);
        }
        qDebug() << "seearch suggests:" << suggests;
        searchSuggest(suggests);
    }

    void MainWindowViewModel::onSearch(const QVariantMap& args) {
        const auto& searchText = args.value("title").toString();
        qDebug() << "onSearch" << searchText;
    }
}
