//
// Created by coder on 12/4/25.
//

#pragma once

#include <QObject>

namespace biliqt::model {

    class ViewModel : public QObject {
        Q_OBJECT
    public:
        explicit ViewModel(QObject *parent)
            : QObject(parent) {}

        virtual void onClear() = 0;
    };

}
