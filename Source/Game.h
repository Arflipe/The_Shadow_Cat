#pragma once
#include <SDL.h>
#include <vector>

#include "AudioSystem.h"
#include "Math.h"
#include "SceneManager.h"
#include "Event.h"
#include "UI/Primitives/UIElement.h"

class Game
{
public:
    static Game& Instance();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Event<bool> OnPauseChanged;
    Event<> OnGameOver;
    Event<> OnGameWon;

    bool Initialize();
    void RunLoop();
    void Shutdown();
    void Quit() { mIsRunning = false; }

    // Game State
    void SetPaused(bool paused);
    bool IsPaused() const { return mIsPaused; }
    void ResetGame();
    void BackToMenu();
    void SetGameOver();
    void SetGameWon();

    // System Access
    class Renderer* GetRenderer() { return mRenderer; }
    class AudioSystem* GetAudio() { return mAudio; }
    SDL_Window* GetWindow() { return mWindow; }

    // Debug
    bool IsDebugging() const { return mIsDebugging; }
    void SetDebugging(bool debug) { mIsDebugging = debug; }
    bool IsGodMode() const { return mIsGodMode; }
    void SetGodMode(bool godmode) { mIsGodMode = godmode; }

    // Fullscreen
    bool IsFullscreen() const { return mIsFullscreen; }
    void SetFullscreen(bool fullscreen) { mIsFullscreen = fullscreen; }

    // Mouse position (used by UI)
    Vector2 GetMouseWorldPosition();
    Vector2 GetMouseAbsolutePosition();

private:
    Game();
    ~Game();

    void UpdateGame(float deltaTime);

    // Systems
    class Renderer* mRenderer;
    class AudioSystem* mAudio;

    // SDL
    SDL_Window* mWindow;

    // Game state
    Uint32 mTicksCount;
    bool mIsRunning;
    bool mIsFullscreen;
    bool mIsPaused;
    bool mIsGameOver;
    bool mIsGameWon;
    bool mIsDebugging;
    bool mIsGodMode;
};