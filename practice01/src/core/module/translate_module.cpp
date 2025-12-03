#include "core/module/translate_module.h"

#include <QGuiApplication>
#include <QQmlEngine>

#include "core/module/setting_module.h"

namespace biliqt::core::module {

    TranslateModule::TranslateModule(QObject *parent) : QObject(parent) {
        _languages << "en";
        _languages << "zh_CN";
        _current = SettingModule::getInstance()->getLanguage();
    }

    void TranslateModule::init(QQmlEngine *engine) {
        _engine = engine;
        _translator = new QTranslator(this);
        QGuiApplication::installTranslator(_translator);
        if (_translator->load(QLocale(), "BiliQt", "_", ":/biliqt/i18n")) {
            _engine->retranslate();
        }
    }

}
