#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>
using namespace geode::prelude;

bool bro = true;

class $modify(PlayerObject) {
    void flipGravity(bool upsideDown, bool ringEffect) {
        if (Mod::get()->getSettingValue<bool>("enabled")) {
            if (auto pl = PlayLayer::get()) {
                int modulo = std::abs(as<int>(std::round(pl->m_gameState.m_cameraAngle)) % 360);
                int nearAngle = modulo <= 90 || modulo > 270 ? 0 : 180;
                bool screenFlipped = nearAngle == 180;

                if (
                    this->m_isUpsideDown != upsideDown
                    && (screenFlipped != upsideDown || bro)
                    && (Mod::get()->getSettingValue<bool>("also-p2") ? this == pl->m_player1 || this == pl->m_player2 : this == pl->m_player1)
                ) {
                    // as<GJBaseGameLayer*>(pl)->updateScreenRotation(-180, true, false, Mod::get()->getSettingValue<double>("rotate-time"), 0, 0, -1, -1);
                    as<GJBaseGameLayer*>(pl)->updateScreenRotation(-180, true, false, 0.2, 0, 0, -1, -1);
                    if (Mod::get()->getSettingValue<bool>("also-mirror")) {
                        pl->toggleFlipped(!screenFlipped, false);
                    }
                }
            }
        }

        PlayerObject::flipGravity(upsideDown, ringEffect);
    }
};

class $modify(PlayLayer) {
    void resetLevel() {
        bro = false;
        PlayLayer::resetLevel();
        bro = true;
    }
};