import QtQuick 2.15
import FluentUI 1.0
import "../component/navigation"

FluWindow {
    id: window_main
    height: 900
    title: qsTrId("app_name")
    visible: true
    width: 1500

    FluNavigationView {
        id: home_navView

        displayMode: FluNavigationViewType.Open
        height: parent.height
        logo: ResourceModule.getDrawable("/app_logo.svg")
        pageMode: FluNavigationViewType.NoStack
        title: qsTrId("app_name")
        width: parent.width

        items: NavCommonItems
        footerItems: NavFooterItems

        Component.onCompleted: {
            NavCommonItems.navigationView = home_navView;
            NavFooterItems.navigationView = home_navView;
            window_main.setHitTestVisible(home_navView.buttonMenu);
            window_main.setHitTestVisible(home_navView.buttonBack);
            window_main.setHitTestVisible(home_navView.imageLogo);
            setCurrentIndex(0);
        }
    }
}
