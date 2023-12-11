#include "Xwing.h"

Xwing::Xwing()
{
}

Xwing::Xwing(GraphicsRender& render, Shader* shader, PhysicsEngine& engine)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;
	InputManager::GetInstance().AddListener(this);
}

Xwing::Xwing(GraphicsRender* render, Shader* shader, PhysicsEngine* engine)
{
	this->render = render;
	this->defaultshader = shader;
	this->engine = engine;
	InputManager::GetInstance().AddListener(this);
}

Xwing::~Xwing()
{
}

void Xwing::LoadModel(Model* copyModel, Texture* copyTexutre)
{
	model = new Model(*copyModel);
//	Texture* loadWingTexture = new Texture();
	//loadWingTexture->LoadTexture("Models/Exam_Models/X-Wing/X-Wing-Texture.jpg", "diffuse_Texture");
	model->meshes[0]->meshMaterial->diffuseTexture = copyTexutre;
	model->id = "Xwing";
	model->transform.SetPosition(glm::vec3(0, 5, 0));
	model->transform.SetScale(glm::vec3(0.05f));
	render->AddModelsAndShader(model, defaultshader);



}

void Xwing::Update(float deltaTime)
{
	if (state ==FOLLOW)
	{
		Direction = glm::normalize(EndPosition - StartPosition);
	}
	SpaceShipPhysics->velocity = Direction;
}

void Xwing::OnKeyPressed(const int& key)
{

}

void Xwing::OnKeyReleased(const int& key)
{
}

void Xwing::OnKeyHeld(const int& key)
{
}
