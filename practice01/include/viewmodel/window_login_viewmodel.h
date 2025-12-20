//
// Created by coder on 12/5/25.
//
#pragma once

#include "base_viewmodel.h"
#include "model/user_model.h"
#include "utils/stdafx.h"

namespace biliqt::viewmodel {

    class LoginWindowViewModel: public ViewModel {
        Q_OBJECT
    public:
        Q_PROPERTY_READONLY_AUTO(biliqt::model::dto::QrcodeState, qrcodeState) = model::dto::QrcodeState::Loading;
        Q_PROPERTY_READONLY_AUTO(QString, qrcodeUrl);
        Q_PROPERTY_READONLY_AUTO(int, ui_statusMode) = 0;
        Q_PROPERTY_READONLY_AUTO(QString, ui_loadingText);
        Q_PROPERTY_READONLY_AUTO(QString, ui_errorText);
    private:
        std::string qrcodeKey = "";
    signals:
        void closeWindowSignal();
    private:
        std::shared_ptr<model::UserModel> userModel;

    public:
        explicit LoginWindowViewModel(QObject *parent = nullptr);

        VIEW_MODEL_COROUTINE_TASK(LoginQrcode)
    private:
        void startQrcodeCheck();
        void doLoginPostWork(const oatpp::Object<core::api::dto::LoginQrcodeTvPollResp::Data>& data);
        void setQrcodeState(const model::dto::QrcodeState& state, const std::string& url, const std::string& authCode, const std::string& message);
    };

}
