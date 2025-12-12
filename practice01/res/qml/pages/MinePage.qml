import QtQuick 2.15
import FluentUI 1.0
import "../component"

FluPage {
    id: page_mine

    property var viewModel: ViewModelModule.createViewModel("page_mine", page_mine)

    launchMode: FluPageType.SingleInstance

    header: Column {
        width: parent.width

        FluText {
            text: qsTrId("mine_current_watching")
            font {
                pointSize: 22
                bold: true
            }
        }

        Item {
            height: 12
            width: parent.width
        }

        ListView {
            width: parent.width
            height: 150
            model: viewModel.currentWatching
            orientation: ListView.Horizontal
            spacing: 12
            highlightFollowsCurrentItem: false

            delegate: BangumiItem {
                cellPadding: 0
                cellContentWidth: 160
                cellContentHeight: 140
                cellContentCoverHeight: 100
                cellCover: modelData.cover
                cellTitle: modelData.title
                cellDesc: modelData.desc

                onBangumiItemTapped: function () {
                    FluRouter.navigate("/bangumi")
                    GlobalSignalModule.requestBangumiInfo({
                        season_id: modelData.season_id,
                    })
                }
            }
        }
    }

    Component {
        id: mine_follow_list_delegate

        BangumiItem {
            cellPadding: viewModel.ui_listCellPadding
            cellContentWidth: viewModel.ui_listCellContentWidth
            cellContentHeight: viewModel.ui_listCellContentHeight
            cellContentCoverHeight: viewModel.ui_listCellContentCoverHeight
            cellCover: model.cover
            cellTitle: model.title
            cellDesc: model.desc

            onBangumiItemTapped: function () {
                FluRouter.navigate("/bangumi")
                GlobalSignalModule.requestBangumiInfo({
                    season_id: model.season_id
                })
            }
        }
    }

    ListModel {
        id: mine_follow_list_want
    }
    ListModel {
        id: mine_follow_list_watching
    }
    ListModel {
        id: mine_follow_list_watched
    }

    FluPivot {
        anchors.fill: parent
        font {
            pointSize: 22
        }

        FluPivotItem {
            title: qsTrId("mine_want")
            contentItem: FollowPage {
                listWidth: viewModel.ui_listWidth
                cellWidth: viewModel.ui_listCellWidth
                cellHeight: viewModel.ui_listCellHeight

                model: mine_follow_list_want
                delegate: mine_follow_list_delegate
                onRequestLoading: function (isRefresh) {
                    viewModel.requestLoadWant({is_refresh: isRefresh})
                }
            }
        }

        FluPivotItem {
            title: qsTrId("mine_watching")
            contentItem: FollowPage {
                listWidth: viewModel.ui_listWidth
                cellWidth: viewModel.ui_listCellWidth
                cellHeight: viewModel.ui_listCellHeight

                model: mine_follow_list_watching
                delegate: mine_follow_list_delegate
                onRequestLoading: function (isRefresh) {
                    viewModel.requestLoadWatching({is_refresh: isRefresh})
                }
            }
        }

        FluPivotItem {
            title: qsTrId("mine_watched")
            contentItem: FollowPage {
                listWidth: viewModel.ui_listWidth
                cellWidth: viewModel.ui_listCellWidth
                cellHeight: viewModel.ui_listCellHeight

                model: mine_follow_list_watched
                delegate: mine_follow_list_delegate
                onRequestLoading: function (isRefresh) {
                    viewModel.requestLoadWatched({is_refresh: isRefresh})
                }
            }
        }
    }

    Component.onCompleted: {
        page_mine.widthChanged.connect(() => viewModel.onPageWidthChanged(page_mine.width))

        viewModel.clearFollowWant.connect(() => mine_follow_list_want.clear())
        viewModel.addFollowWant.connect((data) => mine_follow_list_want.append(data))
        viewModel.clearFollowWatching.connect(() => mine_follow_list_watching.clear())
        viewModel.addFollowWatching.connect((data) => mine_follow_list_watching.append(data))
        viewModel.clearFollowWatched.connect(() => mine_follow_list_watched.clear())
        viewModel.addFollowWatched.connect((data) => mine_follow_list_watched.append(data))
    }
}
