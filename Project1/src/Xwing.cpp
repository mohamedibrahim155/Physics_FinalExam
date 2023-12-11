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
	model->transform.SetScale(glm::vec3(0.05f));
	render->AddModelsAndShader(model, defaultshader);


	xWingPhysics = new PhysicsObject(model);

	xWingPhysics->Initialize(SPHERE, true, DYNAMIC);
	xWingPhysics->gravityValue = 0;

	xWingPhysics->DoCollisionCall([this](PhysicsObject* other)
		{
			if (other->model->id == "SpaceShip")
			{
				std::cout << " X Wing sphere collided with spaceShip" << std::endl;
			}
		});

	engine->AddPhysicsObjects(xWingPhysics);



	debugSpherePhyiscs = new PhysicsObject(debugSphere);

	debugSpherePhyiscs->Initialize(SPHERE, true, DYNAMIC);
	debugSpherePhyiscs->gravityValue = 0;

	debugSpherePhyiscs->DoCollisionCall([this](PhysicsObject* other)
		{
			if (other->model->id =="Xwing")
			{

			}
			if (other->model->id == "SpaceShip")
			{
				std::cout << "Default sphere collided with spaceShip" << std::endl;
			
				glm::vec3 oppostireDirection = -Direction;
				Direction = oppostireDirection;
				state = DEFLECT;
				model->transform.SetOrientationTowardsDirection(oppostireDirection);

				/*glm::vec3 cameraForwad = model->transform.GetForward();

				glm::vec3 cameraright = glm::normalize(glm::cross(glm::vec3(0, 1, 0), cameraForwad));
				glm::vec3 cameraup = glm::normalize(glm::cross(cameraForwad, cameraright));

				camera->transform.SetOrientationFromDirections(cameraup, cameraright);*/
				camera->transform.SetOrientationTowardsDirection(oppostireDirection);

				debugSpherePhyiscs->collisionCallbool = false;
				debugSpherePhyiscs->collisionCallback = nullptr;

			}
		});

	engine->AddPhysicsObjects(debugSpherePhyiscs);
}

void Xwing::SetDebugSphereModel(Model* model)
{
	debugSphere = new Model(*model);
	debugSphere->isWireFrame = true;
	debugSphere->id = "XwingSphere";
	render->AddModelsAndShader(debugSphere, defaultshader);
}

void Xwing::Update(float deltaTime)
{
	if (state ==FOLLOW)
	{
		Direction = model->transform.GetForward();
	}
	

	xWingPhysics->velocity = Direction * speed;
	glm::vec3 forward = model->transform.GetForward() * debugSphereDistance;
	debugSphere->transform.SetPosition(model->transform.position + forward);
}

void Xwing::SetCamera(Camera* camera)
{
	this->camera = camera;
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
