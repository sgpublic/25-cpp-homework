//
// Created by Haven Madray on 2025/12/10.
//

#include "core/module/image_cache_module.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <qpixmapcache.h>

#include "utils/remote_resources.h"
#include "utils/string.h"

namespace biliqt::core::module {

    ImageCacheModule::ImageCacheModule(): QQuickImageProvider(Image) {
    }

    void ImageCacheModule::init(QQmlEngine *engine) {
        engine->addImageProvider("cache", getInstance());
    }

    QString ImageCacheModule::prefix() {
        return "image://cache";
    }

    QImage ImageCacheModule::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
        try {
            if (id.isEmpty()) {
                return {};
            }

            const auto cached = cachedFile(id);
            if (const QString cachePath = cached.filePath(); QFile::exists(cachePath)) {
                QImage img(cachePath);
                if (requestedSize.isValid()) {
                    img = img.scaled(requestedSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
                }
                if (size) *size = img.size();
                return img;
            }

            if (const QDir dir = cached.dir(); !dir.exists() && !dir.mkpath(dir.path())) {
                return {};
            }

            if (download_file(id.toStdString(), cached.filePath().toStdString()) == 0) {
                return requestImage(id, size, requestedSize);
            }
            return {};
        } catch (...) {
            qDebug() << "error during request image:" << id;
            return {};
        }
    }

    QFileInfo ImageCacheModule::cachedFile(const QString &id) {
        const QString exeDir = QCoreApplication::applicationDirPath();

        const std::string cacheId = utils::sha256(id.toStdString());
        const QString filePath = QDir(exeDir).filePath(
            QString("cache/images/%1.png").arg(cacheId)
        );

        return QFileInfo(filePath);
    }
}
