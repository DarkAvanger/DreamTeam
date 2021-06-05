#include "StageSelect.h"  

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include <iostream>

StageSelect::StageSelect(bool startEnabled) : Module(startEnabled)
{

}

StageSelect::~StageSelect()
{

}

// Load assets
bool StageSelect::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//title 
	bgTexture = App->textures->Load("Assets/Sprites/select screen.png");
	Pointer = App->textures->Load("Assets/Sprites/main_menu_selector.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	p_pos.x = p_x;
	p_pos.y = p_y;

	// music and fx
	stageSelectMusic = App->audio->PlayMusic("Assets/Music/Stage Select.ogg", 1.0f);
	selectFx = App->audio->LoadFx("Assets/FX/choose.wav");
	nextFx = App->audio->LoadFx("Assets/FX/press.wav");
	backFx = App->audio->LoadFx("Assets/FX/menu3_back.wav");

	return ret;
}

Update_Status StageSelect::Update()
{
	//key commands 
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) {
		if (M_Index < 2)
		{
			App->audio->PlayFx(selectFx);
			M_Index++;
			p_y -= 13;
		}
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN) {
		if (M_Index > 0)
		{
			App->audio->PlayFx(selectFx);
			M_Index--;
			p_y += 13;
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		if (M_Index == B_Play)
		{
			App->audio->PlayFx(nextFx);
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
		}
		else {
			App->audio->PlayFx(backFx);
		}
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) {		// ESC to close the game
		App->fade->FadeToBlack(this, (Module*)App->mainMenu, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status StageSelect::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL, false, 0.0f, false);
	App->render->Blit(Pointer, p_x, p_y, NULL);

	return Update_Status::UPDATE_CONTINUE;
}