#include "herb.h"

herb::herb() {
	image = al_load_bitmap("items.png");
	useHerb = al_load_sample("music/herb.wav");
	boundx = 48;
	boundy = 31;
	live = false;
}
herb::~herb() {
	al_destroy_bitmap(image);
}
void herb::drawHerb(int xOff, int yOff) {
	if(live){
		al_draw_bitmap_region(image, boundx * 0.1, boundy * 7.1, boundx, boundy, x-xOff, y-yOff, 0);
	}
}
void herb::startHerb(int startx, int starty) {
	live = true;
	x = startx;
	y = starty;
}
void herb::collideHerb(Sprite& player) {
	if (live) {
		if (x > (player.getX() - player.getWidth()) &&
			x < (player.getX() + player.getWidth()) &&
			y >(player.getY() - player.getHeight()) &&
			y < (player.getY() + player.getHeight()))
		{
			player.resetLives();
			live = false;
			al_play_sample(useHerb, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	}
}