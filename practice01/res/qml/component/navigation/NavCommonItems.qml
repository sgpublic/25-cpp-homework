pragma Singleton

import QtQuick 2.15
import FluentUI 1.0

FluObject {
    id: home_navView_item

    property var navigationView
    property var paneItemMenu

    FluPaneItem{
        id: home_navView_item_setting
        title: qsTrId("home_navView_item_home")
        menuDelegate: paneItemMenu
        icon: FluentIcons.Home
        url: ResourceModule.getQml("/pages/HomePage.qml")
        onTap: {
            navigationView.push(url)
        }
    }
    FluPaneItem{
        id: home_navView_item_mine
        title: qsTrId("home_navView_item_mine")
        menuDelegate: paneItemMenu
        icon: FluentIcons.People
        url: ResourceModule.getQml("/pages/MinePage.qml")
        onTap: {
            navigationView.push(url)
        }
    }
}
