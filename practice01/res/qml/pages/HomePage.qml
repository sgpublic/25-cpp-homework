pragma Singleton

import QtQuick 2.15
import FluentUI 1.0

FluScrollablePage {
    id: page_home

    property var viewModel

    launchMode: FluPageType.SingleTask

    FluAutoSuggestBox {
        iconSource: FluentIcons.Search
        emptyText: qsTrId("home_search_hint")
        text: viewModel.searchText
        onTextChanged: {
            viewModel.searchText = text
        }
    }

    Component.onCompleted: {
        viewModel = ViewModelModule.createViewModel("page_home", page_home)
    }
}
