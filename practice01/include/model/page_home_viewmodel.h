//
// Created by coder on 12/4/25.
//
#pragma once

#include "base_viewmodel.h"

namespace biliqt::model {

    class HomePageViewModel: public ViewModel {
        Q_OBJECT
    public:
        explicit HomePageViewModel(QObject *parent = nullptr);
    };

}
