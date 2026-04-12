#pragma once

#include "EnemyBase.h"

class BossBase : public EnemyBase
{
public:
	BossBase(Vector2 position, float forwardSpeed);

	void Kill() override;
};