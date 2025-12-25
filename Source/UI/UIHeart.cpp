#include "UIHeart.h"
#include "Primitives/UIImage.h"

UIHeart::UIHeart(UIElement& parent, Vector2 offset)
	: UIElement(parent, offset, 1.0f, 0.0f)
{
	mEmptyHeart = new UIImage(*this, "../Assets/Icons/LifeBar_2.png", Vector2::Zero, 1.0f, 0.0f);
	mHalfHeart = new UIImage(*mEmptyHeart, "../Assets/Icons/LifeBar_1.png", Vector2::Zero, 1.0f, 0.0f);
	mFullHeart = new UIImage(*mHalfHeart, "../Assets/Icons/LifeBar_0.png", Vector2::Zero, 1.0f, 0.0f);

	mFullHeart->SetIsVisible(false);
	mHalfHeart->SetIsVisible(false);
}

void UIHeart::SetHalfHeart()
{
	mFullHeart->SetIsVisible(false);
	mHalfHeart->SetIsVisible(true);
}

void UIHeart::SetFullHeart()
{
	mFullHeart->SetIsVisible(true);
	mHalfHeart->SetIsVisible(true);
}

void UIHeart::SetEmptyHeart()
{
	mFullHeart->SetIsVisible(false);
	mHalfHeart->SetIsVisible(false);
}