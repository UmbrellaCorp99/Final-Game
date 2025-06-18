#include "objective.h"

objective::objective() {
	for (int i = 0; i < 2; i++) {
		images[i] = NULL;
	}
	stage = 0;
	images[0] = al_load_bitmap("Diamond_Key.png");
	images[1] = al_load_bitmap("Lab_Card_Key.png");
	pickup = al_load_sample("itemPickup.wav");
	image = images[stage];
	live = false;
}
objective::~objective() {
	for (int i = 0; i < 2; i++) {
		al_destroy_bitmap(images[i]);
	}
	al_destroy_bitmap(image);
}

void objective::drawObjective(int xOff, int yOff) {
	if (live) {
		al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
		al_draw_scaled_bitmap(image, 0, 0, 332, 211, x - xOff, y - yOff, 50, 40, 0);
	}
}

void objective::startObjective(int startx, int starty) {
	live = true;
	x = startx;
	y = starty;
}
void objective::collideObjective(Sprite& player) {
	if (live) {
		if (x > (player.getX() - player.getWidth()) &&
			x < (player.getX() + player.getWidth()) &&
			y >(player.getY() - player.getHeight()) &&
			y < (player.getY() + player.getHeight()))
		{
			player.setObjective(true);
			live = false;
			al_play_sample(pickup, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	}
}