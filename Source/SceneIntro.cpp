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

	//logo
	for (int k = 0; k < 15; k++)
	{
		logo.PushBack({ x + 258 * k, y , 256, 224 });
	}
    logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.PushBack({ x , y + 226 , 256, 224 });
	logo.loop = false;
	logo.speed = 0.15f;

    //intro
	for (int l = 1; l < 15; l++)
	{
		Intro.PushBack({ x + 258 * l, y + 226, 256, 224 });
	}
	for (int i = 2; i < 12; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Intro.PushBack({ x + 258 * j, y + 226 * i, 256, 224 });
		}
	}
	Intro.PushBack({ x, y + 226 * 12, 256, 224 });

	Intro.loop = false;
	Intro.speed = 0.085f;
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
	GamePad& pad = App->input->pads[0];
	if (logo.HasFinished()) {
		Intro.Update();
	}
	if (Intro.HasFinished()) {
		App->fade->FadeToBlack(this, (Module*)App->mainMenu, 90);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a)
	{
		App->fade->FadeToBlack(this, (Module*)App->mainMenu, 90);
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &(logo.GetCurrentFrame()), false, 0.85f);
	if (logo.HasFinished()) {
		App->render->Blit(bgTexture, 0, 0, &(Intro.GetCurrentFrame()), false, 0.85f);
	}
	return Update_Status::UPDATE_CONTINUE;
}