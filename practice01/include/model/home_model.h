//
// Created by Haven Madray on 2025/12/20.
//
#pragma once

#include <oatpp/Types.hpp>

#include "core/api/client/api_client.h"
#include "dto/home_dto.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace biliqt::model {

    class HomeModel: public QObject {
        Q_OBJECT
    private:
        std::shared_ptr<core::api::client::ApiClient> apiClient;
    public:
        explicit HomeModel(QObject *parent = nullptr);

        oatpp::Object<dto::HomeBannerModel> getBannerData();

        oatpp::Object<dto::HomeBangumiModel> getBangumiList(std::string cursor, bool isRefresh);
    };

}

#include OATPP_CODEGEN_END(DTO)
