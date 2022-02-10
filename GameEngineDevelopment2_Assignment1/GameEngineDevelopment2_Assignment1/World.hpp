#pragma once

#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.hpp"


class World
{
public:
	explicit                                   World(Game* game);
	void                                       update(const GameTimer& gt);
	void                                       draw();
	void                                       buildScene();

private:

	enum  Layer
	{
		Background,
		Air,
		LayerCount
	};

private:

	Game*                                             mGame;
	SceneNode*                                        mSceneGraph;
	std::array<SceneNode*, 3>                mSceneLayers;
	XMFLOAT4                                          mWorldBounds;
    XMFLOAT2                                          mSpawnPostion;
	float                                             mScrollSpeed;
	Aircraft*                                         mPlayerAircraft;
	SpriteNode*                                       mBackground;





};
