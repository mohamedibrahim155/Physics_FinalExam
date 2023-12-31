#include"SpaceShip.h"

#include "xWingManager.h"
SpaceShip::SpaceShip(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;
	this->camera = &camera;

	InputManager::GetInstance().AddListener(this);
}

SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip:: LoadModel()
{
	// ******************
	// Need to Revert 
	//model = new Model("Models/Exam_Models/Stardestroyer/Stardestroyer_CompleteModel_LayersJoined_xyz_n_uv.ply");
	
	model = new Model("Models/Exam_Models/Stardestroyer/Stardestroyer_CompleteModel_LayersJoined (decimate 10 per, 167,274 vert, 59,360 face).ply");
	model->id = "SPACESHIP";
	model->transform.SetPosition(glm::vec3(0));
	model->transform.SetScale(glm::vec3(0.05f));
	render->AddModelsAndShader(model, defaultshader);


	SpaceShipPhysics = new PhysicsObject(model);

	SpaceShipPhysics->Initialize(MESH_TRIANGLES, true, STATIC);
	SpaceShipPhysics->gravityValue =0;

	SpaceShipPhysics->DoCollisionCall([this](PhysicsObject* other)
		{
			glm::vec3 collisionNormal = engine->collisionNormals[0];
			glm::vec3 velocity = SpaceShipPhysics->velocity;

			
			float dotProduct = glm::dot(collisionNormal, velocity);

			
			if (dotProduct < 0.0f)
			{
				glm::vec3 velocityComponent = dotProduct * collisionNormal;
				SpaceShipPhysics->velocity = velocityComponent;
				std::cout << "Spaceship collided. Velocity clamped." << std::endl;
			}
		});

	engine->AddPhysicsObjects(SpaceShipPhysics);



	//PhysicsObject* deflector1Physics = new PhysicsObject(Deflector1Model);

	//deflector1Physics->Initialize(SPHERE, true, STATIC);
	//deflector1Physics->gravityValue = 0;

	//engine->AddPhysicsObjects(deflector1Physics);

	//PhysicsObject* deflector2Physics = new PhysicsObject(Deflector2Model);
	//deflector2Physics->Initialize(SPHERE, true, STATIC);
	//deflector2Physics->gravityValue = 0;

	//engine->AddPhysicsObjects(deflector2Physics);
}

void SpaceShip::Update(float deltaTime)
{

	//glm::vec3 forward = model->transform.GetForward();
	//camera->transform.SetPosition(model->transform.position + forward  *followDistance + glm::vec3(0, yoffset, 0));
	//DrawAABBCollision(SpaceShipPhysics);
	DrawDebugBvhNodeAABB(SpaceShipPhysics->BvhAABBTree->root);
}

void SpaceShip::DrawAABBCollision(PhysicsObject* physicsObject)
{
	if (!isDebugAAABDraw)
	{
		return;
	}
	std::vector<cAABB> collisionAABBs = physicsObject->GetCollisionAABBs();

	for (size_t i = 0; i < collisionAABBs.size(); i++)
	{
		modelAABB m_Aabb = GetGraphicsAabb(collisionAABBs[i]);
		render->DrawAABB(m_Aabb);
	}
}

void SpaceShip::SpaceShipInputs(GLFWwindow* window, float deltaTime)
{
	//if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	//{

	//	SpaceShipPhysics->velocity = -model->transform.GetForward() *speed;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	//{
	//	SpaceShipPhysics->velocity = model->transform.GetForward() * speed;
	//}
	//else   if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	//{
	//	SpaceShipPhysics->velocity = -model->transform.GetRight() * speed;
	//}
	//else  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	//{

	//	SpaceShipPhysics->velocity = model->transform.GetRight() * speed;
	//}
	//else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	//{
	//	//Direction = model->transform.GetUp();
	//	SpaceShipPhysics->velocity = model->transform.GetUp() * speed;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	//{
	//	//Direction = -model->transform.GetUp();

	//	SpaceShipPhysics->velocity = -model->transform.GetUp() * speed;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	//{
	//	
	//	SpaceShipPhysics->velocity = glm::vec3(0);
	//	
	//}
	

	
}

void SpaceShip::DrawDebugBvhNodeAABB(BvhNode* node)
{
	if (!isDebugAAABDraw)
	{
		return;
	}

	if (node == nullptr)
	{
		return;
	}
	//if (node->nodeIndex == recusiveCount)
	//{
	//    DrawDebugModelAABB(node->GetModelAABB());
	//   return;
	//}

	if (node->trianglesIndex.size() != 0)
	{
		modelAABB m_Aabb = GetGraphicsAabb(node->UpdateAABB());
		render->DrawAABB(m_Aabb);
	}

	if (node->leftChild == nullptr) return;

	DrawDebugBvhNodeAABB(node->leftChild);
	DrawDebugBvhNodeAABB(node->rightChild);


}

void SpaceShip::SetDeflectorModels(Model* deflector1, Model* deflector2)
{
	this->Deflector1Model = new Model(*deflector1);
	Deflector1Model->id = "DEFLECTOR";
	Deflector1Model->transform.SetPosition(glm::vec3(5.25f, 12.5f, 27.8f));
	Deflector1Model->transform.SetScale(glm::vec3(1.1f));
	render->AddModelsAndShader(Deflector1Model, defaultshader);


	this->Deflector2Model = new Model(*deflector2);
	Deflector2Model->id = "DEFLECTOR";
	Deflector2Model->transform.SetPosition(glm::vec3(-5.25f, 12.5f, 27.8f));
	Deflector2Model->transform.SetScale(glm::vec3(1.1f));
	render->AddModelsAndShader(Deflector2Model, defaultshader);
}

void SpaceShip::OnKeyPressed(const int& key)
{
	//if (key == GLFW_KEY_W)
	//{
	//	SpaceShipPhysics->velocity = -model->transform.GetForward() * speed;
	//}
	//else if(key == GLFW_KEY_S)
	//{
	//	SpaceShipPhysics->velocity = model->transform.GetForward() * speed;
	//}

	//else if (key == GLFW_KEY_D)
	//{
	//	SpaceShipPhysics->velocity = -model->transform.GetRight() * speed;
	//}

	//else if (key == GLFW_KEY_A)
	//{
	//	SpaceShipPhysics->velocity = model->transform.GetRight() * speed;
	//}
	//else if (key == GLFW_KEY_Q)
	//{
	//	SpaceShipPhysics->velocity = model->transform.GetUp() * speed;
	//}
	//else if (key == GLFW_KEY_E)
	//{
	//	SpaceShipPhysics->velocity = -model->transform.GetUp() * speed;
	//}


	//else if (key == GLFW_KEY_LEFT)  //LEFT
	//{
	//	model->transform.SetRotation(glm::vec3(model->transform.rotation.x, 
	//		model->transform.rotation.y + rotationAngle,
	//		model->transform.rotation.z));

	//}

	//else if (key == GLFW_KEY_RIGHT) //RIGHT
	//{
	//	model->transform.SetRotation(glm::vec3(model->transform.rotation.x,
	//		model->transform.rotation.y - rotationAngle,
	//		model->transform.rotation.z));

	//}
	//else if (key == GLFW_KEY_UP) //UP
	//{
	//	model->transform.SetRotation(glm::vec3(model->transform.rotation.x ,
	//		model->transform.rotation.y,
	//		model->transform.rotation.z - rotationAngle));

	//}
	//else if (key == GLFW_KEY_DOWN) //DOWN
	//{
	//	model->transform.SetRotation(glm::vec3(model->transform.rotation.x ,
	//		model->transform.rotation.y,
	//		model->transform.rotation.z + rotationAngle));

	//}

	//camera->transform.SetPosition(model->transform.position + model->transform.GetForward() * followDistance + glm::vec3(0, yoffset, 0));

    if (key == GLFW_KEY_0)
	{
		isDebugAAABDraw = !isDebugAAABDraw;
		std::cout << "0 Pressed.. " << std::endl;
	}
}

void SpaceShip::OnKeyReleased(const int& key)
{
}

void SpaceShip::OnKeyHeld(const int& key)
{
}
