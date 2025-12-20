//
// Created by Haven Madray on 2025/12/12.
//
#pragma once
#include <QObject>

#include "utils/singleton.h"

namespace biliqt::core::module {

    class GlobalSignalModule: public QObject {
        Q_OBJECT

        SINGLETON(GlobalSignalModule)
    private:
        explicit GlobalSignalModule(QObject *parent = nullptr);

    signals:
        void requestBangumiInfo(const QVariantMap& args);
        void loginStatusChanged(const bool& isLogin);
        void requestSearch(const QString& searchText);
        void showToastOnMainWindow(bool isSuccess, const QString& searchText);
        void showToastOnBangumiWindow(bool isSuccess, const QString& searchText);
    };

}
