//
// Created by coder on 12/3/25.
//
#pragma once

#include <QtQml/qqml.h>
#include <QTranslator>
#include "utils/singleton.h"
#include "utils/stdafx.h"

namespace biliqt::core::module {

    class TranslateModule : public QObject {
        Q_OBJECT

        Q_PROPERTY_AUTO(QString, current)
        Q_PROPERTY_READONLY_AUTO(QStringList, languages)

        SINGLETON(TranslateModule);
    private:
        explicit TranslateModule(QObject *parent = nullptr);

    public:
        void init(QQmlEngine *engine);
        Q_INVOKABLE void setLanguage(const int& index = -1);
        Q_INVOKABLE int indexOfCurrent();
        Q_INVOKABLE QString keyOfIndex(const int& index);

    private:
        QQmlEngine *_engine = nullptr;
        QTranslator *_translator = nullptr;
    };

}