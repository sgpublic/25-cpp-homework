//
// Created by Haven Madray on 2025/12/10.
//

#pragma once

#include <QFileInfo>
#include <QQuickImageProvider>

#include "utils/singleton.h"

namespace biliqt::core::module {

    class ImageCacheModule: public QQuickImageProvider {
        Q_OBJECT

        SINGLETON(ImageCacheModule)

    private:
        explicit ImageCacheModule();
    public:
        void init(QQmlEngine *engine);
        QString prefix();

        QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    private:
        QFileInfo cachedFile(const QString &id);
    };

}
