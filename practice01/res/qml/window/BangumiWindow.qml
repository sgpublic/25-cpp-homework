import QtQuick 2.15
import QtQuick.Layouts 1.15
import FluentUI 1.0
import BiliQt.ViewModel.LoginWindow 1.0

FluWindow {
    id: window_bangumi
    property var viewModel: ViewModelModule.createViewModel("window_bangumi", window_bangumi)
    title: viewModel.title === "" ? qsTrId("bangumi_title") : viewModel.title

    height: 750
    width: 1200
    minimumHeight: 700
    minimumWidth: 1100
    fitsAppBarWindows: true
    launchMode: FluWindowType.SingleTask

    FluScrollablePage {
        Column {
            Row {
                FluClip {
                    width: 240
                    height: 320
                    radius: [8, 8, 8, 8]

                    Image {
                        source: ResourceModule.getRemoteDrawable(viewModel.cover)
                        width: parent.width
                        height: parent.height
                    }
                }

                FluText {
                    text: viewModel.title
                    font: FluTextStyle.Title
                }
            }
        }
    }
}
