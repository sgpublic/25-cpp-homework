import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Effects 6.5
import FluentUI 1.0

FluWindow {
    id: window_bangumi
    property var viewModel: ViewModelModule.createViewModel("window_bangumi", window_bangumi)
    title: viewModel.title === "" ? qsTrId("bangumi_title") : ""

    height: 750
    width: 1200
    minimumHeight: 700
    minimumWidth: 1100
    fitsAppBarWindows: true
    launchMode: FluWindowType.SingleTask

    appBar: FluAppBar {
        height: 30
        showStayTop: false
    }

    Flickable {
        id: bangumi_container
        anchors.fill: parent
        ScrollBar.vertical: FluScrollBar {
        }
        boundsBehavior: Flickable.StopAtBounds
        contentHeight: bangumi_content.height

        ColumnLayout {
            id: bangumi_content
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
                        blurMax: 64
                        blur: 1.0
                    }

                    source: ResourceModule.getRemoteDrawable(viewModel.cover)
                }

                RowLayout {
                    width: parent.width - 200 > 1200 ? 1200 : parent.width - 200
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

                            RowLayout {
                                height: parent.height
                                Layout.fillWidth: true
                                spacing: 6

                                Item {
                                    height: 20
                                    Layout.fillWidth: true
                                }

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
                                                        return index <= viewModel.score
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

            RowLayout {
                Column {

                }
                Column {
                    FluFrame {
                        FluText {
                            text: qsTrId("bangumi_")
                        }
                    }
                    FluFrame {

                    }
                }
            }
        }
    }
}
