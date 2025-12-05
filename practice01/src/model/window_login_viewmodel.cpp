//
// Created by coder on 12/5/25.
//

#include "model/window_login_viewmodel.h"
#include "core/api/dto/passport_dto.h"
#include "core/api/bili_sign_object.h"

using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api;

namespace biliqt::model {

    LoginWindowViewModel::LoginWindowViewModel(QObject *parent) : ViewModel(parent), _qrcodeState(Loading) {
        _loginApi = PassportApi::createShared();
    }

    void LoginWindowViewModel::requestLoginQrcode() {
        try {
            qrcodeState(Loading);
            auto dto = LoginQrcodeTvReq::createShared();
            auto result = _loginApi->qrcodeTv(dto->asSignedBody());
            auto body = readRespBody<LoginQrcodeTvResp>(result);
            if (body->code != 200) {
                errorMessage(body->message->data());
                qrcodeState(Error);
            } else {
                qrcodeUrl(body->data->url->data());
                qrcodeKey(body->data->authCode->data());
                qrcodeState(Waiting);
            }
        } catch (std::runtime_error e) {
            errorMessage(e.what());
            qrcodeState(Error);
        }
        qDebug() << "LoginWindowViewModel::requestLoginQrcode, error: " << _errorMessage;
    }

    void LoginWindowViewModel::onClear() {

    }

}
