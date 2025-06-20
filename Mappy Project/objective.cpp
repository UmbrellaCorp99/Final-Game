//Alexander Young
//Assignment 5
#include "objective.h"

//This is the constructor for the objective class. Stores 2 different images in an array to be loaded in as the current image based on the current level
//Takes no parameters
//No return
objective::objective() {
	for (int i = 0; i < 2; i++) {
		images[i] = NULL;
	}
	stage = 0;
	images[0] = al_load_bitmap("images/Diamond_Key.png");
	images[1] = al_load_bitmap("images/Lab_Card_Key.png");
	pickup = al_load_sample("music/itemPickup.wav");
	image = images[stage];
	live = false;
}

//This is a deconstructor for the objective class
//Takes no parameters
//No return
objective::~objective() {
	for (int i = 0; i < 2; i++) {
		al_destroy_bitmap(images[i]);
	}
	//al_destroy_bitmap(image);
	al_destroy_sample(pickup);
}

//This function increments the stage variable and chages the current image to be loaded in from images[]
//Takes no parameters
//No return
void objective::incrementStage() {
	stage++;
	image = images[stage];
}

//This function draws a scaled bitmap to the display with the x and y offsets taken into account
//Takes two integers representing the x and y offsets
//No return
void objective::drawObjective(int xOff, int yOff) {
	if (live) {
		al_draw_scaled_bitmap(image, 0, 0, 332, 211, x - xOff, y - yOff, 50, 40, 0);
	}
}

//This function sets the x and y starting value for a "new" objective on the map
//Takes two integers representing the x and y values to be used
//No return
void objective::startObjective(int startx, int starty) {
	if(!live) {
		x = startx;
		y = starty;
		live = true;
	}
	
}

//This function detects if a player collides with the objecive object. if so, it sets the objective bool variable for the player, plays a sound, and despawns
//Takes a Sprite object reference as a parameter
//No return
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