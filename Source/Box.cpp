#include "Box.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "ModulePlayer.h"

#include <iostream>

Box::Box(iPoint pos, Collider* col, Module * mod)
{
	boxPosition = pos;
	colliderBox = col;
	colliderPlayer = App->player->colliderPlayer;
	level = mod;
}

Box::~Box()
{

}

bool Box::Start()
{
	bool ret = true;

	colliderBoxUp = App->collisions->AddCollider({ boxPosition.x, boxPosition.y - 30, 30, 30 }, Collider::Type::BOX, level);
	colliderBoxDown = App->collisions->AddCollider({ boxPosition.x, boxPosition.y + 30, 30, 30 }, Collider::Type::BOX, level);
	colliderBoxLeft = App->collisions->AddCollider({ boxPosition.x - 30, boxPosition.y, 30, 30 }, Collider::Type::BOX, level);
	colliderBoxRight = App->collisions->AddCollider({ boxPosition.x + 30, boxPosition.y, 30, 30 }, Collider::Type::BOX, level);

	return ret;
}

void Box::PreUpdate()
{

}

void Box::Update()
{
	if (step <= 0 && App->player->step <= 0)
	{
		moveDirBox = { 0,0 };
		if (canMoveDirBox[2] && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) 
		{
			step = 30;
			moveDirBox = { -1,0 };
			App->player->canMoveDir[2] = true;
		}
		if (canMoveDirBox[3] && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			step = 30;
			moveDirBox = { 1,0 };
			App->player->canMoveDir[3] = true;
		}
		if (canMoveDirBox[1] && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) 
		{
			step = 30;
			moveDirBox = { 0,1 };
			App->player->canMoveDir[1] = true;
		}
		if (canMoveDirBox[0] && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) 
		{
			step = 30;
			moveDirBox = { 0,-1 };
			App->player->canMoveDir[0] = true;
		}
	}

	else 
	{
		step--;
		boxPosition += moveDirBox;
	}

	colliderBox->SetPos(boxPosition.x, boxPosition.y);
	colliderBoxUp->SetPos(boxPosition.x, boxPosition.y - 30);
	colliderBoxDown->SetPos(boxPosition.x, boxPosition.y + 30);
	colliderBoxLeft->SetPos(boxPosition.x - 30, boxPosition.y);
	colliderBoxRight->SetPos(boxPosition.x + 30, boxPosition.y);
}

void Box::PostUpdate()
{
	if (step > 0) return;

	for (int i = 0; i < 4; i++)
	{
		canMoveDirBox[i] = false;
		crashWall[i] = false;
	}
}

void Box::OnCollision(Collider* c1, Collider* c2) {

	if (step > 0) return;

	if (c2 == colliderPlayer && App->player->step <= 0) 
	{
		if (c1 == colliderBoxUp && !crashWall[1]) 
		{
			canMoveDirBox[1] = true;
		}
		if (c1 == colliderBoxDown && !crashWall[0])
		{
			canMoveDirBox[0] = true;
		}
		if (c1 == colliderBoxLeft && !crashWall[3])
		{
			canMoveDirBox[3] = true;
		}
		if (c1 == colliderBoxRight && !crashWall[2])
		{
			canMoveDirBox[2] = true;
		}
	}

	else if (c2->type == Collider::Type::BOX_CENTER || c2->type == Collider::Type::WALL)
	{
		if (c1 == colliderBoxUp) 
		{
			canMoveDirBox[0] = false;
			crashWall[0] = true;
		}
		if (c1 == colliderBoxDown) 
		{
			canMoveDirBox[1] = false;
			crashWall[1] = true;
		}
		if (c1 == colliderBoxLeft) 
		{
			canMoveDirBox[2] = false;
			crashWall[2] = true;
		}
		if (c1 == colliderBoxRight)
		{
			canMoveDirBox[3] = false;
			crashWall[3] = true;
		}
	}
}