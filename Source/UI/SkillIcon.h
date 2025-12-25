#pragma once

#include "../Components/Skills/SkillBase.h"
#include "../Components/Skills/SkillInputHandler.h"
#include "Primitives/UIElement.h"
#include "Primitives/UIImage.h"
#include "Primitives/UIText.h"

class SkillIcon : public UIElement
{
public:
	static const std::unordered_map<SkillInput, std::string> InputHintTextures;

	SkillIcon(UIElement& parent, Font* font, Vector2 offset, SkillInput skillInput, float scale = 1.0f, float angle = 0.0f);

	void Update();
	void SetIcon(const std::string& iconPath);

	void OnSkillChanged(SkillInput input, SkillBase* skill);

private:
	UIImage* mSlotImage = nullptr;
	UIImage* mIconImage = nullptr;
	UIText* mCooldownOverlay = nullptr;
	UIImage* mInputHintImage = nullptr;
	SkillBase* mSkill = nullptr;
	SkillInput mSkillInput;
};