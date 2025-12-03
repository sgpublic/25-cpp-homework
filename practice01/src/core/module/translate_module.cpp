#include "core/module/translate_module.h"

#include <QGuiApplication>
#include <QQmlEngine>

#include "core/module/setting_module.h"

using namespace Qt::StringLiterals;

namespace biliqt::core::module {

    TranslateModule::TranslateModule(QObject *parent) : QObject(parent) {
        _languages.insert("en", "language_en");
        _languages.insert("zh_CN", "language_zh_CN");
        _current = SettingModule::getInstance()->getLanguage();
    }

    void TranslateModule::init(QQmlEngine *engine) {
        _engine = engine;
        _translator = new QTranslator(this);
        QGuiApplication::installTranslator(_translator);
        if (_translator->load(":/biliqt/i18n/BiliQt_" + _current + ".qm")) {
            _engine->retranslate();
        }
    }

}
