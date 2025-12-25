
#include "DebugActor.h"
#include "../Game.h"
#include "../Components/ParticleSystemComponent.h"

DebugActor::DebugActor()
    : Actor()
{
    mParticleSystem = new ParticleSystemComponent(this, 3, 3, 100, 10, false);
}