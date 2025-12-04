import QtQuick 2.15
import QtQuick.Controls 2.15

GridView {
    property var dataModel: null

    property Component itemDelegate: null

    model: dataModel
    delegate: itemDelegate
    cellHeight: 120

    readonly property int columnsCount: Math.max(1, Math.floor(width / 160))

    cellWidth: width / columnsCount

    clip: true
    flickableDirection: Flickable.Vertical
}
