//
// Created by coder on 12/4/25.
//

#pragma once

#include <QMap>

#include "model/base_viewmodel.h"
#include "utils/singleton.h"

namespace biliqt::core::module {
    class ViewModelModule: public QObject {
        Q_OBJECT
    private:
        explicit ViewModelModule(QObject *parent = nullptr);

        QMap<QString, std::function<QObject*(QObject*)>> viewModelRegistry;

    public:
        SINGLETON(ViewModelModule);

        Q_INVOKABLE QObject* createViewModel(const QString& name, QObject* parent);
    };
}
