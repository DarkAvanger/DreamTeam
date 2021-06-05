#ifndef __STAGE_SELECT_H__  // ADRIAN: .H DE TITLESCREEN
#define __STAGE_SELECT__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class StageSelect : public Module
{
public:

	StageSelect(bool startEnabled);

	~StageSelect();

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
	SDL_Texture* Pointer = nullptr;

	int p_x = SCREEN_WIDTH / 2 - 45;
	int p_y = SCREEN_HEIGHT / 2 + 30;

	SDL_Rect p_pos;

	//The intro animation
	Animation intro;

	//Menu Buttons
	const int B_Play = 2;
	const int B_Coop = 1;
	const int B_Edit = 0;

	int M_Index = 2;

	// Music and FX
	uint stageSelectMusic = 0;
	uint selectFx = 0;
	uint nextFx = 0;
	uint backFx = 0;
};

#endif