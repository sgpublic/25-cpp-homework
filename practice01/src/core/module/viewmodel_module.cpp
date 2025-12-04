//
// Created by coder on 12/4/25.
//

#include "core/module/viewmodel_module.h"

#include <QObject>

#include "model/page_home_viewmodel.h"

using namespace biliqt::model;

namespace biliqt::core::module {

    ViewModelModule::ViewModelModule(QObject *parent) : QObject(parent) {
        viewModelRegistry["page_home"] = [](QObject *parent) -> QObject* {
            return new HomePageViewModel(parent);
        };
    }

    QObject* ViewModelModule::createViewModel(const QString& name, QObject* parent) {
        return viewModelRegistry[name](parent);
    }

}
