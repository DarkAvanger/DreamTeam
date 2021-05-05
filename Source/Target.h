#ifndef _TARGET_H
#define _TARGET_H

#include "Collider.h"
#include "p2Point.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"

class Target
{
public:

	SDL_Rect rect;
	Collider* col = nullptr;
	bool isComplete = false;

public:

	Target(SDL_Rect rect);
	~Target();

	void PostUpdate();

	void OnCollision(Collider* col);
};


#endif // !_TARGET_H


