#include "core/module/translate_module.h"

#include <QGuiApplication>
#include <QQmlEngine>

#include "core/module/setting_module.h"

using namespace Qt::StringLiterals;

namespace biliqt::core::module {

    TranslateModule::TranslateModule(QObject *parent) : QObject(parent) {
        _languages << "zh_CN";
        _languages << "en";
        _current = SettingModule::getInstance()->getLanguage();
    }

    void TranslateModule::init(QQmlEngine *engine) {
        _engine = engine;
        _translator = new QTranslator(this);
        QGuiApplication::installTranslator(_translator);
        setLanguage();
    }

    void TranslateModule::setLanguage(const int& index) {
        QString language = index < 0 ? _current : _languages[index];
        if (_translator->load(":/biliqt/i18n/BiliQt_" + language + ".qm")) {
            _engine->retranslate();
        }
    }

    int TranslateModule::indexOfCurrent() {
        return static_cast<int>(_languages.indexOf(_current));
    }

    QString TranslateModule::keyOfIndex(const int& index) {
        return _languages[index];
    }

}
