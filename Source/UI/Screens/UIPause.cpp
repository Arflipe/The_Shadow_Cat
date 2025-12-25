#include "UIPause.h"
#include "../../Game.h"

UIPause::UIPause(UIElement& parent, const std::string& fontName)
	:UIScreen(parent, fontName)
{
	mPauseFade = new UIImage(*this, "../Assets/HUD/Background/UpgradeBackground.png", Vector2::Zero, 1.0f, 0.0f);
	mPauseText = new UIText(*mPauseFade, "Game Paused", mFont, Vector2(0.0f, 0.0f), Vector3::One, Vector4::Zero, 1.0f, 0.0f);
}

void UIPause::OnKeyPress(int key)
{
	if (key != SDLK_ESCAPE) return;

	if (Game::Instance().IsPaused())
		SetIsVisible(!IsVisible());
	else
		SetIsVisible(false);
}