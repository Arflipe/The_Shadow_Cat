#pragma once

#include "UIScreen.h"

class WinScreen : public UIScreen
{
public:
    WinScreen(UIElement& parent, const std::string& fontName);

    void OnActiveKeyPress(int key) override;
};