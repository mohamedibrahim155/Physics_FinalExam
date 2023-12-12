#pragma once

#include "Xwing.h"
#include "SpaceShip.h"
#include "Bullet.h";
#include "Deflector.h"

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
	void ReduceHealth(bool isRight);

	void Update(float deltaTime);
	bool IsGameOverState();
	static XWingManager& GetInstance();
private:

	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;
	Camera* camera;

	Xwing* newXwing;
	Texture* xwingTexture;
	Model* XwingModel;

	Model* Point1;
	Model* Point2;
	Model* bulletModel;
	Model* defaultSphere;

	Bullet* bullet;

	SpaceShip* spaceshipEntity;

	Deflector* deflector1;
	Deflector* deflector2;

	Model* currentCameraLookingTransform;

	int TotalhealthRight = 100;
	int TotalhealthLeft = 100;

	bool isGameOver = false;

};

