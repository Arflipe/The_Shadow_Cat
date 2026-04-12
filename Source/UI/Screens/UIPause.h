#pragma once

#include "UIScreen.h"
#include "../Primitives/UIText.h"

class UIPause : public UIScreen
{
public:
	UIPause(UIElement& parent, const std::string& fontName);

	void OnKeyPress(int key) override;

private:
	UIText* mPauseText = nullptr;
	UIImage* mPauseFade = nullptr;
};