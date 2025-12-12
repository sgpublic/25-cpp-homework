import QtQuick 2.15
import QtQuick.Layouts 1.15
import FluentUI 1.0
import BiliQt.ViewModel.LoginWindow 1.0

FluWindow {
    id: window_bangumi
    title: qsTrId("bangumi_title")
    property var viewModel: ViewModelModule.createViewModel("window_bangumi", window_bangumi)

    height: 750
    width: 1200
    minimumHeight: 700
    minimumWidth: 1100
    fitsAppBarWindows: true
    launchMode: FluWindowType.SingleTask
}
