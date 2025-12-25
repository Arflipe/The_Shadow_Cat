#pragma once

#include "../Screens/UIScreen.h"
#include "UIElement.h"

class UIRoot : public UIElement
{
public:
	UIRoot();
	~UIRoot();

	void AddScreen(UIScreen* screen);
	void RemoveScreen(UIScreen* screen);

	void UpdateScreens(float deltaTime);
	void HandleKeyPress(int key, UIScreen* activeScreen);

private:
	std::vector<UIScreen*> mScreens;
};