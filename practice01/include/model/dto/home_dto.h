//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::model::dto {

    class HomeBannerModel: public oatpp::DTO {
        DTO_INIT(HomeBannerModel, DTO)
        class Item: public oatpp::DTO {
            DTO_INIT(Item, DTO)
            DTO_FIELD(String, cover);
            DTO_FIELD(String, title);
        };
        DTO_FIELD(List<Object<Item>>, data);
    };

    class HomeBangumiModel : public oatpp::DTO {
        DTO_INIT(HomeBangumiModel, DTO)
        DTO_FIELD(String, next_cursor);
        DTO_FIELD(Boolean, has_next);
        class Item: public oatpp::DTO {
            DTO_INIT(Item, DTO)

            DTO_FIELD(Int32, season_id);
            DTO_FIELD(Int32, episode_id);

            DTO_FIELD(String, cover);
            DTO_FIELD(String, title);
            DTO_FIELD(String, desc);
            DTO_FIELD(String, type);
        };
        DTO_FIELD(List<Object<Item>>, data);
    };

}

#include OATPP_CODEGEN_END(DTO)
