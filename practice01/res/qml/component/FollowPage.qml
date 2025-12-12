import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.Basic 2.15
import FluentUI 1.0

Item {
    width: parent.width
    height: parent.height
    clip: true

    property alias model: list.model
    property alias delegate: list.delegate
    property alias listWidth: list.width
    property alias cellWidth: list.cellWidth
    property alias cellHeight: list.cellHeight

    signal requestLoading(isRefresh: bool)

    GridView {
        id: list

        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter

        boundsBehavior: Flickable.StopAtBounds
        highlightFollowsCurrentItem: false
        delegateModelAccess: DelegateModel.ReadOnly

        onContentYChanged: {
            if (contentY + height < contentHeight) {
                return
            }
            requestLoading(false)
        }
    }

    Column {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 16
        anchors.rightMargin: 16

        spacing: 10

        FluFrame {
            radius: 16
            padding: 6
            FluIconButton {
                iconSource: FluentIcons.Refresh
                iconSize: 18
                radius: 12
                onClicked: {
                    list.positionViewAtBeginning()
                    requestLoading(true)
                }
            }
        }
        FluFrame {
            id: home_backToTop
            radius: 16
            padding: 6
            FluIconButton {
                iconSource: FluentIcons.Up
                iconSize: 18
                radius: 12
                onClicked: {
                    list.positionViewAtBeginning()
                }
            }
        }
    }

}