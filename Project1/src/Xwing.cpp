#include "Xwing.h"

Xwing::Xwing()
{
}

Xwing::Xwing(GraphicsRender& render, Shader* shader, PhysicsEngine& engine)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;
}

Xwing::~Xwing()
{
}

void Xwing::LoadModel()
{
	model = new Model("Models/Exam_Models/X-Wing/X-Wing_Attack_xyz_n_uv.ply");
	model->id = "Xwing";
	model->transform.SetPosition(glm::vec3(0, 5, 0));
	model->transform.SetScale(glm::vec3(0.1f));
	render->AddModelsAndShader(model, defaultshader);



}
