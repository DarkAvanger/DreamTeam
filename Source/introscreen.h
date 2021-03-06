#ifndef __SCREEN_INTRO_H__
#define __SCREEN_INTRO_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ScreenIntro : public Module
{
public:
	//Constructor
	ScreenIntro(bool startEnabled);

	//Destructor
	~ScreenIntro();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:
	//iPoint logoposition;
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* bgTexture1 = nullptr;
	SDL_Texture* bgTexture2 = nullptr;
	SDL_Texture* bgTexture3 = nullptr;
	/*Animation* currentAnimation = nullptr;

	Animation logo;

	SDL_Rect logosprite = { 0,0,270,240 };*/
	//Background animation
	Animation black;

	// Font credits index 
	uint title = 000;
	int titleFont = -1;
	char titleText[10] = { "\0" };

	// Font names index 
	uint names = 000;
	int namesFont = -1;
	char namesText[10] = { "\0" };
};

#endif