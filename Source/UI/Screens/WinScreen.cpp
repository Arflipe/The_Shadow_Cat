#include "WinScreen.h"
#include "../../Game.h"

WinScreen::WinScreen(UIElement& parent, const std::string& fontName)
    :UIScreen(parent, fontName)
{
    mBackgroundImage = new UIImage(*this, "../Assets/HUD/Background/WinBackground.png", Vector2::Zero, 1.0f, 0.0f);
    mWinText = new UIText(*mBackgroundImage, "YOU WIN!", mFont, Vector2(0.0f, -150.0f), 2.0f, 0.0f);
    mBackToMenuButton = new UIButton(*mBackgroundImage, "BACK TO MENU",
        []() { Game::Instance().BackToMenu(); }, mFont,
        Vector2(0.0f, +100.0f), 0.7f);
    mExitButton = new UIButton(*mBackgroundImage, "EXIT",
        []() { Game::Instance().Quit(); }, mFont,
        Vector2(0.0f, +170.0f), 0.7f);

    mButtons.push_back(mBackToMenuButton);
    mButtons.push_back(mExitButton);

    Game::Instance().OnGameWon.Subscribe([this]() { OnGameWon(); });
}


void WinScreen::OnActiveKeyPress(int key)
{
    if (mButtons.empty())
        return;

    switch (key) {
    case SDLK_w:
    case SDLK_UP:
        mSelectedButtonIndex--;
        if (mSelectedButtonIndex < 0)
            mSelectedButtonIndex = (int)mButtons.size() - 1;
        break;
    case SDLK_s:
    case SDLK_DOWN:
        mSelectedButtonIndex++;
        if (mSelectedButtonIndex >= (int)mButtons.size())
            mSelectedButtonIndex = 0;
        break;
    case SDLK_RETURN:
    case SDLK_KP_ENTER:
        mButtons[mSelectedButtonIndex]->OnClick();
        SetIsVisible(false);
        return;

    default:
        break;
    }

    UpdateSelectedButton();
}

void WinScreen::OnGameWon()
{
    SetIsVisible(true);
    mSelectedButtonIndex = 0;
    UpdateSelectedButton();
}

void WinScreen::UpdateSelectedButton()
{
    for (auto button : mButtons)
        button->SetHighlighted(false);
    mButtons[mSelectedButtonIndex]->SetHighlighted(true);
}