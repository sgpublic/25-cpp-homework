//
// Created by coder on 12/2/25.
//

#include <utils/resources.h>
using namespace biliqt::utils;

QUrl Resources::real_get(const std::string& path) {
    return QUrl("qrc:" + QString::fromStdString(path));
}

QUrl Resources::get(const std::string& path) {
    return real_get("/biliqt" + path);
}

QUrl Resources::get_qml(const std::string& path) {
    return get("/qml" + path);
}

QUrl Resources::get_drawable(const std::string& path) {
    return get("/drawable" + path);
}
