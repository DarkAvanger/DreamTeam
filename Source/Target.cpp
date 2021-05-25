#include "Target.h"

Target::Target(SDL_Rect rect, Module* mod)
{
	this->rect = rect;
	level = mod;
	col = App->collisions->AddCollider(rect, Collider::TARGET, level);

}

Target::~Target()
{

}

void Target::PostUpdate()
{
	isComplete = false;
}

void Target::OnCollision(Collider* col)
{
	if(col->type== Collider::BOX_CENTER)
	{
		if(col->getPos().x == rect.x && col->getPos().y == rect.y)
		{
			isComplete = true;
		}		
	}
}
