#ifndef STATUS2H
#define STATUS2H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "SpriteSheet.h"
class status2
{
public:
	~status2();
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
