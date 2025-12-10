pragma Singleton

import QtQuick 2.15
import QtQuick.Layouts 2.15
import FluentUI 1.0

FluScrollablePage {
    id: page_home

    property var viewModel

    launchMode: FluPageType.SingleTask

    FluAutoSuggestBox {
        Layout.alignment: Qt.AlignHCenter
        Layout.preferredWidth: 400

        iconSource: FluentIcons.Search
        placeholderText: qsTrId("home_search_hint")
        text: viewModel.searchText
        onTextChanged: {
            viewModel.searchText = text
        }
    }

    FluCarousel {
        id: banner_carousel

        Layout.preferredWidth: 680
        Layout.preferredHeight: 200
        Layout.alignment: Qt.AlignHCenter
        Layout.topMargin: 20

        model: [...viewModel.bannerData]

        orientation: Qt.Horizontal
        indicatorGravity: Qt.AlignBottom | Qt.AlignHCenter
        autoPlay: true
        loopTime: 5000
        delegate: Component {
            FluClip {
                radius: [12, 12, 12, 12]
                anchors.fill: parent

                Image {
                    anchors.fill: parent
                    source: model.cover
                    asynchronous: true
                    fillMode: Image.PreserveAspectCrop
                }
            }
        }
    }

    Component.onCompleted: {
        viewModel = ViewModelModule.createViewModel("page_home", page_home)
    }
}
