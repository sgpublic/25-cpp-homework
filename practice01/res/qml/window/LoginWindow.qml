import QtQuick 2.15
import QtQuick.Layouts 1.15
import FluentUI 1.0
import BiliQt.ViewModel.LoginWindow 1.0

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

        FluStatusLayout {
            id: login_qrcode
            implicitWidth: 140
            implicitHeight: 140
            Layout.topMargin: 40
            Layout.alignment: Qt.AlignHCenter

            statusMode: viewModel.ui_statusMode
            errorText: viewModel.ui_errorText
            loadingText: viewModel.ui_loadingText

            FluQRCode {
                size: 140
                margins: 10

                text: viewModel.qrcodeUrl
            }
        }
        Connections {
            target: login_qrcode

            function onErrorClicked() {
                viewModel.requestLoginQrcode()
            }
        }

        FluText {
            Layout.topMargin: 20
            Layout.alignment: Qt.AlignHCenter

            text: qsTrId("login_qrcode_scan_info")
            font: FluTextStyle.Body
        }
    }

    Component.onCompleted: {
        viewModel = ViewModelModule.createViewModel("window_login", window_login)

        viewModel.closeWindowSignal.connect(function() {
            setResult({loginSucceed: true})
            window_login.close();
        })

        viewModel.requestLoginQrcode()
    }
}