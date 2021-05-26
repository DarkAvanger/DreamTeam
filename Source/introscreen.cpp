#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "introscreen.h"

#include <iostream>

ScreenIntro::ScreenIntro(bool startEnabled) : Module(startEnabled)
{

}

ScreenIntro::~ScreenIntro()
{

}

// Load assets
bool ScreenIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/introscreen.png");
	//App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status ScreenIntro::Update()
{
	logo.Update();
	
	
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 220);
	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ScreenIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &logosprite, false, 0.85f);
	//App->render->Blit(bgTexture, 0, 0, &(logo.GetCurrentFrame()), false, 0.85f);
	return Update_Status::UPDATE_CONTINUE;
}