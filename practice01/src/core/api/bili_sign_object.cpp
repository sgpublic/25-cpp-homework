//
// Created by coder on 12/5/25.
//

#include "core/api/bili_sign_object.h"

#include <queue>

using namespace nlohmann;

namespace biliqt::core::api {
    json readRespBody(const std::shared_ptr<oatpp::web::protocol::http::incoming::Response> &body) {
        std::string bodyStr = body->readBodyToString();
        return json::parse(bodyStr);
    }

    std::string calculateSignValue(const std::unordered_map<std::string, std::string> &params, const std::string& apiSecret) {
        std::priority_queue<std::string, std::vector<std::string>, std::greater<>> keys;
        for (const auto &key: params | std::views::keys) {
            keys.push(key);
        }
        std::ostringstream secretCalculate;
        bool isFirst = true;
        while (!keys.empty()) {
            auto key = keys.top();
            keys.pop();
            if (isFirst) {
                isFirst = false;
            } else {
                secretCalculate << "&";
            }
            secretCalculate << key << "=" << utils::url_encode(params.at(key));
        }
        secretCalculate << apiSecret;
        return utils::md5(secretCalculate.str());
    }
}
