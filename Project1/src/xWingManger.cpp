#include "xWingManager.h"

XWingManager::XWingManager()
{
}

XWingManager::XWingManager(GraphicsRender& render, Shader* shader, PhysicsEngine& engine)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;

	XwingModel = new Model("Models/Exam_Models/X-Wing/X-Wing_Attack_xyz_n_uv.ply", true);

	xwingTexture = new Texture();
	xwingTexture->LoadTexture("Models/Exam_Models/X-Wing/X-Wing-Texture.jpg", "diffuse_Texture");

	//Point1 = new Model()
}

XWingManager::~XWingManager()
{
}

void XWingManager::SpawnXwing()
{
	Xwing* newXwing = new Xwing(render, defaultshader, engine);
	newXwing->LoadModel(XwingModel, xwingTexture);
	xwingList.push_back(newXwing);
}

void XWingManager::Removexwing(Xwing* xwing)
{
	std::vector<Xwing*> ::iterator it = std::find(xwingList.begin(), xwingList.end(), xwing);
	if (it != xwingList.end()) // if exists
	{
		xwingList.erase(it);
	}
}
