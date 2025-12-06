//
// Created by coder on 12/5/25.
//

#pragma once
#include <oatpp/web/client/HttpRequestExecutor.hpp>
#include <oatpp/web/client/RequestExecutor.hpp>

namespace biliqt::core::api {
    class BiliApiExecutor: public oatpp::web::client::RequestExecutor {
    private:
        std::shared_ptr<oatpp::web::client::HttpRequestExecutor> _inner;
    public:
        BiliApiExecutor(const std::string& baseUrl, const bool& useHttps, const std::shared_ptr<oatpp::web::client::RetryPolicy>& retryPolicy = nullptr);

        std::shared_ptr<ConnectionHandle> getConnection() override;

        oatpp::async::CoroutineStarterForResult<const std::shared_ptr<ConnectionHandle> &>
        getConnectionAsync() override;

        void invalidateConnection(const std::shared_ptr<ConnectionHandle> &connectionHandle) override;

        std::shared_ptr<Response> executeOnce(const String &method, const String &path, const Headers &headers,
            const std::shared_ptr<Body> &body, const std::shared_ptr<ConnectionHandle> &connectionHandle) override;

        std::shared_ptr<Response> executeOnceReal(const int& redirectTime, const String &method, const String &path, const Headers &headers,
            const std::shared_ptr<Body> &body, const std::shared_ptr<ConnectionHandle> &connectionHandle);

        oatpp::async::CoroutineStarterForResult<const std::shared_ptr<Response> &> executeOnceAsync(
            const String &method, const String &path, const Headers &headers, const std::shared_ptr<Body> &body,
            const std::shared_ptr<ConnectionHandle> &connectionHandle) override;

        oatpp::async::CoroutineStarterForResult<const std::shared_ptr<Response> &> executeOnceAsyncReal(
            const int& redirectTime, const String &method, const String &path, const Headers &headers, const std::shared_ptr<Body> &body,
            const std::shared_ptr<ConnectionHandle> &connectionHandle);

    private:
        void printRequestDetails(const String &method, const String &path, const Headers &headers);
    };
}
