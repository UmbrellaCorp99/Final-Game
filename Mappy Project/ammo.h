#ifndef AMMOH
#define AMMOH
#include <allegro5//allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "SpriteSheet.h"
class ammo
{
public:
	ammo();
	~ammo();
	void drawAmmo(int xOff, int yOff);
	void startAmmo(int startx, int starty);
	void collideAmmo(Sprite& player);
	void setLive(bool b) { live = b; }
private:
	bool live;
	int x, y;
	int boundx, boundy;
	ALLEGRO_BITMAP* ammoImage;
	ALLEGRO_SAMPLE* useAmmo;
};
#endif
