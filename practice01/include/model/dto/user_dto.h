//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include "oatpp/codegen/dto/base_define.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::model::dto {

    class UserInfoModel: public oatpp::DTO {
        DTO_INIT(UserInfoModel, DTO)
        DTO_FIELD(String, avatar);
        DTO_FIELD(String, nick);
    };

}

#include OATPP_CODEGEN_END(DTO)
