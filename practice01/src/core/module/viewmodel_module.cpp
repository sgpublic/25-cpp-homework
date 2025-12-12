//
// Created by coder on 12/4/25.
//

#include "core/module/viewmodel_module.h"

#include <QObject>

#include "model/page_home_viewmodel.h"
#include "model/page_mine_viewmodel.h"
#include "model/window_bangumi_viewmodel.h"
#include "model/window_login_viewmodel.h"
#include "model/window_main_viewmodel.h"

using namespace biliqt::model;

namespace biliqt::core::module {

    ViewModelModule::ViewModelModule(QObject *parent) : QObject(parent) {
        viewModelRegistry["page_home"] = [](QObject *parent) -> QObject* {
            return new HomePageViewModel(parent);
        };
        viewModelRegistry["page_mine"] = [](QObject *parent) -> QObject * {
            return new MinePageViewModel(parent);
        };
        viewModelRegistry["window_main"] = [](QObject *parent) -> QObject* {
            return new MainWindowViewModel(parent);
        };
        viewModelRegistry["window_login"] = [](QObject *parent) -> QObject* {
            return new LoginWindowViewModel(parent);
        };
        viewModelRegistry["window_bangumi"] = [](QObject *parent) -> QObject* {
            return new BangumiWindowViewModel(parent);
        };
    }

    QObject* ViewModelModule::createViewModel(const QString& name, QObject* parent) {
        return viewModelRegistry[name](parent);
    }

}
