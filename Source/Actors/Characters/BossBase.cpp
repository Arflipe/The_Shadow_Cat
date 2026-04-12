#include "BossBase.h"
#include "../../Game.h"
#include "../../LevelManager.h"

BossBase::BossBase(Vector2 position, float forwardSpeed)
	: EnemyBase(position, forwardSpeed)
{
	LevelManager::Instance().RegisterBoss(this);
}

void BossBase::Kill()
{
	LevelManager::Instance().UnregisterBoss(this);
	EnemyBase::Kill();
}