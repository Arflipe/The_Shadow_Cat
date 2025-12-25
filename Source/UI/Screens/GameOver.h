#pragma once

#include "UIScreen.h"

class GameOver : public UIScreen
{
public:
    GameOver(UIElement& parent, const std::string& fontName);

    void OnActiveKeyPress(int key) override;

private:
    void OnGameOver();

    void UpdateSelectedButton();

    UIText* mGameOverText = nullptr;
    UIImage* mBackgroundImage = nullptr;
    UIButton* mTryAgainButton = nullptr;
    UIButton* mBackToMenuButton = nullptr;
    UIButton* mExitButton = nullptr;
};