#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"


#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 170, 131, 19, 31 });//left
	idleAnim.PushBack({ 5, 195, 13, 30 });//right
	idleAnim.PushBack({ 5, 69, 20, 29 });//up
	idleAnim.PushBack({ 5, 9, 20, 24 });//down
	// left move 
	leftAnim.PushBack({ 170, 131, 19, 31 });
	leftAnim.PushBack({ 145, 131, 21, 31 });
	leftAnim.PushBack({ 121, 132, 22, 31 });
	leftAnim.PushBack({ 100, 132, 19, 31 });
	leftAnim.PushBack({ 74, 130, 17, 31 });
	leftAnim.PushBack({ 50, 131, 15, 31 });
	leftAnim.PushBack({ 27, 132, 17, 30 });
	leftAnim.PushBack({ 4, 131, 17, 30 });
	leftAnim.loop = true;
	leftAnim.speed = 0.2f;

	// right move
	rightAnim.PushBack({ 5, 195, 13, 30 });
	rightAnim.PushBack({ 27, 196, 13, 29 });
	rightAnim.PushBack({ 49, 196, 15, 29 });
	rightAnim.PushBack({ 73, 197, 18, 28 });
	rightAnim.PushBack({ 99, 198, 18, 27 });
	rightAnim.PushBack({ 125, 196, 14, 29 });
	rightAnim.PushBack({ 148, 196, 16, 29 });
	rightAnim.PushBack({ 172, 197, 18, 28 });
	rightAnim.loop = true;
	rightAnim.speed = 0.2f;

	// move upwards
	upAnim.PushBack({ 5, 69, 20, 29 });
	upAnim.PushBack({ 28, 68, 20, 29 });
	upAnim.PushBack({ 49, 69, 20, 29 });
	upAnim.PushBack({ 74, 69, 20, 29 });
	upAnim.PushBack({ 97, 72, 20, 29 });
	upAnim.PushBack({ 121, 69, 20, 29 });
	upAnim.PushBack({ 145, 69, 20, 29 });
	upAnim.PushBack({ 169, 70, 20, 29 });
    upAnim.loop = true;
	upAnim.speed = 0.2f;

	// Move down
	downAnim.PushBack({ 5, 9, 20, 28 });
	downAnim.PushBack({ 28, 8, 20, 28 });
	downAnim.PushBack({ 50, 5, 20, 28 });
	downAnim.PushBack({ 75, 8, 20, 28 });
	downAnim.PushBack({ 98, 10, 20, 28 });
	downAnim.PushBack({ 123, 8, 19, 28 });
	downAnim.PushBack({ 147, 6, 20, 28 });
	downAnim.PushBack({ 173, 9, 18, 28 });
	downAnim.loop = true;
	downAnim.speed = 0.2f;

	//Push box up
	upPushAnim.PushBack({});

	//Push box down
	downPushAnim.PushBack({ 5,40,18,25 });
	downPushAnim.PushBack({ 28,40,18,25 });
	downPushAnim.PushBack({ 51,40,18,25 });
	downPushAnim.PushBack({ 73,40,18,25 });
	downPushAnim.PushBack({ 97,40,18,25 });
	downPushAnim.PushBack({ 122,40,18,25 });
	downPushAnim.PushBack({ 146,40,18,25 });
	downPushAnim.PushBack({ 169,40,18,25 });
	downPushAnim.PushBack({ 192,40,18,25 });

	//Push box left
	leftPushAnim.PushBack({});

	//Push box right
	rightPushAnim.PushBack({});
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/CharacterAnimation.png");
	scoretable = App->textures->Load("Assets/Sprites/scoreboard.png");
	currentAnimation = &idleAnim;

	//laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	//explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x;
	position.y;

	colliderPlayer = App->collisions->AddCollider({ position.x, position.y, 30, 30 }, Collider::Type::PLAYER, this);
	colliderPlayerUp = App->collisions->AddCollider({ position.x, position.y-30, 30, 30 }, Collider::Type::PLAYER, this);
	colliderPlayerDown = App->collisions->AddCollider({ position.x, position.y+30, 30, 30 }, Collider::Type::PLAYER, this);
	colliderPlayerLeft = App->collisions->AddCollider({ position.x-30, position.y, 30, 30 }, Collider::Type::PLAYER, this);
	colliderPlayerRight = App->collisions->AddCollider({ position.x+30, position.y, 30, 30 }, Collider::Type::PLAYER, this);

	
	char lookupTable[] = { "0123456789 0123456789" };
	scoreFont = App->fonts->Load("Assets/Fonts/Score1.png", lookupTable, 2);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	//App->player->position.x -= -2;
	//currentAnimation = &idleAnim;
	if (step <= 0) {
		idleAnim.SetcurrentFrame(idleDir);
		currentAnimation = &idleAnim;
		GamePad& pad = App->input->pads[0];

		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.left_x < 0.0f || pad.left)
		{
			if (canMoveDir[2]) {
				step = 30;
				moveDir = { -1,0 };
				steps++;
			}
			idleDir = 3;
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || pad.left_x > 0.0f || pad.right)
		{
			if (canMoveDir[3]) {
				step = 30;
				moveDir = { 1,0 };
				steps++;
			}
			idleDir = 0;
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT || pad.left_y > 0.0f || pad.down)
		{
			if (canMoveDir[1]) {
				step = 30;
				moveDir = { 0,1 };
				steps++;
			}
			idleDir = 2;
			if (currentAnimation != &downAnim)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT || pad.left_y < 0.0f || pad.up)
		{
			if (canMoveDir[0]) 
			{
				step = 30;
				moveDir = { 0,-1 };
				steps++;
			}
			idleDir = 1;
			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
		}
	}
	else {
		step--;
		position += moveDir;
	}

	colliderPlayer->SetPos(position.x, position.y);
	colliderPlayerUp->SetPos(position.x, position.y-30);
	colliderPlayerDown->SetPos(position.x, position.y+30);
	colliderPlayerLeft->SetPos(position.x-30, position.y);
	colliderPlayerRight->SetPos(position.x+30, position.y);

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x+7, position.y, &rect);

		for (int i = 0; i < 4; i++) {
			canMoveDir[i] = true;
        }

		// Draw UI (score) --------------------------------------
		App->render->Blit(scoretable, 240, 30, NULL);

		sprintf_s(stepText, 10, "%4d", steps);
		App->fonts->BlitText(270, 44, scoreFont, stepText);

		sprintf_s(limitText, 10, "%4d", limit);
		App->fonts->BlitText(270, 54, scoreFont, limitText);

		sprintf_s(stageText, 10, "%2d", stage);
		App->fonts->BlitText(280, 32, scoreFont, stageText);

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::WALL || c2->type == Collider::Type::BOX_CENTER) {
		if (c1 == colliderPlayerUp) {
			canMoveDir[0] = false;
		}
		else if (c1 == colliderPlayerDown) {
			canMoveDir[1] = false;
		}
		else if (c1 == colliderPlayerLeft) {
			canMoveDir[2] = false;
		}
		else if (c1 == colliderPlayerRight) {
			canMoveDir[3] = false;
		}
	}
}