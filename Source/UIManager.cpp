#include "UIManager.h"
#include "UI/Screens/MainMenu.h"
#include "UI/Primitives/UIElement.h"
#include "UI/Screens/UIPause.h"
#include "UI/Screens/UIScreen.h"
#include "UI/Screens/HUD.h"
#include "UI/Screens/TutorialHUD.h"
#include "UI/Screens/UpgradeHUD.h"
#include "UI/Screens/GameOver.h"
#include "UI/Screens/WinScreen.h"
#include "Game.h"
#include "UI/Primitives/UIRoot.h"
#include "UI/Screens/UIPause.h"

UIManager::UIManager()
    :mRootUI(nullptr)
    ,mHUD(nullptr)
    ,mUpgradeHUD(nullptr)
    ,mTutorialHUD(nullptr)
{
}

UIManager::~UIManager()
{
}

UIManager& UIManager::Instance()
{
    static UIManager instance;
    return instance;
}

void UIManager::Initialize()
{
    mRootUI = new UIRoot();
    new HUD(*mRootUI, "../Assets/Fonts/Pixellari.ttf");
    new TutorialHUD(*mRootUI, "../Assets/Fonts/Pixellari.ttf");
	new GameOver(*mRootUI, "../Assets/Fonts/Pixellari.ttf");
	new WinScreen(*mRootUI, "../Assets/Fonts/Pixellari.ttf");
	new MainMenu(*mRootUI, "../Assets/Fonts/Pixellari.ttf");
    new UpgradeHUD(*mRootUI, "../Assets/Fonts/Pixellari.ttf");
    new UIPause(*mRootUI, "../Assets/Fonts/Pixellari.ttf");
}

void UIManager::Shutdown()
{
    delete mRootUI;
    mUIStack.clear();
    mRootUI = nullptr;
    mHUD = nullptr;
    mUpgradeHUD = nullptr;
    mTutorialHUD = nullptr;
}

void UIManager::PushUI(UIScreen* screen)
{
    mUIStack.emplace_back(screen);
}

void UIManager::RemoveUI(UIScreen* screen)
{
	auto it = std::find(mUIStack.begin(), mUIStack.end(), screen);
	if (it != mUIStack.end()) mUIStack.erase(it);
}

void UIManager::Update(float deltaTime)
{
	mRootUI->UpdateScreens(deltaTime);
}

