#include "SkillIcon.h"

#include "../LevelManager.h"
#include "../Actors/Characters/ShadowCat.h"

const std::unordered_map<SkillInput, std::string> SkillIcon::InputHintTextures = {
	{SkillInput(InputType::Mouse, SDL_BUTTON_LEFT), "../Assets/HUD/Menu/KeyboardLMB.png"},
	{SkillInput(InputType::Mouse, SDL_BUTTON_RIGHT), "../Assets/HUD/Menu/KeyboardRMB.png"},
	{SkillInput(InputType::Keyboard, SDL_SCANCODE_Q), "../Assets/HUD/Menu/KeyboardQ.png"},
	{SkillInput(InputType::Keyboard, SDL_SCANCODE_E), "../Assets/HUD/Menu/KeyboardE.png"},
	{SkillInput(InputType::Keyboard, SDL_SCANCODE_LSHIFT), "../Assets/HUD/Menu/KeyboardSHIFT.png"}
};

SkillIcon::SkillIcon(UIElement& parent, Font* font, Vector2 offset, SkillInput skillInput, float scale, float angle)
	:UIElement(parent, offset, scale, angle)
{
	mSlotImage = new UIImage(*this, "../Assets/Icons/ItemSlot.png", Vector2::Zero, 1.4f, 0.0f);
	mIconImage = new UIImage(*mSlotImage, Vector2::Zero, 1.0f, 0.0f);
	mCooldownOverlay = new UIText(*mIconImage, "",  font, Vector2(0.0f, 5.0f), Vector3::One, Vector4::Zero, 0.7f, 0.0f);
	mInputHintImage = new UIImage(*this, SkillIcon::InputHintTextures.at(skillInput), Vector2(20.0f, 35.0f), 0.8f, 0.0f);
	mSkillInput = skillInput;
	
	SkillInputHandler::OnSkillChanged.Subscribe([this](SkillInput input, SkillBase* skill) { OnSkillChanged(input, skill); });

	auto player = LevelManager::Instance().GetPlayer();
	if (!player) return;
	auto skillInputHandler = player->GetComponent<SkillInputHandler>();
	mSkill = skillInputHandler->GetSkillForInput(skillInput);
	if (mSkill) SetIcon(mSkill->GetIconPath());
}

void SkillIcon::Update()
{
	if (!mSkill) return;

	float cdRemaining = mSkill->GetCooldown();
	if (cdRemaining > 0.0f)
		mCooldownOverlay->SetText(std::to_string(static_cast<int>(std::ceil(cdRemaining))));
	else mCooldownOverlay->SetText("");
}

void SkillIcon::SetIcon(const std::string& iconPath)
{
	mIconImage->SetImage(iconPath);
}

void SkillIcon::OnSkillChanged(SkillInput input, SkillBase* skill)
{
	if (mSkillInput != input) return;

	mSkill = skill;
	if (mSkill) SetIcon(mSkill->GetIconPath());
	else mIconImage->ClearImage();
}