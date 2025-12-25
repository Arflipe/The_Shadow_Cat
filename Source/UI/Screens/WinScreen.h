#pragma once

#include "UIScreen.h"

class WinScreen : public UIScreen
{
public:
    WinScreen(UIElement& parent, const std::string& fontName);

    void OnActiveKeyPress(int key) override;

private:
    void OnGameWon();

    void UpdateSelectedButton();

    UIText* mWinText = nullptr;
    UIImage* mBackgroundImage = nullptr;
    UIButton* mBackToMenuButton = nullptr;
    UIButton* mExitButton = nullptr;
};