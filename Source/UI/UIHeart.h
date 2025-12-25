#pragma once

#include "Primitives/UIElement.h"

class UIHeart : public UIElement
{
public:
	UIHeart(UIElement& parent, Vector2 offset);

	void SetHalfHeart();
	void SetFullHeart();
	void SetEmptyHeart();

private:
	UIElement* mEmptyHeart;
	UIElement* mHalfHeart;
	UIElement* mFullHeart;
};