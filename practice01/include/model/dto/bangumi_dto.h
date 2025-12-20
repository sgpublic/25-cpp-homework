//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include "oatpp/codegen/dto/base_define.hpp"
#include "oatpp/codegen/dto/base_define.hpp"
#include "oatpp/codegen/dto/base_define.hpp"
#include "oatpp/codegen/dto/base_define.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::model::dto {

    class BangumiInfoModel: public oatpp::DTO {
        DTO_INIT(BangumiInfoModel, DTO)

        class MetaData: public oatpp::DTO {
            DTO_INIT(MetaData, DTO)

            DTO_FIELD(String, title);
            DTO_FIELD(String, cover);
            DTO_FIELD(String, desc);
            DTO_FIELD(String, pubtime);
            DTO_FIELD(String, state);

            DTO_FIELD(Int32, danmakus);
            DTO_FIELD(Int32, followers);
            DTO_FIELD(Int32, totalPlay);
        };
        DTO_FIELD(Object<MetaData>, metaData);

        class Rating: public oatpp::DTO {
            DTO_INIT(Rating, DTO)
            DTO_FIELD(Int32, count);
            DTO_FIELD(Float32, score);
        };
        DTO_FIELD(Object<Rating>, rating) = nullptr;

        class Episode: public oatpp::DTO {
            DTO_INIT(Episode, DTO)

            DTO_FIELD(Int32, episode_id);
            DTO_FIELD(String, cover);
            DTO_FIELD(String, title);
        };
        DTO_FIELD(List<Object<Episode>>, episodes);

        class Series: public oatpp::DTO {
            DTO_INIT(Series, DTO)
            class Season: public oatpp::DTO {
                DTO_INIT(Season, DTO)

                DTO_FIELD(Int32, season_id);
                DTO_FIELD(String, cover);
                DTO_FIELD(String, title);
            };

            DTO_FIELD(String, title);
            DTO_FIELD(List<Object<Season>>, seasons);
        };
        DTO_FIELD(Object<Series>, series) = nullptr;

        class Celebrity: public oatpp::DTO {
            DTO_INIT(Celebrity, DTO)
            DTO_FIELD(String, avatar);
            DTO_FIELD(String, desc);
            DTO_FIELD(String, name);
        };
        DTO_FIELD(List<Object<Celebrity>>, celebrity) = nullptr;
    };

    class BangumiRecommendModel: public oatpp::DTO {
        DTO_INIT(BangumiRecommendModel, DTO)

        class Season: public oatpp::DTO {
            DTO_INIT(Season, DTO)

            DTO_FIELD(String, cover);
            DTO_FIELD(Int32, season_id);
            DTO_FIELD(String, title);
        };
        DTO_FIELD(List<Object<Season>>, data);
    };

}

#include OATPP_CODEGEN_END(DTO)
