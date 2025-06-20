//Alexander Young
//Assignment 5
#include "finalboss.h"

//This is the constuctor for the finalboss class, sets up animation variables and allegro samples and a bitmap
//Takes no parameters
//No return
finalboss::finalboss() {
	image = al_load_bitmap("player2.png");
	injured = al_load_sample("music/05 PC-Voice (S.E. Collection).wav");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));

	maxFrame = 3;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 3;
	animationRows = 4;
	animationDirection = 1;
	live = false;
}

//This is the deconstructor for the finalboss class
//Takes no parameters
//No return
finalboss::~finalboss() {
	//al_destroy_bitmap(bossimage);
	//al_destroy_sample(bossinjured);
}

//This function starts a "new" finalboss at a specified x and y value of the map
//Takes two integers representing the width and height of the map
//No return
void finalboss::initBoss(int width, int height) {
	if (!live) {
		x = width;
		y = height;
		lives = 25;
		live = true;
	}
}

//This function draws the bitmap from the specified region of the sprite sheet used in the constructor according to the current frame
//Take two integers representing the x and y offsets
//No return
void finalboss::drawBoss(int xOff, int yOff) {
	if (live) {
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = animationRows * frameHeight;

		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xOff, y - yOff, 0);
	}
}

//This function updates the x and y locaion of the finalboss, as well as the sequence in the animation
//Takes two integers representing the display height and width, and a Sprite object reference
//No return
void finalboss::updateBoss(int width, int height, Sprite& player) {
	if (live) {
		int oldx = x;
		int oldy = y;

		if (x < player.getX()) { //right
			animationDirection = 1;
			animationRows = 2;
			x += 1.25;
			if (++frameCount > frameDelay)
			{
				frameCount = 0;
				if (++curFrame > 8)
					curFrame = 6;
			}
		}
		else if (x > player.getX()) { //left
			animationDirection = 2;
			animationRows = 1;
			x -= 1.25;
			if (++frameCount > frameDelay)
			{
				frameCount = 0;
				if (++curFrame > 5)
					curFrame = 3;
			}
		}
		if (y < player.getY()) { //down
			animationDirection = 3;
			animationRows = 0;
			y += 1.25;
			if (++frameCount > frameDelay)
			{
				frameCount = 0;
				if (++curFrame > 2)
					curFrame = 0;
			}
		}
		else if (y > player.getY()) { //up
			animationDirection = 4;
			animationRows = 3;
			y -= 1.25;
			if (++frameCount > frameDelay)
			{
				frameCount = 0;
				if (++curFrame > 11)
					curFrame = 9;
			}
		}
	}
}

//This function detects if a player collides with an enemy.If so, play a sound
//Takes a Sprite object reference as a parameter
//No return
void finalboss::collideBoss(Sprite& p) {
	if (live) {
		if (x > (p.getX() - p.getWidth()) &&
			x < (p.getX() + p.getWidth()) &&
			y >(p.getY() - p.getHeight()) &&
			y < (p.getY() + p.getHeight()))
		{
			p.removeLives(4);
			if (p.getLives() > 0) {
				al_play_sample(injured, .7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
	}
}