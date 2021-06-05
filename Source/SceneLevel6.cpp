#include "SceneLevel6.h"

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

Box* box6[5] = { nullptr };
Target* targets6[5] = { nullptr };

SceneLevel6::SceneLevel6(bool startEnabled) : Module(startEnabled)
{
	block = { 96,34,30,30 };
	wall = { 0, 34, 30, 30 };
	floor = { 32, 34, 30, 30 };
	destination = { 64, 34, 30, 30 };
	wallwithshadow = { 96, 1, 30, 30 };
	boxondestination = { 32,3,30,30 };
}

SceneLevel6::~SceneLevel6()
{

}
bool SceneLevel6::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Scenario.png");
	winTexture = App->textures->Load("Assets/Sprites/win.png");
	loseTexture = App->textures->Load("Assets/Sprites/lose.png");
	App->audio->PlayMusic("Assets/Music/Hard Labor.ogg", 1.0f);

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

	App->player->stage = 06;
	App->player->limit = 60;
	App->player->steps = 0;

	App->player->Enable();

	App->player->position.x = 210;
	App->player->position.y = 120;

	box6[0] = new Box({ 120,90 }, App->collisions->AddCollider({ 120,90,30,30 }, Collider::Type::BOX_CENTER), this);
	box6[1] = new Box({ 90,120 }, App->collisions->AddCollider({ 90,120,30,30 }, Collider::Type::BOX_CENTER), this);
	box6[2] = new Box({ 150,120 }, App->collisions->AddCollider({ 150,120,30,30 }, Collider::Type::BOX_CENTER), this);
	box6[3] = new Box({ 120,150 }, App->collisions->AddCollider({ 120,150,30,30 }, Collider::Type::BOX_CENTER), this);
	box6[4] = new Box({ 180,150 }, App->collisions->AddCollider({ 180,150,30,30 }, Collider::Type::BOX_CENTER), this);

	targets6[0] = new Target({ 60,90,30,30 }, this);
	targets6[1] = new Target({ 30,120,30,30 }, this);
	targets6[2] = new Target({ 60,120,30,30 }, this);
	targets6[3] = new Target({ 30,150,30,30 }, this);
	targets6[4] = new Target({ 60,150,30,30 }, this);

	for (int i = 0; i < 5; i++) {
		box6[i]->Start();
	}
	return ret;
}
Update_Status SceneLevel6::PreUpdate()
{
	for (int i = 0; i < 5; i++)
	{
		box6[i]->PreUpdate();
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel6::Update()
{
	App->render->camera.x += 0;
	GamePad& pad = App->input->pads[0];

	if (App->player->steps == App->player->limit || dLose == true)
	{
		for (int i = 0; i < 4; i++) {
			App->player->canMoveDir[i] = false;
		}
	}
	if (completeCount == 5 || dWin == true)
	{
		for (int i = 0; i < 4; i++) {
			App->player->canMoveDir[i] = false;
		}
	}

	completeCount = 0;
	for (int i = 0; i < 5; i++)
	{
		box6[i]->Update();

		if (targets6[i]->isComplete)
		{
			completeCount++;
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a)
	{
		dWin = false;
		dLose = false;
		App->fade->FadeToBlack(this, (Module*)App->mainMenu, 90);
	}
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN || pad.back) {		// ESC to return to menu
		App->fade->FadeToBlack(this, (Module*)App->mainMenu, 90);
	}
	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN && dWin == false)
	{
		dWin = true;
	}
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN && dLose == false)
	{
		dLose = true;
	}
	if (App->input->keys[SDL_SCANCODE_R] == Key_State::KEY_DOWN || pad.b)	// Restart the level
	{
		dWin = false;
		dLose = false;
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_6, 90);
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel6::PostUpdate()
{
	for (int i = 0; i < 5; i++)
	{
		box6[i]->PostUpdate();
		targets6[i]->PostUpdate();
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

	for (int i = 0; i < 5; i++) {
		App->render->Blit(bgTexture, box6[i]->boxPosition.x, box6[i]->boxPosition.y, box6[i]->getRenderRect());
	}

	if (App->player->steps == App->player->limit || dLose == true)
	{	// dLose= f3 direct loose

		App->render->Blit(loseTexture, 110, 100, NULL);
		if (loseF != true)
		{
			if (playingmusic)
			{
				App->audio->PlayMusic("Assets/Music/Failure.ogg", 0);
				playingmusic = false;
			}
			loseF = true;
		}
		//CleanUp();
	}
	if (completeCount == 5 || dWin == true) // dWin= F3 direct win
	{
		if (winF != true) {
			if (playingmusic) {
				App->audio->PlayMusic("Assets/Music/StageComplete.ogg", 0);
				playingmusic = false;
			}
			winF = true;
		}
		App->render->Blit(winTexture, 110, 100, NULL);
		LOG("level 6 completed");
		//CleanUp();
		//if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)	// go to the next level when winning
		//{
		//	//App->audio->PlayFx(nextFx);
		//	App->fade->FadeToBlack(this, (Module*)App->mainMenu, 90);
		//}
	}
	return Update_Status::UPDATE_CONTINUE;
}
bool SceneLevel6::CleanUp()
{
	App->player->Disable();

	// Clean boxs & targets
	for (int i = 0; i < 5; i++)
	{
		if (box6[i] != nullptr)
		{
			delete box6[i];
			box6[i] = nullptr;
		}
		if (targets6[i] != nullptr)
		{
			delete targets6[i];
			targets6[i] = nullptr;
		}
	}
	App->collisions->CleanUp();

	return true;
}
void SceneLevel6::OnCollision(Collider* c1, Collider* c2) {
	for (int i = 0; i < 5; i++)
	{
		if (box6[i] != nullptr) {
			if (c1 == box6[i]->colliderBox ||
				c1 == box6[i]->colliderBoxUp ||
				c1 == box6[i]->colliderBoxDown ||
				c1 == box6[i]->colliderBoxLeft ||
				c1 == box6[i]->colliderBoxRight)
			{
				box6[i]->OnCollision(c1, c2);
			}
		}
		if (targets6[i] != nullptr) {
			if (c1 == targets6[i]->col)
			{
				targets6[i]->OnCollision(c2);
			}
		}
	}
}
