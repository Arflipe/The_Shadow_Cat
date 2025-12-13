#include "UIRoot.h"

UIRoot::UIRoot()
	: UIElement()
{
}

UIRoot::~UIRoot()
{
}

void UIRoot::AddScreen(UIScreen* screen)
{
	mScreens.push_back(screen);
	AddChild(screen);
}

void UIRoot::RemoveScreen(UIScreen* screen)
{
	auto it = std::find(mScreens.begin(), mScreens.end(), screen);
	if (it != mScreens.end())
	{
		mScreens.erase(it);
		RemoveChild(screen);
	}
}

void UIRoot::UpdateScreens(float deltaTime)
{
	for (auto screen : mScreens)
		if (screen->IsVisible())
			screen->Update(deltaTime);
}

void UIRoot::HandleKeyPress(int key, UIScreen* activeScreen)
{
	for (auto screen : mScreens)
		screen->HandleKeyPress(key, screen == activeScreen);
}