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

    void LoginWindowViewModel::getLoginQrcode() {
        qrcodeState(Loading);
        auto dto = LoginQrcodeTvReq::createShared();
        auto result = _loginApi->qrcodeTv(dto->signedBody());
        auto body = readRespBody<LoginQrcodeTvResp>(result);
        qrcodeUrl(body->data->url->data());
        qrcodeKey(body->data->authCode->data());
        qrcodeState(Waiting);
    }

    void LoginWindowViewModel::onClear() {

    }

}
