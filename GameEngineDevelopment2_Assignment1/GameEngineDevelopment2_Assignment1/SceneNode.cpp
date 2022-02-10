/*
-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// SceneNode.cpp
-------------------------------------------------------------------------*/
#include "SceneNode.hpp"

SceneNode::SceneNode(Game* game) :
	mChildren(),
	mParent(nullptr),
	gameInstance(game)
{
	mWorldPosition = XMFLOAT3(0, 0, 0);
	mWorldScale = XMFLOAT3(1, 1, 1);
	mWorlRotation = XMFLOAT3(0, 0, 0);
}

void SceneNode::attachChild(Ptr child)
{

	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(const GameTimer& gt)
{
	updateCurrent(gt);
	updateChildren(gt);
}

void SceneNode::draw() const
{
	
	// Draw node and children with changed transform
	drawCurrent();
	drawChildren();
}

void SceneNode::build()
{
	buildCurrent();
	buildChildren();
}

XMFLOAT3 SceneNode::getWorldPosition() const
{
	return mWorldPosition;
}

void SceneNode::setPosition(float x, float y, float z)
{
	mWorldPosition.x = x;
	mWorldPosition.y = y;
	mWorldPosition.z = z;
}

XMFLOAT3 SceneNode::getWorldRotation() const
{
	return mWorlRotation;
}

void SceneNode::setWorldRotation(float x, float y, float z)
{
	mWorlRotation.x = x;
	mWorlRotation.y = y;
	mWorlRotation.z = z;

}

XMFLOAT3 SceneNode::getWorldScale() const
{
	return mWorldScale;
}

void SceneNode::setScale(float x, float y, float z)
{
	mWorldScale.x = x;
	mWorldScale.y = y;
	mWorldScale.z = z;
}

XMFLOAT4X4 SceneNode::getWorldTransform() const
{
	
	XMFLOAT4X4 transform = MathHelper::Identity4x4();
	XMMATRIX T = XMLoadFloat4x4(&transform);
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		XMMATRIX Tp = XMLoadFloat4x4(&node->getTransform());
		T = Tp * T;
		
	}

	XMStoreFloat4x4(&transform, T);


	return transform;
}

XMFLOAT4X4 SceneNode::getTransform() const
{
	XMFLOAT4X4 transform = MathHelper::Identity4x4();
	XMMATRIX T=XMMatrixScaling(mWorldScale.x,mWorldScale.y,mWorldScale.z)
		* XMMatrixTranslation(mWorldPosition.x,mWorldPosition.y,mWorldPosition.z)
		* XMMatrixRotationRollPitchYaw(mWorlRotation.x, mWorlRotation.y,mWorlRotation.z);
	XMStoreFloat4x4(&transform, T);

	
	return transform;

}

void SceneNode::move(float x, float y, float z)
{
	mWorldPosition.x += x;
	mWorldPosition.y += y;
	mWorldPosition.z += z;
}

void SceneNode::updateCurrent(const GameTimer& gt)
{
	
}

void SceneNode::updateChildren(const GameTimer& gt)
{
	for (Ptr& child : mChildren)
	{
		child->update(gt);
	}
}

void SceneNode::drawCurrent() const
{

}

void SceneNode::drawChildren() const
{
	for (const Ptr& child : mChildren)
	{
		child->draw();

	}
}

void SceneNode::buildCurrent()
{
}

void SceneNode::buildChildren()
{
	for (const Ptr& child : mChildren)
	{
		child->build();
		
	}
}
