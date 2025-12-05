import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import FluentUI 1.0

FluWindow {
    id: window_login
    property var viewModel

    title: qsTrId("login_title")
    width: 320
    height: 280
    fixSize: true
    launchMode: FluWindowType.SingleTask

    ColumnLayout {
        width: parent.width
        FluQRCode{
            Layout.topMargin: 40
            Layout.alignment: Qt.AlignHCenter

            size: 140
            text: viewModel.qrcodeUrl
        }
    }

    Component.onCompleted: {
        viewModel = ViewModelModule.createViewModel("window_login", window_login)
        viewModel.requestLoginQrcode()
    }
}