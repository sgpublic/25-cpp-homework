//
// Created by coder on 12/3/25.
//
#pragma once

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>
#include <QSettings>
#include <QScopedPointer>
#include "utils/singleton.h"
#include "utils/settings.h"

namespace biliqt::core::module {
    class SettingModule : public QObject {
        Q_OBJECT

    private:
        explicit SettingModule(QObject *parent = nullptr);

        QScopedPointer<QSettings> m_settings;

        void save(const QString &key, QVariant val);

        QVariant get(const QString &key, QVariant def = {});

    public:
        SINGLETON(SettingModule)

        void init(char *argv[]);

    public:
        SETTING_MEMBER(darkMode, int, Int, 0)
        SETTING_MEMBER(language, QString, String, "zh_CN")

        SETTING_MEMBER(login, bool, Bool, false)
        SETTING_MEMBER(username, QString, String, "")
        SETTING_MEMBER(accessToken, QString, String, "")
        SETTING_MEMBER(refreshToken, QString, String, "")
        SETTING_MEMBER(cookie_BiliJct, QString, String, "")
        SETTING_MEMBER(cookie_DedeUserID, QString, String, "")
        SETTING_MEMBER(cookie_DedeUserID__ckMd5, QString, String, "")
        SETTING_MEMBER(cookie_sid, QString, String, "")
        SETTING_MEMBER(cookie_SESSDATA, QString, String, "")
    };
}
