//
// Created by coder on 12/8/25.
//
#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>
#include "core/api/bili_sign_object.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::core::api::dto {

    class MyinfoReq final : public oatpp::DTO {
        BILI_SIGN_PASSPORT_REQUEST_DTO(MyinfoReq)
        DTO_FIELD(String, access_key);
    };

    class MyinfoResp final : public oatpp::DTO {
    public:
        class Data final : public oatpp::DTO {
            DTO_INIT(Data, DTO)

            DTO_FIELD(String, name);
            DTO_FIELD(String, face);
        };
        BILI_RESP_DATA_DTO(MyinfoResp, Data)
    };

}

#include OATPP_CODEGEN_END(DTO)
