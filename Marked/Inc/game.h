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

typedef struct Enemy {
	CP_Vector vel;
	CP_Vector dir;
	float speed;
	GameObject* goEnemy;

	float bt; //time between bullets
} Enemy;

typedef struct Dummy {

	CP_Vector vel;
} Dummy;

typedef struct Player {
	CP_Vector vel;
	CP_Vector dir;
	float speed;
	GameObject* goPlayer;
	GameObject* markedObject;

} Player;

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


typedef struct Door {
	CP_BOOL isOpened;
} Door;

typedef struct Button {
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
void DespawnGameObject(GameObject* go);
GameObject* InitGoPtr();
void FreeGoPtr(GameObject* goPtr);

void CollisionResponse(GameObject* go, GameObject* go2);
CP_BOOL CheckCollision(GameObject* go, GameObject* go2);

void SideScrolling(GameObject* self);

void RestartPressed();
void QuitPressed();

void ManageCollision();