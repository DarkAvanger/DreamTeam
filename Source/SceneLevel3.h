#ifndef __SCENE_LEVEL3_H__
#define __SCENE_LEVEL3_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class SceneLevel3 : public Module
{
public:
	//Constructor
	SceneLevel3(bool startEnabled);

	//Destructor
	~SceneLevel3();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2) override;
public:
	//0-block,1-wall,2-box,3-floor,4-destination,5-wallwithshadow,6-player,7-boxondestination
	int map[10][11] = {
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,5,5,5,5,5,1,0,0},
		{0,0,1,3,3,4,4,4,1,0,0},
		{0,0,1,3,3,3,5,5,5,1,0},
		{0,1,5,5,3,3,3,3,3,1,0},
		{0,1,3,3,3,1,3,5,3,1,0},
		{0,1,3,3,3,1,3,3,3,1,0},
		{0,1,3,3,3,1,5,5,5,5,0},
		{0,5,5,5,5,5,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0}
	};
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	// The scoreboard loaded into an SDL_Texture
	SDL_Texture* scoreTexture = nullptr;
	// The winningboard loaded into an SDL_Texture
	SDL_Texture* winTexture = nullptr;
	// The sprite rectangle for the block
	SDL_Rect block;

	// The sprite rectangle for the wall
	SDL_Rect wall;

	// The sprite rectangle for the floor
	SDL_Rect floor;

	// The sprite rectangle for the destination
	SDL_Rect destination;

	// The sprite rectangle for the wallwithshadow
	SDL_Rect wallwithshadow;

	// The sprite rectangle for the boxondestination
	SDL_Rect boxondestination;

	int completeCount = 0;
	int score = 0;
};

#endif