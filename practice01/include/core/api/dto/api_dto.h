//
// Created by coder on 12/8/25.
//

#pragma once
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "core/api/bili_sign_object.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::core::api::dto {
#define TV_LOCAL_ID 0

    class PgcPageReq final : public oatpp::DTO {
        BILI_SIGN_PASSPORT_REQUEST_DTO(PgcPageReq)
        DTO_FIELD(String, access_key);
        DTO_FIELD(Int32, tab_id) = 8;
    };

    class PgcPageResp final : public oatpp::DTO {
        BILI_RESP_SAMPLE_DTO(MyinfoResp)
    };

}
