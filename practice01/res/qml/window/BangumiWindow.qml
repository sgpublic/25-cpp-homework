import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Effects 6.5
import FluentUI 1.0
import "../component"

FluWindow {
    id: window_bangumi
    property var viewModel: ViewModelModule.createViewModel("window_bangumi", window_bangumi)
    title: viewModel.title === "" ? qsTrId("bangumi_title") : viewModel.title

    height: 750
    width: 1200
    minimumHeight: 700
    minimumWidth: 1100
    fitsAppBarWindows: true
    launchMode: FluWindowType.SingleTask
    showStayTop: false

    function backToTop() {
        bangumi_container.contentY = 0
    }

    Item {
        anchors.fill: parent

        Flickable {
            id: bangumi_container
            anchors.fill: parent
            boundsBehavior: Flickable.StopAtBounds
            contentHeight: bangumi_content.height

            Column {
                id: bangumi_content
                width: parent.width

                ColumnLayout {
                    width: parent.width
                    height: 340

                    Item {
                        width: parent.width
                        height: parent.height
                        clip: true

                        Image {
                            width: parent.width + 40
                            height: parent.height + 40
                            fillMode: Image.PreserveAspectCrop
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter

                            layer.enabled: true
                            layer.effect: MultiEffect {
                                brightness: -0.15
                                blurEnabled: true
                                blurMax: 32
                                blur: 1.0
                            }

                            source: ResourceModule.getRemoteDrawable(viewModel.cover)
                        }

                        RowLayout {
                            width: viewModel.ui_contentWidth
                            height: 240
                            spacing: 20
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter

                            FluClip {
                                width: 180
                                height: 240
                                radius: [8, 8, 8, 8]

                                Image {
                                    width: parent.width
                                    height: parent.height

                                    source: ResourceModule.getRemoteDrawable(viewModel.cover)
                                }
                            }

                            Column {
                                Layout.fillWidth: true
                                Layout.fillHeight: true

                                Row {
                                    FluText {
                                        text: viewModel.title
                                        font {
                                            pointSize: 22
                                            bold: true
                                        }
                                        textColor: "white"
                                    }
                                }

                                Item {
                                    height: 20
                                    width: parent.width
                                }

                                RowLayout {
                                    spacing: 18
                                    width: parent.width

                                    Column {
                                        width: 80
                                        spacing: 6
                                        FluText {
                                            text: qsTrId("bangumi_total_play")
                                            textColor: "white"
                                            font {
                                                pointSize: 12
                                            }
                                        }
                                        FluText {
                                            text: viewModel.totalPlay
                                            textColor: "white"
                                            font {
                                                pointSize: 12
                                                bold: true
                                            }
                                        }
                                    }

                                    Rectangle {
                                        width: 1
                                        height: parent.height
                                        color: "white"
                                    }

                                    Column {
                                        width: 80
                                        spacing: 6
                                        FluText {
                                            text: qsTrId("bangumi_followers")
                                            textColor: "white"
                                            font {
                                                pointSize: 12
                                            }
                                        }
                                        FluText {
                                            text: viewModel.followers
                                            textColor: "white"
                                            font {
                                                pointSize: 12
                                                bold: true
                                            }
                                        }
                                    }

                                    Rectangle {
                                        width: 1
                                        height: parent.height
                                        color: "white"
                                    }

                                    Column {
                                        width: 80
                                        spacing: 6
                                        FluText {
                                            text: qsTrId("bangumi_danmakus")
                                            textColor: "white"
                                            font {
                                                pointSize: 12
                                            }
                                        }
                                        FluText {
                                            text: viewModel.danmakus
                                            textColor: "white"
                                            font {
                                                pointSize: 12
                                                bold: true
                                            }
                                        }
                                    }

                                    Item {
                                        height: 20
                                        Layout.fillWidth: true
                                    }

                                    RowLayout {
                                        height: parent.height
                                        spacing: 6

                                        visible: viewModel.hasScore

                                        FluText {
                                            text: viewModel.score.toFixed(1)
                                            font {
                                                pointSize: 32
                                                bold: true
                                            }
                                            textColor: "#FFA726"
                                        }
                                        Column {
                                            Row {
                                                spacing: 0
                                                Repeater {
                                                    model: 5
                                                    Item {
                                                        width: 26
                                                        height: 26
                                                        FluIcon {
                                                            property bool isSelected: {
                                                                return index < Math.round(viewModel.score / 2)
                                                            }
                                                            iconSize: 18
                                                            iconSource: isSelected ? FluentIcons.FavoriteStarFill : FluentIcons.FavoriteStar
                                                            iconColor: isSelected ? "#FFA726" : (FluTheme.dark ? "#FFFFFF" : "#000000")
                                                            anchors.centerIn: parent
                                                        }
                                                    }
                                                }
                                            }

                                            FluText {
                                                text: qsTrId("bangumi_rank_count").arg(viewModel.ratingCount)
                                                textColor: "white"
                                                leftPadding: 4
                                                font {
                                                    pointSize: 12
                                                }
                                            }
                                        }
                                    }
                                }

                                Item {
                                    height: 20
                                    width: parent.width
                                }

                                Row {
                                    spacing: 20

                                    FluText {
                                        text: viewModel.pubtime
                                        textColor: "white"
                                        font {
                                            pointSize: 12
                                        }
                                    }

                                    FluText {
                                        text: viewModel.timeLength
                                        textColor: "white"
                                        font {
                                            pointSize: 12
                                        }
                                    }
                                }

                                Item {
                                    height: 12
                                    width: parent.width
                                }

                                FluText {
                                    width: parent.width

                                    text: viewModel.desc
                                    textColor: "white"
                                    font {
                                        pointSize: 12
                                    }
                                    maximumLineCount: 6
                                    wrapMode: Text.Wrap
                                    elide: Text.ElideRight
                                }
                            }
                        }
                    }
                }

                ColumnLayout {
                    width: viewModel.ui_contentWidth
                    anchors.horizontalCenter: parent.horizontalCenter

                    Column {
                        width: parent.width
                        visible: viewModel.hasEpisode

                        Item {
                            width: parent.width
                            height: 20
                        }

                        FluText {
                            text: qsTrId("bangumi_episodes")
                            font {
                                pointSize: 18
                                bold: true
                            }
                        }

                        Item {
                            width: parent.width
                            height: 10
                        }

                        Grid {
                            id: bangumi_episodes_list
                            width: parent.width
                            height: viewModel.ui_episodeList_height
                            columns: viewModel.ui_episodeList_coloumn
                            rows: 2

                            Repeater {
                                model: viewModel.currentEpisodeList

                                delegate: Item {
                                    width: viewModel.ui_episodeList_cellWidth
                                    height: viewModel.ui_episodeList_cellHeight

                                    BangumiItem {
                                        cellPadding: viewModel.ui_episodeList_cellPadding
                                        cellContentWidth: viewModel.ui_episodeList_cellContentWidth
                                        cellContentHeight: viewModel.ui_episodeList_cellContentHeight
                                        cellContentCoverHeight: viewModel.ui_episodeList_cellContentCoverHeight
                                        cellCover: modelData.cover
                                        cellTitle: modelData.title

                                        onBangumiItemTapped: function () {
                                            // FluRouter.navigate("/bangumi")
                                            // GlobalSignalModule.requestBangumiInfo({
                                            //     season_id: viewModel.seasonId,
                                            //     episode_id: modelData.ep_id
                                            // })
                                            // backToTop()
                                        }
                                    }
                                }
                            }
                        }

                        FluPagination {
                            id: episode_pagination
                            anchors.horizontalCenter: parent.horizontalCenter
                            visible: viewModel.episodePageCount > 1

                            previousText: qsTrId("search_pre")
                            nextText: qsTrId("search_next")

                            pageCurrent: viewModel.episodePageIndex
                            pageCount: viewModel.episodePageCount
                            itemCount: viewModel.episodeList.length
                            __itemPerPage: viewModel.ui_episodeList_coloumn * 2

                            Component.onCompleted: {
                                episode_pagination.requestPage.connect(function (page, count) {
                                    viewModel.episodePageIndex = page
                                    viewModel.loadEpisodeSlice()
                                })
                            }
                        }
                    }

                    Column {
                        width: parent.width
                        visible: viewModel.hasSeries

                        Item {
                            width: parent.width
                            height: 20
                        }

                        FluText {
                            text: qsTrId("bangumi_series").arg(viewModel.seriesTitle)
                            font {
                                pointSize: 18
                                bold: true
                            }
                        }

                        Item {
                            width: parent.width
                            height: 10
                        }

                        Grid {
                            id: bangumi_episodes_series
                            width: parent.width
                            columns: viewModel.ui_seriesList_coloumn

                            Repeater {
                                model: viewModel.seriesList

                                delegate: Item {
                                    width: viewModel.ui_seriesList_cellWidth
                                    height: viewModel.ui_seriesList_cellHeight

                                    BangumiItem {
                                        cellPadding: viewModel.ui_seriesList_cellPadding
                                        cellContentWidth: viewModel.ui_seriesList_cellContentWidth
                                        cellContentHeight: viewModel.ui_seriesList_cellContentHeight
                                        cellContentCoverHeight: viewModel.ui_seriesList_cellContentCoverHeight
                                        cellCover: modelData.cover
                                        cellTitle: modelData.title

                                        onBangumiItemTapped: function () {
                                            FluRouter.navigate("/bangumi")
                                            GlobalSignalModule.requestBangumiInfo({
                                                season_id: modelData.season_id,
                                            })
                                            backToTop()
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Column {
                        width: parent.width
                        visible: viewModel.hasCelebrity

                        Item {
                            width: parent.width
                            height: 20
                        }

                        FluText {
                            text: qsTrId("bangumi_celebrity")
                            font {
                                pointSize: 18
                                bold: true
                            }
                        }
                        Item {
                            width: parent.width
                            height: 10
                        }

                        Grid {
                            id: bangumi_episodes_celebrity
                            width: parent.width
                            columns: viewModel.ui_celebrityList_coloumn
                            rows: 1

                            Repeater {
                                model: viewModel.currentCelebrityList

                                delegate: Item {
                                    width: viewModel.ui_celebrityList_cellWidth
                                    height: viewModel.ui_celebrityList_cellHeight

                                    BangumiItem {
                                        cellPadding: viewModel.ui_celebrityList_cellPadding
                                        cellContentWidth: viewModel.ui_celebrityList_cellContentWidth
                                        cellContentHeight: viewModel.ui_celebrityList_cellContentHeight
                                        cellContentCoverHeight: viewModel.ui_celebrityList_cellContentCoverHeight
                                        cellCover: modelData.avatar
                                        cellTitle: modelData.name
                                        cellDesc: modelData.desc

                                        onBangumiItemTapped: function () { }
                                    }
                                }
                            }
                        }

                        FluPagination {
                            id: celebrity_pagination
                            anchors.horizontalCenter: parent.horizontalCenter
                            visible: viewModel.celebrityPageCount > 1

                            previousText: qsTrId("search_pre")
                            nextText: qsTrId("search_next")

                            pageCurrent: viewModel.celebrityPageIndex
                            pageCount: viewModel.celebrityPageCount
                            itemCount: viewModel.celebrity.length
                            __itemPerPage: viewModel.ui_celebrityList_coloumn

                            Component.onCompleted: {
                                celebrity_pagination.requestPage.connect(function (page, count) {
                                    viewModel.celebrityPageIndex = page
                                    viewModel.loadCelebritySlice()
                                })
                            }
                        }
                    }

                    Column {
                        width: parent.width
                        visible: viewModel.hasRecommend

                        Item {
                            width: parent.width
                            height: 20
                        }


                        FluText {
                            text: qsTrId("bangumi_recommend")
                            font {
                                pointSize: 18
                                bold: true
                            }
                        }

                        Item {
                            width: parent.width
                            height: 10
                        }

                        Grid {
                            id: bangumi_episodes_recommend
                            width: parent.width
                            columns: viewModel.ui_recommendList_coloumn

                            Repeater {
                                model: viewModel.recommendList

                                delegate: Item {
                                    width: viewModel.ui_recommendList_cellWidth
                                    height: viewModel.ui_recommendList_cellHeight

                                    BangumiItem {
                                        cellPadding: viewModel.ui_recommendList_cellPadding
                                        cellContentWidth: viewModel.ui_recommendList_cellContentWidth
                                        cellContentHeight: viewModel.ui_recommendList_cellContentHeight
                                        cellContentCoverHeight: viewModel.ui_recommendList_cellContentCoverHeight
                                        cellCover: modelData.cover
                                        cellTitle: modelData.title

                                        onBangumiItemTapped: function () {
                                            FluRouter.navigate("/bangumi")
                                            GlobalSignalModule.requestBangumiInfo({
                                                season_id: modelData.season_id,
                                            })
                                            backToTop()
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Item {
                        width: parent.width
                        height: 40
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
                id: bangumi_backToTop
                radius: 16
                padding: 6

                FluIconButton {
                    iconSource: FluentIcons.Up
                    iconSize: 18
                    radius: 12
                    onClicked: {
                        backToTop()
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        window_bangumi.widthChanged.connect(() => viewModel.onPageWidthChanged(window_bangumi.width))
        viewModel.onPageWidthChanged(window_bangumi.width)
        GlobalSignalModule.requestBangumiInfo.connect(function (data) {
            backToTop()
        })
        GlobalSignalModule.loginStatusChanged.connect(function (isLogin) {
            window_bangumi.close()
        })
        GlobalSignalModule.showToastOnBangumiWindow.connect(function (isSuccess, text) {
            if (isSuccess) {
                showSuccess(text)
            } else {
                showError(text)
            }
        })
    }
}
