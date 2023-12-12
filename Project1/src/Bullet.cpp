#include "Bullet.h"
#include "xWingManager.h"
Bullet::Bullet()
{
}

Bullet::Bullet(GraphicsRender* render, Shader* shader, PhysicsEngine* engine)
{
	this->render = render;
	this->defaultshader = shader;
	this->engine = engine;
}

Bullet::~Bullet()
{
}

void Bullet::LoadBullet(Model* _model)
{
	model = new Model(*_model);
	model->id = "BULLET";
	model->transform.SetPosition(glm::vec3(starPosition));
	this->model->transform.SetScale(glm::vec3(0.1f));

	this->model->transform.SetOrientationTowardsDirection(Direction);
	render->AddModelsAndShader(model, defaultshader);


	BulletPhysics = new PhysicsObject(model);

	BulletPhysics->Initialize(SPHERE, true, DYNAMIC);
	BulletPhysics->gravityValue = 0;

	BulletPhysics->DoCollisionCall([this](PhysicsObject* other)
		{
			if (other->model->id == "DEFLECTOR_RIGHT")
			{
				std::cout << "Bullet hit Deflector left side" << std::endl;
				glm::vec3 collisionPoint = engine->collisionPoints[0];

				// REDUCE HEALTH
				XWingManager::GetInstance().ReduceHealth(true);
				BulletPhysics->collisionCallback = nullptr;
				BulletPhysics->collisionCallbool = false;
				isDestroyed = true;
				model->isVisible = false;

				BulletPhysics->mode = STATIC;

			}
			if (other->model->id == "DEFLECTOR_LEFT")
			{
				std::cout << "Bullet hit Deflector Right side" << std::endl;
				glm::vec3 collisionPoint = engine->collisionPoints[0];

				// REDUCE HEALTH
				XWingManager::GetInstance().ReduceHealth(false);

				BulletPhysics->collisionCallback = nullptr;
				BulletPhysics->collisionCallbool = false;
				isDestroyed = true;
				model->isVisible = false;

				BulletPhysics->mode = STATIC;
			}
			if (other->model->id =="SPACESHIP")
			{
				
				std::cout << "Bullet hit SpaceShip" << std::endl;
				glm::vec3 collisionPoint = engine->collisionPoints[0];
				XWingManager::GetInstance().SpawnSphere(collisionPoint);

				BulletPhysics->collisionCallback = nullptr;
				BulletPhysics->collisionCallbool = false;
				isDestroyed = true;
				model->isVisible = false;

				BulletPhysics->mode = STATIC;
			}

			
		});

	engine->AddPhysicsObjects(BulletPhysics);
}

void Bullet::LoadBullet()
{
	this->model = new Model("Models/Exam_Models/TearDropBullet.ply");
	this->model->id = "BULLET";
	this->model->transform.SetPosition(glm::vec3(starPosition));
	this->model->transform.SetScale(glm::vec3(0.1f));
	this->model->transform.SetOrientationTowardsDirection(Direction);

	render->AddModelsAndShader(model, defaultshader);


	BulletPhysics = new PhysicsObject(model);

	BulletPhysics->Initialize(AABB, true, DYNAMIC);
	BulletPhysics->gravityValue = 0;
	BulletPhysics->bounciness = 0;

	BulletPhysics->DoCollisionCall([this](PhysicsObject* other)
		{
			if (other->model->id == "SPACESHIP")
			{
				std::cout << "Bullet hit SpaceShip" << std::endl;

				isDestroyed = true;
				BulletPhysics->collisionCallback = nullptr;
				BulletPhysics->collisionCallbool = false;
			}
		});

	engine->AddPhysicsObjects(BulletPhysics);
}
void Bullet::SetSpawnposition(const glm::vec3& Startposition)
{
	this->starPosition = Startposition;
}

void Bullet::SetDirection(const glm::vec3& direction)
{
	this->Direction = direction;
}

void Bullet::Update(float deltaTime)
{
	if (isDestroyed)
	{
		return;
	}
	glm::vec3 forawrd = -model->transform.GetForward();
	BulletPhysics->velocity = forawrd * speed;
}

