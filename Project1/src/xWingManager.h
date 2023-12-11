#pragma once

#include "Xwing.h"
#include "SpaceShip.h"
#include "Bullet.h";
class XWingManager
{
public:
	XWingManager();
	XWingManager(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera);
	~XWingManager();

	std::vector<Xwing*> xwingList;
	std::vector<Bullet*> bulletList;

	void SetRenderers(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera);
	void SpawnXwing();
	void SpawnSphere(const glm::vec3 spawnPosition);
	void Removexwing(Xwing* xwing);
	void SpawnBullet(const glm::vec3 startPosition, const glm::vec3 direction);
	void RemoveBullet(Bullet* bullet);


	void SetSpaceShip(SpaceShip* spaceshipEntity);

	void Update(float deltaTime);

	static XWingManager& GetInstance();
private:

	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;
	Camera* camera;


	Texture* xwingTexture;
	Model* XwingModel;

	Model* Point1;
	Model* Point2;
	Model* bulletModel;
	Model* defaultSphere;

	Bullet* bullet;

	SpaceShip* spaceshipEntity;

	Model* currentCameraLookingTransform;
};

