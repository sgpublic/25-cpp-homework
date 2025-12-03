import QtQuick 2.15
import QtQuick.Window 2.15
import FluentUI 1.0

FluLauncher {
    id: biliQt

    Component.onCompleted: {
        FluApp.init(biliQt, Qt.locale("zh_CN"));
        FluApp.useSystemAppBar = true;
        FluTheme.darkMode = 0;
        FluTheme.animationEnabled = true;
        FluRouter.routes = {
            "/": "qrc:/biliqt/qml/window/MainWindow.qml"
        };
        var args = Qt.application.arguments;
        if (args.length >= 2 && args[1].startsWith("-crashed=")) {
            FluRouter.navigate("/crash", {
                crashFilePath: args[1].replace("-crashed=", "")
            });
        } else {
            FluRouter.navigate("/");
        }
    }
}
