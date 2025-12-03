#include <QApplication>
#include <QQmlApplicationEngine>
#include <utils/resources.h>

using namespace biliqt::utils;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(Resources::get_qml("/App.qml"));

    return QApplication::exec();
}
