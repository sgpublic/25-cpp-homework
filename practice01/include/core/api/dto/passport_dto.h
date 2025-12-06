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
            DTO_FIELD(String, auth_code);
        };
        BILI_RESP_DTO(LoginQrcodeTvResp, Data)
    };

    class LoginQrcodeTvPollReq: public oatpp::DTO {
        BILI_SIGN_PASSPORT_REQUEST_DTO(LoginQrcodeTvPollReq)
        DTO_FIELD(Int32, local_id) = 0;
    };

    class LoginQrcodeTvPollResp: public oatpp::DTO {
    public:
        class Data: public oatpp::DTO {
            DTO_INIT(Data, DTO)

            DTO_FIELD(Int32, status);
            DTO_FIELD(String, message);
            DTO_FIELD(String, url);

            class TokenInfo: public oatpp::DTO {
                DTO_INIT(TokenInfo, DTO)

                DTO_FIELD(String, mid);
                DTO_FIELD(String, access_token);
                DTO_FIELD(String, refresh_token);
                DTO_FIELD(Int32, expires_in);
            };

            DTO_FIELD(Object<TokenInfo>, token_info);

            class CookieInfo: public oatpp::DTO {
                DTO_INIT(CookieInfo, DTO)

                class Cookie: public oatpp::DTO {
                    DTO_INIT(Cookie, DTO)

                    DTO_FIELD(String, name);
                    DTO_FIELD(String, value);
                };
                DTO_FIELD(List<Object<Cookie>>, cookies);
            };

            DTO_FIELD(Object<CookieInfo>, cookie_info);
        };
        BILI_RESP_DTO(LoginQrcodeTvPollResp, Data)
    };

}

#include OATPP_CODEGEN_END(DTO)
