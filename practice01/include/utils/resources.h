//
// Created by coder on 12/2/25.
//
#pragma once

#include <QUrl>
namespace biliqt::utils {
    class Resources {
    public:
        static QUrl get(const std::string& path);
        static QUrl get_qml(const std::string& path);
        static QUrl get_resources(const std::string& path);
    private:
        static QUrl real_get(const std::string& path);
    };
}
