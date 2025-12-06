#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "core/module/setting_module.h"
#include "core/module/resource_module.h"

#include "core/module/translate_module.h"
#include "core/module/viewmodel_module.h"

#include "oatpp/core/macro/component.hpp"

using namespace biliqt::utils;
using namespace biliqt::core::module;

int main(int argc, char *argv[]) {
    oatpp::base::Environment::init();

    SettingModule::getInstance()->init(argv);

    QApplication application(argc, argv);

    QQmlApplicationEngine engine;

    TranslateModule::getInstance()->init(&engine);
    engine.rootContext()->setContextProperty("ResourceModule", ResourceModule::getInstance());
    engine.rootContext()->setContextProperty("SettingModule", SettingModule::getInstance());
    engine.rootContext()->setContextProperty("TranslateModule", TranslateModule::getInstance());
    engine.rootContext()->setContextProperty("ViewModelModule", ViewModelModule::getInstance());

    engine.load(ResourceModule::getInstance()->getQml("/App.qml"));

    const int exitCode = QApplication::exec();

    oatpp::base::Environment::destroy();
    return exitCode;
}
