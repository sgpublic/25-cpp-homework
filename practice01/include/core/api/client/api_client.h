//
// Created by coder on 12/4/25.
//
#pragma once

#include <oatpp/web/client/ApiClient.hpp>
#include <oatpp/macro/codegen.hpp>

#include "_base_client.h"
#include "core/api/bili_wbi_object.h"
#include "core/module/setting_module.h"

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

        API_CALL(
            "GET", "/x/web-interface/nav",
            web_nav
        )
        API_CALL_HEADERS(web_nav) {
            BILI_WBI_DEFAULT_HEADERS
            BILI_WBI_COOKIE_SESSDATA
        }

        API_CALL(
            "GET", "/x/web-interface/wbi/search/type",
            web_search_type,
            QUERY(String, queries)
        )
        API_CALL_HEADERS(web_search_type) {
            BILI_WBI_DEFAULT_HEADERS
            BILI_WBI_COOKIE_SESSDATA
            headers.putOrReplace("Referer", "https://search.bilibili.com");
        }

        API_CALL(
            "GET", "/pgc/view/v2/app/season",
            pgc_season,
            QUERY(String, queries)
        )
        BILI_SIGN_GET(pgc_season)
    };

}

#include OATPP_CODEGEN_END(ApiClient)
