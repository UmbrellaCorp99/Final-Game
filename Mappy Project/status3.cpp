#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "status3.h"

void status3::drawStatus(int xOffset, int yOffset) {
	al_draw_scaled_bitmap(image[curframe], 0, 0, 320, 158, x, y, 160, 79, 0);
}

void status3::updateStatus() {
	if (framecount++ > framedelay)
	{
		framecount = 0;
		curframe++;
		if (curframe >= maxframe)
			curframe = 0;
	}
}

void status3::load_animated_status(int size, int WIDTH, int HEIGHT) {
	char s[80];
	maxframe = size;
	for (int n = 0; n < size; n++)
	{
		sprintf_s(s, "danger/frame_%d_delay-0.04s.png", n);
		image[n] = al_load_bitmap(s);

		al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
	}
	width = al_get_bitmap_width(image[0]) / 2;
	height = al_get_bitmap_height(image[0]) / 2;
	x = WIDTH - width;
	y = HEIGHT - height;
	curframe = 0;
	framedelay = 1;
	framecount = 0;
}

status3::~status3() {
	for (int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}