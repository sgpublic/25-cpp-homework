//
// Created by Haven Madray on 2025/12/15.
//
#include "core/api/bili_wbi_object.h"

#include "core/module/setting_module.h"

using namespace oatpp::web::protocol::http;
using namespace biliqt::core::module;

namespace biliqt::core::api {

    std::string mixin_key() {
        const auto& module = SettingModule::getInstance();
        // qDebug() << "mixin_key test, expect: ea1db124af3c7062474693fa704f4ff8, actual:" <<
        //     mixin_key("7cd084941338484aae1ad9425b84077c", "4932caff0ff746eab6f01bf08b70ac45");
        return mixin_key(module->wbi_img_key().toStdString(), module->wbi_sub_key().toStdString());
    }

    std::string mixin_key(const std::string& img_key, const std::string& sub_key) {
        const int MIXIN_KEY_ENC_TAB[] = {
            46, 47, 18, 2, 53, 8, 23, 32, 15, 50, 10, 31, 58, 3, 45, 35, 27, 43, 5, 49,
            33, 9, 42, 19, 29, 28, 14, 39, 12, 38, 41, 13, 37, 48, 7, 16, 24, 55, 40,
            61, 26, 17, 0, 1, 60, 51, 30, 4, 22, 25, 54, 21, 56, 59, 6, 63, 57, 62, 11,
            36, 20, 34, 44, 52
        };
        const std::string& raw_wbi_key = img_key + sub_key;
        std::ostringstream mixin_key_builder;
        for (const int& index : MIXIN_KEY_ENC_TAB) {
            mixin_key_builder << raw_wbi_key[index];
        }
        return mixin_key_builder.str().substr(0, 32);
    }

    void add_cookies_header(Headers& headers, const std::string& cookieItem) {
        std::ostringstream cookies;
        const auto& currentCookie = headers.get("Cookie").getValue("");
        cookies << currentCookie;
        if (!currentCookie.empty() && !currentCookie.ends_with(';')) {
            cookies << ";";
        }
        cookies << cookieItem << ";";
        const oatpp::String finalCookies = cookies.str();
        headers.putOrReplace("Cookie", finalCookies);
    }

    void add_cookies_header(Headers &headers, const std::string &key, const QString &cookie) {
        const std::string cookieItem = key + "=" + cookie.toStdString();
        add_cookies_header(headers, cookieItem);
    }

}
