//
// Created by coder on 12/5/25.
//

#include "viewmodel/window_main_viewmodel.h"

#include "core/api/dto/search_dto.h"
#include "core/module/setting_module.h"

using namespace biliqt::utils;
using namespace biliqt::core::module;
using namespace biliqt::core::api;
using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;

namespace biliqt::viewmodel {

    MainWindowViewModel::MainWindowViewModel(QObject *parent) : ViewModel(parent) {
        userModel = std::make_shared<model::UserModel>(parent);
        searchModel = std::make_shared<model::SearchModel>(parent);
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
        try {
            const auto body = userModel->getUserInfo();
            nick(body->nick != nullptr ? body->nick->data() : nullptr);
            avatarUrl(body->avatar != nullptr ? body->avatar->data() : nullptr);
        } catch (std::runtime_error& e) {
            // TODO: add error message
        }
    }

    void MainWindowViewModel::onLogout(const QVariantMap& args) {
        userModel->logout();
        hasLogin(false);
    }

    void MainWindowViewModel::onLoadSearchSuggest(const QVariantMap& args) {
        try {
            const std::string searchText = args.value("search_text").toString().toStdString();
            const auto result = searchModel->suggest(searchText);
            searchSuggest(dtoToQVariant(*result->data));
        } catch (...) {
        }
    }

}
