#include "InputHandler.h"
#include "UIManager.h"
#include "Game.h"
#include "LevelManager.h"
#include "GameConstants.h"
#include <SDL.h>
#include "UI/Screens/UIScreen.h"
#include "Renderer/Renderer.h"
#include "UI/Screens/TutorialHUD.h"
#include "Actors/Characters/ShadowCat.h"

// Singleton instance
InputHandler& InputHandler::Instance()
{
    static InputHandler instance;
    return instance;
}

InputHandler::InputHandler()
    : mController(nullptr)
{
}

InputHandler::~InputHandler()
{
    Shutdown();
}

void InputHandler::Initialize()
{
    // Check for existing game controllers
    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
        {
            HandleControllerAdded(i);
            if (mController)
                break; // Only open one controller
        }
    }
}

void InputHandler::Shutdown()
{
    if (mController)
    {
        SDL_GameControllerClose(mController);
        mController = nullptr;
    }
}

void InputHandler::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Game::Instance().Quit();
            break;

        case SDL_CONTROLLERDEVICEADDED:
            if (!mController)
            {
                HandleControllerAdded(event.cdevice.which);
            }
            break;

        case SDL_CONTROLLERDEVICEREMOVED:
            HandleControllerRemoved(event.cdevice.which);
            break;

        case SDL_KEYDOWN:
        case SDL_MOUSEBUTTONDOWN:
            // Handle UI and system keys first
            if (event.type == SDL_KEYDOWN)
            {
                HandleKeyPress(event.key.keysym.sym, event.key.repeat);
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                HandleMouseButton();
            }

            // Pass the original event to all actors (for skills, etc.)
            for (auto actor : LevelManager::Instance().GetActors())
            {
                actor->OnHandleEvent(event);
            }
            break;
        }
    }

    // Process continuous keyboard input for actors
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    LevelManager::Instance().ProcessInput(state);
}

void InputHandler::HandleControllerAdded(int deviceIndex)
{
    mController = SDL_GameControllerOpen(deviceIndex);
    if (mController)
    {
        SDL_Log("Game controller added: %s", SDL_GameControllerName(mController));
    }
    else
    {
        SDL_Log("Could not open game controller %i: %s", deviceIndex, SDL_GetError());
    }
}

void InputHandler::HandleControllerRemoved(SDL_JoystickID instanceID)
{
    if (mController && SDL_GameControllerGetJoystick(mController) == SDL_JoystickFromInstanceID(instanceID))
    {
        SDL_Log("Game controller removed");
        SDL_GameControllerClose(mController);
        mController = nullptr;
    }
}

void InputHandler::HandleKeyPress(SDL_Keycode key, Uint8 repeat)
{
    auto& uiStack = UIManager::Instance().GetUIStack();
    UIManager::Instance().GetRootUI()->HandleKeyPress(key, uiStack.empty() ? nullptr : uiStack.back());

    // Fullscreen toggle (F11) - only on initial press
    if (key == SDLK_F11 && repeat == 0)
    {
        bool isFullscreen = Game::Instance().IsFullscreen();
        Game::Instance().SetFullscreen(!isFullscreen);

        if (!isFullscreen)
        {
            SDL_SetWindowFullscreen(Game::Instance().GetWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
            int w, h;
            SDL_GetWindowSize(Game::Instance().GetWindow(), &w, &h);
            Game::Instance().GetRenderer()->UpdateViewport(w, h);
        }
        else
        {
            SDL_SetWindowFullscreen(Game::Instance().GetWindow(), 0);
            Game::Instance().GetRenderer()->UpdateViewport(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT);
        }
    }

    // Debug toggle (F1) - only on initial press
    if (key == SDLK_F1 && repeat == 0)
    {
        Game::Instance().SetDebugging(!Game::Instance().IsDebugging());
    }

    // Pause toggle (ESC) - only on initial press
    if (key == SDLK_ESCAPE && repeat == 0)
    {
        if (SceneManager::Instance().GetCurrentScene() > GameScene::MainMenu &&
            LevelManager::Instance().GetPlayer() && 
            LevelManager::Instance().GetPlayer()->GetUpgradePoints() == 0)
        {
            Game::Instance().SetPaused(!Game::Instance().IsPaused());
        }
    }
}

void InputHandler::HandleMouseButton()
{
    auto& uiStack = UIManager::Instance().GetUIStack();
    UIManager::Instance().GetRootUI()->HandleKeyPress(SDLK_UNKNOWN, uiStack.empty() ? nullptr : uiStack.back());
}