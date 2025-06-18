#include "herb.h"

herb::herb() {
	image = al_load_bitmap("G_herb.png");
	useHerb = al_load_sample("music/herb.wav");
	boundx = 50;
	boundy = 40;
	live = false;
}
herb::~herb() {
	al_destroy_bitmap(image);
	al_destroy_sample(useHerb);
}
void herb::drawHerb(int xOff, int yOff) {
	if (live) {
		al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
		al_draw_scaled_bitmap(image, 0, 0, 100, 80, x - xOff, y - yOff, 50, 40, 0);
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