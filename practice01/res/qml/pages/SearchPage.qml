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

        GridView {
            id: search_list
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            cellWidth: width / 2
            cellHeight: 180

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
            model: viewModel.searchResultList
            delegateModelAccess: DelegateModel.ReadOnly
            delegate: Row {
                padding: 10

                FluClip {
                    width: 120
                    height: 160
                    radius: [8, 8, 8, 8]

                    Image {
                        width: parent.width
                        height: parent.height

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

                Column {
                    leftPadding: 8
                    rightPadding: 8

                    width: search_list.cellWidth - 156

                    Text {
                        id: bangumi_item_title
                        width: parent.width

                        text: modelData.title

                        wrapMode: Text.Wrap
                        elide: Text.ElideRight
                        maximumLineCount: 1

                        font {
                            pointSize: 17
                            bold: true
                        }
                    }
                    Row {
                        width: parent.width
                        topPadding: 6
                        spacing: 4

                        Text {
                            text: modelData.styles
                            font {
                                pointSize: 12
                                bold: false
                            }
                            color: "#888888"
                        }
                        Text {
                            text: modelData.index_show
                            font {
                                pointSize: 12
                                bold: false
                            }
                            color: "#888888"
                        }
                        Text {
                            text: viewModel.timeFromTimestamp(modelData.pubtime)
                            font {
                                pointSize: 12
                                bold: false
                            }
                            color: "#888888"
                        }
                    }
                    Text {
                        width: parent.width
                        topPadding: 4

                        text: modelData.desc

                        wrapMode: Text.Wrap
                        elide: Text.ElideRight
                        maximumLineCount: 5

                        font {
                            pointSize: 12
                            bold: false
                        }
                        color: Qt.rgba(0.53, 0.53, 0.53, 0.6)
                    }
                }

                HoverHandler {
                    id: bangumi_item_hoverHandler
                    onHoveredChanged: function () {
                        if (bangumi_item_hoverHandler.hovered && bangumi_item_title.enabled) {
                            bangumi_item_title.color = "#20b0e3"
                        } else {
                            bangumi_item_title.color = FluTheme.fontPrimaryColor
                        }
                    }
                }

                Component.onCompleted: {
                    FluTheme.darkChanged.connect(function () {
                        bangumi_item_title.color = FluTheme.fontPrimaryColor
                    })
                }

                TapHandler {
                    id: bangumi_item_tapHandler
                    onTapped: {
                        FluRouter.navigate("/bangumi")
                        GlobalSignalModule.requestBangumiInfo({
                            season_id: modelData.season_id
                        })
                    }
                }
            }

            footer: Item {
                width: parent.width
                height: 60
                FluPagination {
                    id: search_pagination

                    anchors.horizontalCenter: parent.horizontalCenter

                    previousText: qsTrId("search_pre")
                    nextText: qsTrId("search_next")

                    pageCurrent: viewModel.currentPage
                    pageCount: viewModel.pageCount
                    itemCount: viewModel.numResults
                    __itemPerPage: viewModel.pagesize

                    visible: viewModel.pageCount > 1

                    Component.onCompleted: {
                        search_pagination.requestPage.connect(function (page, count) {
                            viewModel.requestLoadSearchResult({
                                page: page
                            })
                        })
                    }
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
                        search_list.positionViewAtBeginning()
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
