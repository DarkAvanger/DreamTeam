#include "SceneLevel5.h"

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

Box* box5[3] = { nullptr };
Target* targets5[3] = { nullptr };

SceneLevel5::SceneLevel5(bool startEnabled) : Module(startEnabled)
{
	block = { 96,34,30,30 };
	wall = { 0, 34, 30, 30 };
	floor = { 32, 34, 30, 30 };
	destination = { 64, 34, 30, 30 };
	wallwithshadow = { 96, 1, 30, 30 };
	boxondestination = { 32,3,30,30 };
}

SceneLevel5::~SceneLevel5()
{

}
bool SceneLevel5::Start()
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

	App->player->position.x = 120;
	App->player->position.y = 90;

	box5[0] = new Box({ 120,90 }, App->collisions->AddCollider({ 120,90,30,30 }, Collider::Type::BOX_CENTER), this);
	box5[1] = new Box({ 90,180 }, App->collisions->AddCollider({ 90,180,30,30 }, Collider::Type::BOX_CENTER), this);
	box5[2] = new Box({ 180,210 }, App->collisions->AddCollider({ 180,210,30,30 }, Collider::Type::BOX_CENTER), this);

	targets5[0] = new Target({ 60,150,30,30 }, this);
	targets5[1] = new Target({ 60,180,30,30 }, this);
	targets5[2] = new Target({ 60,210,30,30 }, this);

	for (int i = 0; i < 3; i++) {
		box5[i]->Start();
	}
	return ret;
}
Update_Status SceneLevel5::PreUpdate()
{
	for (int i = 0; i < 3; i++)
	{
		box5[i]->PreUpdate();
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel5::Update()
{
	App->render->camera.x += 0;

	completeCount = 0;
	for (int i = 0; i < 3; i++)
	{
		box5[i]->Update();

		if (targets5[i]->isComplete)
		{
			completeCount++;
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	//printf("%d\n", completeCount);
	return Update_Status::UPDATE_CONTINUE;
}
// Update: draw background
Update_Status SceneLevel5::PostUpdate()
{
	for (int i = 0; i < 3; i++)
	{
		box5[i]->PostUpdate();
		targets5[i]->PostUpdate();
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
		App->render->Blit(bgTexture, box5[i]->boxPosition.x, box5[i]->boxPosition.y, box5[i]->getRenderRect());
	}
	if (completeCount == 3) {
		App->render->Blit(winTexture, 110, 100, NULL);
	}
	return Update_Status::UPDATE_CONTINUE;
}
bool SceneLevel5::CleanUp()
{
	App->player->Disable();

	// Clean boxs & targets
	for (int i = 0; i < 3; i++)
	{
		if (box5[i] != nullptr)
		{
			delete box5[i];
			box5[i] = nullptr;
		}
		if (targets5[i] != nullptr)
		{
			delete targets5[i];
			targets5[i] = nullptr;
		}
	}
	App->collisions->CleanUp();

	return true;
}
void SceneLevel5::OnCollision(Collider* c1, Collider* c2) {
	for (int i = 0; i < 3; i++)
	{
		if (box5[i] != nullptr) {
			if (c1 == box5[i]->colliderBox ||
				c1 == box5[i]->colliderBoxUp ||
				c1 == box5[i]->colliderBoxDown ||
				c1 == box5[i]->colliderBoxLeft ||
				c1 == box5[i]->colliderBoxRight)
			{
				box5[i]->OnCollision(c1, c2);
			}
		}
		if (targets5[i] != nullptr) {
			if (c1 == targets5[i]->col)
			{
				targets5[i]->OnCollision(c2);
			}
		}
	}
}
