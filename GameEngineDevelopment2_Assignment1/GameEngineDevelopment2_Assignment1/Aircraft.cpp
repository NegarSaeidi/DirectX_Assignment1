#include "Aircraft.hpp"
#include "Game.hpp"
Aircraft::Aircraft(Type type, Game* game):Entity(game), mType(type),index(0)
{
	switch (type)
	{
	case (Eagle):
		mSprite = "Eagle";
		break;
	case (Raptor):
		mSprite ="Raptor";
		break;
	default:
		mSprite = "Eagle";
			break;
	}
}

void Aircraft::drawCurrent() const
{

	
}

void Aircraft::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();


	
	
	//XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(temp.x, temp.y, temp.z) * XMMatrixTranslation(temp1.x, temp1.y, temp1.z));
	renderer->World = getTransform();
	renderer->ObjCBIndex = gameInstance->getRenderItems().size();
	renderer->Mat = gameInstance->getMaterilas()[mSprite].get();
	renderer->Geo = gameInstance->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	
	gameInstance ->getRenderItems().push_back(std::move(render));



	

}
