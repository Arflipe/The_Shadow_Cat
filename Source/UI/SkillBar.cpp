#include "SkillBar.h"
#include "SkillIcon.h"

SkillBar::SkillBar(UIElement& parent, Font* font, Vector2 offset, float scale, float angle)
	:UIElement(parent, offset, scale, angle)
{
	for (size_t i = 0; i < SkillInputHandler::DefaultSkillInputs.size(); ++i)
	{
		Vector2 iconOffset(i * SKILL_ICON_SPACING, 0.0f);
		auto icon = new SkillIcon(*this, font, iconOffset, SkillInputHandler::DefaultSkillInputs[i], 1.0f, 0.0f);
		mSkillIcons.push_back(icon);
	}
}

void SkillBar::Update()
{
	for (auto& icon : mSkillIcons) icon->Update();
}
