//
// Created by coder on 12/4/25.
//
#pragma once

#include <oatpp/web/client/ApiClient.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/codegen/ApiClient_define.hpp>

#include "_base_client.h"
#include "core/api/bili_sign_client.h"
#include "core/api/bili_sign_object.h"
#include "utils/string.h"

#include OATPP_CODEGEN_BEGIN(ApiClient)

class QrcodeResp;

namespace biliqt::core::api::client {

    class AppClient : public BaseApiClient {
        BILI_SIGN_CLIENT_INIT(AppClient, "app.bilibili.com", true)

    public:
        API_CALL(
            "GET", "/x/v2/account/myinfo",
            myinfo,
            QUERY(String, queries)
        )
        BILI_SIGN_GET(myinfo)

    };

}

#include OATPP_CODEGEN_END(ApiClient)
