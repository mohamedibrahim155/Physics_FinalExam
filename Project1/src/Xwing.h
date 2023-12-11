#pragma once

#include"PhysicsEngine.h"
#include "GraphicsRender.h"
#include "InputManager.h"


enum xWingState
{
	FOLLOW =0,
	DISECT
};
class Xwing : public iInputListener
{
public:
	Xwing();
	Xwing(GraphicsRender& render, Shader* shader, PhysicsEngine& engine );
	Xwing(GraphicsRender* render, Shader* shader, PhysicsEngine* engine );

	~Xwing();


	Model* model;
	PhysicsObject* SpaceShipPhysics;
	xWingState state = FOLLOW;
	void LoadModel(Model* copyModel, Texture* copyTexutre);

	void Update(float deltaTime);
	void DrawAABBCollision(PhysicsObject* physicsObject);

	glm::vec3 StartPosition;
	glm::vec3 EndPosition;

	glm::vec3 Direction;
private:

	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;

	float speed = 2;

	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHeld(const int& key) override;
};

