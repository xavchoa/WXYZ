struct GameObject;

void InitPlayer(float x, float y);
void InitPlayerProjectile();
void UpdateProjectile(GameObject* self);
void PlayerMovement();
void KeysPressed();
void SwapPositions();