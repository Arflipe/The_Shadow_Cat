#include "HUD.h"
#include "../../Game.h"
#include "../../GameConstants.h"
#include "../../Actors/Characters/ShadowCat.h"
#include <string>

#include "../../LevelManager.h"

HUD::HUD(UIElement& parent, const std::string& fontName)
    : UIScreen(parent, fontName)
{   
    mShadowCatHP = new ShadowCatHP(*this, Vector2(-500.0f, 280.0f));
    mSkillBar = new SkillBar(*this, mFont, Vector2(300.0f, 300.0f), 1.0f, 0.0f);

    // Enemy counter top right
    new UIText(*this, "Enemies Left:", mFont, Vector2(500.0f, -300.0f), Vector3::One, Vector4::Zero, 0.7f, 0.0f);
    mEnemiesLeftCount = new UIText(*this, "0", mFont, Vector2(600.0f, -300.0f), Vector3::One, Vector4::Zero, 0.7f, 0.0f);
    
    mAreaClearTxt = new UIText(*this, "            Area clear!\nProceed to the red carpet!", mFont, Vector2(630.0f, -220.0f), Vector3::One, Vector4::Zero, 0.5f, 0.0f);
    mAreaClearTxt->SetIsVisible(false);
    
    for (auto &txt : mTexts) {
        txt->SetTextColor(Vector3::One); // White
        txt->SetBackgroundColor(Vector4::Zero); // Transparent
    }

    // Cursor
    mCursorImage = new UIImage(*this, "../Assets/Icons/Cursor.png", Vector2(0.0f, 0.0f), 1.0f, 0.0f);
    
    SceneManager::Instance().OnSceneChanged.Subscribe([this](GameScene scene) { OnSceneChanged(scene); });
    Game::Instance().OnPauseChanged.Subscribe([this](bool isPaused) { OnPauseChanged(isPaused); });
}

void HUD::Update(float deltaTime)
{
    // Update skills
    mSkillBar->Update();

    // // Update cursor pos  ------------------- //
    Vector2 mouseAbsPos = Game::Instance().GetMouseAbsolutePosition();
    Vector2 mouseRelPos = Game::Instance().GetMouseWorldPosition();
    auto player = LevelManager::Instance().GetPlayer();
    Vector2 playerPos = player ? player->GetPosition() : Vector2::Zero;

    // Rotate cursor based on relative deviation from player
    Vector2 dir = mouseRelPos - playerPos;

    float angle = Math::Atan2(dir.y, dir.x) + Math::PiOver2;

    mCursorImage->SetAngle(angle);
    mCursorImage->SetOffset(mouseAbsPos - Vector2(GameConstants::WINDOW_WIDTH / 2.0f, GameConstants::WINDOW_HEIGHT / 2.0f));

    // Update enemies left  ------------------- //
    int enemiesLeft = LevelManager::Instance().CountAliveEnemies();
    mEnemiesLeftCount->SetText(std::to_string(enemiesLeft));

    // Update health ------------------- //
    mShadowCatHP->Update();
}

void HUD::OnSceneChanged(GameScene scene)
{
    SetIsVisible(scene != GameScene::MainMenu);
}

void HUD::OnPauseChanged(bool isPaused)
{
    mCursorImage->SetIsVisible(!isPaused);
}