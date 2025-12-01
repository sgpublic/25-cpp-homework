import QtQuick 2.15
import FluentUI 1.0

FluWindow {
    height: 300
    title: "test"
    visible: true
    width: 400

    FluNavigationView {
        id: navView

        displayMode: FluNavigationViewType.Auto
        height: parent.height

        // 导航项数据
        items: navigationItems

        // 基本属性
        logo: "qrc:/res/image/logo.ico"
        pageMode: FluNavigationViewType.NoStack
        title: "我的应用"
        width: parent.width

        // Logo点击事件
        onLogoClicked: {
            console.log("Logo被点击");
        }
    }
}
