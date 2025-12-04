//
// Created by coder on 12/4/25.
//
#pragma once

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiClient)

class QrcodeResp;

namespace biliqt::core::api::client {
    class LoginApi : public oatpp::web::client::ApiClient {
        API_CLIENT_INIT(LoginApi)

        API_CALL(
            "GET", "/x/passport-tv-login/qrcode/auth_code",
            getResource
        )
    };
}

#include OATPP_CODEGEN_END(ApiClient)
