//Alexander Young
//Assignment 5
#include "ammo.h"

//This is the constructor for the ammo class
//Takes no parameters
//No return
ammo::ammo() {
	ammoImage = al_load_bitmap("hand-gun-bullets.png");
	useAmmo = al_load_sample("music/reload.wav");
	boundx = 50;
	boundy = 40;
	live = false;
}

//This is a deconstructor for the ammo class
//Takes no parameters
//No return
ammo::~ammo() {
	al_destroy_bitmap(ammoImage);
	al_destroy_sample(useAmmo);
}

//This function draws a scaled bitmap to the display with the x and y offsets taken into account
//Takes two integers representing the x and y offsets
//No return
void ammo::drawAmmo(int xOff, int yOff) {
	if (live) {
		al_draw_scaled_bitmap(ammoImage, 0, 0, 450, 360, x - xOff, y - yOff, 50, 40, 0);
	}
}

//This function sets the x and y starting value for a "new" ammo on the map
//Takes two integers representing the x and y values to be used
//No return
void ammo::startAmmo(int startx, int starty) {
	live = true;
	x = startx;
	y = starty;
}

//This function detects if a player collides with the ammo object. if so, it increases the bullets variable for the player, plays a sound, and despawns
//Takes a Sprite object reference as a parameter
//No return
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