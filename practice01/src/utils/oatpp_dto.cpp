//
// Created by Haven Madray on 2025/12/17.
//

#include "utils/oatpp_dto.h"

#include <oatpp/base/Log.hpp>


namespace biliqt::utils {

    QVariantMap treeToQVariant(const oatpp::data::mapping::TreeMap &dto) {
        auto map = QVariantMap();
        for (int index = 0; index < dto.size(); index++) {
            const auto&[key, value] = dto[index];
            map[key->c_str()] = treeToQVariant(dto[key]);
        }
        return map;
    }

    QVariantList treeToQVariant(const std::vector<oatpp::data::mapping::Tree> &dto) {
        auto list = QVariantList();
        for (const auto& item : dto) {
            list.append(treeToQVariant(item));
        }
        return list;
    }

    QVariantMap treeToQVariant(const std::vector<std::pair<oatpp::String, oatpp::data::mapping::Tree>> &dto) {
        auto map = QVariantMap();
        for (const auto& [key, value] : dto) {
            map[key->c_str()] = treeToQVariant(value);
        }
        return map;
    }

    QVariant treeToQVariant(const oatpp::Tree &dto) {
        switch (dto->getType()) {
            case oatpp::data::mapping::Tree::Type::UNDEFINED:
            case oatpp::data::mapping::Tree::Type::NULL_VALUE:
                return {};
            case oatpp::data::mapping::Tree::Type::INT_32:
                return dto->getPrimitive<int32_t>();
            case oatpp::data::mapping::Tree::Type::INTEGER:
                return dto->getInteger();
            case oatpp::data::mapping::Tree::Type::FLOAT:
                return dto->getFloat();
            case oatpp::data::mapping::Tree::Type::BOOL:
                return dto->getPrimitive<bool>();
            case oatpp::data::mapping::Tree::Type::INT_8:
                return dto->getPrimitive<int8_t>();
            case oatpp::data::mapping::Tree::Type::UINT_8:
                return dto->getPrimitive<uint8_t>();
            case oatpp::data::mapping::Tree::Type::INT_16:
                return dto->getPrimitive<int16_t>();
            case oatpp::data::mapping::Tree::Type::UINT_16:
                return dto->getPrimitive<uint16_t>();
            case oatpp::data::mapping::Tree::Type::UINT_32:
                return dto->getPrimitive<uint32_t>();
            case oatpp::data::mapping::Tree::Type::INT_64:
                return dto->getPrimitive<int64_t>();
            case oatpp::data::mapping::Tree::Type::UINT_64:
                return dto->getPrimitive<uint64_t>();
            case oatpp::data::mapping::Tree::Type::FLOAT_32:
                return dto->getPrimitive<v_float32>();
            case oatpp::data::mapping::Tree::Type::FLOAT_64:
                return dto->getPrimitive<v_float64>();
            case oatpp::data::mapping::Tree::Type::STRING:
                return dto->getString()->c_str();
            case oatpp::data::mapping::Tree::Type::VECTOR:
                return treeToQVariant(dto->getVector());
            case oatpp::data::mapping::Tree::Type::MAP:
                return treeToQVariant(dto->getMap());
            case oatpp::data::mapping::Tree::Type::PAIRS:
                return treeToQVariant(dto->getPairs());
        }
        OATPP_LOGd("treeToQVariant", "unknown type of Tree: {}", static_cast<int>(dto->getType()));
        return {};
    }
}
