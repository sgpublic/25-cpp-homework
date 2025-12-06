//
// Created by coder on 12/5/25.
//
#pragma once

#include "base_viewmodel.h"
#include "core/api/client/passport_api.h"
#include "core/api/dto/passport_dto.h"
#include "utils/stdafx.h"

namespace biliqt::model {

    class LoginWindowViewModel: public ViewModel {
        Q_OBJECT
    public:
        enum QrcodeState {
            Loading, // 加载二维码
            Waiting, // 等待扫描
            Success, // 扫描成功
            Error, // 出错
            Scanned, // 已扫描，等待确认
            Expired, // 已过期
        };
        Q_ENUM(QrcodeState)
        Q_PROPERTY_READONLY_AUTO(QrcodeState, qrcodeState) = Loading;
        Q_PROPERTY_READONLY_AUTO(QString, qrcodeUrl);
        Q_PROPERTY_READONLY_AUTO(QString, qrcodeKey);
        Q_PROPERTY_READONLY_AUTO(int, ui_statusMode) = 0;
        Q_PROPERTY_READONLY_AUTO(QString, ui_loadingText);
        Q_PROPERTY_READONLY_AUTO(QString, ui_errorText);
    signals:
        void closeWindowSignal();
    private:
        std::shared_ptr<core::api::client::PassportApi> _loginApi;

    public:
        explicit LoginWindowViewModel(QObject *parent = nullptr);

        VIEW_MODEL_COROUTINE_TASK(LoginQrcode)
    private:

        void startQrcodeCheck();
        void doLoginPostWork(const oatpp::Object<core::api::dto::LoginQrcodeTvPollResp::Data>& data);
        void setQrcodeState(const QrcodeState& state, const std::string& url, const std::string& authCode, const std::string& message);
    };

}
