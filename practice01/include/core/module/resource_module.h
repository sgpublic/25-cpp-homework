//
// Created by coder on 12/2/25.
//
#pragma once

#include <QObject>
#include <QUrl>

#include "utils/singleton.h"

using namespace biliqt::utils;

namespace biliqt::core::module {
    class ResourceModule: public QObject {
        Q_OBJECT
    public:
        SINGLETON(ResourceModule);

        Q_INVOKABLE QString get(const QString& path);
        Q_INVOKABLE QString get_qml(const QString& path);
        Q_INVOKABLE QString get_drawable(const QString& path);
    private:
        QString get_qrc(const QString& path);

        explicit ResourceModule(QObject *parent = nullptr);
    };
}
