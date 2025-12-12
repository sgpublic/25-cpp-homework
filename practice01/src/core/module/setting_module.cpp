#include "core/module/setting_module.h"

#include <QStandardPaths>
#include <QFileInfo>

namespace biliqt::core::module {

    SettingModule::SettingModule(QObject *parent) : QObject(parent) {
    }

    void SettingModule::save(const QString &key, QVariant val) {
        m_settings->setValue(key, val);
        m_settings->sync();
    }

    QVariant SettingModule::get(const QString &key, QVariant def) {
        QVariant data = m_settings->value(key);
        if (!data.isNull() && data.isValid()) {
            return data;
        }
        return def;
    }

    void SettingModule::init(char *argv[]) {
        QString applicationPath = QString::fromStdString(argv[0]);
        const QFileInfo fileInfo(applicationPath);
        const QString iniFileName = fileInfo.completeBaseName() + ".ini";
        const QString iniFilePath = fileInfo.path() + "/" + iniFileName;
        m_settings.reset(new QSettings(iniFilePath, QSettings::IniFormat));
    }

}