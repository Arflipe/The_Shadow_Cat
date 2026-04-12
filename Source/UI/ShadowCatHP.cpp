#include "ShadowCatHP.h"

#include "../LevelManager.h"
#include "../Actors/Characters/ShadowCat.h"

ShadowCatHP::ShadowCatHP(UIElement& parent, Vector2 offset)
	: UIElement(parent, offset, 1.0f, 0.0f),
	  mHP(0),
	  mMaxHP(0)
{
}

void ShadowCatHP::Update()
{
	auto player = LevelManager::Instance().GetPlayer();
	if (player == nullptr) return;

	int maxHP = player->GetMaxHP();
	int currentHP = player->GetHP();

	if (maxHP != mMaxHP) SetMaxHealth(maxHP, currentHP == mMaxHP);
	if (currentHP != mHP) SetHealth(currentHP);
}

void ShadowCatHP::SetHealth(int newHP)
{
	if (newHP == mHP) return;
	
	int currentHalfHearts = newHP * 2 / HP_PER_HEART;
	int fullHearts = currentHalfHearts / 2;
	bool hasHalfHeart = (currentHalfHearts % 2 == 1);
	
	for (int i = 0; i < fullHearts && i < mHearts.size(); ++i)
		mHearts[i]->SetFullHeart();
	
	if (hasHalfHeart && fullHearts < mHearts.size())
		mHearts[fullHearts]->SetHalfHeart();
	
	int firstEmptyHeart = hasHalfHeart ? fullHearts + 1 : fullHearts;
	for (int i = firstEmptyHeart; i < mHearts.size(); ++i)
		mHearts[i]->SetEmptyHeart();

	mHP = newHP;
}

void ShadowCatHP::SetMaxHealth(int newMaxHealth, bool fill)
{
	int newHeartCount = (newMaxHealth + HP_PER_HEART - 1) / HP_PER_HEART;

	for (int i = mHearts.size(); i < newHeartCount; ++i)
	{
		int x = i % HEARTS_IN_ROW;
		int y = -(i / HEARTS_IN_ROW);
		UIHeart* heart = new UIHeart(*this, Vector2(x * HEART_SPACING, y * HEART_SPACING));
		mHearts.push_back(heart);
	}

	mMaxHP = newMaxHealth;
}