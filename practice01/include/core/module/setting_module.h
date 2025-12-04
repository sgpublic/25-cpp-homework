//
// Created by coder on 12/3/25.
//
#pragma once

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>
#include <QSettings>
#include <QScopedPointer>
#include "utils/singleton.h"

using namespace biliqt::utils;

namespace biliqt::core::module {

    class SettingModule : public QObject {
        Q_OBJECT
    private:
        explicit SettingModule(QObject *parent = nullptr);

    public:
        SINGLETON(SettingModule)
        void init(char *argv[]);
        Q_INVOKABLE void saveDarkMode(int darkModel) {
            save("darkMode", darkModel);
        }
        Q_INVOKABLE int getDarkMode() {
            return get("darkMode", QVariant(0)).toInt();
        }

        Q_INVOKABLE void saveLanguage(const QString &language) {
            save("language", language);
        }
        Q_INVOKABLE QString getLanguage() {
            return get("language", QVariant("zh_CN")).toString();
        }

        Q_INVOKABLE void saveUsername(const QString &username) {
            save("username", username);
        }
        Q_INVOKABLE QString getUsername() {
            return get("username", QVariant("")).toString();
        }

    private:
        void save(const QString &key, QVariant val);
        QVariant get(const QString &key, QVariant def = {});

    private:
        QScopedPointer<QSettings> m_settings;
    };

}
