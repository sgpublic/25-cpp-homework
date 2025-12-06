import QtQuick 2.15
import QtQuick.Window 2.15
import FluentUI 1.0

FluLauncher {
    id: biliQt

    Component.onCompleted: {
        FluApp.init(biliQt, Qt.locale(TranslateModule.current));
        FluApp.useSystemAppBar = true;
        FluApp.windowIcon = ResourceModule.getDrawable("/app_logo.svg");
        FluTheme.darkMode = SettingModule.darkMode();
        FluTheme.animationEnabled = true;
        FluRouter.routes = {
            "/": ResourceModule.getQml("/window/MainWindow.qml"),
            "/login": ResourceModule.getQml("/window/LoginWindow.qml"),
            "/about": ResourceModule.getQml("/window/AboutWindow.qml")
        };
        FluRouter.navigate("/");
    }
}
