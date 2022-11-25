#include "cprocessing.h"
#include <stdlib.h>
#include <math.h>
#include "game.h"

void CreateEnemy(float x, float y) {
	endPoint->enemyCount++;
	GameObject* goEnemy = GetGameObject();
	goEnemy->hasCollider = TRUE;
	goEnemy->type = Type_Enemy;
	goEnemy->pos = CP_Vector_Set(x, y);
	goEnemy->size = CP_Vector_Set(50.f, 50.f);
	goEnemy->color = CP_Color_Create(100, 100, 100, 0);
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	if (enemy) {
		enemy->vel = CP_Vector_Set(100, 0);
		enemy->dir = CP_Vector_Set(1, 0);
		enemy->bt = 0.f;
		goEnemy->childData = enemy;
	}
}

void UpdateEnemyProj(GameObject* self) {
	float speedScale = 2.f;
	Projectile* proj = self->childData;
	self->pos.x += proj->dir.x * proj->speed * speedScale * CP_System_GetDt();
	proj->range += proj->dir.x * proj->speed * speedScale * CP_System_GetDt();

	if (fabs(proj->range) >= proj->maxRange) {
		proj->range = 0.f;
		DespawnGameObject(self);
	}
}

void EnemyShoot(GameObject* _enemy) {
	Enemy* enemy = (Enemy*)_enemy->childData;
	GameObject* enemyProj = GetGameObject();
	enemyProj->hasCollider = TRUE;
	enemyProj->size = CP_Vector_Set(20.f, 20.f);
	enemyProj->color = ENEMY_COLOR;
	enemyProj->type = Type_EnemyProj;
	Projectile* proj = (Projectile*)malloc(sizeof(Projectile));
	if (proj) {
		proj->maxRange = 600.f;
		proj->range = 0.f;
		proj->speed = 500.f;
		proj->goProj = enemyProj;
		proj->dir = enemy->dir;
	}
	if (enemy->dir.x > 0)
		enemyProj->pos = CP_Vector_Add(_enemy->pos, CP_Vector_Set(_enemy->size.x + 10.f, 10.f));
	else
		enemyProj->pos = CP_Vector_Add(_enemy->pos, CP_Vector_Set(-10.f, 10.f));
	enemyProj->childData = proj;
}

void UpdateEnemy(GameObject* self) {
	Enemy* e = (Enemy*)self->childData;
	e->vel.y += gravity * CP_System_GetDt();

	self->pos.y += e->vel.y * CP_System_GetDt();
	self->pos.x += e->dir.x * e->vel.x * CP_System_GetDt();

	// Shooting
	if (e->bt >= .5f) {
		e->bt = 0.f;
		EnemyShoot(self);
	}
	e->bt += CP_System_GetDt();
}
