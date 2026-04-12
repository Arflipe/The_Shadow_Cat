#pragma once
#include <vector>
#include "Math.h"
#include "UI/Primitives/UIRoot.h"

class UIManager
{
public:
    static UIManager& Instance();

    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

    void Initialize();
    void Shutdown();

    // UI Stack Management
    void PushUI(class UIScreen* screen);
    void RemoveUI(class UIScreen* screen);
    std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }

    // UI Element Access
    class UIRoot* GetRootUI() { return mRootUI; }
    class HUD* GetHUD() { return mHUD; }
    class TutorialHUD* GetTutorialHUD() { return mTutorialHUD; }
    class UpgradeHUD* GetUpgradeHUD() { return mUpgradeHUD; }

    void SetHUD(class HUD* hud) { mHUD = hud; }
    void SetTutorialHUD(class TutorialHUD* hud) { mTutorialHUD = hud; }
    void SetUpgradeHUD(class UpgradeHUD* hud) { mUpgradeHUD = hud; }

    // Update & Cleanup
    void Update(float deltaTime);

private:
    UIManager();
    ~UIManager();

    class UIRoot* mRootUI;
    std::vector<class UIScreen*> mUIStack;
    class HUD* mHUD;
    class UpgradeHUD* mUpgradeHUD;
    class TutorialHUD* mTutorialHUD;
};
