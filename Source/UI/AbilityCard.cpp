#include "AbilityCard.h"
#include "Primitives/UIElement.h"
#include "Screens/UpgradeHUD.h"


AbilityCard::AbilityCard(UIElement& parent, class Font* font, const Vector2& offset, const float scale, const float angle)
	: UIElement(parent, offset, scale, angle)
{
	mFont = font;
	// mBackgroundImage = new UIImage(*this, Vector2::Zero, 1.0f, 0.0f);
	mAbilityIcon = new UIImage(*this, Vector2(0.0f, -32.0f), CARD_SCALE * 0.5f, 0.0f);
	mBorderImage = new UIImage(*this, "../Assets/HUD/Cards/Cards9.png", Vector2::Zero, CARD_SCALE, 0.0f);
	mSelectedBorderImage = new UIImage(*mBorderImage, "../Assets/HUD/Cards/Cards10.png", Vector2::Zero, CARD_SCALE, 0.0f);
	mCardTitle = new UIText(*this, "Ability Card", mFont, Vector2(0.0f, -102.0f), TEXT_SCALE, 0.0f, 40);
	mAbilityName = new UIText(*this, "Ability Name", mFont, Vector2(0.0f, 30.0f), TEXT_SCALE, 0.0f, 40);
	mAbilityDescription = new UIText(*this, "Ability Description", mFont, Vector2(0.0f, 70.0f), TEXT_SCALE, 0.0f, 40, 250.0f);

	UpgradeHUD::OnCardSelected.Subscribe([this](AbilityCard* selectedCard) {
		OnCardSelected(selectedCard);
	});
}

void AbilityCard::SetAbility(UpgradeInfo upgradeInfo)
{
	mCardTitle->SetText(upgradeInfo.name);
	mAbilityName->SetText(upgradeInfo.skill->GetName());
	auto upgradeText = "Level: " + std::to_string(upgradeInfo.currentLevel) + (upgradeInfo.maxLevel >= 0 ? ("/" + std::to_string(upgradeInfo.maxLevel)) : "") + (upgradeInfo.value > 0 ? "\n+" : "\n") + std::to_string(upgradeInfo.value);
	// Cut 2 decimal places for float values
	size_t dotPos = upgradeText.find('.');
	if (dotPos != std::string::npos && dotPos + 3 < upgradeText.length())
		upgradeText = upgradeText.substr(0, dotPos + 3);
	mAbilityDescription->SetText(upgradeText);
	mAbilityIcon->SetImage(upgradeInfo.skill->GetIconPath());
}

void AbilityCard::OnCardSelected(AbilityCard* selectedCard)
{
	if (this == selectedCard) mSelectedBorderImage->SetIsVisible(true);
	else mSelectedBorderImage->SetIsVisible(false);
}