import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.Basic 2.15
import FluentUI 1.0
import "../component"

FluPage {
    id: page_search

    property var viewModel: ViewModelModule.createViewModel("page_search", page_search)

    launchMode: FluPageType.SingleInstance

    Item {
        width: parent.width
        height: parent.height

        ListModel {
            id: search_list_data
        }

        GridView {
            id: search_list
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            cellWidth: width / 2
            cellHeight: 160
            contentHeight: 1600

            header: Item {
                width: parent.width
                height: 60

                FluText {
                    text: qsTrId("search_title").arg(viewModel.searchText)
                    font {
                        pointSize: 24
                        bold: true
                    }
                }
            }

            boundsBehavior: Flickable.StopAtBounds
            highlightFollowsCurrentItem: false
            model: search_list_data
            delegateModelAccess: DelegateModel.ReadOnly
            delegate: Component {
                Text {

                }
            }
        }

        Column {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: 16
            anchors.rightMargin: 16

            spacing: 10

            FluFrame {
                id: home_backToTop
                radius: 16
                padding: 6
                FluIconButton {
                    iconSource: FluentIcons.Up
                    iconSize: 18
                    radius: 12
                    onClicked: {
                        bangumi_list.positionViewAtBeginning()
                    }
                }
            }
        }

    }

    Component.onCompleted: {
        GlobalSignalModule.requestSearch.connect(function (searchText) {
            viewModel.searchText = searchText
            viewModel.requestLoadSearchResult({search_text: searchText})
        })
    }
}
