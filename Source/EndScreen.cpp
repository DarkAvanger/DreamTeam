#include "EndScreen.h"  

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include <iostream>

EndScreen::EndScreen(bool startEnabled) : Module(startEnabled)
{

}

EndScreen::~EndScreen()
{

}

// Load assets
bool EndScreen::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//title 
	bgTexture = App->textures->Load("Assets/Sprites/main_menu_title.png");
	scroller = App->textures->Load("Assets/Sprites/main_menu_scroller.png");
	scroller2 = App->textures->Load("Assets/Sprites/main_menu_scroller.png");
	menu_box = App->textures->Load("Assets/Sprites/main_menu.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	menuFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);


	// music and fx
	titleMenuMusic = App->audio->PlayMusic("Assets/Music/End Screen.ogg", 1.0f);
	nextFx = App->audio->LoadFx("Assets/FX/press.wav");

	return ret;
}

Update_Status EndScreen::Update()
{
	GamePad& pad = App->input->pads[0];

	scrollerY -= 1;
	scroller2Y -= 1;

	if (scrollerY < -1036) {
		scrollerY = 1034;
	}
	if (scroller2Y < -1036) {
		scroller2Y = 1034;
	}
	//key commands 
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a)
	{
		App->audio->PlayFx(nextFx);
		App->fade->FadeToBlack(this, (Module*)App->screenIntro, 90);
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN || pad.back) {		// ESC to close the game
		return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
}


// Update: draw background
Update_Status EndScreen::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(scroller, 0, scrollerY, NULL);
	App->render->Blit(scroller2, 0, scroller2Y, NULL);
	App->render->Blit(menu_box, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 25, NULL);

	App->render->Blit(bgTexture, SCREEN_WIDTH / 2 - 115, SCREEN_HEIGHT / 2 - 120, NULL);

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 45, SCREEN_HEIGHT / 2 + 33, menuFont, "space<restart");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 26, SCREEN_HEIGHT / 2 + 46, menuFont, "esc<exit");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 22, SCREEN_HEIGHT / 2 + 59, menuFont, "thanks!");

	return Update_Status::UPDATE_CONTINUE;
}