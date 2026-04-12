#include "TutorialHUD.h"
#include "../../Game.h"
#include "../../SceneManager.h"
#include <string>

TutorialHUD::TutorialHUD(UIElement& parent, const std::string& fontName)
    : UIScreen(parent, fontName)
{
    auto scroll = new UIImage(*this, "../Assets/HUD/Menu/Scroll1.png", Vector2(0.0f, -178.0f), 13.0f, 0.0f);
    auto controlsBox = new UIElement(*scroll);

    // WASD
    new UIImage(*controlsBox, "../Assets/HUD/Menu/KeyboardW.png", Vector2(-220.0f, -62.0f), 0.8f, 0.0f);
    new UIImage(*controlsBox, "../Assets/HUD/Menu/KeyboardA.png", Vector2(-195.0f, -62.0f), 0.8f, 0.0f);
    new UIImage(*controlsBox, "../Assets/HUD/Menu/KeyboardS.png", Vector2(-170.0f, -62.0f), 0.8f, 0.0f);
    new UIImage(*controlsBox, "../Assets/HUD/Menu/KeyboardD.png", Vector2(-145.0f, -62.0f), 0.8f, 0.0f);

    // Skills
    new UIImage(*controlsBox, "../Assets/HUD/Menu/KeyboardLMB.png", Vector2(-220.0f, -22.0f), 0.8f, 0.0f);
    new UIImage(*controlsBox, "../Assets/HUD/Menu/KeyboardRMB.png", Vector2(-100.0f, -22.0f), 0.8f, 0.0f);
    new UIImage(*controlsBox, "../Assets/HUD/Menu/KeyboardQ.png", Vector2(40.0f, -62.0f), 0.8f, 0.0f);
    new UIImage(*controlsBox, "../Assets/HUD/Menu/KeyboardE.png", Vector2(40.0f, -37.0f), 0.8f, 0.0f);
    new UIImage(*controlsBox, "../Assets/HUD/Menu/KeyboardSHIFT.png", Vector2(40.0f, -12.0f), 1.0f, 0.0f);
    // Mouse aim
    new UIImage(*controlsBox, "../Assets/Icons/Cursor.png", Vector2(255.0f, -62.0f), 0.6f, 0.0f);
    new UIImage(*controlsBox, "../Assets/Icons/Cursor.png", Vector2(255.0f, -37.0f), 0.6f, 0.0f);
    new UIImage(*controlsBox, "../Assets/Icons/Cursor.png", Vector2(255.0f, -12.0f), 0.6f, 0.0f);

    // Text labels
    new UIText(*controlsBox, "Move", mFont, Vector2(-110.0f, -62.0f), Vector3::Zero, Vector4::Zero, 0.4f);
    new UIText(*controlsBox, "Basic Attack", mFont, Vector2(-165.0f, -22.0f), Vector3::Zero, Vector4::Zero, 0.4f);
    new UIText(*controlsBox, "Claw Attack", mFont, Vector2(-45.0f, -22.0f), Vector3::Zero, Vector4::Zero, 0.4f);
    new UIText(*controlsBox, "Stomp - Aim with mouse", mFont, Vector2(150.0f, -62.0f), Vector3::Zero, Vector4::Zero, 0.4f);
    new UIText(*controlsBox, "Furball - Aim with mouse", mFont, Vector2(150.0f, -37.0f), Vector3::Zero, Vector4::Zero, 0.4f);
    new UIText(*controlsBox, "Dash - Aim with mouse", mFont, Vector2(150.0f, -12.0f), Vector3::Zero, Vector4::Zero, 0.4f);

    // Toggle visibility instruction
    new UIImage(*controlsBox, "../Assets/HUD/Menu/KeyboardH.png", Vector2(-110.0f, 13.0f), 0.8f, 0.0f);
    new UIText(*controlsBox, "Hide/Show controls guide", mFont, Vector2(0.0f, 13.0f), Vector3::Zero, Vector4::Zero, 0.4f);

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