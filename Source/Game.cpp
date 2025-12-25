#include "Game.h"
#include "LevelManager.h"
#include "InputHandler.h"
#include "SceneManager.h"
#include "GameRenderer.h"
#include "UIManager.h"
#include "SystemInitializer.h"
#include "SkillFactory.h"
#include "Random.h"
#include "Renderer/Renderer.h"
#include "AudioSystem.h"
#include "GameConstants.h"
#include "UI/Screens/MainMenu.h"
#include "UI/Screens/HUD.h"
#include "UI/Screens/TutorialHUD.h"
#include "UI/Screens/UpgradeHUD.h"
#include "UI/Screens/GameOver.h"
#include "UI/Screens/WinScreen.h"
#include <SDL.h>

Game& Game::Instance()
{
    static Game instance;
    return instance;
}

Game::Game()
    : mRenderer(nullptr),
      mAudio(nullptr),
      mWindow(nullptr),
      mTicksCount(0),
      mIsRunning(true),
      mIsFullscreen(false),
      mIsPaused(false),
      mIsGameOver(false),
      mIsGameWon(false),
      mIsDebugging(false),
      mIsGodMode(true)
{
}

Game::~Game()
{
}

bool Game::Initialize()
{
    Random::Init();

    if (!SystemInitializer::InitializeSDL())  return false;

    mWindow = SystemInitializer::CreateGameWindow(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT);
    if (!mWindow) return false;

    mRenderer = new Renderer(mWindow);
    mRenderer->Initialize(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT);

    SDL_ShowCursor(SDL_DISABLE);
    
    mAudio = new AudioSystem();
    mAudio->CacheAllSounds();
    
    InputHandler::Instance().Initialize();
    LevelManager::Instance().Initialize();
    SceneManager::Instance().Initialize();
    GameRenderer::Instance().Initialize();
    UIManager::Instance().Initialize();

    SkillFactory::InitializeSkills();

    SceneManager::Instance().SetScene(GameScene::MainMenu);

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
        if (deltaTime > 0.05f) deltaTime = 0.05f;

        mTicksCount = SDL_GetTicks();

        InputHandler::Instance().ProcessInput();
        UpdateGame(deltaTime);
        GameRenderer::Instance().Render();

        int sleepTime = (1000 / GameConstants::FPS) - (SDL_GetTicks() - mTicksCount);
        if (sleepTime > 0) SDL_Delay(sleepTime);
    }
}

void Game::UpdateGame(float deltaTime)
{
    // Update level (actors, camera, portal, transitions)
    LevelManager::Instance().Update(deltaTime);

    // Update audio
    if (mAudio) mAudio->Update(deltaTime);

    // Update UI
    UIManager::Instance().Update(deltaTime);
}

void Game::SetPaused(bool paused)
{
    if (mIsPaused == paused) return;

    mIsPaused = paused;
    OnPauseChanged.Invoke(mIsPaused);
    auto newState = mIsPaused ? ActorState::Paused : ActorState::Active;
    for (auto actor : LevelManager::Instance().GetActors()) actor->SetState(newState);
}

void Game::ResetGame()
{
    mAudio->StopAllSounds();

    mIsGameOver = false;
    mIsGameWon = false;
    
    SetPaused(false);
    
    SceneManager::Instance().SetScene(GameScene::Level1);
    
    if (LevelManager::Instance().GetPlayer())
        LevelManager::Instance().GetPlayer()->SetHP(LevelManager::Instance().GetPlayer()->GetMaxHP());
}

void Game::BackToMenu()
{
    mAudio->StopAllSounds();

    mIsGameOver = false;
    mIsGameWon = false;
    
    SetPaused(false);
    
    SceneManager::Instance().SetScene(GameScene::MainMenu);
}

Vector2 Game::GetMouseWorldPosition()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    float scaleX = static_cast<float>(GameConstants::WINDOW_WIDTH) / static_cast<float>(mRenderer->GetScreenWidth());
    float scaleY = static_cast<float>(GameConstants::WINDOW_HEIGHT) / static_cast<float>(mRenderer->GetScreenHeight());
    mouseX = static_cast<int>(mouseX * scaleX);
    mouseY = static_cast<int>(mouseY * scaleY);

    Vector2 worldPos;
    worldPos.x = static_cast<float>(mouseX) + LevelManager::Instance().GetCameraPos().x;
    worldPos.y = static_cast<float>(mouseY) + LevelManager::Instance().GetCameraPos().y;

    return worldPos;
}

Vector2 Game::GetMouseAbsolutePosition()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    float scaleX = static_cast<float>(GameConstants::WINDOW_WIDTH) / static_cast<float>(mRenderer->GetScreenWidth());
    float scaleY = static_cast<float>(GameConstants::WINDOW_HEIGHT) / static_cast<float>(mRenderer->GetScreenHeight());
    
    return Vector2(static_cast<float>(mouseX * scaleX), static_cast<float>(mouseY * scaleY));
}

void Game::Shutdown()
{
    UIManager::Instance().Shutdown();
    GameRenderer::Instance().Shutdown();
    SceneManager::Instance().Shutdown();
    InputHandler::Instance().Shutdown();
    LevelManager::Instance().Shutdown();

    mRenderer->Shutdown();
    delete mRenderer;
    mRenderer = nullptr;

    delete mAudio;
    mAudio = nullptr;

    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::SetGameOver()
{
    SetPaused(true);
    mIsGameOver = true;
    OnGameOver.Invoke();
}

void Game::SetGameWon()
{
    SetPaused(true);
    mIsGameWon = true;
    OnGameWon.Invoke();
}