#ifndef HERBH
#define HERBH
#include <allegro5//allegro.h>
#include <allegro5/allegro_image.h>
#include "SpriteSheet.h"
class herb
{
public:
	herb();
	~herb();
	void drawHerb(int xOff, int yOff);
	void startHerb(int startx, int starty);
	void collideHerb(Sprite &player);
	void setLive(bool b) { live = b; }
private:
	bool live;
	int x, y;
	int boundx, boundy;
	ALLEGRO_BITMAP* image;
};
#endif
