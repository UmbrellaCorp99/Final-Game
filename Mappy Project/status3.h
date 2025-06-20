//Alexander Young
//Assignment 5
#ifndef STATUS3H
#define STATUS3H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "SpriteSheet.h"
class status3
{
public:
	~status3();
	void updateStatus();
	void load_animated_status(int size, int WIDTH, int HEIGHT);
	void drawStatus(int xOffset, int yOffset);
	int getX() { return x; }
	int getY() { return y; }
	int getWidth() { return width; }
	int getHeight() { return height; }
private:
	int x, y;
	int width, height;
	int xdelay, ydelay;
	int xcount, ycount;
	int curframe, maxframe;
	int framecount, framedelay;
	ALLEGRO_BITMAP* image[54];
};
#endif
