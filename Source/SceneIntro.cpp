#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include <iostream>

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	int x = 2;
	int y = 2;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			logo.PushBack({ x + 258 * j, y + 226 * i, 256, 224 });
		}
	}
	logo.PushBack({ x, y + 226 * 12, 256, 224 });

	logo.loop = false;
	logo.speed = 0.08f;
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/IntroAnimation.png");
	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	logo.Update();
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(bgTexture, 0, 0, &(logo.GetCurrentFrame()), false, 0.85f);
	return Update_Status::UPDATE_CONTINUE;
}