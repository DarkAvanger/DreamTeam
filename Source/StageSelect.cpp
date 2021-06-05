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
	levelsBoard = App->textures->Load("Assets/Sprites/game_menu_levels.png");
	levelOption = App->textures->Load("Assets/Sprites/game_menu_options.png");
	levelTitle = App->textures->Load("Assets/Sprites/game_menu_title.png");
	debugBorad = App->textures->Load("Assets/Sprites/level_menu.png");
	leftBorad = App->textures->Load("Assets/Sprites/game_menu_left.png");
	rightBorad = App->textures->Load("Assets/Sprites/game_menu_right.png");
	numberBorad = App->textures->Load("Assets/Sprites/game_menu_number.png");

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	menuFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	pointerPosX = 73;
	pointerPosY = 152;

	display = false;

	// music and fx
	stageSelectMusic = App->audio->PlayMusic("Assets/Music/Stage Select.ogg", 1.0f);
	selectFx = App->audio->LoadFx("Assets/FX/choose.wav");
	nextFx = App->audio->LoadFx("Assets/FX/press.wav");
	backFx = App->audio->LoadFx("Assets/FX/menu3_back.wav");

	return ret;
}

Update_Status StageSelect::Update()
{
	GamePad& pad = App->input->pads[0];
	if (display == false) {
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || pad.down || pad.left_y > 0.0f)
		{
			if (pointerPosY == 38) {
				pointerPosY = 58;
				pointerPosX = 102;
				App->audio->PlayFx(selectFx);
			}
			else if (pointerPosY == 58) {
				pointerPosY = 152;
				pointerPosX = 73;
				App->audio->PlayFx(selectFx);
			}
		}
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN || pad.up || pad.left_y < 0.0f)
		{
			if (pointerPosY == 152) {
				pointerPosY = 58;
				pointerPosX = 102;
				App->audio->PlayFx(selectFx);
			}
			else if (pointerPosY == 58) {
				pointerPosY = 38;
				pointerPosX = 102;
				App->audio->PlayFx(selectFx);
			}
		}
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.left || pad.left_x < 0.0f)
		{
			if (pointerPosY == 152 && pointerPosX > 73) {
				pointerPosX = pointerPosX - 16;
				App->audio->PlayFx(selectFx);
			}
		}
		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.right || pad.left_x > 0.0f)
		{
			if (pointerPosY == 152 && pointerPosX < 153) {
				pointerPosX = pointerPosX + 16;
				App->audio->PlayFx(selectFx);
			}
		}
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a) {

			// controls
			if (pointerPosY == 30) {
				App->audio->PlayFx(nextFx);
				display = true;
			}
			// exit
			if (pointerPosY == 50) {
				App->audio->PlayFx(backFx);
				App->fade->FadeToBlack(this, (Module*)App->mainMenu, 60);
			}
			// 1
			if (pointerPosX == 105 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 60);
			}
			// 2
			if (pointerPosX == 121 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 60);
			}
			// 3
			if (pointerPosX == 137 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_3, 60);
			}
			// 4
			if (pointerPosX == 153 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_4, 60);
			}
			// 5
			if (pointerPosX == 169 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_5, 60);
			}
			// 6
			if (pointerPosX == 185 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->sceneLevel_6, 60);
			}

		}
	}
	if (display == true) {
		if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN || pad.a) {
			display = false;
			App->audio->PlayFx(backFx);
		}
	}
	

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN || pad.back) {		// ESC to close the game
		App->fade->FadeToBlack(this, (Module*)App->mainMenu, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status StageSelect::PostUpdate()
{
	// Draw everything --------------------------------------
	if (display == false) {
		App->render->Blit(bgTexture, 0, 0, NULL);
		App->render->Blit(levelsBoard, 84, 150, NULL);
		App->render->Blit(numberBorad, 90, 246, NULL);
		App->render->Blit(leftBorad, 6, 95, NULL);
		App->render->Blit(rightBorad, 253, 95, NULL);
		App->render->Blit(levelTitle, 92, 106, NULL);
		App->render->Blit(levelOption, 94, 25, NULL);
		App->render->Blit(Pointer, pointerPosX, pointerPosY, NULL);

		App->fonts->BlitText(115, 112, menuFont, "select stage");
		App->fonts->BlitText(120, 60, menuFont, "game controls");
		App->fonts->BlitText(120, 40, menuFont, "back to menu");
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool StageSelect::CleanUp() {
	pointerPosX = 130;
	pointerPosY = 110;
	display = false;
	return true;
}