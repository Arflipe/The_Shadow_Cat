#pragma once

#include "UIScreen.h"
#include "../../SceneManager.h"

class MainMenu : public UIScreen
{
public:
    MainMenu(UIElement& parent, const std::string& fontName);

    void OnActiveKeyPress(int key) override;
    void OnSceneChanged(GameScene scene);
};