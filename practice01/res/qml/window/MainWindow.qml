import QtQuick 2.15
import FluentUI 1.0

FluWindow {
    id: window_main
    title: qsTrId("app_name")
    property var viewModel: ViewModelModule.createViewModel("window_main", window_main)

    height: 750
    width: 1200
    minimumHeight: 700
    minimumWidth: 1100
    fitsAppBarWindows: true
    launchMode: FluWindowType.SingleTask

    appBar: FluAppBar {
        height: 30
        showStayTop: false
        z: 7
    }

    FluNavigationView {
        id: home_navView

        displayMode: FluNavigationViewType.Open
        anchors.fill: parent
        logo: ResourceModule.getDrawable("/app_logo.svg")
        pageMode: FluNavigationViewType.Stack
        title: qsTrId("app_name")
        topPadding: FluTools.isMacos() ? 20 : 0

        buttonBack.visible: false

        items: FluObject {
            FluPaneItem {
                id: home_navView_item_setting
                title: qsTrId("home_navView_item_home")
                icon: FluentIcons.Home
                url: ResourceModule.getQml("/pages/HomePage.qml")
                onTap: {
                    home_navView.push(url)
                }
            }
            FluPaneItem {
                id: home_navView_item_mine
                title: qsTrId("home_navView_item_mine")
                icon: FluentIcons.People
                url: ResourceModule.getQml("/pages/MinePage.qml")
                onTap: {
                    if (viewModel.hasLogin) {
                        home_navView.push(url)
                    } else {
                        login_resultLauncher.launch()
                    }
                }
            }
        }

        footerItems: FluObject {
            FluPaneItem {
                id: home_navView_footer_login
                title: qsTrId("home_navView_footer_login")
                icon: FluentIcons.Contact
                onTapListener: function () {
                    FluRouter.navigate("/login")
                }
                visible: !viewModel.hasLogin
            }
            FluContentDialog{
                id: home_navView_logout_dialog
                title: qsTrId("home_logout_title")
                message: qsTrId("home_logout_msg")
                negativeText: qsTrId("home_logout_cancel")
                positiveText: qsTrId("home_logout_ok")
                buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
                onPositiveClicked: {
                    viewModel.requestLogout()
                }
            }
            FluPaneItem {
                id: home_navView_footer_user
                icon: FluentIcons.Contact
                property Component avatarImg: FluClip {
                    radius: [12, 12, 12, 12]
                    width: 24
                    height: 24

                    Image {
                        sourceSize.width: 24
                        sourceSize.height: 24
                        source: ResourceModule.getRemoteDrawable(viewModel.avatarUrl)
                    }
                }
                iconDelegate: viewModel.avatarUrl === "" ? null : avatarImg
                title: viewModel.nick
                onTapListener: function () {
                    home_navView_logout_dialog.open()
                }
                visible: viewModel.hasLogin
            }
            FluPaneItem {
                id: home_navView_footer_about
                title: qsTrId("home_navView_footer_about")
                icon: FluentIcons.Info
                onTapListener: function () {
                    FluRouter.navigate("/about")
                }
            }
            FluPaneItem {
                id: home_navView_footer_setting
                title: qsTrId("home_navView_footer_setting")
                icon: FluentIcons.Settings
                url: ResourceModule.getQml("/pages/SettingPage.qml")
                onTap: {
                    home_navView.push(url)
                }
            }
        }

        Component.onCompleted: {
            setCurrentIndex(0);
        }
    }

    Component.onCompleted: {
        window_main.setHitTestVisible(home_navView.buttonMenu);
        window_main.setHitTestVisible(home_navView.buttonBack);
        window_main.setHitTestVisible(home_navView.imageLogo);

        GlobalSignalModule.loginSuccess.connect(function () {
            viewModel.requestLoginSucceed()
        })
    }
}
