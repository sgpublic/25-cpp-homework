//
// Created by coder on 12/5/25.
//
#pragma once

#include "base_viewmodel.h"
#include "utils/stdafx.h"

namespace biliqt::model {

    class MainWindowViewModel: public ViewModel {
    public:
        explicit MainWindowViewModel(QObject *parent = nullptr);
        void onClear() override;

        Q_PROPERTY_READONLY_AUTO(bool, hasLogin);
    };

}
