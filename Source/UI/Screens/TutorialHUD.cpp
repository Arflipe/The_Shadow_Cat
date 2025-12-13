#include "TutorialHUD.h"
#include "../../Game.h"
#include "../../SceneManager.h"
#include <string>

TutorialHUD::TutorialHUD(UIElement& parent, const std::string& fontName)
    : UIScreen(parent, fontName)
{
    auto scroll = new UIImage(*this, "../Assets/HUD/Menu/Scroll1.png", Vector2(0.0f, -178.0f), 13.0f, 0.0f);

    // WASD
    new UIImage(*scroll, "../Assets/HUD/Menu/KeyboardW.png", Vector2(-220.0f, -240.0f), 0.8f, 0.0f);
    new UIImage(*scroll, "../Assets/HUD/Menu/KeyboardA.png", Vector2(-195.0f, -240.0f), 0.8f, 0.0f);
    new UIImage(*scroll, "../Assets/HUD/Menu/KeyboardS.png", Vector2(-170.0f, -240.0f), 0.8f, 0.0f);
    new UIImage(*scroll, "../Assets/HUD/Menu/KeyboardD.png", Vector2(-145.0f, -240.0f), 0.8f, 0.0f);

    // Skills
    new UIImage(*scroll, "../Assets/HUD/Menu/KeyboardLMB.png", Vector2(-220.0f, -200.0f), 0.8f, 0.0f);
    new UIImage(*scroll, "../Assets/HUD/Menu/KeyboardRMB.png", Vector2(-100.0f, -200.0f), 0.8f, 0.0f);
    new UIImage(*scroll, "../Assets/HUD/Menu/KeyboardQ.png", Vector2(40.0f, -240.0f), 0.8f, 0.0f);
    new UIImage(*scroll, "../Assets/HUD/Menu/KeyboardE.png", Vector2(40.0f, -215.0f), 0.8f, 0.0f);
    new UIImage(*scroll, "../Assets/HUD/Menu/KeyboardSHIFT.png", Vector2(40.0f, -190.0f), 1.0f, 0.0f);

    // Mouse aim
    new UIImage(*scroll, "../Assets/Icons/Cursor.png", Vector2(255.0f, -240.0f), 0.6f, 0.0f);
    new UIImage(*scroll, "../Assets/Icons/Cursor.png", Vector2(255.0f, -215.0f), 0.6f, 0.0f);
    new UIImage(*scroll, "../Assets/Icons/Cursor.png", Vector2(255.0f, -190.0f), 0.6f, 0.0f);

    // Text labels
    new UIText(*scroll, "Move", mFont, Vector2(-110.0f, -240.0f), Vector3::Zero, Vector4::Zero, 0.4f);
    new UIText(*scroll, "Basic Attack", mFont, Vector2(-165.0f, -200.0f), Vector3::Zero, Vector4::Zero, 0.4f);
    new UIText(*scroll, "Claw Attack", mFont, Vector2(-45.0f, -200.0f), Vector3::Zero, Vector4::Zero, 0.4f);
    new UIText(*scroll, "Stomp - Aim with mouse", mFont, Vector2(150.0f, -240.0f), Vector3::Zero, Vector4::Zero, 0.4f);
    new UIText(*scroll, "Furball - Aim with mouse", mFont, Vector2(150.0f, -215.0f), Vector3::Zero, Vector4::Zero, 0.4f);
    new UIText(*scroll, "Dash - Aim with mouse", mFont, Vector2(150.0f, -190.0f), Vector3::Zero, Vector4::Zero, 0.4f);

    // Toggle visibility instruction
    new UIImage(*scroll, "../Assets/HUD/Menu/KeyboardH.png", Vector2(-110.0f, -165.0f), 0.8f, 0.0f);
    new UIText(*scroll, "Hide/Show controls guide", mFont, Vector2(0.0f, -165.0f), Vector3::Zero, Vector4::Zero, 0.4f);

    SceneManager::Instance().OnSceneChanged.Subscribe([this](GameScene scene) {
        OnSceneChanged(scene);
    });
}

void TutorialHUD::OnKeyPress(int key)
{
    if (key != SDLK_h) return;

    SetIsVisible(!IsVisible());
}

void TutorialHUD::OnSceneChanged(GameScene newScene)
{
    SetIsVisible(newScene == GameScene::Lobby);
}