//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::model::dto {

    class UserInfoModel: public oatpp::DTO {
        DTO_INIT(UserInfoModel, DTO)
        DTO_FIELD(String, avatar);
        DTO_FIELD(String, nick);
    };

    ENUM(QrcodeState, int,
        VALUE(Loading, 1),
        VALUE(Loaded, 2),
        VALUE(Waiting, 3),
        VALUE(Success, 4),
        VALUE(Error, 5),
        VALUE(Scanned, 6),
        VALUE(Expired, 7)
    )

    class UserQrcodeStateModel: public oatpp::DTO {
        DTO_INIT(UserQrcodeStateModel, DTO)

        DTO_FIELD(Enum<QrcodeState>, state);
        DTO_FIELD(String, url);
        DTO_FIELD(String, authCode);
        DTO_FIELD(String, message);
    };

}

#include OATPP_CODEGEN_END(DTO)
