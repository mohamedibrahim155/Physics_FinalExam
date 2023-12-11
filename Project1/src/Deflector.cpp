#include "Deflector.h"
#include "xWingManager.h"
Deflector::Deflector(GraphicsRender* render, Shader* shader, PhysicsEngine* engine)
{
	this->render = render;
	this->defaultshader = shader;
	this->engine = engine;
}

Deflector::~Deflector()
{
}

Deflector::Deflector()
{
}

void Deflector::LoadDeflector(Model* _model, const glm::vec3& Startposition)
{
	model = new Model(*_model);
	if (isRight)
	{
		model->id = "DEFLECTOR_RIGHT";
	}
	else
	{
		model->id = "DEFLECTOR_LEFT";
	}
	model->transform.SetPosition(glm::vec3(Startposition));
	this->model->transform.SetScale(glm::vec3(1.2f));
	render->AddModelsAndShader(model, defaultshader);


	DeflectorPhysics = new PhysicsObject(model);

	DeflectorPhysics->Initialize(SPHERE, true, STATIC);
	DeflectorPhysics->gravityValue = 0;

	DeflectorPhysics->DoCollisionCall([this](PhysicsObject* other)
		{
			if (other->model->id == "BULLET")
			{

				std::cout << "Bullet hits in deflector" << std::endl;
				glm::vec3 collisionPoint = engine->collisionPoints[0];
				
				
				//XWingManager::GetInstance().SpawnSphere(collisionPoint);

			}
		});

	engine->AddPhysicsObjects(DeflectorPhysics);
}

void Deflector::StartPosition(const glm::vec3& Startposition)
{
	this->starPosition = Startposition;
}

void Deflector::LoadDeflector()
{
}

void Deflector::SetSide(bool isRight)
{
	this->isRight = isRight;
}
