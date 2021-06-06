#ifndef __END_SCREEN_H__  // ADRIAN: .H DE TITLESCREEN
#define __END_SCREEN_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class EndScreen : public Module
{
public:

	EndScreen(bool startEnabled);

	~EndScreen();

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
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* menu_box = nullptr;
	SDL_Texture* scroller = nullptr;
	SDL_Texture* scroller2 = nullptr;
	int scrollerY = 0;
	int scroller2Y = 1036;

	// Font index
	int menuFont = -1;

	// Music and FX
	uint titleMenuMusic = 0;
	uint nextFx = 0;
};

#endif