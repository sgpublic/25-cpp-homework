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

#include OATPP_CODEGEN_BEGIN(ApiClient)

class QrcodeResp;

namespace biliqt::core::api::client {

    class ApiClient : public BaseApiClient {
        BILI_SIGN_CLIENT_INIT(ApiClient, "api.bilibili.com", true)

    public:
        API_CALL(
            "GET", "/pgc/page/",
            pgc_page,
            QUERY(String, queries)
        )
        BILI_SIGN_GET(pgc_page)

    };

}

#include OATPP_CODEGEN_END(ApiClient)
