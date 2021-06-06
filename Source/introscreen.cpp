#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "introscreen.h"

#include <iostream>

ScreenIntro::ScreenIntro(bool startEnabled) : Module(startEnabled)
{
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.loop = false;
	black.speed = 0.05f;
}

ScreenIntro::~ScreenIntro()
{

}

// Load assets
bool ScreenIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/LOGO.png");
	bgTexture1 = App->textures->Load("Assets/Sprites/UPC.png");
	bgTexture2 = App->textures->Load("Assets/Sprites/CITM.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	titleFont = App->fonts->Load("Assets/Fonts/rtype_font.png", lookupTable, 1);
	namesFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status ScreenIntro::Update()
{
	GamePad& pad = App->input->pads[0];
	black.Update();
	if (black.HasFinished())
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	else if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ScreenIntro::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(bgTexture1, 240 , SCREEN_HEIGHT / 2 + 60, NULL);
	App->render->Blit(bgTexture2, 20, SCREEN_HEIGHT / 2 + 60, NULL);
	
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 - 100, titleFont, "project 1 ");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 164, SCREEN_HEIGHT / 2 - 85, namesFont, "we are recreating the game super soukoban");

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 - 50, titleFont, " teachers");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 35, namesFont, "ramon santamaria");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 45, SCREEN_HEIGHT / 2 - 20, namesFont, "jesus alonso");

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 76, SCREEN_HEIGHT / 2 + 5, titleFont, "upc universitat citm");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 + 20, namesFont, "video game design and development");

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 66, SCREEN_HEIGHT / 2 + 45, titleFont, "dreamteam members");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 34, SCREEN_HEIGHT / 2 + 60, namesFont, "hang xue");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 46, SCREEN_HEIGHT / 2 + 75, namesFont, "sofia liles");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 51, SCREEN_HEIGHT / 2 + 90, namesFont, "angel consola");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 49, SCREEN_HEIGHT / 2 + 105, namesFont, "marta llurba");
	
	return Update_Status::UPDATE_CONTINUE;
}