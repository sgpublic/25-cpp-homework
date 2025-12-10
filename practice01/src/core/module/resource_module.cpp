//
// Created by coder on 12/2/25.
//

#include "core/module/resource_module.h"

#include "core/module/image_cache_module.h"

namespace biliqt::core::module {

    ResourceModule::ResourceModule(QObject *parent) : QObject(parent) {
    }

    QString ResourceModule::get(const QString& path) {
        return "qrc:/biliqt" + path;
    }

    QString ResourceModule::getQml(const QString& path) {
        return get("/qml" + path);
    }

    QString ResourceModule::getDrawable(const QString& path) {
        return get("/drawable" + path);
    }

    QString ResourceModule::getRemoteDrawable(const QString &path) {
        return ImageCacheModule::getInstance()->prefix() + "/" + path;
    }
}
