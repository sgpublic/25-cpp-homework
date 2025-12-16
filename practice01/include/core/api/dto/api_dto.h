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
            DTO_FIELD(Int32, numResults);
            DTO_FIELD(Int32, pagesize);

            class Result: public oatpp::DTO {
                EXPOSE_PROPERTY_DTO(Result)

                DTO_FIELD(Int32, season_id);
                DTO_FIELD(String, title);
                DTO_FIELD(String, desc);
                DTO_FIELD(String, cover);
                DTO_FIELD(String, styles);
                DTO_FIELD(Int64, pubtime);
                DTO_FIELD(String, index_show);

                class MediaScore: public oatpp::DTO {
                    DTO_INIT(MediaScore, DTO)

                    DTO_FIELD(Float32, score);
                    DTO_FIELD(Int32, user_count);
                };
                // DTO_FIELD(Object<MediaScore>, media_score);
            };
            DTO_FIELD(List<Object<Result>>, result);

            class VVoucher: public oatpp::DTO {
                DTO_INIT(VVoucher, DTO)
            };
            DTO_FIELD(Object<VVoucher>, v_voucher) = nullptr;
        };
        BILI_RESP_DATA_DTO(WebSearchTypeResp, Data)
    };

    class PgcSeasonReq: public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(PgcSeasonReq)
        DTO_FIELD(Int64, season_id);
        DTO_FIELD(String, access_key);
    };

    class PgcSeasonResp: public oatpp::DTO {
    public:
        class Data: public oatpp::DTO {
            DTO_INIT(Data, DTO)
            DTO_FIELD(String, evaluate);

            class NewEp: public oatpp::DTO {
                DTO_INIT(NewEp, DTO)
                DTO_FIELD(String, desc);
            };
            DTO_FIELD(Object<NewEp>, new_ep);
            DTO_FIELD(String, origin_name);
            class Publish: public oatpp::DTO {
                DTO_INIT(Publish, DTO)
                DTO_FIELD(Int32, is_finish);
                DTO_FIELD(Int32, is_started);
                DTO_FIELD(String, release_date_show);
                DTO_FIELD(String, time_length_show);
            };
            DTO_FIELD(Object<Publish>, publish);
            class Rating: public oatpp::DTO {
                DTO_INIT(Rating, DTO)
                DTO_FIELD(Float32, score);
            };
            DTO_FIELD(Object<Rating>, rating);
            DTO_FIELD(String, refine_cover);
            DTO_FIELD(String, season_title);
            class Stat: public oatpp::DTO {
                DTO_INIT(Stat, DTO)
                DTO_FIELD(String, followers);
                DTO_FIELD(String, play);
            };
            DTO_FIELD(Object<Stat>, stat);
            class Style: public oatpp::DTO {
                DTO_INIT(Style, DTO)
                DTO_FIELD(String, name);
            };
            DTO_FIELD(Object<Style>, styles);
            DTO_FIELD(Int32, total);
            class UserStatus: public oatpp::DTO {
                DTO_INIT(UserStatus, DTO)
                class Progress: public oatpp::DTO {
                    DTO_INIT(Progress, DTO)
                    DTO_FIELD(Int32, last_ep_id);
                    DTO_FIELD(Int64, last_time);
                };
                DTO_FIELD(Object<Progress>, progress);
            };
            DTO_FIELD(Object<UserStatus>, user_status);
        };
        BILI_RESP_DATA_DTO(PgcSeasonResp, Data)
    };

}

#include OATPP_CODEGEN_END(DTO)
