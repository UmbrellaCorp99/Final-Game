//Alexander Young
//Assignment 5
#include "EnemySprite.h"

//This is the constuctor for the Enemy class, sets up animation variables and allegro samples and a bitmap
//Takes no parameters
//No return
Enemy::Enemy()
{
	enemyImage = al_load_bitmap("player3.png");
	injured = al_load_sample("music/05 PC-Voice (S.E. Collection).wav");
	al_convert_mask_to_alpha(enemyImage, al_map_rgb(255, 0, 255));

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

//This is the deconstructor for the Enemy class
//Takes no parameters
//No return
Enemy::~Enemy()
{
	al_destroy_bitmap(enemyImage);
	al_destroy_sample(injured);
}

//This function starts a "new" Enemy a a random x and y value of the map, ensuring no spawning on the player, with different health depending on the level
//Takes two integers representing the width and height of the map, an integer representing the current level, and a Sprite object reference
//No return
void Enemy::InitSprites(int width, int height, int level, Sprite &player)
{
	if (!live) {
		x = (rand() % width);
		y = (rand() % width);
		if (level == 0) {
			lives = 2;
		}
		else if (level == 1) {
			lives = 3;
		}
		if (x > (player.getX() - player.getWidth()) &&
			x < (player.getX() + player.getWidth()) &&
			y >(player.getY() - player.getHeight()) &&
			y < (player.getY() + player.getHeight())) {
			live = false;
		}
		else {
			live = true;
		}
	}
}

//This function updates the x and y locaion of the enemy, as well as the sequence in the animation. Basic movement homing in on player
//Takes two integers representing the display height and width, and a Sprite object reference
//No return
void Enemy::UpdateSprites(int width, int height, Sprite &player)
{
	if (live) {
		int oldx = x;
		int oldy = y;

		if (x < player.getX()) { //right
			animationDirection = 1;
			animationRows = 2;
			x += .65;
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
			x -= .65;
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
			y += .65;
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
			y -= .65;
			if (++frameCount > frameDelay)
			{
				frameCount = 0;
				if (++curFrame > 11)
					curFrame = 9;
			}
		}
	}
}

//This function draws the bitmap from the specified region of the sprite sheet used in the constructor according to the current frame
//Take two integers representing the x and y offsets
//No return
void Enemy::DrawSprites(int xoffset, int yoffset)
{
	if (live) {
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = animationRows * frameHeight;

		al_draw_bitmap_region(enemyImage, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	
}

//This function detects if a player collides with an enemy. If so, remove a life from the player, play a sound, and despawn the enemy
//Takes a Sprite object reference as a parameter
//No return
void Enemy::CollideSprite(Sprite &p) {
	if (live) {
		if (x > (p.getX() - p.getWidth()) &&
			x < (p.getX() + p.getWidth()) &&
			y >(p.getY() - p.getHeight()) &&
			y < (p.getY() + p.getHeight())) 
		{
			p.removeLife();
			live = false;
			p.incDamage();
			if (p.getLives() != 0) {
				al_play_sample(injured, .7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
	}
}