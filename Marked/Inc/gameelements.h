#pragma once
struct GameObject;

GameObject* GetGameObject();
void DespawnGameObject(GameObject* go);

//Create Platform
void CreateGameElement(CP_BOOL collider, enum GAMEOBJECT_TYPE type, CP_Vector pos, CP_Vector size, CP_Color color);
void CreateButtonDoorLink(CP_Vector buttonPos, CP_Vector doorPos, int type);
void UpdateDoor(GameObject* self);

void CreateDummy(float x, float y);
void UpdateDummy(GameObject* self);

void InitEndPoint(float x, float y);
void UpdateEndPoint(GameObject* self);

void CreateLaser(float x, float y, float width, float height, float velx, float vely, float time);
void UpdateLaser(GameObject* self);

void SideScrolling(GameObject* self);