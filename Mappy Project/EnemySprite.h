#ifndef ENEMYH
#define ENEMYH
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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
	void CollideSprite(Sprite &p);
	float getX() { return x; }
	float getY() { return y; }
	int getWidth() { return frameWidth; }
	int getHeight() { return frameHeight; }
	void setLive(bool b) { live = b; }
	bool getlive() { return live; }
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
	ALLEGRO_SAMPLE* injured;
	ALLEGRO_BITMAP* image;
};
#endif

