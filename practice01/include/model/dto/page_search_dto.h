//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::model::dto {

    class SearchResultModel : public oatpp::DTO {
        DTO_INIT(SearchResultModel, DTO)

        DTO_FIELD(Int32, totalCount);
        DTO_FIELD(Int32, pageCount);
        DTO_FIELD(Int32, pageSize);
        DTO_FIELD(Int32, currentPage);

        class Item: public oatpp::DTO {
            DTO_INIT(Item, DTO)

            DTO_FIELD(Int32, season_id);
            DTO_FIELD(String, title);
            DTO_FIELD(String, desc);
            DTO_FIELD(String, cover);
            DTO_FIELD(String, styles);
            DTO_FIELD(Int64, pubtime);
            DTO_FIELD(String, index_show);

            // class MediaScore: public oatpp::DTO {
            //     DTO_INIT(MediaScore, DTO)
            //
            //     DTO_FIELD(Float32, score);
            //     DTO_FIELD(Int32, user_count);
            // };
            // DTO_FIELD(Object<MediaScore>, media_score);
        };
        DTO_FIELD(List<Object<Item>>, data);
    };

}

#include OATPP_CODEGEN_END(DTO)
