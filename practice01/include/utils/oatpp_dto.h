//
// Created by Haven Madray on 2025/12/17.
//
#pragma once

#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include <oatpp/Types.hpp>

#include <oatpp_remapper.h>

namespace biliqt::utils {
    QVariantMap treeToQVariant(const oatpp::data::mapping::TreeMap &dto);

    QVariantList treeToQVariant(const std::vector<oatpp::data::mapping::Tree> &dto);

    QVariantMap treeToQVariant(const std::vector<std::pair<oatpp::String, oatpp::data::mapping::Tree>> &dto);

    QVariant treeToQVariant(const oatpp::Tree& dto);

    template<typename T>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, T>::value,
        QVariantMap
    >::type
    dtoToQVariant(const oatpp::Object<T>& dto) {
        const auto& remapper = createRemapper();
        const auto& tree = remapper.remap<oatpp::Tree>(dto);
        const auto& treeMap = tree->getMap();
        return treeToQVariant(treeMap);
    }

    template<typename T>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, T>::value,
        QVariantList
    >::type
    dtoToQVariant(const oatpp::List<oatpp::Object<T>>& dto) {
        const auto& remapper = createRemapper();
        const auto& tree = remapper.remap<oatpp::Tree>(*dto)->getVector();
        return treeToQVariant(tree);
    }

    template<typename T>
    typename std::enable_if<
        std::is_base_of<oatpp::DTO, T>::value,
        QVariantList
    >::type
    dtoToQVariant(const std::list<oatpp::Object<T>>& dto) {
        auto list = QVariantList();
        for (const auto& item : dto) {
            list.append(dtoToQVariant(item));
        }
        return list;
    }

}
