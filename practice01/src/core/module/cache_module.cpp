//
// Created by Haven Madray on 2025/12/10.
//

#include "core/module/cache_module.h"

#include <QCoreApplication>
#include <QFile>
#include <qpixmapcache.h>
#include <QQmlContext>
#include <QStandardPaths>

#include "utils/string.h"

namespace biliqt::core::module {
    void CacheModule::init(QQmlEngine *engine) {

    }

    QPixmap CacheModule::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
        QPixmap pix;
        if (QPixmapCache::find(id, &pix)) {
            return pix;  // 已经缓存过
        }
    }
}
