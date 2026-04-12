#pragma once

#include "Primitives/UIElement.h"
#include "../Components/Skills/SkillInputHandler.h"
#include "SkillIcon.h"
#include <unordered_map>
#include <string>
#include <vector>

class SkillBar : public UIElement
{
public:
	static constexpr float SKILL_ICON_SPACING = 70.0f;

	SkillBar(UIElement& parent, Font* font, Vector2 offset, float scale = 1.0f, float angle = 0.0f);

	void Update();

private:
	std::vector<SkillIcon*> mSkillIcons;
};
