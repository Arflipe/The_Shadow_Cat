#pragma once
#include "Actor.h"

class ParticleSystemComponent;

class DebugActor : public Actor {
public:
    DebugActor();
    ~DebugActor() override = default;

    ParticleSystemComponent *GetParticleSystemComponent() { return mParticleSystem; }
private:
    ParticleSystemComponent *mParticleSystem;
};
