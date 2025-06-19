#ifndef FINALBOSSH
#define FINALBOSSH
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "SpriteSheet.h"
#include <iostream>
class finalboss
{
public:
	finalboss();
	~finalboss();
	void initBoss(int width, int height);
	void drawBoss(int xoffset, int yoffset);
	void updateBoss(int width, int height, Sprite& player);
	void collideBoss(Sprite& p);
	float getX() { return x; }
	float getY() { return y; }
	int getWidth() { return frameWidth; }
	int getHeight() { return frameHeight; }
	void setLive(bool b) { live = b; }
	bool getlive() { return live; }
	int getLives() { return lives; }
	void removeLives() { lives--; }
private:
	float x;
	float y;
	bool live;
	int lives;
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
