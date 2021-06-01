#include "MainMenu.h"  

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include <iostream>

MainMenu::MainMenu(bool startEnabled) : Module(startEnabled)
{

}

MainMenu::~MainMenu()
{

}

// Load assets
bool MainMenu::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//title 
	bgTexture = App->textures->Load("Assets/Sprites/main_menu_title.png");
	Pointer = App->textures->Load("Assets/Sprites/main_menu_selector.png");
	scroller = App->textures->Load("Assets/Sprites/main_menu_scroller.png");
	scroller2 = App->textures->Load("Assets/Sprites/main_menu_scroller.png");
	menu_box = App->textures->Load("Assets/Sprites/main_menu.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	p_pos.x = p_x;
	p_pos.y = p_y;

	char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	menuFont = App->fonts->Load("Assets/Fonts/rtype_font.png", lookupTable, 1);

	// music and fx
	titleMenuMusic = App->audio->PlayMusic("Assets/Music/Title Screen.ogg", 1.0f);
	selectFx = App->audio->LoadFx("Assets/FX/choose.wav");
	nextFx = App->audio->LoadFx("Assets/FX/press.wav");
	backFx = App->audio->LoadFx("Assets/FX/menu3_back.wav");

	return ret;
}

Update_Status MainMenu::Update()
{
	scrollerY -= 1;
	scroller2Y -= 1;

	if (scrollerY < -1036) {
		scrollerY = 1034;
	}
	if (scroller2Y < -1036) {
		scroller2Y = 1034;
	}
	//key commands 
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN) {
		if (M_Index < 2)
		{
			M_Index++;
			p_y -= 13;
			App->audio->PlayFx(selectFx);
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN) {
		if (M_Index > 0)
		{
			M_Index--;
			p_y += 13;
			App->audio->PlayFx(selectFx);
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

	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);

	}
	if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);

	}
	if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_3, 90);

	}
	if (App->input->keys[SDL_SCANCODE_4] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_4, 90);

	}
	if (App->input->keys[SDL_SCANCODE_5] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_5, 90);

	}
	if (App->input->keys[SDL_SCANCODE_6] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_6, 90);

	}
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) {		// ESC to close the game
		return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
}



// Update: draw background
Update_Status MainMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(scroller, 0, scrollerY, NULL);
	App->render->Blit(scroller2, 0, scroller2Y, NULL);
	App->render->Blit(menu_box, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 25, NULL);


	App->render->Blit(bgTexture, SCREEN_WIDTH / 2 - 115, SCREEN_HEIGHT / 2 - 120, NULL);
	App->render->Blit(Pointer, p_x, p_y, NULL);

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 20, 150, menuFont, "play game");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 20, 162, menuFont, "coop mode");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 20, 174, menuFont, "level edit");


	return Update_Status::UPDATE_CONTINUE;
}