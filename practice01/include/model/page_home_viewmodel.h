//
// Created by coder on 12/4/25.
//
#pragma once

#include "base_viewmodel.h"
#include "utils/stdafx.h"

namespace biliqt::model {

    class HomePageViewModel: public ViewModel {
        Q_OBJECT
    public:
        Q_PROPERTY_AUTO(QString, searchText);
    public:
        explicit HomePageViewModel(QObject *parent = nullptr);
        VIEW_MODEL_COROUTINE_TASK(LoadSearchSuggest)
    };

}
