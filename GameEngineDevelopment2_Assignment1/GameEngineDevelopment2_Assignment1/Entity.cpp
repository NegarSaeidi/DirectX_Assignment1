#include "Entity.hpp"

Entity::Entity(Game* game):SceneNode(game)
{
	
}

void Entity::setVelocity(XMFLOAT2 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

XMFLOAT2 Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::updateCurrent(const GameTimer& gt)
{
	float xMovement = mVelocity.x * gt.DeltaTime();
	float yMovement = mVelocity.y * gt.DeltaTime();
	move(xMovement,yMovement,0);
}
