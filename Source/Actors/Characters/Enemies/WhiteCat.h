#pragma once

#include "../EnemyBase.h"

class WhiteCat : public EnemyBase {
public:
    WhiteCat(Vector2 position, float forwardSpeed = 200.0f);

protected:
    void SetupAIBehaviors(const nlohmann::json& data) override;
};