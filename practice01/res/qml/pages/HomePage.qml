import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.Basic 2.15
import FluentUI 1.0
import "../component"

FluPage {
    id: page_home

    property var viewModel: ViewModelModule.createViewModel("page_home", page_home)

    launchMode: FluPageType.SingleInstance

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

    Item {
        width: parent.width
        height: parent.height

        ListModel {
            id: bangumi_list_data
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

            boundsBehavior: Flickable.StopAtBounds
            highlightFollowsCurrentItem: false
            model: bangumi_list_data
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
                radius: 16
                padding: 6
                FluIconButton {
                    iconSource: FluentIcons.Refresh
                    iconSize: 18
                    radius: 12
                    onClicked: {
                        bangumi_list.positionViewAtBeginning()
                        viewModel.requestLoadBangumiList({"is_refresh": true});
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

        GlobalSignalModule.loginSuccess.connect(function () {
            viewModel.requestLoginSucceed()
            viewModel.requestLoadBannerData()
        })

        viewModel.requestLoadBannerData();
        viewModel.requestLoadBangumiList({"is_refresh": false});
    }
}
