//
// Created by coder on 12/3/25.
//
#pragma once

#include <QtQml/qqml.h>
#include <QTranslator>
#include "utils/singleton.h"
#include "utils/stdafx.h"

using namespace biliqt::utils;
using namespace std;

namespace biliqt::core::module {

    class TranslateModule : public QObject {
        Q_OBJECT
        Q_PROPERTY_AUTO(QString, current)
        Q_PROPERTY_READONLY_AUTO(QVariantMap, languages)
    private:
        explicit TranslateModule(QObject *parent = nullptr);

    public:
        SINGLETON(TranslateModule);
        void init(QQmlEngine *engine);

    private:
        QQmlEngine *_engine = nullptr;
        QTranslator *_translator = nullptr;
    };

}