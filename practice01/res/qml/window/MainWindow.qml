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

    FluNavigationView {
        id: home_navView

        displayMode: FluNavigationViewType.Open
        height: parent.height
        logo: ResourceModule.getDrawable("/app_logo.svg")
        pageMode: FluNavigationViewType.Stack
        title: qsTrId("app_name")
        width: parent.width

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
                id: home_navView_footer_about
                title: qsTrId("home_navView_footer_about")
                icon: FluentIcons.Contact
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
