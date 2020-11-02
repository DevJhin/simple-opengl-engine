#include "Light.h"

Light::Light(Actor* actor):Component(actor)
{
	LOG("Constructor of Light Component");
	World::GetInstance()->RegisterLight(this);
}
