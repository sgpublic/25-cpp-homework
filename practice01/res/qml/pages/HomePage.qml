pragma Singleton

import QtQuick 2.15
import QtQuick.Layouts 2.15
import FluentUI 1.0

FluPage {
    id: page_home

    property var viewModel

    launchMode: FluPageType.SingleTask

    header: Item {
        width: parent.width
        height: 40

        FluAutoSuggestBox {
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            width: 400

            iconSource: FluentIcons.Search
            placeholderText: qsTrId("home_search_hint")
            text: viewModel.searchText
            onTextChanged: {
                viewModel.searchText = text
            }
        }
    }

    GridView {
        id: bangumi_list
        width: viewModel.ui_listWidth
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        cellWidth: viewModel.ui_listCellWidth
        cellHeight: viewModel.ui_listCellHeight

        header: Item {
            width: viewModel.ui_listWidth
            height: 230

            FluCarousel {
                id: banner_carousel
                width: 680
                height: 200
                anchors.centerIn: parent

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
                            source: ResourceModule.getRemoteDrawable(model.cover)
                            asynchronous: true
                            fillMode: Image.PreserveAspectCrop
                        }
                    }
                }
            }
        }

        highlightFollowsCurrentItem: false
        model: viewModel.bangumiList
        delegateModelAccess: DelegateModel.ReadOnly
        delegate: Component {
            Column {
                anchors.margins: viewModel.ui_listCellPadding
                width: viewModel.ui_listCellContentWidth
                height: viewModel.ui_listCellContentHeight

                FluClip {
                    radius: [8, 8, 8, 8]
                    width: parent.width
                    height: viewModel.ui_listCellContentCoverHeight

                    Image {
                        source: ResourceModule.getRemoteDrawable(modelData.cover)
                        cache: true
                        asynchronous: true
                        retainWhileLoading: true
                        mipmap: true
                        sourceSize {
                            width: parent.width
                            height: parent.height
                        }

                        fillMode: Image.PreserveAspectCrop
                    }
                }

                Text {
                    text: modelData.title
                    width: parent.width
                    wrapMode: Text.Wrap
                    elide: Text.ElideRight
                    maximumLineCount: 2
                    font.pointSize: 12
                    font.bold: true
                }
                Text {
                    text: modelData.desc
                    width: parent.width
                    elide: Text.ElideRight
                    maximumLineCount: 1
                    font.pointSize: 8
                    color: "gray"
                }
            }
        }
    }

    Component.onCompleted: {
        viewModel = ViewModelModule.createViewModel("page_home", page_home)
        page_home.widthChanged.connect(() => viewModel.onPageWidthChanged(page_home.width))
    }
}
