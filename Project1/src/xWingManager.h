#pragma once

#include "Xwing.h"

class XWingManager
{
public:
	XWingManager();
	XWingManager(GraphicsRender& render, Shader* shader, PhysicsEngine& engine);
	~XWingManager();

	std::vector<Xwing*> xwingList;

	void SpawnXwing();

	void Removexwing(Xwing* xwing);
private:

	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;


	Texture* xwingTexture;
	Model* XwingModel;

	Model* Point1;
	Model* Point2;
};

