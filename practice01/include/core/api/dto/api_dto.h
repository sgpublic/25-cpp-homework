//
// Created by coder on 12/8/25.
//
#pragma once

#include <oatpp/codegen/dto/base_define.hpp>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "core/api/bili_sign_object.h"
#include "core/api/bili_wbi_object.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::core::api::dto {

    class PgcPageReq : public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(PgcPageReq)
        DTO_FIELD(String, access_key);
        DTO_FIELD(Int32, tab_id) = 8;
    };

    class PgcPageResp : public oatpp::DTO {
        BILI_RESP_SAMPLE_DTO(PgcPageResp)
        class ModuleItems: public oatpp::DTO {
            EXPOSE_PROPERTY_DTO(ModuleItems)
            DTO_FIELD(String, cover);
            DTO_FIELD(String, title);
        };
    };

    class PgcPageBangumiReq : public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(PgcPageBangumiReq)
        DTO_FIELD(String, access_key);
        DTO_FIELD(String, cursor);
        DTO_FIELD(Int32, is_refresh);
    };

    class PgcPageBangumiResp : public oatpp::DTO {
        BILI_RESP_SAMPLE_DTO(PgcPageBangumiResp)
        class ModuleItems: public oatpp::DTO {
            EXPOSE_PROPERTY_DTO(ModuleItems)
            DTO_FIELD(Int32, season_id);
            DTO_FIELD(Int32, episode_id);

            DTO_FIELD(String, cover);
            DTO_FIELD(String, title);
            DTO_FIELD(String, desc);
            DTO_FIELD(String, type);
        };
    };

    class PgcPagePcBangumiTabReq : public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(PgcPagePcBangumiTabReq)
        DTO_FIELD(String, access_key);
    };

    class PgcPagePcBangumiTabResp : public oatpp::DTO {
        BILI_RESP_SAMPLE_DTO(PgcPagePcBangumiTabResp)
        class ModuleItems: public oatpp::DTO {
            EXPOSE_PROPERTY_DTO(ModuleItems)

            DTO_FIELD(Int32, season_id);

            DTO_FIELD(String, cover);
            DTO_FIELD(String, title);
            DTO_FIELD(String, desc);
        };
    };

    class PgcFollowBangumiReq : public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(PgcFollowBangumiReq)
        DTO_FIELD(Int32, status);
        DTO_FIELD(Int32, pn);
        DTO_FIELD(Int32, ps) = 20;
        DTO_FIELD(String, access_key);
    };

    class PgcFollowBangumiResp : public oatpp::DTO {
    public:
        class Data: public oatpp::DTO {
            DTO_INIT(Data, DTO)

            DTO_FIELD(Int32, has_next);

            class Item: public oatpp::DTO {
                EXPOSE_PROPERTY_DTO(Item)

                DTO_FIELD(Int32, season_id);

                DTO_FIELD(String, cover);
                DTO_FIELD(String, title);
            };

            DTO_FIELD(List<Object<Item>>, follow_list);
        };
        BILI_RESP_RESULT_DTO(PgcFollowBangumiResp, Data)
    };

    class WebNavResp: public oatpp::DTO {
    public:
        class Data: public oatpp::DTO {
            DTO_INIT(Data, DTO)

            DTO_FIELD(String, face);
            DTO_FIELD(String, uname);

            class WbiImg: public oatpp::DTO {
                DTO_INIT(WbiImg, DTO)

                DTO_FIELD(String, img_url);
                DTO_FIELD(String, sub_url);
            };
            DTO_FIELD(Object<WbiImg>, wbi_img);
        };
        BILI_RESP_DATA_DTO(WebNavResp, Data)
    };

    class WebSearchTypeReq: public oatpp::DTO {
        BILI_WBI_SEARCH_REQUEST_DTO(WebSearchTypeReq)
        DTO_FIELD(String, keyword);
        DTO_FIELD(Int32, page);
        DTO_FIELD(String, search_type) = "media_bangumi";
    };

    class WebSearchTypeResp: public oatpp::DTO {
        class Data: public oatpp::DTO {
            DTO_INIT(Data, DTO)

            DTO_FIELD(Int32, page);
            DTO_FIELD(Int32, numPages);

            class Result: public oatpp::DTO {
                DTO_INIT(Result, DTO)

                DTO_FIELD(Int32, season_id);
                DTO_FIELD(String, title);
                DTO_FIELD(String, desc);
                DTO_FIELD(String, pubtime);
            };
            DTO_FIELD(List<Object<Result>>, result);

            class VVoucher: public oatpp::DTO {
                DTO_INIT(VVoucher, DTO)
            };
            DTO_FIELD(Object<VVoucher>, v_voucher);
        };
        BILI_RESP_DATA_DTO(WebSearchTypeResp, Data)
    };

}

#include OATPP_CODEGEN_END(DTO)
