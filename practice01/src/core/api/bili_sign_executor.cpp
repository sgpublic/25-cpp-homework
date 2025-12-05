//
// Created by coder on 12/5/25.
//

#include <oatpp/network/Address.hpp>
#include <oatpp/network/tcp/client/ConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp-openssl/client/ConnectionProvider.hpp>

#include "core/api/bili_sign_executor.h"

#include <QDebug>

using namespace oatpp::parser::json::mapping;
using namespace oatpp::web::client;

namespace biliqt::core::api {
    BiliApiExecutor::BiliApiExecutor(const std::string& baseUrl, const bool& useHttps, const std::shared_ptr<RetryPolicy>& retryPolicy) : RequestExecutor(retryPolicy) {
        auto jsonObjectMapper = ObjectMapper::createShared();
        auto address = oatpp::network::Address(baseUrl, 443);
        std::shared_ptr<oatpp::network::ClientConnectionProvider> connectionProvider = nullptr;
        if (useHttps) {
            const std::shared_ptr<oatpp::openssl::Config> config = oatpp::openssl::Config::createDefaultClientConfigShared();
            connectionProvider = oatpp::openssl::client::ConnectionProvider::createShared(config, address);
        } else {
            connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared(address);
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

    std::shared_ptr<RequestExecutor::Response> BiliApiExecutor::executeOnceReal(const int &redirectTime,
        const String &method, const String &path, const Headers &headers, const std::shared_ptr<Body> &body,
        const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        if (redirectTime >= 10) {
            throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_429, "Too Many Requests");
        }

        std::shared_ptr<Response> resp = _inner->executeOnce(method, path, headers, body, connectionHandle);
        // const int status = resp->getStatusCode();
        // if (status != 301 && status != 302 && status != 307) {
            return resp;
        // }
        // const std::string location = resp->getHeader("Location");
        // if (status == 307) {
        //     return executeOnceReal(redirectTime + 1, method, location, headers, body, connectionHandle);
        // }
        // return executeOnceReal(redirectTime + 1, "GET", location, headers, body, connectionHandle);
    }

    oatpp::async::CoroutineStarterForResult<const std::shared_ptr<RequestExecutor::Response>&>
    BiliApiExecutor::executeOnceAsync(const String &method, const String &path, const Headers &headers,
        const std::shared_ptr<Body> &body, const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        auto resp = _inner->executeOnceAsync(method, path, headers, body, connectionHandle);
        return resp;
    }

    oatpp::async::CoroutineStarterForResult<const std::shared_ptr<RequestExecutor::Response> &>
    BiliApiExecutor::executeOnceAsyncReal(const int &redirectTime, const String &method, const String &path, const Headers &headers,
        const std::shared_ptr<Body> &body, const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        oatpp::async::CoroutineStarterForResult<const std::shared_ptr<Response>&> resp = _inner->executeAsync(method, path, headers, body, connectionHandle);
        return resp;
    }
}
