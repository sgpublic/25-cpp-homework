//
// Created by coder on 12/5/25.
//

#include <oatpp/network/Address.hpp>
#include <oatpp/network/Url.hpp>
#include <oatpp/network/tcp/client/ConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp-openssl/client/ConnectionProvider.hpp>

#include "core/api/bili_sign_executor.h"

#include "core/api/bili_sign_client.h"
#include "core/api/bili_sign_object.h"

using namespace oatpp::parser::json::mapping;
using namespace oatpp::web::client;
using namespace oatpp::network;

namespace biliqt::core::api {

    std::shared_ptr<RequestExecutor::Response> BiliApiExecutor::executeOnceReal(const int &redirectTime,
        const String &method, const String &path, const Headers &headers, const std::shared_ptr<Body> &body,
        const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        const auto newPath = signedPath(method, path);
        printRequestDetails(method, newPath, headers);
        std::shared_ptr<Response> resp = _inner->executeOnce(method, newPath, headers, body, connectionHandle);
        return resp;
    }

    oatpp::async::CoroutineStarterForResult<const std::shared_ptr<RequestExecutor::Response> &>
    BiliApiExecutor::executeOnceAsyncReal(const int &redirectTime, const String &method, const String &path, const Headers &headers,
        const std::shared_ptr<Body> &body, const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        const auto newPath = signedPath(method, path);
        printRequestDetails(method, newPath, headers);
        oatpp::async::CoroutineStarterForResult<const std::shared_ptr<Response>&> resp = _inner->executeAsync(method, newPath, headers, body, connectionHandle);
        return resp;
    }

    void BiliApiExecutor::printRequestDetails(const String &method, const String &path, const Headers &headers) {
        OATPP_LOGD("BiliApiExecutor", " %s %s", method->c_str(), path->c_str());
        for (const auto&[key, value] : headers.getAll()) {
            OATPP_LOGD("BiliApiExecutor", "   %s: %s", key.std_str().c_str(), value.std_str().c_str());
        }
    }

    oatpp::String BiliApiExecutor::signedPath(const String &method, const String &path) {
        if (method != "GET") {
            return path;
        }
        const int queryMark = path->find('?');
        if (queryMark < 0) {
            return path;
        }
        const Url& url = Url::Parser::parseUrl(path);
        const std::string queriesStr = path->substr(queryMark + 9);
        return url.path + "?" + queriesStr;
    }

    BiliApiExecutor::BiliApiExecutor(const std::string& baseUrl, const bool& useHttps, const std::shared_ptr<RetryPolicy>& retryPolicy) : RequestExecutor(retryPolicy) {
        const auto address = Address(baseUrl, 443);
        std::shared_ptr<ClientConnectionProvider> connectionProvider = nullptr;
        if (useHttps) {
            const std::shared_ptr<oatpp::openssl::Config> config = oatpp::openssl::Config::createDefaultClientConfigShared();
            connectionProvider = oatpp::openssl::client::ConnectionProvider::createShared(config, address);
        } else {
            connectionProvider = tcp::client::ConnectionProvider::createShared(address);
        }
        _inner = HttpRequestExecutor::createShared(connectionProvider);
    }

    std::shared_ptr<RequestExecutor::ConnectionHandle> BiliApiExecutor::getConnection() {
        return _inner->getConnection();
    }

    oatpp::async::CoroutineStarterForResult<const std::shared_ptr<RequestExecutor::ConnectionHandle> &> BiliApiExecutor::getConnectionAsync() {
        return _inner->getConnectionAsync();
    }

    void BiliApiExecutor::invalidateConnection(const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        _inner->invalidateConnection(connectionHandle);
    }

    std::shared_ptr<RequestExecutor::Response>
    BiliApiExecutor::executeOnce(const String &method, const String &path, const Headers &headers, const std::shared_ptr<Body> &body,
        const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        return executeOnceReal(0, method, path, headers, body, connectionHandle);
    }

    oatpp::async::CoroutineStarterForResult<const std::shared_ptr<RequestExecutor::Response>&>
    BiliApiExecutor::executeOnceAsync(const String &method, const String &path, const Headers &headers,
        const std::shared_ptr<Body> &body, const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        return executeOnceAsyncReal(0, method, path, headers, body, connectionHandle);
    }
}
