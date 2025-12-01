#include <QApplication>
#include <QPushButton>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/ui/MainWindow.qml")));

    return QApplication::exec();
}
