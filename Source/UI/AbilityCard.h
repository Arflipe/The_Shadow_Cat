#pragma once

#include "Primitives/UIElement.h"
#include "Primitives/UIImage.h"
#include "Primitives/UIText.h"
#include "../Components/Skills/UpgradeInfo.h"

class AbilityCard : public UIElement
{
public:
	static constexpr float CARD_SCALE = 6.0f;
	static constexpr float TEXT_SCALE = 0.4f;
	static constexpr float CARD_SPACING = 200.0f;
	static constexpr float CARD_INIT_X = -400.0f;
	static constexpr float CARD_Y = 0.0f;
	static constexpr float TEXT_OFFSET_Y = -5.0f;
	static constexpr float BUTTON_OFFSET_Y = -150.0f;

	AbilityCard(UIElement& parent, class Font* font, const Vector2& offset = Vector2::Zero, const float scale = 1.0f, const float angle = 0.0f);
	~AbilityCard();

	void SetAbility(UpgradeInfo upgradeInfo);
	void OnCardSelected(AbilityCard* selectedCard);

private:
	class Font* mFont;
	UIText* mCardTitle;
	UIText* mAbilityName;
	UIText* mAbilityDescription;
	UIImage* mBackgroundImage;
	UIImage* mAbilityIcon;
	UIImage* mBorderImage;
	UIImage* mSelectedBorderImage;
};