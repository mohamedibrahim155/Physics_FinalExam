#pragma once

#include"PhysicsEngine.h"
#include "GraphicsRender.h"
#include "InputManager.h"


enum xWingState
{
	FOLLOW =0,
	DEFLECT
};
class Xwing : public iInputListener
{
public:
	Xwing();
	Xwing(GraphicsRender& render, Shader* shader, PhysicsEngine& engine );
	Xwing(GraphicsRender* render, Shader* shader, PhysicsEngine* engine );

	~Xwing();


	Model* model;
	PhysicsObject* xWingPhysics;

	Model* debugSphere;
	PhysicsObject* debugSpherePhyiscs;

	xWingState state = FOLLOW;
	void LoadModel(Model* copyModel, Texture* copyTexutre);
	void SetDebugSphereModel(Model* model);

	void Update(float deltaTime);
	void DrawAABBCollision(PhysicsObject* physicsObject);
	void SetCamera(Camera* camera);
	glm::vec3 StartPosition;
	glm::vec3 EndPosition;

	glm::vec3 Direction;
private:

	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;
	Camera* camera;
	float speed = 20;
	float debugSphereDistance = 3.5f;


	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHeld(const int& key) override;
};

