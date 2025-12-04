pragma Singleton

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FluentUI 1.0
import QtQuick.Controls.FluentWinUI3

FluScrollablePage {
    title: qsTrId("page_setting_title")
    launchMode: FluPageType.SingleInstance

    FluFrame {
        id: page_setting_theme

        Layout.topMargin: 20
        Layout.fillWidth: true
        height: 50
        padding: 10

        ColumnLayout {
            width: parent.width
            spacing: 10

            FluText {
                Layout.bottomMargin: 4

                text: qsTrId("page_setting_display")
                font: FluTextStyle.BodyStrong
            }

            ColumnLayout {
                RowLayout {
                    FluText {
                        Layout.fillWidth: true
                        Layout.horizontalStretchFactor: 1

                        text: qsTrId("page_setting_theme")
                        font: FluTextStyle.BodyStrong
                    }

                    FluComboBox {
                        model: ListModel {
                            id: page_setting_theme_model
                            ListElement {
                                text: qsTrId("page_setting_theme_followSystem")
                            }
                            ListElement {
                                text: qsTrId("page_setting_theme_light")
                            }
                            ListElement {
                                text: qsTrId("page_setting_theme_dark")
                            }
                        }
                        currentIndex: SettingModule.getDarkMode();

                        onCurrentIndexChanged: {
                            SettingModule.saveDarkMode(currentIndex)
                            FluTheme.darkMode = currentIndex
                        }
                    }
                }

                RowLayout {
                    FluText {
                        Layout.fillWidth: true
                        Layout.horizontalStretchFactor: 1

                        text: qsTrId("page_setting_language")
                        font: FluTextStyle.BodyStrong
                    }

                    FluComboBox {
                        model: ListModel {
                            id: page_setting_language_model
                            ListElement {
                                text: "简体中文"
                            }
                            ListElement {
                                text: "English"
                            }
                        }
                        currentIndex: TranslateModule.indexOfCurrent();

                        onCurrentIndexChanged: {
                            SettingModule.saveLanguage(TranslateModule.keyOfIndex(currentIndex));
                            TranslateModule.setLanguage(currentIndex);
                        }
                    }
                }
            }
        }
    }
}
