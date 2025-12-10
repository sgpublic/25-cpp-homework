//
// Created by Haven Madray on 2025/12/10.
//

#pragma once

#include <QQuickImageProvider>

namespace biliqt::core::module {

    class CacheModule: public QQuickImageProvider {
        Q_OBJECT

    public:
        void init(QQmlEngine *engine);

        QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
    };

}
