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

    std::shared_ptr<RequestExecutor::Response> BiliApiExecutor::executeOnceReal(const int &redirectTime,
        const String &method, const String &path, const Headers &headers, const std::shared_ptr<Body> &body,
        const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        printRequestDetails(method, path, headers);
        std::shared_ptr<Response> resp = _inner->executeOnce(method, path, headers, body, connectionHandle);
        return resp;
    }

    oatpp::async::CoroutineStarterForResult<const std::shared_ptr<RequestExecutor::Response> &>
    BiliApiExecutor::executeOnceAsyncReal(const int &redirectTime, const String &method, const String &path, const Headers &headers,
        const std::shared_ptr<Body> &body, const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        printRequestDetails(method, path, headers);
        oatpp::async::CoroutineStarterForResult<const std::shared_ptr<Response>&> resp = _inner->executeAsync(method, path, headers, body, connectionHandle);
        return resp;
    }

    void BiliApiExecutor::printRequestDetails(const String &method, const String &path, const Headers &headers) {
        OATPP_LOGI("BiliApiExecutor", "- %s %s", method->c_str(), path->c_str());
        for (const auto&[key, value] : headers.getAll()) {
            OATPP_LOGI("BiliApiExecutor", "  %s: %s", key.std_str().c_str(), value.std_str().c_str());
        }
    }

    BiliApiExecutor::BiliApiExecutor(const std::string& baseUrl, const bool& useHttps, const std::shared_ptr<RetryPolicy>& retryPolicy) : RequestExecutor(retryPolicy) {
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

    oatpp::async::CoroutineStarterForResult<const std::shared_ptr<RequestExecutor::Response>&>
    BiliApiExecutor::executeOnceAsync(const String &method, const String &path, const Headers &headers,
        const std::shared_ptr<Body> &body, const std::shared_ptr<ConnectionHandle> &connectionHandle) {
        return executeOnceAsyncReal(0, method, path, headers, body, connectionHandle);
    }
}
