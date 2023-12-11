#pragma once

#include"PhysicsEngine.h"
#include "GraphicsRender.h"


class Xwing
{
public:
	Xwing();
	Xwing(GraphicsRender& render, Shader* shader, PhysicsEngine& engine );

	~Xwing();


	Model* model;
	PhysicsObject* SpaceShipPhysics;

	void LoadModel();

	void Update(float deltaTime);
	void DrawAABBCollision(PhysicsObject* physicsObject);
private:

	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;
};

