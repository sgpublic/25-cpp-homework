//
// Created by coder on 12/5/25.
//
#pragma once

#include "base_viewmodel.h"
#include "core/api/client/passport_api.h"
#include "utils/stdafx.h"

namespace biliqt::model {

    class LoginWindowViewModel: public ViewModel {
    private:
        std::shared_ptr<core::api::client::PassportApi> _loginApi;

    public:
        explicit LoginWindowViewModel(QObject *parent = nullptr);
        void onClear() override;

        enum QrcodeState {
            Loading, // 加载二维码
            Waiting, // 等待扫描
            Success, // 扫描成功
            Error, // 出错
            Scanned, // 已扫描，等待确认
            Expired, // 已过期
        };
        Q_PROPERTY_READONLY_AUTO(QrcodeState, qrcodeState);
        Q_PROPERTY_READONLY_AUTO(QString, qrcodeUrl);
        Q_PROPERTY_READONLY_AUTO(QString, qrcodeKey);
        Q_PROPERTY_READONLY_AUTO(QString, errorMessage);

        Q_INVOKABLE void getLoginQrcode();
    };

}
