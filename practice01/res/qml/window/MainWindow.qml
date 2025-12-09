import QtQuick 2.15
import FluentUI 1.0

FluWindow {
    id: window_main
    property var viewModel

    height: 900
    title: qsTrId("app_name")
    visible: true
    width: 1500
    launchMode: FluWindowType.SingleTask

    FluWindowResultLauncher {
        id: loginResultLauncher
        path: "/login"
        onResult: (data) => {
            if (data.loginSucceed) {
                viewModel.requestLoginSucceed()
                viewModel.requestLoadBannerData()
            }
        }
    }

    FluNavigationView {
        id: home_navView

        displayMode: FluNavigationViewType.Open
        height: parent.height
        logo: ResourceModule.getDrawable("/app_logo.svg")
        pageMode: FluNavigationViewType.Stack
        title: qsTrId("app_name")
        width: parent.width

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
                    home_navView.push(url)
                }
            }
        }

        footerItems: FluObject {
            FluPaneItem {
                id: home_navView_footer_login
                title: qsTrId("home_navView_footer_login")
                icon: FluentIcons.Contact
                onTapListener: function () {
                    loginResultLauncher.launch()
                }
                visible: !viewModel.hasLogin
            }
            FluPaneItem {
                id: home_navView_footer_user
                icon: FluentIcons.Contact
                property Component avatarImg: FluClip {
                    radius: [12, 12, 12, 12]
                    width: 24
                    height: 24

                    FluImage {
                        width: 24
                        height: 24
                        source: viewModel.avatarUrl
                    }
                }
                iconDelegate: viewModel.avatarUrl === "" ? null : avatarImg
                title: viewModel.nick
                onTapListener: function () {

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
            viewModel = ViewModelModule.createViewModel("window_main", window_main)

            window_main.setHitTestVisible(home_navView.buttonMenu);
            window_main.setHitTestVisible(home_navView.buttonBack);
            window_main.setHitTestVisible(home_navView.imageLogo);
            setCurrentIndex(0);
        }
    }
}
