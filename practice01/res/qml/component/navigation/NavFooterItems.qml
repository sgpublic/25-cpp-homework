pragma Singleton

import QtQuick 2.15
import FluentUI 1.0

FluObject {
    id: home_navView_footer

    property var navigationView
    property var paneItemMenu

    FluPaneItem{
        id: home_navView_footer_setting
        title: qsTrId("home_navView_footer_setting")
        menuDelegate: paneItemMenu
        icon: FluentIcons.Settings
        url: ResourceModule.getQml("/pages/SettingPage.qml")
        onTap: {
            navigationView.push(url)
        }
    }
}
