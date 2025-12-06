//
// Created by coder on 12/4/25.
//
#pragma once

#include <oatpp/web/client/ApiClient.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "core/api/bili_sign_client.h"
#include <oatpp/codegen/ApiClient_define.hpp>

#include OATPP_CODEGEN_BEGIN(ApiClient)

class QrcodeResp;

namespace biliqt::core::api::client {

    class PassportApi : public oatpp::web::client::ApiClient {
        BILI_SIGN_CLIENT_INIT(PassportApi, "passport.bilibili.com", true)

    public:
        API_CALL(
            "POST", "/x/passport-tv-login/qrcode/auth_code",
            qrcodeTv,
            BODY_STRING(String, body)
        )
        BILI_SIGN_POST(qrcodeTv)

        API_CALL(
            "POST", "/x/passport-tv-login/qrcode/poll",
            qrcodeTvPoll,
            BODY_STRING(String, body)
        )
        BILI_SIGN_POST(qrcodeTvPoll)
    };

}

#include OATPP_CODEGEN_END(ApiClient)
