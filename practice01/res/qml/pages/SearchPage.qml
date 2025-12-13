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
            width: viewModel.ui_listWidth
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            cellWidth: viewModel.ui_listCellWidth
            cellHeight: viewModel.ui_listCellHeight

            header: Item {
                width: viewModel.ui_listWidth
                height: 60

            }

            boundsBehavior: Flickable.StopAtBounds
            highlightFollowsCurrentItem: false
            model: search_list_data
            delegateModelAccess: DelegateModel.ReadOnly
            delegate: BangumiItem {
                cellPadding: viewModel.ui_listCellPadding
                cellContentWidth: viewModel.ui_listCellContentWidth
                cellContentHeight: viewModel.ui_listCellContentHeight
                cellContentCoverHeight: viewModel.ui_listCellContentCoverHeight
                cellCover: model.cover
                cellTitle: model.title
                cellDesc: model.desc

                onBangumiItemTapped: function () {
                    if (!SettingModule.login()) {
                        FluRouter.navigate("/login")
                        return
                    }
                    FluRouter.navigate("/bangumi")
                    GlobalSignalModule.requestBangumiInfo({
                        season_id: model.season_id,
                        episode_id: model.episode_id
                    })
                }
            }

            onContentYChanged: {
                const currentY = contentY;
                if (contentY + height + 280 < contentHeight) {
                    return
                }
                viewModel.requestLoadBangumiList({is_refresh: false})
                contentY = currentY
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
        viewModel.addBangumiData.connect(function (data) {
            bangumi_list_data.append(data)
        })
        viewModel.clearBangumiList.connect(() => bangumi_list_data.clear())
        page_home.widthChanged.connect(() => viewModel.onPageWidthChanged(page_home.width))

        GlobalSignalModule.loginStatusChanged.connect(function (isLogin) {
            viewModel.requestLoadBannerData()
            viewModel.requestLoadBangumiList({"is_refresh": true});
        })

        viewModel.requestLoadBannerData();
        viewModel.requestLoadBangumiList({"is_refresh": false});
    }
}
