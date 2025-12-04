//
// Created by coder on 12/4/25.
//
#pragma once

#include <oatpp/codegen/ApiClient_define.hpp>

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiClient)

using namespace oatpp::web::client;
using namespace oatpp::data::mapping;

class QrcodeResp;

namespace biliqt::core::api::client {
    class LoginApi : public ApiClient {
        API_CLIENT_INIT(LoginApi)

        API_CALL(
            "GET", "/x/passport-tv-login/qrcode/auth_code",
            getResource
        )
    };
}

#include OATPP_CODEGEN_END(ApiClient)
