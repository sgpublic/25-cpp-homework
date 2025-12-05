//
// Created by coder on 12/4/25.
//
#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "core/api/bili_sign_object.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::core::api::dto {

    class LoginQrcodeTvReq: public oatpp::DTO {
        BILI_SIGN_PASSPORT_REQUEST_DTO(LoginQrcodeTvReq)
        DTO_FIELD(Int32, local_id) = 0;
    };

    class LoginQrcodeTvResp: public oatpp::DTO {
    public:
        class Data: public oatpp::DTO {
            DTO_INIT(Data, DTO)

            DTO_FIELD(String, url);
            DTO_FIELD(String, authCode);
        };
        BILI_RESP_DTO(LoginQrcodeTvResp, Data)
    };

}

#include OATPP_CODEGEN_END(DTO)
