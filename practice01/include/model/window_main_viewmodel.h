//
// Created by coder on 12/5/25.
//
#pragma once

#include "base_viewmodel.h"
#include "utils/stdafx.h"

namespace biliqt::model {

    class MainWindowViewModel: public ViewModel {
        Q_OBJECT

        Q_PROPERTY_READONLY_AUTO(bool, hasLogin) = false;
        Q_PROPERTY_READONLY_AUTO(QString, username);
        Q_PROPERTY_READONLY_AUTO(QString, avatarUrl);
    public:
        explicit MainWindowViewModel(QObject *parent = nullptr);

        VIEW_MODEL_COROUTINE_TASK(LoginSucceed)
    };

}
