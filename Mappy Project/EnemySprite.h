#ifndef ENEMYH
#define ENEMYH
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "SpriteSheet.h"
#include <iostream>
using namespace std;
class Enemy
{
	friend int collided(int x, int y);
	friend bool endValue(int x, int y);
public:
	Enemy();
	~Enemy();
	void InitSprites(int width, int height);
	void UpdateSprites(int width, int height, Sprite &player);
	void DrawSprites(int xoffset, int yoffset);
	bool CollideSprite();
	float getX() { return x; }
	float getY() { return y; }
	int getWidth() { return frameWidth; }
	int getHeight() { return frameHeight; }
	bool CollisionEndBlock();
	void setLive(bool b) { live = b; }
private:
	float x;
	float y;
	bool live;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationRows;
	int animationDirection;

	ALLEGRO_BITMAP* image;
};
#endif

