#include "GameOver.h"
#include "../../Game.h"


GameOver::GameOver(UIElement& parent, const std::string& fontName)
    :UIScreen(parent, fontName)
{
    mBackgroundImage = new UIImage(*this, Vector2::Zero, 1.0f, 0.0f);
    mGameOverText = new UIText(*mBackgroundImage, "GAME OVER :(", mFont, Vector2(0.0f, -150.0f), 2.0f, 0.0f);
    mTryAgainButton = new UIButton(*mBackgroundImage, "TRY AGAIN",
        []() { Game::Instance().ResetGame(); }, mFont,
        Vector2(0.0f, +100.0f), 0.7f);
    mBackToMenuButton = new UIButton(*mBackgroundImage, "BACK TO MENU",
        []() { Game::Instance().BackToMenu(); }, mFont,
        Vector2(0.0f, +170.0f), 0.7f);
    mExitButton = new UIButton(*mBackgroundImage, "EXIT",
        []() { Game::Instance().Quit(); }, mFont,
        Vector2(0.0f, +240.0f), 0.7f);

    mButtons.push_back(mTryAgainButton);
    mButtons.push_back(mBackToMenuButton);
    mButtons.push_back(mExitButton);

    Game::Instance().OnGameOver.Subscribe([this]() { OnGameOver(); });
}

void GameOver::OnActiveKeyPress(int key)
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

void GameOver::OnGameOver()
{
    switch (SceneManager::Instance().GetCurrentScene())
    {
    case GameScene::Level1_Boss:
        mBackgroundImage->SetImage("../Assets/HUD/Background/DefeatBackground1.png");
        break;
    case GameScene::Level2_Boss:
        mBackgroundImage->SetImage("../Assets/HUD/Background/DefeatBackground3.png");
        break;
    case GameScene::Level3_Boss:
        mBackgroundImage->SetImage("../Assets/HUD/Background/DefeatBackground2.png");
        break;
    default:
        mBackgroundImage->SetImage("../Assets/HUD/Background/DefeatBackground4.png");
        break;
    }
    SetIsVisible(true);
    mSelectedButtonIndex = 0;
    UpdateSelectedButton();
}

void GameOver::UpdateSelectedButton()
{
    for (auto button : mButtons)
        button->SetHighlighted(false);
    mButtons[mSelectedButtonIndex]->SetHighlighted(true);
}