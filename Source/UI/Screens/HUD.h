#pragma once

#include <string>

#include "UIScreen.h"
#include "../ShadowCatHP.h"
#include "../SkillBar.h"
#include "../../SceneManager.h"

class HUD : public UIScreen
{
public:
    HUD(UIElement& parent, const std::string& fontName);

    void Update(float deltaTime) override;

private:
    void OnSceneChanged(GameScene scene);
    void OnPauseChanged(bool isPaused);

    UIText* mEnemiesLeftCount;
    UIText* mAreaClearTxt;

    UIImage* mCursorImage;
    ShadowCatHP* mShadowCatHP = nullptr;
    SkillBar* mSkillBar = nullptr;
};
