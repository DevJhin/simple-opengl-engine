#include "GameScene.h"
#include "AArcBall.h"
#include "Animator.h"
#include "Resources.h"

/*
 * Called When scene is loaded.
 */

struct Level
{
	int level;
	float speedMult;
	float startTime;

	Level(int level, float speedMult, float startTime): level(level),speedMult(speedMult), startTime(startTime)
	{
	}
};



Animation* CreateAnimation(Level level) {

    Animation* animation = new Animation();

	float totalKeyCnt = 90;
	float lifeTime = 0;
	animation->AddKey(Vector3(0, 10, 0), Vector3(0, 0, 0), 0);

	
	for(int i=1;i<totalKeyCnt-1;i++)
	{
		
		float timeInterval = Random::randomRange(1.0f, 2.0f) * level.speedMult;
		

		
		lifeTime += timeInterval;

		Vector3 pos = Random::randomRange(Vector3(-10, -10, 0), Vector3(10, 10, 0));
		Vector3 rot = Random::randomRange(Vector3(-180, -180, -180), Vector3(180, 180, 180));
		animation->AddKey(pos, rot, lifeTime);
		
	}
	lifeTime += 2.0f;
	animation->AddKey(Vector3(0, -10, 0), Vector3(0,0,0), lifeTime);
	animation->playTime = lifeTime;
	animation->ComputeTangents();
	return animation;
}

AObstacle* InitObstacle(APlayer* player, Level level)
{
	Animation* obstacleAnim = CreateAnimation(level);
	
	//Create original cube(Textured).
	AObstacle* obstacle = new AObstacle();
	obstacle->player = player;
	obstacle->lifeTime = obstacleAnim->playTime;
	obstacle->tag = "Obstacle";
	obstacle->GetTransform().SetPosition(Vector3(3, 3, 0));
	obstacle->startTime = level.startTime;
	
	Renderer* obstacleRenderer = obstacle->AddComponent<Renderer>();
	Animator* obstacleAnimator = obstacle->AddComponent<Animator>();
	obstacle->animator = obstacleAnimator;
	
	obstacleAnimator->animation = obstacleAnim;
	
	Shader* obstacleShader = Shader::Find("Standard_Spec");
	Material* obstacleMaterial = new Material(obstacleShader);
	Texture* texture = Resources::LoadTexture("InClass09/metal.png");
	
	obstacleMaterial->Use();
	obstacleMaterial->SetVec4("mainColor", Vector4(1, 1, 0, 1));
	obstacleMaterial->GetTextures().push_back(texture);

	obstacleRenderer->material = obstacleMaterial;
	obstacleRenderer->mesh = Resources::GetPrimitiveCubeMesh();

	return obstacle;
}

void InitStage()
{
	List<AObstacle*> obstacles;
	
}



APlayer* InitPlayer()
{
	//Create original cube(Textured).
	APlayer* playerActor = new APlayer();
	playerActor->tag = "Player";
	playerActor->GetTransform().SetPosition(Vector3(0, 0, 0));
	playerActor->speed = 10;
	Renderer* playerRenderer = playerActor->AddComponent<Renderer>();
	Animator* playerAnimator = playerActor->AddComponent<Animator>();

	playerActor->GetTransform().SetScale(Vector3(0.1f, 0.1f, 0.1f));
	playerActor->GetTransform().Rotate(Vec3Math::RIGHT, 90);
	Shader* playerShader = Shader::Find("Standard_Spec");
	Material* playerMaterial = new Material(playerShader);
	Texture* texture = Resources::LoadTexture("player/diffuse.jpg");
	Texture* texture2 = Resources::LoadTexture("player/specular.jpg");
	playerMaterial->Use();
	playerMaterial->SetVec4("mainColor", Vector4(1, 0, 0, 1));
	playerMaterial->GetTextures().push_back(texture);
	playerMaterial->GetTextures().push_back(texture);
	
	ModelData* modelData = Resources::LoadModel("player/SciFi_Fighter.obj");

	playerActor->renderer = playerRenderer;
	playerRenderer->material = playerMaterial;
	playerRenderer->mesh = modelData->mesh;

	
	return playerActor;
}

Material* environMaterial = nullptr;

Actor* InitEnvironment()
{
	Actor* environActor = new Actor();
	
	environActor->tag = "environ";
	environActor->GetTransform().SetPosition(Vector3(0, 0, -20));
	Renderer* environRenderer = environActor->AddComponent<Renderer>();

	environActor->GetTransform().SetScale(Vector3(0.03f, 0.03f, -0.03f));
	environActor->GetTransform().Rotate(Vec3Math::RIGHT, 90);
	Shader* environShader = Shader::Find("Standard_Spec");
	if(environMaterial == nullptr){
		environMaterial = new Material(environShader);
		Texture* texture = Resources::LoadTexture("environ/diffuse.jpg");
		Texture* texture2 = Resources::LoadTexture("environ/specular.jpg");
		texture->name = "material.diffuse";
		texture2->name = "material.specular";
		environMaterial->Use();
		environMaterial->GetTextures().push_back(texture);
		environMaterial->GetTextures().push_back(texture2);
		environMaterial->SetTexture(texture->name, *texture);
		environMaterial->SetTexture(texture2->name, *texture2);
	}
	

	ModelData* modelData = Resources::LoadModel("environ/Corvette-F3.obj");

	environRenderer->material = environMaterial;
	environRenderer->mesh = modelData->mesh;


	return environActor;
}

Actor* InitBar(float y, Vector4 color)
{
	Actor* barActor = new Actor();

	barActor->tag = "bar";
	barActor->GetTransform().SetPosition(Vector3(0, y, 6));
	Renderer* barRenderer = barActor->AddComponent<Renderer>();

	barActor->GetTransform().SetScale(Vector3(5, 0.3f, 1));

	Shader* barShader = Shader::Find("Unlit");
	Material* barMaterial = new Material(barShader);

	barMaterial->Use();
	barMaterial->SetVec4("mainColor", color);

	barRenderer->material = barMaterial;
	barRenderer->mesh = Resources::GetPrimitiveCubeMesh();


	return barActor;
	
}



void GameScene::LoadSceneObjects()
{
	Actor* environment1 = InitEnvironment();
	Actor* environment2 = InitEnvironment();
	AddSceneObject(environment1);
	AddSceneObject(environment2);
	
	APlayer* player = InitPlayer();
	
	player->MAX_PLAY_TIME = 85;
	player->MAX_LIFE = 5;

	player->environment1 = &environment1->GetTransform();
	player->environment2 = &environment2->GetTransform();
	
	AddSceneObject(player);

	Level level1(1, 1.0f, 5);
	AObstacle* obstacle = InitObstacle(player, level1);
	
	AddSceneObject(obstacle);


	Level level2(2, 0.9f, 25);
	AObstacle* obstacle2 = InitObstacle(player, level2);

	AddSceneObject(obstacle2);


	Level level3(3, 0.85f, 50);
	AObstacle* obstacle3 = InitObstacle(player, level3);
	AddSceneObject(obstacle3);

	Level level4(4, 0.75f, 70);
	AObstacle* obstacle4 = InitObstacle(player, level4);
	AddSceneObject(obstacle4);

	
	//Create Directional Light.
	Actor* directionalLightActor = new Actor();
	directionalLightActor->GetTransform().SetRotation(QuatMath::euler(Vector3(-90,0,30)));
	
	//Add Light Component
	Light* directionalLight = directionalLightActor->AddComponent<Light>();
	directionalLight->lightMode = LightMode::Directional;
	directionalLight->intensity = 1.1f;
	directionalLight->color = Vector3(0.8, 0.8, 1);

	Light* pointLight = directionalLightActor->AddComponent<Light>();
	pointLight->lightMode = LightMode::Point;
	pointLight->transform->SetPosition(Vector3(0,0,-18.0f));
	pointLight->intensity = 0.8f;
	pointLight->color = Vector3(0.9, 0.4, 0.2);
	pointLight->range = 10.0f;
	

	Camera* cam = World::GetInstance()->camera;
	cam->GetTransform().SetPosition(Vector3(0,0,15));

	Actor* lifeBar = InitBar(-4.0, Vector4(1, 0, 0, 1));
	Actor* timeBar = InitBar(-4.5, Vector4(1, 1, 1, 1));

	player->timeBar = timeBar;
	player->lifeBar = lifeBar;
	player->directionalLight = directionalLight;
	
	AddSceneObject(timeBar);
	AddSceneObject(lifeBar);
	
	AddSceneObject(directionalLightActor);
}



