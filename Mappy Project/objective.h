#ifndef OBJECTIVEH
#define OBJECTIVEH
#include <allegro5//allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "SpriteSheet.h"
class objective
{
public:
	objective();
	~objective();
	void drawObjective(int xOff, int yOff);
	void startObjective(int startx, int starty);
	void collideObjective(Sprite& player);
	void setLive(bool b) { live = b; }
	void incStage() { stage++; }
private:
	int stage;
	bool live;
	int x, y;
	int boundx, boundy;
	ALLEGRO_BITMAP* image;
	ALLEGRO_BITMAP* images[2];
	ALLEGRO_SAMPLE* pickup;
};
#endif
