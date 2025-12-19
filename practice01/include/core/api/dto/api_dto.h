//
// Created by coder on 12/8/25.
//
#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

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
    public:
        class Result: public oatpp::DTO {
            BILI_RESP_MODULES_DTO(Result)

            class TopicModule: public oatpp::DTO {
            public:
                class Item: public oatpp::DTO {
                    DTO_INIT(Item, DTO)
                    DTO_FIELD(String, cover);
                    DTO_FIELD(String, title);
                };
                BILI_RESP_MODULE_ITEM_DTO(TopicModule, Item, "topic")
            };
        };
        BILI_RESP_RESULT_DTO(PgcPageResp, Result)
    };

    class PgcPageBangumiReq : public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(PgcPageBangumiReq)
        DTO_FIELD(String, access_key);
        DTO_FIELD(String, cursor);
        DTO_FIELD(Int32, is_refresh);
    };

    class PgcPageBangumiResp : public oatpp::DTO {
    public:
        class Result: public oatpp::DTO {
            BILI_RESP_MODULES_DTO(Result)
            DTO_FIELD(String, next_cursor);
            DTO_FIELD(Int32, has_next);

            class DoubleFeedModule: public oatpp::DTO {
            public:
                class Item: public oatpp::DTO {
                    DTO_INIT(Item, DTO)

                    DTO_FIELD(Int32, season_id);
                    DTO_FIELD(Int32, episode_id);

                    DTO_FIELD(String, cover);
                    DTO_FIELD(String, title);
                    DTO_FIELD(String, desc);
                    DTO_FIELD(String, type);
                };
                BILI_RESP_MODULE_ITEM_DTO(DoubleFeedModule, Item, "double_feed")
            };
        };
        BILI_RESP_RESULT_DTO(PgcPageBangumiResp, Result)
    };

    class PgcPagePcBangumiTabReq : public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(PgcPagePcBangumiTabReq)
        DTO_FIELD(String, access_key);
    };

    class PgcPagePcBangumiTabResp : public oatpp::DTO {
    public:
        class Data: public oatpp::DTO {
            BILI_RESP_MODULES_DTO(Data)

            class FollowModule: public oatpp::DTO {
            public:
                class Item: public oatpp::DTO {
                    DTO_INIT(Item, DTO)

                    DTO_FIELD(Int32, season_id);

                    DTO_FIELD(String, cover);
                    DTO_FIELD(String, title);
                    DTO_FIELD(String, desc);
                };
                BILI_RESP_MODULE_ITEM_DTO(FollowModule, Item, "follow")
            };
        };
        BILI_RESP_DATA_DTO(PgcPagePcBangumiTabResp, Data)
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
        class Result: public oatpp::DTO {
            DTO_INIT(Result, DTO)
            DTO_FIELD(Int32, has_next);

            class Item: public oatpp::DTO {
                DTO_INIT(Item, DTO)

                DTO_FIELD(Int32, season_id);

                DTO_FIELD(String, cover);
                DTO_FIELD(String, title);
            };

            DTO_FIELD(List<Object<Item>>, follow_list);
        };
        BILI_RESP_RESULT_DTO(PgcFollowBangumiResp, Result)
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
                DTO_INIT(Result, DTO)

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
            BILI_RESP_MODULES_DTO(Data)

            class SeasonModule: public oatpp::DTO {
                BILI_RESP_MODULE_DTO(SeasonModule, "season")
                class Data: public oatpp::DTO {
                    DTO_INIT(Data, DTO)
                    class Season: public oatpp::DTO {
                        DTO_INIT(Season, DTO)

                        DTO_FIELD(Int32, season_id);
                        DTO_FIELD(String, cover);
                        DTO_FIELD(String, title);
                        DTO_FIELD(String, season_title);
                    };

                    DTO_FIELD(List<Object<Season>>, seasons);
                };
                DTO_FIELD(Object<Data>, data);
                DTO_FIELD(String, title);
            };

            class EpisodeModule: public oatpp::DTO {
                BILI_RESP_MODULE_DTO(SeasonModule, "episode")
                class Data: public oatpp::DTO {
                    DTO_INIT(Data, DTO)
                    class Episode: public oatpp::DTO {
                        DTO_INIT(Episode, DTO)

                        DTO_FIELD(Int32, ep_id);
                        DTO_FIELD(Int32, ep_index);
                        DTO_FIELD(Int32, pub_time);
                        DTO_FIELD(String, cover);
                        DTO_FIELD(String, long_title);
                        DTO_FIELD(String, show_title);
                    };

                    DTO_FIELD(List<Object<Episode>>, episodes);
                };
                DTO_FIELD(Object<Data>, data);
            };

            class Celebrity: public oatpp::DTO {
                DTO_INIT(Celebrity, DTO)
                DTO_FIELD(String, avatar);
                DTO_FIELD(String, desc);
                DTO_FIELD(String, name);
            };
            DTO_FIELD(List<Object<Celebrity>>, celebrity);
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
                DTO_FIELD(Int32, count);
                DTO_FIELD(Float32, score);
            };
            DTO_FIELD(Object<Rating>, rating);
            DTO_FIELD(String, refine_cover);
            DTO_FIELD(String, season_title);
            class Stat: public oatpp::DTO {
                DTO_INIT(Stat, DTO)
                DTO_FIELD(Int32, danmakus);
                DTO_FIELD(Int32, favorite);
                DTO_FIELD(Int32, views);
            };
            DTO_FIELD(Object<Stat>, stat);
            class Style: public oatpp::DTO {
                DTO_INIT(Style, DTO)
                DTO_FIELD(String, name);
            };
            DTO_FIELD(List<Object<Style>>, styles);
            DTO_FIELD(Int32, total);
            class UserStatus: public oatpp::DTO {
                DTO_INIT(UserStatus, DTO)
                class Progress: public oatpp::DTO {
                    DTO_INIT(Progress, DTO)
                    DTO_FIELD(Int32, last_ep_id);
                    DTO_FIELD(Int64, last_time);
                };
                DTO_FIELD(Object<Progress>, progress) = nullptr;
            };
            DTO_FIELD(Object<UserStatus>, user_status);
        };

        BILI_RESP_DATA_DTO(PgcSeasonResp, Data)
    };

    class PgcSeasonRecommendReq: public oatpp::DTO {
        BILI_SIGN_API_REQUEST_DTO(PgcSeasonRecommendReq)
        DTO_FIELD(Int64, season_id);
        DTO_FIELD(String, access_key);
    };

    class PgcSeasonRecommendResp: public oatpp::DTO {
    public:
        class Data: public oatpp::DTO {
            DTO_INIT(Data, DTO)
        };

        BILI_RESP_DATA_DTO(PgcSeasonRecommendResp, Data)
    };



}

#include OATPP_CODEGEN_END(DTO)
