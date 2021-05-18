#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Box.h"
#include "Target.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"

#include <iostream>

Box* box1[3] = { nullptr };
Target* targets1[3] = { nullptr };

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{
	block = { 96,34,30,30 };
	wall = { 0, 34, 30, 30 };
	floor = { 32, 34, 30, 30 };
	destination = { 64, 34, 30, 30 };
	wallwithshadow = { 96, 1, 30, 30 };
	boxondestination = { 32,3,30,30 };
}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Scenario.png");
	scoreTexture = App->textures->Load("Assets/Sprites/scoreboard.png");
	winTexture = App->textures->Load("Assets/Sprites/win.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	for (int i = 0, y = 0; i < 10; i++) {
		for (int j = 0, x = 0; j < 11; j++, x += 30) {
			if (map[i][j] == 1) {
				App->collisions->AddCollider({ 30 * j, 30 * i, 30 , 30 }, Collider::Type::WALL);
			}
			else if (map[i][j] == 5) {
				App->collisions->AddCollider({ 30 * j, 30 * i, 30 , 30 }, Collider::Type::WALL);
			}
		}
	}

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();

	box1[0] = new Box({ 120,120 }, App->collisions->AddCollider({ 120,120,30,30}, Collider::Type::BOX_CENTER));
	box1[1] = new Box({ 90,180 }, App->collisions->AddCollider({ 90,180,30,30 }, Collider::Type::BOX_CENTER));
	box1[2] = new Box({ 180,150 }, App->collisions->AddCollider({ 180,150,30,30 }, Collider::Type::BOX_CENTER));

	targets1[0] = new Target({ 150,60,30,30 });
	targets1[1] = new Target({ 180,60,30,30 });
	targets1[2] = new Target({ 210,60,30,30 });

	for (int i = 0; i < 3; i++) {
		box1[i]->Start();
	}
	return ret;
}

Update_Status SceneLevel1::PreUpdate()
{
	for (int i = 0; i < 3; i++) 
	{
		box1[i]->PreUpdate();
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.x += 0;

	completeCount = 0;
	for (int i = 0; i < 3; i++)
	{
		box1[i]->Update();

		if (targets1[i]->isComplete)
		{
			completeCount++;
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
	}
	//printf("%d\n", completeCount);
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	for (int i = 0; i < 3; i++) 
	{
		box1[i]->PostUpdate();
		targets1[i]->PostUpdate();
	}
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	for (int i = 0, y = 0; i < 10; i++) {
		for (int j = 0, x = 0; j < 11; j++, x += 30) {
			if (map[i][j] == 0) {
				App->render->Blit(bgTexture, x, y, &block, 0.75f);
			}
			else if (map[i][j] == 1) {
				App->render->Blit(bgTexture, x, y, &wall, 0.75f);
			}
			else if (map[i][j] == 3) {
				App->render->Blit(bgTexture, x, y, &floor, 0.75f);
			}
			else if (map[i][j] == 4) {
				App->render->Blit(bgTexture, x, y, &destination, 0.75f);
			}
			else if (map[i][j] == 5) {
				App->render->Blit(bgTexture, x, y, &wallwithshadow, 0.75f);
			}
			else if (map[i][j] == 7) {
				App->render->Blit(bgTexture, x, y, &boxondestination, 0.75f);
			}
		}
		y += 30;
	}
	App->render->Blit(scoreTexture, 220, 30, NULL);

	for (int i = 0; i < 3; i++) {
		App->render->Blit(bgTexture, box1[i]->boxPosition.x, box1[i]->boxPosition.y, box1[i]->getRenderRect());
	}
	if (completeCount == 3) {
		App->render->Blit(winTexture, 110, 100, NULL);
		//App->audio->StopMusic();
		//App->audio->CleanUp();
		//App->audio->Init();
		//App->audio->PlayMusic("Assets/Music/StageComplete.ogg", 1.0f);
	}
	return Update_Status::UPDATE_CONTINUE;
}
bool SceneLevel1::CleanUp()
{
	App->player->Disable();

	// Clean boxs & targets
	for (int i = 0; i < 3; i++)
	{
		if (box1[i] != nullptr)
		{
			delete box1[i];
			box1[i] = nullptr;
		}
		if(targets1[i] != nullptr)
		{
			delete targets1[i];
			targets1[i] = nullptr;
		}
	}
	App->collisions->CleanUp();
	return true;
}
void SceneLevel1::OnCollision(Collider* c1, Collider* c2) {
	for (int i = 0; i < 3; i++)
	{
		if (box1[i] != nullptr) {
			if (c1 == box1[i]->colliderBox ||
				c1 == box1[i]->colliderBoxUp ||
				c1 == box1[i]->colliderBoxDown ||
				c1 == box1[i]->colliderBoxLeft ||
				c1 == box1[i]->colliderBoxRight)
			{
				box1[i]->OnCollision(c1, c2);
			}
		}
		if (targets1[i] != nullptr) {
			if (c1 == targets1[i]->col)
			{
				targets1[i]->OnCollision(c2);
			}
		}
	}
}



