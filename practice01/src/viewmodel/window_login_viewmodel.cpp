//
// Created by coder on 12/5/25.
//

#include "viewmodel/window_login_viewmodel.h"

#ifdef Q_OS_MACOS
#include <unistd.h>
#endif

#include "core/api/bili_sign_object.h"

using namespace biliqt::core::api::client;
using namespace biliqt::model::dto;
using namespace biliqt::core::api;
using namespace biliqt::model;

namespace biliqt::viewmodel {

    LoginWindowViewModel::LoginWindowViewModel(QObject *parent) : ViewModel(parent) {
        userModel = std::make_shared<UserModel>(parent);
    }

    void LoginWindowViewModel::onLoginQrcode(const QVariantMap& args) {
        try {
            setQrcodeState(QrcodeState::Loading, "", "", "");
            const auto& state = userModel->getQrcode();
            setQrcodeState(state->state, state->url, state->authCode, state->message);
            startTask([this] {
                sleep(5);
                startQrcodeCheck();
            });
        } catch (std::runtime_error& e) {
            setQrcodeState(QrcodeState::Error, "", "", e.what());
        }
    }

    void LoginWindowViewModel::startQrcodeCheck() {
        if (qrcodeState() != QrcodeState::Waiting && qrcodeState() != QrcodeState::Scanned && qrcodeState() != QrcodeState::Loaded) {
            return;
        }
        startTask([this] {
            try {
                const auto& state = userModel->checkQrcode(qrcodeKey);
                setQrcodeState(state->state, state->url, state->authCode, state->message);
                sleep(2);
                startQrcodeCheck();
            } catch (std::runtime_error& e) {
                setQrcodeState(QrcodeState::Error, "", "", e.what());
            }
        });
    }

    void LoginWindowViewModel::setQrcodeState(
        const QrcodeState &state, const std::string &url, const std::string &authCode, const std::string &message
    ) {
        OATPP_LOGd("SearchPageViewModel::onLoadSearchResult", "setQrcodeState: {}, message: {}", static_cast<int>(state), message);
        switch (state) {
            case QrcodeState::Loading:
                qrcodeUrl(nullptr);
                qrcodeKey = "";
                ui_statusMode(0x0000);
                ui_loadingText(qtTrId("login_qrcode_loading"));
                break;
            case QrcodeState::Loaded:
                qrcodeUrl(url.data());
                qrcodeKey = authCode;
                ui_statusMode(0x0004);
                break;
            case QrcodeState::Waiting:
                ui_statusMode(0x0004);
                break;
            case QrcodeState::Success:
                ui_statusMode(0x0000);
                ui_loadingText(qtTrId("login_qrcode_doing"));
                emit closeWindowSignal();
                break;
            case QrcodeState::Error:
                ui_statusMode(0x0002);
                ui_errorText(qtTrId("login_qrcode_error").arg(message.data()));
                break;
            case QrcodeState::Scanned:
                ui_statusMode(0x0000);
                ui_loadingText(qtTrId("login_qrcode_confirm"));
                break;
            case QrcodeState::Expired:
                ui_statusMode(0x0002);
                ui_errorText(qtTrId("login_qrcode_expire"));
                break;
        }
        qrcodeState(state);
    }

}
