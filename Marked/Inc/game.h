#pragma once
#define FALSE 0
#define TRUE 1
#define GOARRAY_SIZE 500
#define PLATFORM_COLOR CP_Color_Create(0, 0, 0, 255)
#define OBSTACLE_COLOR CP_Color_Create(128, 0, 0, 50)
#define ENEMY_COLOR CP_Color_Create(100, 100, 100, 255)

int windowWidth, windowHeight;
float const gravity;
CP_BOOL isGrounded;
CP_BOOL rightPressed;
CP_BOOL leftPressed;
CP_BOOL shootPressed;
CP_BOOL isPlatformCollided;
CP_BOOL isGameOver;

enum GAMEOBJECT_TYPE {
	Type_Player,
	Type_Proj,
	Type_Enemy,
	Type_EnemyProj,
	Type_Dummy,
	Type_Barrel,
	Type_Explosion,
	Type_Button,
	Type_Door,
	Type_Platform,
	Type_Obstacle,
	Type_EndPoint,
	Type_Laser,
	Type_Info,
	Type_Info2,
	Type_None
};

typedef struct GameObject {

	CP_BOOL isActive;

	CP_Vector pos;
	CP_Vector size;
	CP_Color color;

	void* childData;

	CP_BOOL hasCollider;

	enum GAMEOBJECT_TYPE type;

} GameObject;


typedef struct Player {
	CP_Vector vel;
	CP_Vector dir;
	float speed;
	GameObject* goPlayer;
	GameObject* markedObject;

} Player;

typedef struct Enemy {
	CP_Vector vel;
	CP_Vector dir;
	float speed;
	//GameObject* goPlatform;
	GameObject* goEnemy;

	float bt; //time between bullets
} Enemy;

typedef struct Dummy {

	CP_Vector vel;
} Dummy;
typedef struct Projectile {
	CP_Vector vel;
	CP_Vector dir;
	float maxRange;
	float range;
	float speed;
	GameObject* goProj;
	CP_BOOL projAlive;

} Projectile;

typedef struct EndPoint {
	int enemyCount;
} EndPoint;

typedef struct Platform {
	CP_Vector vel;
	float speed;
} Platform;

typedef struct Barrel {
	CP_BOOL isExploded;

} Barrel;

typedef struct Door {
	CP_BOOL isOpened;

} Door;

typedef struct Button {
	//CP_BOOL isPushed;
	Door* linkedDoor;

} Button;

typedef struct Laser {
	CP_Vector vel;
	CP_Vector dir;
	float time;
	float timeMax;
	GameObject* goLaser;
} Laser;

GameObject* goPtr;
Player* player;
Projectile* projectile;
EndPoint* endPoint;

GameObject* GetGameObject();

void PlayerMovement();
void KeysPressed();

void DespawnGameObject(GameObject* go);

void CollisionResponse(GameObject* go, GameObject* go2);

CP_BOOL CheckCollision(GameObject* go, GameObject* go2);
	
void SetProjSpawn(float x, float y);

void UpdateDoor(GameObject* self);

void UpdateEndPoint(GameObject* self);

void UpdateEnemyProj(GameObject* self);

void EnemyShoot(GameObject* _enemy);

void UpdateLaser(GameObject* self);

void InitPlayer(float x, float y);

void InitEndPoint(float x, float y);

void InitPlayerProjectile();
//	CreateGameElement(TRUE, Type_Obstacle, CP_Vector_Set(1000.f, windowHeight * 0.8 + 10), CP_Vector_Set(100.f, 100.f), OBSTACLE_COLOR);
void CreateGameElement(CP_BOOL collider, enum GAMEOBJECT_TYPE type, CP_Vector pos, CP_Vector size, CP_Color color); 
		
#ifndef CREATE_CODE

void CreatePlatform(float x, float y, float width, float height);
void CreateLaser(float x, float y, float width, float height, float velx, float vely, float time);

void CreateEnemy(float x, float y);

void CreateDummy(float x, float y);
void CreateButtonDoorLink(CP_Vector buttonPos, CP_Vector doorPos);
#endif

void DrawGameElements(GameObject* self);

void UpdateProjectile(GameObject* self);
void UpdateDummy(GameObject* self);
void UpdateEnemy(GameObject* self);
	
void SideScrolling(GameObject* self);
void DisplayGameOver();
void RenderScene();
		

