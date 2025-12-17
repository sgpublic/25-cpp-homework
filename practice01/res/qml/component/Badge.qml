import FluentUI 1.0

FluRectangle {
    property alias text: content_text.text
    property alias textColor: content_text.textColor
    property alias textFont: content_text.font
    property alias textPadding: content_text.padding

    borderWidth: 2
    borderStyle: Qt.DashLine

    FluText {
        id: content_text
        width: parent.width
        height: parent.height
    }
}