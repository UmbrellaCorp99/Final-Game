#ifndef WEAPONH
#define WEAPONH
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "EnemySprite.h"
#include "SpriteSheet.h"
#include "finalboss.h"
class weapon
{
	friend int collided(int x, int y);
	friend bool endValue(int x, int y);
public:
	weapon();
	~weapon();
	void drawWeapon(int xoffset, int yoffset);
	void updateWeapon(int width, int height);
	void fireWeapon(Sprite &player);
	void collideWeapon(Enemy e[], int csize, Sprite &p);
	void collideWeaponBoss(finalboss e, Sprite& p);
	void setLive(bool b) { live = b; }
	bool getLive() { return live; }
private:
	float x;
	float y;
	bool live;
	int boundx;
	int boundy;
	int speed;
	int dir;
	ALLEGRO_BITMAP* image;
	ALLEGRO_SAMPLE* shot;
};
#endif

