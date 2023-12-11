#pragma once

#include "PhysicsEngine.h"
#include"GraphicsRender.h"

class Deflector
{
public:

	Deflector(GraphicsRender* render, Shader* shader, PhysicsEngine* engine);
	~Deflector();
	Deflector();

	Model* model;
	PhysicsObject* DeflectorPhysics;


	void LoadDeflector(Model* model, const glm::vec3& Startposition);
	void StartPosition(const glm::vec3& Startposition);
	void LoadDeflector();
	
	void SetSide(bool isRight);

	bool IsDestroyed() { return isDestroyed; }
private:

	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;

	glm::vec3 starPosition = glm::vec3(0);

	bool isRight=false;
	bool isDestroyed = false;
};

