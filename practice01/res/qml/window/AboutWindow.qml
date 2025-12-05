import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import FluentUI 1.0

FluWindow {

    id: window
    title: qsTrId("about_title")
    width: 320
    height: 280
    fixSize: true
    launchMode: FluWindowType.SingleTask

    ColumnLayout {
        width: parent.width

        RowLayout {
            Layout.topMargin: 40
            Layout.alignment: Qt.AlignHCenter

            Image {
                sourceSize.width: 60
                sourceSize.height: 60
                source: ResourceModule.getDrawable("/app_logo.svg")
            }
            FluText {
                text: qsTrId("app_name")
                font: FluTextStyle.Title
            }
        }

        FluText {
            Layout.topMargin: 10
            Layout.alignment: Qt.AlignHCenter

            text: "v0.1.0"
            font: FluTextStyle.Body
        }

        RowLayout {
            Layout.topMargin: 60
            Layout.alignment: Qt.AlignHCenter

            FluText {
                text: "GitHub："
            }
            FluTextButton {
                id: text_hublink
                topPadding: 0
                bottomPadding: 0
                text: "sgpublic/25-cpp-homework"
                Layout.alignment: Qt.AlignBottom
                onClicked: {
                    Qt.openUrlExternally("https://github.com/" + text_hublink.text)
                }
            }
        }
    }
}