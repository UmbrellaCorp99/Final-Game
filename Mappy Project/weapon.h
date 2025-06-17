#ifndef WEAPONH
#define WEAPONH
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "SpriteSheet.h"
class weapon
{
public:
	weapon();
	~weapon();
	void drawWeapon(int xoffset, int yoffset);
	void updateWeapon(int width, int height);
	void fireWeapon(Sprite &player);
	void collideWeapon();
private:
	float x;
	float y;
	bool live;
	int boundx;
	int boundy;
	int speed;
	int dir;
	ALLEGRO_BITMAP* image;
};
#endif

