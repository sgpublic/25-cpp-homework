//
// Created by coder on 12/4/25.
//
#pragma once

#include <oatpp/web/client/ApiClient.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include "_base_client.h"

#include OATPP_CODEGEN_BEGIN(ApiClient)

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

        API_CALL(
            "GET", "/pgc/page/bangumi",
            pgc_page_bangumi,
            QUERY(String, queries)
        )
        BILI_SIGN_GET(pgc_page_bangumi)

        API_CALL(
            "GET", "/pgc/page/pc/bangumi/tab",
            pgc_page_pc_bangumi_tab,
            QUERY(String, queries)
        )
        BILI_SIGN_GET(pgc_page_pc_bangumi_tab)

        API_CALL(
            "GET", "/pgc/app/follow/v2/bangumi",
            pgc_follow_bangumi,
            QUERY(String, queries)
        )
        BILI_SIGN_GET(pgc_follow_bangumi)

    };

}

#include OATPP_CODEGEN_END(ApiClient)
