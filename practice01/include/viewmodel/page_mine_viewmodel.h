//
// Created by coder on 12/4/25.
//
#pragma once

#include <functional>

#include "base_viewmodel.h"
#include "model/follow_model.h"
#include "utils/stdafx.h"

namespace biliqt::viewmodel {

    class MinePageViewModel: public ViewModel {
        Q_OBJECT
    public:
        Q_PROPERTY_READONLY_AUTO(QVariantList, currentWatching);
    private:
        std::shared_ptr<model::FollowModel> followModel;

        struct PageState {
            const int status;
            int currentPage;
            bool loading;
            bool hasNext;
        };

        PageState followWantState = {1, 0, false, true};
        PageState followWatchingState = {2, 0, false, true};
        PageState followWatchedState = {3, 0, false, true};
    public:
        explicit MinePageViewModel(QObject *parent = nullptr);
        VIEW_MODEL_COROUTINE_TASK(LoadCurrentWatching)
        VIEW_MODEL_COROUTINE_TASK(LoadFollowWatching)
        VIEW_MODEL_COROUTINE_TASK(LoadFollowWatched)
        VIEW_MODEL_COROUTINE_TASK(LoadFollowWant)
    private:
        void requestLoadFollow(
            const QVariantMap &args, PageState& state,
            const std::function<void()> &clearSignal,
            const std::function<void(const QVariantMap&)> &addSignal
        );
    public:
        Q_PROPERTY_READONLY_AUTO(double, ui_listWidth) = 0;
        Q_PROPERTY_READONLY_AUTO(double, ui_listHeaderHeight) = 230;

        Q_PROPERTY_READONLY_AUTO(double, ui_listCellHeight) = 100;
        Q_PROPERTY_READONLY_AUTO(double, ui_listCellWidth) = 100;
        Q_PROPERTY_READONLY_AUTO(double, ui_listCellPadding) = 8;

        Q_PROPERTY_READONLY_AUTO(int, ui_listCellContentHeight) = 100;
        Q_PROPERTY_READONLY_AUTO(int, ui_listCellContentWidth) = 100;
        Q_PROPERTY_READONLY_AUTO(int, ui_listCellContentCoverHeight) = 100;
    public:
        Q_INVOKABLE void onPageWidthChanged(double width);

    signals:
        void clearFollowWant();
        void addFollowWant(const QVariantMap& data);
        void clearFollowWatching();
        void addFollowWatching(const QVariantMap& data);
        void clearFollowWatched();
        void addFollowWatched(const QVariantMap& data);
    };

}
