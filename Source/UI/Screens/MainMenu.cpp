#include "MainMenu.h"

#include "../AbilityCard.h"
#include "../../Game.h"
#include "../../GameConstants.h"
#include "../../SceneManager.h"

MainMenu::MainMenu(UIElement& parent, const std::string& fontName)
    :UIScreen(parent, fontName)
{
    const float SCALE = 0.7f;

    auto scroll = new UIImage(*this, "../Assets/HUD/Menu/Scroll2.png", Vector2(0.0f, 0.0f), 3.0f, 0.0f);

    auto titleTextShadow = new UIText(*this, "The Shadow Cat", mFont, Vector2(3.0f, -237.0f), Vector3(0.9f, 0.0f, 0.9f), Vector4::Zero, 1.2f, 0.0f, 60);
    auto titleText = new UIText(*titleTextShadow, "The Shadow Cat", mFont, Vector2(-3.0f, -3.0f), Vector3::Zero, Vector4::Zero, 1.2f, 0.0f, 60);

    // Drop shadow on text
    float wrapLength = 185.0f;
    auto newAdventureTextShadow = new UIText(*scroll, "    New\nAdventure", mFont, Vector2(3.0f, -7.0f), Vector3(0.6f), Vector4::Zero, SCALE, 0.0f, 40, wrapLength);
    auto quitTextShadow = new UIText(*scroll, "Quit", mFont, Vector2(3.0f, 12.0f), Vector3(0.6f), Vector4::Zero, SCALE);

    auto newAdventureButton = new UIButton(*newAdventureTextShadow, "    New\nAdventure",
        []() { SceneManager::Instance().SetScene(GameConstants::DEFAULT_STARTING_SCENE); },
        mFont, Vector2(-3.0f, -3.0f), SCALE, 0.0f, 40, wrapLength);

    auto quitButton = new UIButton(*quitTextShadow, "Quit",
        [this]() { Game::Instance().Quit(); },
        mFont, Vector2(-3.0f, -3.0f), SCALE);

    mButtons.push_back(newAdventureButton);
    mButtons.push_back(quitButton);

    mSelectedButtonIndex = 0;
    mButtons[0]->SetHighlighted(true); // new game

    // Customize buttons
    for (auto button : mButtons) {
        button->SetTextColor(Vector3::One);
        button->SetTextHighlightColor(Vector3(0.9f, 0.0f, 0.9f)); // violet
        button->SetBackgroundColor(Vector4::Zero); // transparent
    }
    
    auto versionText = "Version " + std::to_string(GameConstants::VERSION_MAJOR) + "." +
        std::to_string(GameConstants::VERSION_MINOR) + "." +
        std::to_string(GameConstants::VERSION_PATCH);
    new UIText(*this, versionText, mFont, Vector2(540.0f, 328.0f), Vector3(0.8f), Vector4::Zero, 0.7f);

    SceneManager::Instance().OnSceneChanged.Subscribe([this](GameScene scene) { OnSceneChanged(scene); });
}

void MainMenu::OnActiveKeyPress(int key)
{
    if (mButtons.empty())
        return;

    switch (key) {
    case SDLK_w:
    case SDLK_UP:
        if (mSelectedButtonIndex == 0) break;

        mButtons[mSelectedButtonIndex]->SetHighlighted(false);
        mSelectedButtonIndex--;
        mButtons[mSelectedButtonIndex]->SetHighlighted(true);
        break;
    
    case SDLK_s:
    case SDLK_DOWN:
        if (mSelectedButtonIndex == (int) mButtons.size() - 1) break;

        mButtons[mSelectedButtonIndex]->SetHighlighted(false);
        mSelectedButtonIndex++;
        mButtons[mSelectedButtonIndex]->SetHighlighted(true);
        break;
    
    case SDLK_e:
    case SDLK_RETURN:
    case SDLK_KP_ENTER:
        mButtons[mSelectedButtonIndex]->OnClick();
        break;

    default:
        break;
    }
}

void MainMenu::OnSceneChanged(GameScene scene)
{
    SetIsVisible(scene == GameScene::MainMenu);
}