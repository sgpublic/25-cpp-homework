//
// Created by coder on 12/2/25.
//
#pragma once

#include <QObject>
#include <QUrl>

#include "utils/singleton.h"

namespace biliqt::core::module {
    class ResourceModule: public QObject {
        Q_OBJECT
    public:
        SINGLETON(ResourceModule);

        Q_INVOKABLE QString get(const QString& path);
        Q_INVOKABLE QString getQml(const QString& path);
        Q_INVOKABLE QString getDrawable(const QString& path);
        Q_INVOKABLE QString getRemoteDrawable(const QString& path);
    private:
        explicit ResourceModule(QObject *parent = nullptr);
    };
}
