//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::model::dto {

    class MineCurrentWatchingModel: public oatpp::DTO {
        DTO_INIT(MineCurrentWatchingModel, DTO)
        class Item: public oatpp::DTO {
            DTO_INIT(Item, DTO)

            DTO_FIELD(Int32, season_id);

            DTO_FIELD(String, cover);
            DTO_FIELD(String, title);
            DTO_FIELD(String, desc);
        };
        DTO_FIELD(List<Object<Item>>, data);
    };

    class MineFollowListModel: public oatpp::DTO {
        DTO_INIT(MineFollowListModel, DTO)
        DTO_FIELD(Boolean, has_next);
        DTO_FIELD(Int32, current_page);

        class Item: public oatpp::DTO {
            DTO_INIT(Item, DTO)

            DTO_FIELD(Int32, season_id);

            DTO_FIELD(String, cover);
            DTO_FIELD(String, title);
        };

        DTO_FIELD(List<Object<Item>>, data);
    };

}

#include OATPP_CODEGEN_END(DTO)
