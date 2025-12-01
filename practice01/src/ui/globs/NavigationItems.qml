pragma Singleton
import QtQuick 2.15
import FluentUI 1.0

FluObject {
    property var navigationView

    FluPaneItem {
        icon: FluentIcons.Home
        title: "首页"

        onTap: {
            navigationView.push(url);
        }
    }
}