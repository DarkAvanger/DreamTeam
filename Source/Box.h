#ifndef __BOX_H__
#define __BOX_H__


#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Collider.h"
#include "ModuleRender.h"

struct SDL_Texture;
class Box
{
public:
	// Constructor
	Box(iPoint pos, Collider* col);

	// Destructor
	~Box();

	bool Start();

	void PreUpdate();

	void Update();

	void PostUpdate();

	void OnCollision(Collider* c1, Collider* c2);

	SDL_Rect* getRenderRect() {
		return &renderRect;
	}
public:
	// Position of the box in the map
	iPoint boxPosition;

	iPoint moveDirBox = { 0,0 };
	int step = 0;
	// The speed in which we move the player (pixels per frame)
	int speed = 30;

	bool canMoveDirBox[4] = { false };
	bool crashWall[4] = { false };
	
	// The Box's collider
	Collider* colliderBox = nullptr;
	Collider* colliderBoxUp = nullptr;
	Collider* colliderBoxDown = nullptr;
	Collider* colliderBoxLeft = nullptr;
	Collider* colliderBoxRight = nullptr;
	Collider* colliderPlayer = nullptr;

	SDL_Rect renderRect = { 0, 3, 30, 30 };
	// A flag to detect when the player has been destroyed
	bool destroyed = false;
};

#endif //!__BOX_H__