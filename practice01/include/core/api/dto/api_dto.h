//
// Created by coder on 12/8/25.
//
#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "core/api/bili_sign_object.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::core::api::dto {

    class PgcPageReq : public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(PgcPageReq)
        DTO_FIELD(String, access_key);
        DTO_FIELD(Int32, tab_id) = 8;
    };

    class PgcPageResp : public oatpp::DTO {
        BILI_RESP_SAMPLE_DTO(PgcPageResp)
        class ModuleItems: public oatpp::DTO {
            EXPOSE_PROPERTY_DTO(ModuleItems)
            DTO_FIELD(String, cover);
            DTO_FIELD(String, title);
        };
    };

    class PgcPageBangumiReq : public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(PgcPageBangumiReq)
        DTO_FIELD(String, access_key);
        DTO_FIELD(String, cursor);
        DTO_FIELD(Int32, is_refresh);
    };

    class PgcPageBangumiResp : public oatpp::DTO {
        BILI_RESP_SAMPLE_DTO(PgcPageBangumiResp)
        class ModuleItems: public oatpp::DTO {
            EXPOSE_PROPERTY_DTO(ModuleItems)
            DTO_FIELD(Int32, season_id);
            DTO_FIELD(Int32, episode_id);

            DTO_FIELD(String, cover);
            DTO_FIELD(String, title);
            DTO_FIELD(String, desc);
            DTO_FIELD(String, type);
        };
    };

}

#include OATPP_CODEGEN_END(DTO)
