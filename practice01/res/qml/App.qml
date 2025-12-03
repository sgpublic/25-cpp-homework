import QtQuick 2.15
import QtQuick.Window 2.15
import FluentUI 1.0

FluLauncher {
    id: biliQt

    Component.onCompleted: {
        FluApp.init(biliQt, Qt.locale(TranslateModule.current));
        FluApp.useSystemAppBar = true;
        FluTheme.darkMode = 0;
        FluTheme.animationEnabled = true;
        FluRouter.routes = {
            "/": ResourceModule.get_qml("/window/MainWindow.qml")
        };
        FluRouter.navigate("/");
    }
}
