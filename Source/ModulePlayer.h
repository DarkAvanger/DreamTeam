#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Box.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	int step = 0;
	iPoint moveDir = { 0,0 };
	int idleDir = 0;
	bool canMoveDir[4] = {true};
	// The speed in which we move the player (pixels per frame)
	int speed = 1;//30

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* scoretable = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;

	Animation upPushAnim;
	Animation downPushAnim;
	Animation leftPushAnim;
	Animation rightPushAnim;
    
	// The player's collider
	Collider* colliderPlayer = nullptr;
	Collider* colliderPlayerUp = nullptr;
	Collider* colliderPlayerDown = nullptr;
	Collider* colliderPlayerLeft = nullptr;
	Collider* colliderPlayerRight = nullptr;

	// Font score index
	uint steps = 0000;
	uint limit = 0000;
	uint stage = 0000;

	int scoreFont = -1;
	char stepText[10] = { "\0" };

	int limitFont = -1;
	char limitText[10] = { "\0" };

	int stageFont = -1;
	char stageText[10] = { "\0" };
};

#endif //!__MODULE_PLAYER_H__