#pragma once

#include "Xwing.h"
#include "SpaceShip.h"

class XWingManager
{
public:
	XWingManager();
	XWingManager(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera);
	~XWingManager();

	std::vector<Xwing*> xwingList;

	void SpawnXwing();
	void Removexwing(Xwing* xwing);

	void SetSpaceShip(SpaceShip* spaceshipEntity);

	void Update(float deltaTime);
private:

	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;
	Camera* camera;


	Texture* xwingTexture;
	Model* XwingModel;

	Model* Point1;
	Model* Point2;
	SpaceShip* spaceshipEntity;

	Model* currentCameraLookingTransform;
};

