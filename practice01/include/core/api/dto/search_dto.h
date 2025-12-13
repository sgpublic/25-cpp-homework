//
// Created by coder on 12/4/25.
//
#pragma once

#include <oatpp/codegen/dto/base_define.hpp>
#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>
#include "core/api/bili_sign_object.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::core::api::dto {
    class SearchSuggestReq final : public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(SearchSuggestReq)

        DTO_FIELD(String, term);
        DTO_FIELD(String, main_ver) = "v1";
        DTO_FIELD(Int32, special_acc_num) = 1;
        DTO_FIELD(Int32, topic_acc_num) = 1;
        DTO_FIELD(Int32, upuser_acc_num) = 3;
        DTO_FIELD(Int32, tag_num) = 10;
        DTO_FIELD(Int32, special_num) = 10;
        DTO_FIELD(Int32, bangumi_num) = 10;
        DTO_FIELD(Int32, upuser_num) = 10;
    };

    class SearchSuggestResp final : public oatpp::DTO {
        EXPOSE_PROPERTY_DTO(SearchSuggestResp)
        DTO_FIELD(Int32, code);
        class Data: public oatpp::DTO {
            DTO_INIT(Data, DTO)

            class Item final : public oatpp::DTO {
                DTO_INIT(Item, DTO)

                DTO_FIELD(String, value);
                DTO_FIELD(String, name);
            };
            DTO_FIELD(List<Object<Item>>, tag);
        };
        DTO_FIELD(Object<Data>, result);
    };

}

#include OATPP_CODEGEN_END(DTO)
