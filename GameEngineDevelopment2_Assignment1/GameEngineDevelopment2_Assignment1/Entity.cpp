/*
-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// Entity.cpp, adjusts the velocity of the entity
-------------------------------------------------------------------------*/
#include "Entity.hpp"

Entity::Entity(Game* game):SceneNode(game), mVelocity(0, 0)
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
	move(xMovement,0, yMovement);

	
}
