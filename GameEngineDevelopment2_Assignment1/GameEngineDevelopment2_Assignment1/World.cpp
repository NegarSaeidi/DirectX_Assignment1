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
	, mWorldBounds(-4.f, 4.f, 200.0f, 0.0f)
	, mSpawnPostion(0.0f,0.0f)
	, mScrollSpeed(-1.f)
{
	
}
/**
 * Updates the scene graph, calls the update function of eahc scene node
 *@param const GameTimer& gt
 * @return void
 */
void World::update(const GameTimer& gt)
{
	
      mBackground->move(0.f, 0, mScrollSpeed * gt.DeltaTime());
	
	
	XMFLOAT3 position = mPlayerAircraft->getWorldPosition();
	XMFLOAT2 velocity = mPlayerAircraft->getVelocity();
	
	if (position.x <= mWorldBounds.x
		|| position.x >=mWorldBounds.y)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);

	}
	

	mSceneGraph->update(gt);
	
}

void World::draw()
{
	mSceneGraph->draw();
}
/**
 * builds the game scene, creates scene nodes and adds the m to the scene graph
 *@param void
 * @return void
 */
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
	auto raptor = enemy1.get();
	raptor->setPosition(0.9, 0.2, -1.0);
	raptor->setScale(1,1, 1);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor1 = enemy2.get();
	raptor1->setPosition(-0.9, 0.2, -1.0);
	raptor1->setScale(1, 1, 1);
	
	mPlayerAircraft->attachChild(std::move(enemy2));


	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0);
	mBackground->setScale(300, 1, 300);
	mSceneGraph->attachChild(std::move(backgroundSprite));
	
	mSceneGraph->build();

}
