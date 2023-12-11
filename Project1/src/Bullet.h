#pragma once

#include "PhysicsEngine.h"
#include"GraphicsRender.h"
class Bullet
{
public:
	Bullet();
	Bullet(GraphicsRender* render, Shader* shader, PhysicsEngine* engine);
	~Bullet();
	Model* model;
	PhysicsObject* BulletPhysics;

	void LoadBullet(Model* model);
	void LoadBullet();

	void SetSpawnposition(const glm::vec3 &Startposition);
	void SetDirection(const glm::vec3 &direction);

	void Update(float deltaTime);

	bool IsDestroyed() { return isDestroyed; }
private:

	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;

	glm::vec3 starPosition = glm::vec3(0);
	glm::vec3 Direction = glm::vec3(0);

	float speed = 20;

	bool isDestroyed = false;
	
};

