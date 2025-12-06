//
// Created by coder on 12/5/25.
//

#include "model/window_main_viewmodel.h"

#include "core/module/setting_module.h"

namespace biliqt::model {

    MainWindowViewModel::MainWindowViewModel(QObject *parent) : ViewModel(parent) {
        hasLogin(core::module::SettingModule::getInstance()->login());
    }

    void MainWindowViewModel::LoginSucceed() {
        hasLogin(true);
    }

}
