#pragma once

#include "Primitives/UIElement.h"
#include "UIHeart.h"
#include <vector>


class ShadowCatHP : public UIElement
{
public:
	static constexpr int HP_PER_HEART = 20;
	static constexpr int HEARTS_IN_ROW = 5;
	static constexpr float HEART_SPACING = 40.0f;

	ShadowCatHP(UIElement& parent, Vector2 offset);

	void SetHealth(int health);
	void SetMaxHealth(int maxHealth, bool fill = false);

	void Update();

private:
	int mHP;
	int mMaxHP;

	std::vector<UIHeart*> mHearts;
};