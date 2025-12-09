//
// Created by coder on 12/5/25.
//

#include "model/window_login_viewmodel.h"
#include "core/api/dto/passport_dto.h"
#include "core/api/bili_sign_object.h"
#include "core/module/setting_module.h"

using namespace biliqt::core::api::client;
using namespace biliqt::core::api::dto;
using namespace biliqt::core::api;

namespace biliqt::model {

    LoginWindowViewModel::LoginWindowViewModel(QObject *parent) : ViewModel(parent) {
        _passportClient = PassportClient::createShared();
    }

    void LoginWindowViewModel::onLoginQrcode(const QVariantMap& args) {
        try {
            setQrcodeState(Loading, "", "", "");
            const auto dto = LoginQrcodeTvReq::createShared();
            const auto result = _passportClient->qrcodeTv(dto->asSignedParams());
            if (result->getStatusCode() != 200) {
                setQrcodeState(Error, "", "", result->getStatusDescription());
                return;
            }
            const auto body = readRespBody<LoginQrcodeTvResp>(result);
            if (body->code != 0) {
                setQrcodeState(Error, "", "", body->message);
                return;
            }
            setQrcodeState(Waiting, body->data->url, body->data->auth_code, "");

            startTask([this] {
                sleep(5);
                startQrcodeCheck();
            });
        } catch (std::runtime_error& e) {
            setQrcodeState(Error, "", "", e.what());
        }
    }

    void LoginWindowViewModel::startQrcodeCheck() {
        if (_qrcodeState != Waiting && _qrcodeState != Scanned) {
            return;
        }
        startTask([this] {
            const oatpp::Object<LoginQrcodeTvPollReq>& dto = LoginQrcodeTvPollReq::createShared();
            dto->auth_code = oat_str(_qrcodeKey);
            const auto result = _passportClient->qrcodeTvPoll(dto->asSignedParams());
            qDebug() << "statusCode:" << result->getStatusCode();
            if (result->getStatusCode() != 200) {
                setQrcodeState(Error, "", "", result->getStatusDescription());
                return;
            }
            const auto body = readRespBody<LoginQrcodeTvPollResp>(result);
            qDebug() << "code:" << body->code << "message:" << body->message->data();
            switch (body->code) {
                case 0:
                    setQrcodeState(Success, "", "", "");
                    doLoginPostWork(body->data);
                    break;
                case 86039:
                    break;
                case 86090:
                    setQrcodeState(Scanned, "", "", "");
                    break;
                case 86038:
                    setQrcodeState(Expired, "", "", "");
                    break;
                default:
                    setQrcodeState(Error, "", "", body->message);
                    break;
            }

            sleep(2);
            startQrcodeCheck();
        });
    }

    void LoginWindowViewModel::doLoginPostWork(const oatpp::Object<LoginQrcodeTvPollResp::Data>& data) {
        const auto& setting = core::module::SettingModule::getInstance();
        setting->accessToken(data->token_info->access_token->data());
        setting->refreshToken(data->token_info->refresh_token->data());
        const auto& cookies = data->cookie_info->cookies;
        for (const auto& cookieItem : *cookies) {
            const auto& value = cookieItem->name->data();
            if (cookieItem->name == "bili_jct") {
                setting->cookie_BiliJct(value);
            } else if (cookieItem->name == "DedeUserID") {
                setting->cookie_DedeUserID(value);
            } else if (cookieItem->name == "DedeUserID__ckMd5") {
                setting->cookie_DedeUserID__ckMd5(value);
            } else if (cookieItem->name == "sid") {
                setting->cookie_sid(value);
            } else if (cookieItem->name == "SESSDATA") {
                setting->cookie_SESSDATA(value);
            }
        }
        setting->login(true);
        emit closeWindowSignal();
    }

    void LoginWindowViewModel::setQrcodeState(
        const QrcodeState &state, const std::string &url, const std::string &authCode, const std::string &message
    ) {
        qDebug() << "setQrcodeState:" << state << ", message:" << message;
        switch (state) {
            case Loading:
                qrcodeUrl(nullptr);
                qrcodeKey(nullptr);
                ui_statusMode(0x0000);
                ui_loadingText(qtTrId("login_qrcode_loading"));
                break;
            case Waiting:
                qrcodeUrl(url.data());
                qrcodeKey(authCode.data());
                ui_statusMode(0x0004);
                break;
            case Success:
                ui_statusMode(0x0000);
                ui_loadingText(qtTrId("login_qrcode_doing"));
                break;
            case Error:
                ui_statusMode(0x0002);
                ui_errorText(qtTrId("login_qrcode_error").arg(message.data()));
                break;
            case Scanned:
                ui_statusMode(0x0000);
                ui_loadingText(qtTrId("login_qrcode_confirm"));
                break;
            case Expired:
                ui_statusMode(0x0002);
                ui_errorText(qtTrId("login_qrcode_expire"));
                break;
        }
        qrcodeState(state);
    }

}
