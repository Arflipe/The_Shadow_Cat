#pragma once

#include "UIScreen.h"

class GameOver : public UIScreen
{
public:
    GameOver(UIElement& parent, const std::string& fontName);

    void OnActiveKeyPress(int key) override;
};