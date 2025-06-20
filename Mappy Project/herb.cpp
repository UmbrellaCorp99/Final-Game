#include "herb.h"

//This is the constructor for the herb class
//Takes no parameters
//No return
herb::herb() {
	image = al_load_bitmap("G_herb.png");
	useHerb = al_load_sample("music/herb.wav");
	boundx = 50;
	boundy = 40;
	live = false;
}

//This is a deconstructor for the herb class
//Takes no parameters
//No return
herb::~herb() {
	al_destroy_bitmap(image);
	al_destroy_sample(useHerb);
}

//This function removes the black background from the image in the constructor and draws a scaled bitmap to the display with the x and y offsets taken into account
//Takes two integers representing the x and y offsets
//No return
void herb::drawHerb(int xOff, int yOff) {
	if (live) {
		al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
		al_draw_scaled_bitmap(image, 0, 0, 100, 80, x - xOff, y - yOff, 50, 40, 0);
	}
}

//This function sets the x and y starting value for a "new" herb on the map
//Takes two integers representing the x and y values to be used
//No return
void herb::startHerb(int startx, int starty) {
	live = true;
	x = startx;
	y = starty;
}

//This function detects if a player collides with the herb object. if so, it reset the lives variable for the player, plays a sound, and despawns
//Takes a Sprite object reference as a parameter
//No return
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