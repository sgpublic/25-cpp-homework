//
// Created by Haven Madray on 2025/12/13.
//
#pragma once

#include <oatpp/web/client/ApiClient.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/codegen/ApiClient_define.hpp>

#include "_base_client.h"

#include OATPP_CODEGEN_BEGIN(ApiClient)

namespace biliqt::core::api::client {

    class SearchClient : public BaseApiClient {
        BILI_SIGN_CLIENT_INIT(SearchClient, "s.search.bilibili.com", true)

    public:
        API_CALL(
            "GET", "/main/suggest",
            suggest,
            QUERY(String, queries)
        )
        API_CALL_HEADERS(suggest) {
            BILI_SIGN_DEFAULT_HEADERS
            headers.putOrReplace("Referer", "https://s.search.bilibili.com");
        }
    };

}

#include OATPP_CODEGEN_END(ApiClient)
