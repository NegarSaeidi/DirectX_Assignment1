/*
-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// World.cpp
-------------------------------------------------------------------------*/
#include "World.hpp"
#include "Game.hpp"
World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, 200.0f, 0.0f)
	, mSpawnPostion(0.0f,0.0f)
	, mScrollSpeed(-1.f)
{
	
}

void World::update(const GameTimer& gt)
{
	
      mBackground->move(0.f, 0, mScrollSpeed * gt.DeltaTime());
	
	// Move the player sidewards (plane scouts follow the main aircraft)
	XMFLOAT3 position = mPlayerAircraft->getWorldPosition();
	XMFLOAT2 velocity = mPlayerAircraft->getVelocity();
	
	// If player touches borders, flip its X velocity
	if (position.x <= -4
		|| position.x >=4)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
		Escort1->setVelocity(velocity);
		Escort2->setVelocity(velocity);
	}
	

	mSceneGraph->update(gt);
	
}

void World::draw()
{
	mSceneGraph->draw();
}

void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode(mGame));
		mSceneLayers[i] = layer.get();

		mSceneGraph->attachChild(std::move(layer));
	}
	std::unique_ptr<Aircraft> aircraft(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = aircraft.get();
	mPlayerAircraft->setPosition(0, 0.1, -2.0);
	mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	mPlayerAircraft->setVelocity(1,0.0001);
	mSceneLayers[Air]->attachChild(std::move(aircraft));



	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
	Escort1 = enemy1.get();
	Escort1->setPosition(0.9, 0.2, -3.0);
	Escort1->setScale(1,1, 1);
	Escort1->setVelocity(1, 0.0001);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	Escort2 = enemy2.get();
	Escort2->setPosition(-0.9, 0.2, -3.0);
	Escort2->setScale(1, 1, 1);
	Escort2->setVelocity(1, 0.0001);;
	mPlayerAircraft->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0);
	mBackground->setScale(300, 1, 300);
	mSceneGraph->attachChild(std::move(backgroundSprite));
	
	mSceneGraph->build();

}
