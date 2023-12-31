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

    bulletModel = new Model("Models/Exam_Models/TearDropBullet.ply");

    defaultSphere = new Model("Models/DefaultSphere/Sphere_1_unit_Radius.ply");

    deflector1 = new Deflector(this->render, defaultshader, this->engine);
    deflector1->SetSide(false);
    deflector1->LoadDeflector(defaultSphere, glm::vec3(5.25f, 12.5f, 27.8f));     // left 

    deflector2 = new Deflector(this->render, defaultshader, this->engine);
    deflector1->SetSide(true);
    deflector2->LoadDeflector(defaultSphere, glm::vec3(-5.25f, 12.5f, 27.8f));    // right
}

XWingManager::~XWingManager()
{
}

void XWingManager::SetRenderers(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera)
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

    bulletModel = new Model("Models/Exam_Models/TearDropBullet.ply");

    defaultSphere = new Model("Models/DefaultSphere/Sphere_1_unit_Radius.ply");

    deflector1 = new Deflector(this->render, defaultshader, this->engine);
    deflector1->SetSide(true);
    deflector1->LoadDeflector(defaultSphere, glm::vec3(5.25f, 12.5f, 27.8f));     // right

    deflector2 = new Deflector(this->render, defaultshader, this->engine);
    deflector1->SetSide(false);
    deflector2->LoadDeflector(defaultSphere, glm::vec3(-5.25f, 12.5f, 27.8f));    // left  
}

void XWingManager::SpawnXwing()
{
    if (isGameOver)
    {
        return;
    }
	Model* pointA = new Model(*Point1);
	Model* pointB = new Model(*Point2);

  

      glm::vec3 SpaceShipCenter = GetRandomPoint1();
     glm::vec3 SpaceShipCenter2 = GetRandomPoint2();


    pointA->transform.SetPosition(SpaceShipCenter);
    pointB->transform.SetPosition(SpaceShipCenter2);

    std::cout << " POINT A: X: " << pointA->transform.position.x << " Y: " << pointA->transform.position.y << " Z: " << pointA->transform.position.z << std::endl;
    std::cout << " POINT B: X: " << pointB->transform.position.x << " Y: " << pointB->transform.position.y << " Z: " << pointB->transform.position.z << std::endl;

    render->AddModelsAndShader(pointA, defaultshader);
    render->AddModelsAndShader(pointB, defaultshader);


	newXwing = new Xwing(render, defaultshader, engine);
    newXwing->StartPosition = pointA->transform.position;
    newXwing->EndPosition = pointB->transform.position;
    newXwing->SetCamera(camera);
    newXwing->SetDebugSphereModel(Point1);


	newXwing->LoadModel(XwingModel, xwingTexture);
    
	xwingList.push_back(newXwing);

    currentCameraLookingTransform = newXwing->model;  // CurrentModel
    newXwing->model->transform.SetPosition(newXwing->StartPosition);

    glm::vec3 forward = glm::normalize(pointB->transform.position - newXwing->model->transform.position);
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
    glm::vec3 up = glm::normalize(glm::cross(forward, right));

    newXwing->model->transform.SetOrientationFromDirections(up, right);

    glm::vec3 cameraForwad = newXwing->model->transform.GetForward();
    glm::vec3 cameraright = glm::normalize(glm::cross(glm::vec3(0, 1, 0), cameraForwad));
    glm::vec3 cameraup = glm::normalize(glm::cross(cameraForwad, cameraright));

    camera->transform.SetOrientationFromDirections(cameraup, cameraright);

    


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

void XWingManager::SpawnXwing2()
{
    if (isGameOver)
    {
        return;
    }

    Model* pointA = new Model(*Point1);
    Model* pointB = new Model(*Point2);

    int getRandomNum = GetRandomIntNumber(0, 2);
    bool isRight = getRandomNum == 0 ? true : false;

    glm::vec3 center = isRight ? glm::vec3(5.25f, 12.5f, 27.8f) : glm::vec3(-5.25f, 12.5f, 27.8f);

    glm::vec3 randomDir = GetRandomDirection();


    glm::vec3 getOpposite = -randomDir;
    randomDir = (randomDir * 40.0f + center);
    getOpposite = (getOpposite * 40.0f + center);

    glm::vec3 SpaceShipCenter = randomDir;
    glm::vec3 SpaceShipCenter2 = getOpposite;

    pointA->transform.SetPosition(SpaceShipCenter);
    pointB->transform.SetPosition(SpaceShipCenter2);

    std::cout << " POINT A: X: " << pointA->transform.position.x << " Y: " << pointA->transform.position.y << " Z: " << pointA->transform.position.z << std::endl;
    std::cout << " POINT B: X: " << pointB->transform.position.x << " Y: " << pointB->transform.position.y << " Z: " << pointB->transform.position.z << std::endl;

    render->AddModelsAndShader(pointA, defaultshader);
    render->AddModelsAndShader(pointB, defaultshader);


    newXwing = new Xwing(render, defaultshader, engine);
    newXwing->StartPosition = pointA->transform.position;
    newXwing->EndPosition = pointB->transform.position;
    newXwing->SetCamera(camera);
    newXwing->SetDebugSphereModel(Point1);


    newXwing->LoadModel(XwingModel, xwingTexture);

    xwingList.push_back(newXwing);

    currentCameraLookingTransform = newXwing->model;  // CurrentModel
    newXwing->model->transform.SetPosition(newXwing->StartPosition);

    glm::vec3 forward = glm::normalize(pointB->transform.position - newXwing->model->transform.position);
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
    glm::vec3 up = glm::normalize(glm::cross(forward, right));

    newXwing->model->transform.SetOrientationFromDirections(up, right);

    glm::vec3 cameraForwad = newXwing->model->transform.GetForward();
    glm::vec3 cameraright = glm::normalize(glm::cross(glm::vec3(0, 1, 0), cameraForwad));
    glm::vec3 cameraup = glm::normalize(glm::cross(cameraForwad, cameraright));

    camera->transform.SetOrientationFromDirections(cameraup, cameraright);




    float distance = glm::distance(SpaceShipCenter, SpaceShipCenter2);
    float stepSize = 2;
    int breakdowns = static_cast<int>(distance / stepSize);

    glm::vec3 direction = glm::normalize(SpaceShipCenter2 - SpaceShipCenter);

    for (int i = 0; i <= breakdowns; ++i) {
        Model* model = new Model(*render->defaultBox);
        model->transform.position = SpaceShipCenter + (static_cast<float>(i) / breakdowns) * distance * direction;
        model->transform.scale = glm::vec3(0.05f);

        render->AddModelsAndShader(model, defaultshader);

        // DebugLineModels.push_back(model);
    }
}

void XWingManager::SpawnSphere(const glm::vec3 spawnPosition)
{
    Model* sphere = new Model(*defaultSphere);

    sphere->id = "DEBUG_SPHERE";
    sphere->transform.SetPosition(spawnPosition);
    sphere->transform.SetScale(glm::vec3(0.5f));

    render->AddModelsAndShader(sphere, defaultshader);
}

void XWingManager::Removexwing(Xwing* xwing)
{
	std::vector<Xwing*> ::iterator it = std::find(xwingList.begin(), xwingList.end(), xwing);
	if (it != xwingList.end()) // if exists
	{
		xwingList.erase(it);
	}
}

void XWingManager::SpawnBullet(const glm::vec3 startPosition, const glm::vec3 direction)
{
    bullet = new Bullet(render, defaultshader, engine);
    bullet->SetSpawnposition(startPosition);
    bullet->SetDirection(direction);
    bullet->LoadBullet(bulletModel);
    //bullet->LoadBullet();

    bulletList.push_back(bullet);
}

void XWingManager::RemoveBullet(Bullet* bullet)
{
    engine->RemovePhysicsObject(bullet->BulletPhysics);
    render->RemoveModels(bullet->model);

    std::vector<Bullet*>::iterator it = std::find(bulletList.begin(), bulletList.end(), bullet);
    if (it != bulletList.end())
    {
        bulletList.erase(it);
    }

}


void XWingManager::RemoveXWING(Xwing* xWing)
{
    engine->RemovePhysicsObject(xWing->debugSpherePhyiscs);
    engine->RemovePhysicsObject(xWing->xWingPhysics);
    render->RemoveModels(xWing->model);

    std::vector<Xwing*>::iterator it = std::find(xwingList.begin(), xwingList.end(), xWing);
    if (it != xwingList.end())
    {
        xwingList.erase(it);
      
    }
    //delete xWing;
}

void XWingManager::SetSpaceShip(SpaceShip* spaceshipEntity)
{
    this->spaceshipEntity = spaceshipEntity;
}

void XWingManager::ReduceHealth(bool isRight)
{
    if (isRight)
    {

        TotalhealthRight -= 25;
        if (TotalhealthRight < 0)
        {
            TotalhealthRight = 0;
        }
        std::cout << " TOTAL HEALTH RIGHT : " << TotalhealthRight << std::endl;
    }
    else
    {
        TotalhealthLeft -= 25;

        if (TotalhealthLeft <= 0)
        {
            TotalhealthLeft = 0;
        }
        std::cout << " TOTAL HEALTH LEFT : " << TotalhealthLeft << std::endl;
    }


    if (TotalhealthLeft == 0 && TotalhealthRight == 0)
    {
        isGameOver = true;
    }
}

void XWingManager::Update(float deltaTime)
{
    if (IsGameOverState())
    {
        std::cout << "GAME OVER :" << std::endl;
        return;
    }
    for (size_t i = 0; i < xwingList.size(); i++)
    {
        xwingList[i]->Update(deltaTime);

        if (xwingList[i]->IsDestroy())
        {
            RemoveXWING(xwingList[i]);
        }
    }

    for (size_t i = 0; i < bulletList.size(); i++)
    {
        bulletList[i]->Update(deltaTime);

        if (bulletList[i]->IsDestroyed())
        {
            RemoveBullet(bulletList[i]);
        }
    }

     
    glm::vec3 backward = -currentCameraLookingTransform->transform.GetForward() * 5.0f;
    camera->transform.SetPosition(currentCameraLookingTransform->transform.position + backward + glm::vec3(0, 1, 0));
}

bool XWingManager::IsGameOverState()
{
    if (isGameOver)
    {
        return true;
    }
    else
    {
        return false;
    }
   
}

XWingManager& XWingManager::GetInstance()
{
    
    static XWingManager instance;
    return instance;
}
