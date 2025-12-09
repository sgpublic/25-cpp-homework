//
// Created by coder on 12/4/25.
//

#pragma once

#include <QtConcurrentRun>
#include <oatpp/core/Types.hpp>

#include "base_viewmodel.h"

namespace biliqt::model {

    class ViewModel : public QObject {
    private:
        QList<QFuture<void>> tasks;
    public:
        explicit ViewModel(QObject *parent = nullptr) : QObject(parent) {}

        ~ViewModel() override {
            for (QFuture<void>& task : tasks) {
                if (!task.isFinished()) {
                    task.cancel();
                }
            }
        }

        void startTask(const std::function<void()>& block) {
            if (needInterrupt()) {
                return;
            }
            const QFuture<void> task = QtConcurrent::run(block);
            tasks.append(task);
        }

        static oatpp::String oat_str(const QString& qstr) {
            return {qstr.toUtf8().data(), qstr.toUtf8().size()};
        }

        static bool needInterrupt() {
            return QThread::currentThread()->isInterruptionRequested();
        }
    };

}

#define VIEW_MODEL_COROUTINE_TASK(NAME)                                                                    \
    public:                                                                                                \
        Q_INVOKABLE void request##NAME(const QVariantMap& args = QVariantMap()) {                          \
            startTask([this, args]() {                                                                     \
                on##NAME(args);                                                                            \
            });                                                                                            \
        }                                                                                                  \
    private:                                                                                               \
        void on##NAME(const QVariantMap& args = QVariantMap());
