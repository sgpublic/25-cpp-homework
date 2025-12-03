pragma Singleton

import QtQuick 2.15
import FluentUI 1.0

FluScrollablePage {
    title: qsTrId("page_home_title")

    launchMode: FluPageType.SingleInstance
}
