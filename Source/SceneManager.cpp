#include "SceneManager.h"
#include "UIManager.h"
#include "Game.h"
#include "LevelManager.h"
#include "GameConstants.h"
#include "UI/Screens/MainMenu.h"
#include "UI/Screens/HUD.h"
#include "UI/Screens/TutorialHUD.h"
#include "UI/Screens/UpgradeHUD.h"

// Singleton instance
SceneManager& SceneManager::Instance()
{
    static SceneManager instance;
    return instance;
}

SceneManager::SceneManager()
    : mGame(nullptr),
      mCurrentScene(GameScene::MainMenu)
{
}

SceneManager::~SceneManager()
{
    Shutdown();
}

void SceneManager::Initialize(Game* game)
{
    mGame = game;
    mCurrentScene = GameScene::MainMenu;
}

void SceneManager::Shutdown()
{
    if (mBackgroundMusic.IsValid() && mGame)
    {
        Game::Instance().GetAudio()->StopSound(mBackgroundMusic);
        mBackgroundMusic.Reset();
    }
    mGame = nullptr;
}

void SceneManager::SetScene(GameScene nextScene)
{
    UnloadScene();
    mCurrentScene = nextScene;

    switch (nextScene)
    {
    case GameScene::MainMenu:
        mBackgroundMusic = Game::Instance().GetAudio()->PlaySound("m01_main_menu.mp3", true, 0.3f);
        break;

    case GameScene::Lobby:
        mBackgroundMusic = Game::Instance().GetAudio()->PlaySound("m04_tutorial.mp3", true, 0.5f);
        LevelManager::Instance().LoadAndBuildLevel(nextScene);
        break;

    case GameScene::Level1:
        mBackgroundMusic = Game::Instance().GetAudio()->PlaySound("m05_level1.mp3", true, 0.5f);
        LevelManager::Instance().LoadAndBuildLevel(nextScene);
        break;

    case GameScene::Level1_Boss:
        mBackgroundMusic = Game::Instance().GetAudio()->PlaySound("m08_boss1_grass.mp3", true, 0.3f);
        LevelManager::Instance().LoadAndBuildLevel(nextScene);
        break;

    case GameScene::Level2:
        mBackgroundMusic = Game::Instance().GetAudio()->PlaySound("m06_level2.mp3", true, 0.6f);
        LevelManager::Instance().LoadAndBuildLevel(nextScene);
        break;

    case GameScene::Level2_Boss:
        mBackgroundMusic = Game::Instance().GetAudio()->PlaySound("m09_boss2_bricks.mp3", true);
        LevelManager::Instance().LoadAndBuildLevel(nextScene);
        break;

    case GameScene::Level3:
        mBackgroundMusic = Game::Instance().GetAudio()->PlaySound("m07_level3.mp3", true);
        LevelManager::Instance().LoadAndBuildLevel(nextScene);
        break;

    case GameScene::Level3_Boss:
        mBackgroundMusic = Game::Instance().GetAudio()->PlaySound("m10_boss3_stone.mp3", true);
        LevelManager::Instance().LoadAndBuildLevel(nextScene);
        break;
    }

    OnSceneChanged.Invoke(mCurrentScene);
}

void SceneManager::UnloadScene()
{
    if (mBackgroundMusic.IsValid())
    {
        Game::Instance().GetAudio()->StopSound(mBackgroundMusic);
        mBackgroundMusic.Reset();
    }

    LevelManager::Instance().UnloadLevel();
}

GroundType SceneManager::GetGroundType() const
{
    switch (mCurrentScene)
    {
    case GameScene::Lobby:
    case GameScene::Level1:
    case GameScene::Level1_Boss:
        return GroundType::Grass;
    case GameScene::Level2:
    case GameScene::Level2_Boss:
        return GroundType::Brick;
    case GameScene::Level3:
    case GameScene::Level3_Boss:
        return GroundType::Stone;
    default:
        return GroundType::Grass;
    }
}

std::string SceneManager::GetBackgroundPath() const
{
    switch (mCurrentScene)
    {
    case GameScene::MainMenu:
        return "../Assets/HUD/Background/MainMenuBackground.png";
    case GameScene::Lobby:
        return "../Assets/Levels/Lobby/LobbyBackground.png";
    case GameScene::Level1:
        return "../Assets/Levels/Level1/Level1Background.png";
    case GameScene::Level1_Boss:
        return "../Assets/Levels/Level1_Boss/Level1_Boss_Background.png";
    case GameScene::Level2:
        return "../Assets/Levels/Level2/Level2Background.png";
    case GameScene::Level2_Boss:
        return "../Assets/Levels/Level2_Boss/Level2_Boss_Background.png";
    case GameScene::Level3:
        return "../Assets/Levels/Level3/Level3Background.png";
    case GameScene::Level3_Boss:
        return "../Assets/Levels/Level3_Boss/Level3_Boss_Background.png";
    default:
        return "../Assets/Levels/Lobby/LobbyBackground.png";
    }
}
