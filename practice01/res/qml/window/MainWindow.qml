import QtQuick 2.15
import FluentUI 1.0

FluWindow {
    height: 900
    title: qsTrId("app_name")
    visible: true
    width: 1500

    FluNavigationView {
        id: navView

        displayMode: FluNavigationViewType.Open
        height: parent.height

        pageMode: FluNavigationViewType.NoStack
        title: qsTrId("app_name")
        width: parent.width
    }
}
