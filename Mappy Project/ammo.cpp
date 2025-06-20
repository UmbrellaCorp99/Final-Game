#include "ammo.h"

ammo::ammo() {
	ammoImage = al_load_bitmap("hand-gun-bullets.png");
	useAmmo = al_load_sample("music/reload.wav");
	boundx = 50;
	boundy = 40;
	live = false;
}
ammo::~ammo() {
	al_destroy_bitmap(ammoImage);
	al_destroy_sample(useAmmo);
}
void ammo::drawAmmo(int xOff, int yOff) {
	if (live) {
		al_draw_scaled_bitmap(ammoImage, 0, 0, 450, 360, x - xOff, y - yOff, 50, 40, 0);
	}
}
void ammo::startAmmo(int startx, int starty) {
	live = true;
	x = startx;
	y = starty;
}
void ammo::collideAmmo(Sprite& player) {
	if (live) {
		if (x > (player.getX() - player.getWidth()) &&
			x < (player.getX() + player.getWidth()) &&
			y >(player.getY() - player.getHeight()) &&
			y < (player.getY() + player.getHeight()))
		{
			player.setBullets(player.getBullets() + 20);
			live = false;
			al_play_sample(useAmmo, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	}
}