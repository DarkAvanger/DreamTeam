#include "SceneLevel2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Box.h"
#include "Target.h"

#include <iostream>

Box* box2[3] = { nullptr };
Target* targets2[3] = { nullptr };

SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{
	block = { 96,34,30,30 };
	wall = { 0, 34, 30, 30 };
	floor = { 32, 34, 30, 30 };
	destination = { 64, 34, 30, 30 };
	wallwithshadow = { 96, 1, 30, 30 };
	boxondestination = { 32,3,30,30 };
}

SceneLevel2::~SceneLevel2()
{

}
bool SceneLevel2::Start()
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

	box2[0] = new Box({ 90,90 }, App->collisions->AddCollider({ 90,90,30,30 }, Collider::Type::BOX_CENTER));
	box2[1] = new Box({ 120,90}, App->collisions->AddCollider({ 120,90,30,30 }, Collider::Type::BOX_CENTER));
	box2[2] = new Box({ 90,120 }, App->collisions->AddCollider({ 90,120,30,30 }, Collider::Type::BOX_CENTER));

	targets2[0] = new Target({ 240,120,30,30 });
	targets2[1] = new Target({ 240,150,30,30 });
	targets2[2] = new Target({ 240,180,30,30 });

	for (int i = 0; i < 3; i++) {
		box2[i]->Start();
	}
	return ret;
}
Update_Status SceneLevel2::PreUpdate()
{
	for (int i = 0; i < 3; i++)
	{
		box2[i]->PreUpdate();
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel2::Update()
{
	App->render->camera.x += 0;

	completeCount = 0;
	for (int i = 0; i < 3; i++)
	{
		box2[i]->Update();

		if (targets2[i]->isComplete)
		{
			completeCount++;
		}
	}
	//printf("%d\n", completeCount);
	return Update_Status::UPDATE_CONTINUE;
}
// Update: draw background
Update_Status SceneLevel2::PostUpdate()
{
	for (int i = 0; i < 3; i++)
	{
		box2[i]->PostUpdate();
		targets2[i]->PostUpdate();
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
		App->render->Blit(bgTexture, box2[i]->boxPosition.x, box2[i]->boxPosition.y, box2[i]->getRenderRect());
	}
	if (completeCount == 3) {
		App->render->Blit(winTexture, 110, 100, NULL);
	}
	return Update_Status::UPDATE_CONTINUE;
}
bool SceneLevel2::CleanUp()
{
	App->player->Disable();

	// Clean boxs & targets
	for (int i = 0; i < 3; i++)
	{
		if (box2[i] != nullptr)
		{
			delete box2[i];
			box2[i] = nullptr;
		}
		if (targets2[i] != nullptr)
		{
			delete targets2[i];
			targets2[i] = nullptr;
		}
	}

	return true;
}
void SceneLevel2::OnCollision(Collider* c1, Collider* c2) {
	for (int i = 0; i < 3; i++)
	{
		if (box2[i] != nullptr) {
			if (c1 == box2[i]->colliderBox ||
				c1 == box2[i]->colliderBoxUp ||
				c1 == box2[i]->colliderBoxDown ||
				c1 == box2[i]->colliderBoxLeft ||
				c1 == box2[i]->colliderBoxRight)
			{
				box2[i]->OnCollision(c1, c2);
			}
		}
		if (targets2[i] != nullptr) {
			if (c1 == targets2[i]->col)
			{
				targets2[i]->OnCollision(c2);
			}
		}
	}
}
