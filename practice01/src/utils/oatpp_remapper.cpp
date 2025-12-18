//
// Created by Haven Madray on 2025/12/17.
//

#include "utils/oatpp_remapper.h"

namespace biliqt::utils {

    oatpp::data::mapping::ObjectRemapper createRemapper() {
        oatpp::data::mapping::ObjectRemapper remapper;
        remapper.objectToTreeConfig().useUnqualifiedEnumNames = true;
        remapper.objectToTreeConfig().useUnqualifiedFieldNames = true;
        remapper.treeToObjectConfig().useUnqualifiedEnumNames = true;
        remapper.treeToObjectConfig().useUnqualifiedFieldNames = true;
        return remapper;
    }

}
