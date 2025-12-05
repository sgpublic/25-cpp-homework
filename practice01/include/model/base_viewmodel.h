//
// Created by coder on 12/4/25.
//

#pragma once

#include <QObject>

namespace biliqt::model {

    class ViewModel : public QObject {
    public:
        explicit ViewModel(QObject *parent = nullptr) : QObject(parent) {}

        virtual void onClear() = 0;
    };

}
