#include "xWingManager.h"
#include "Random.h"

XWingManager::XWingManager()
{
}

XWingManager::XWingManager(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;
    this->camera = &camera;

	XwingModel = new Model("Models/Exam_Models/X-Wing/X-Wing_Attack_xyz_n_uv.ply", true);

	xwingTexture = new Texture();
	xwingTexture->LoadTexture("Models/Exam_Models/X-Wing/X-Wing-Texture.jpg", "diffuse_Texture");

	Point1 = new Model("Models/DefaultSphere/Sphere_1_unit_Radius.ply");
	Point2 = new Model("Models/DefaultSphere/Sphere_1_unit_Radius.ply");
}

XWingManager::~XWingManager()
{
}

void XWingManager::SpawnXwing()
{
	Model* pointA = new Model(*Point1);
	Model* pointB = new Model(*Point2);

    cAABB  spaceShipAABB = spaceshipEntity->SpaceShipPhysics->UpdateAABB();
    glm::vec3 center = 0.5f * (spaceShipAABB.minV + spaceShipAABB.maxV);

    float minX = spaceShipAABB.minV.x - 20;
    float minY = spaceShipAABB.minV.y - 20;
    float minZ = spaceShipAABB.minV.z - 20;

    float centerX = center.x;

    float maxX = spaceShipAABB.maxV.x + 20;
    float maxY = spaceShipAABB.maxV.y + 20;
    float maxZ = spaceShipAABB.maxV.z + 20;

    float getRandomNegX = GetRandomFloatNumber(minX, spaceShipAABB.minV.x);
    float getRandomNegY = GetRandomFloatNumber(minY, spaceShipAABB.minV.y);
    float getRandomNegZ = GetRandomFloatNumber(minZ, spaceShipAABB.minV.z);


    float getRandomPosX = GetRandomFloatNumber(spaceShipAABB.maxV.x, maxX);
    float getRandomPosY = GetRandomFloatNumber(spaceShipAABB.maxV.y, maxY);
    float getRandomPosZ = GetRandomFloatNumber(spaceShipAABB.maxV.z, maxZ);

    glm::vec3 randomDir = GetRandomDirection();

    glm::vec3 getOpposite = -randomDir;
    randomDir = (randomDir + center) * 40.0f;
    getOpposite = (getOpposite + center) * 40.0f;

    glm::vec3 offset(spaceShipAABB.minV);
    // glm::vec3 SpaceShipCenter = center + offset;
    // glm::vec3 SpaceShipCenter = center + glm::vec3(getRandomNegX, getRandomNegY, getRandomNegZ);
    // glm::vec3 SpaceShipCenter2 = center + glm::vec3(getRandomPosX, getRandomPosY, getRandomPosZ);

    glm::vec3 SpaceShipCenter = randomDir;
    glm::vec3 SpaceShipCenter2 = getOpposite;
    //  glm::vec3 SpaceShipCenter = GetRandomPoint1();
  //   glm::vec3 SpaceShipCenter2 = GetRandomPoint2();


    pointA->transform.SetPosition(SpaceShipCenter);
    pointB->transform.SetPosition(SpaceShipCenter2);

    std::cout << " POINT A: X: " << pointA->transform.position.x << " Y: " << pointA->transform.position.y << " Z: " << pointA->transform.position.z << std::endl;
    std::cout << " POINT B: X: " << pointB->transform.position.x << " Y: " << pointB->transform.position.y << " Z: " << pointB->transform.position.z << std::endl;

    render->AddModelsAndShader(pointA, defaultshader);
    render->AddModelsAndShader(pointB, defaultshader);


	Xwing* newXwing = new Xwing(render, defaultshader, engine);

    newXwing->SetDebugSphereModel(Point1);


	newXwing->LoadModel(XwingModel, xwingTexture);
    newXwing->StartPosition = pointA->transform.position;
    newXwing->EndPosition = pointB->transform.position;
	xwingList.push_back(newXwing);


    newXwing->model->transform.SetPosition(newXwing->StartPosition);

    glm::vec3 forward = glm::normalize(pointB->transform.position - newXwing->model->transform.position);
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
    glm::vec3 up = glm::normalize(glm::cross(forward, right));

    newXwing->model->transform.SetOrientationFromDirections(up, right);

    glm::vec3 cameraForwad = newXwing->model->transform.GetForward();
    glm::vec3 cameraright = glm::normalize(glm::cross(glm::vec3(0, 1, 0), cameraForwad));
    glm::vec3 cameraup = glm::normalize(glm::cross(cameraForwad, cameraright));

    camera->transform.SetOrientationFromDirections(cameraup, cameraright);

    currentCameraLookingTransform = newXwing->model;  // CurrentModel


    float distance = glm::distance(SpaceShipCenter, SpaceShipCenter2);
    float stepSize = 2;
    int breakdowns = static_cast<int>(distance / stepSize);

    glm::vec3 direction = glm::normalize(SpaceShipCenter2 - SpaceShipCenter);

    for (int i = 0; i <= breakdowns; ++i) {
        Model* model = new Model(*render->defaultBox);
        model->transform.position = SpaceShipCenter + (static_cast<float>(i) / breakdowns) * distance * direction;
        model->transform.scale = glm::vec3(0.1);

        render->AddModelsAndShader(model, defaultshader);

       // DebugLineModels.push_back(model);
    }
}

void XWingManager::Removexwing(Xwing* xwing)
{
	std::vector<Xwing*> ::iterator it = std::find(xwingList.begin(), xwingList.end(), xwing);
	if (it != xwingList.end()) // if exists
	{
		xwingList.erase(it);
	}
}

void XWingManager::SetSpaceShip(SpaceShip* spaceshipEntity)
{
    this->spaceshipEntity = spaceshipEntity;
}

void XWingManager::Update(float deltaTime)
{
    for (size_t i = 0; i < xwingList.size(); i++)
    {
        xwingList[i]->Update(deltaTime);
    }

   

     
    glm::vec3 backward = -currentCameraLookingTransform->transform.GetForward() * 5.0f;
    camera->transform.SetPosition(currentCameraLookingTransform->transform.position + backward + glm::vec3(0, 1, 0));
}
