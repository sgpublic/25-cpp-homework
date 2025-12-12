import QtQuick 2.15
import QtQuick.Controls 2.15
import FluentUI 1.0

Column {
    property var cellPadding
    property var cellContentWidth
    property var cellContentHeight
    property var cellContentCoverRadius: [8, 8, 8, 8]
    property var cellContentCoverHeight

    property var cellCover
    property var cellTitle
    property var cellTitleMarginTop: 8
    property var cellTitleSize: 13
    property var cellTitleHeighlightColor: "#20b0e3"
    property var cellDesc
    property var cellDescMarginTop: 2
    property var cellDescSize: 9
    property var cellDescColor: "gray"

    anchors.margins: cellPadding
    width: cellContentWidth
    height: cellContentHeight

    FluClip {
        id: bangumi_item_cover
        radius: cellContentCoverRadius
        width: parent.width
        height: cellContentCoverHeight

        Image {
            source: ResourceModule.getRemoteDrawable(cellCover)
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

    Item {
        height: cellTitleMarginTop
        width: parent.width
    }
    FluText {
        id: bangumi_item_title
        width: parent.width

        text: cellTitle ?? ""
        wrapMode: Text.Wrap
        elide: Text.ElideRight
        maximumLineCount: 1

        font {
            pointSize: cellTitleSize
            bold: true
        }
    }

    Item {
        height: cellDescMarginTop
        width: parent.width
    }
    FluText {
        text: cellDesc ?? ""
        width: parent.width

        elide: Text.ElideRight
        maximumLineCount: 1
        font {
            pointSize: cellDescSize
        }
        textColor: cellDescColor
    }

    HoverHandler {
        id: bangumi_item_hoverHandler
        onHoveredChanged: function () {
            if (bangumi_item_hoverHandler.hovered && bangumi_item_title.enabled) {
                bangumi_item_title.color = cellTitleHeighlightColor
            } else {
                bangumi_item_title.color = bangumi_item_title.textColor
            }
        }
    }

    signal bangumiItemTapped()

    TapHandler {
        id: bangumi_item_tapHandler
        onTapped: {
            bangumiItemTapped()
        }
    }
}