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
            const auto dto = LoginQrcodeTvReq::createShared();
            const auto result = _loginApi->qrcodeTv(dto->asSignedBody());
            if (result->getStatusCode() != 200) {
                errorMessage(result->getStatusDescription()->data());
                qrcodeState(Error);
                qDebug() << "LoginWindowViewModel::requestLoginQrcode, code:" << result->getStatusCode() << "error:" << _errorMessage;
                return;
            }
            auto body = readRespBody<LoginQrcodeTvResp>(result);
            if (body->code != 0) {
                errorMessage(body->message->data());
                qrcodeState(Error);
                qDebug() << "LoginWindowViewModel::requestLoginQrcode, errorMessage: " << _errorMessage;
                return;
            }
            qrcodeUrl(body->data->url->data());
            qrcodeKey(body->data->auth_code->data());
            qrcodeState(Waiting);
            qDebug() << "LoginWindowViewModel::requestLoginQrcode, url: " << _qrcodeUrl;
        } catch (std::runtime_error& e) {
            errorMessage(e.what());
            qrcodeState(Error);
            qDebug() << "LoginWindowViewModel::requestLoginQrcode, catched error: " << _errorMessage;
        }
    }

    void LoginWindowViewModel::onClear() {

    }

}
