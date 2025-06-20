//Alexander Young
//Assignment 5
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "SpriteSheet.h"

//This is the constuctor for the SpriteSheet class
//Takes no parameters
//No return
Sprite::Sprite()
{
	image=NULL;
	lives = 6;
}

//This is the deconstructor for the SpriteSheet class
//Takes no parameters
//No return
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}

//This function starts a Sprite a a specified x and y value of the map
//Takes two integers representing the width and height of the map, an integer representing the current level
//No return
void Sprite::InitSprites(int xstart, int ystart)
{
	x = xstart;
	y = ystart;

	stagesCleared = 0;
	objective = false;
	kills = 0;
	damageTaken = 0;
	maxFrame = 3;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 3;
	animationRows = 8;
	animationDirection = 2;

	image = al_load_bitmap("player.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
}

//This function updates the x and y locaion of the Sprite, as well as the sequence in the animation
//Takes two integers representing the display height and width and an integer representing the direction
//No return
void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if(dir == 1){ //right key
		animationDirection = 1;
		animationRows = 2;
		x+=2.5;
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > 26)
				curFrame=24;
		}
	} 
	else if (dir == 0){ //left key
		animationDirection = 0; 
		animationRows = 1;
		x-=2.5; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > 14)
				curFrame=12;
		}
	}
	else if (dir == 3){	//up key
		animationDirection = 3;
		animationRows = 3;
		y -= 2.5;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 38)
				curFrame = 36;
		}
	}
	else if (dir == 4) {	//down key
		animationDirection = 4;
		animationRows = 0;
		y += 2.5;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 2)
				curFrame = 0;
		}
	}

	//check for collided with foreground tiles
	if (animationDirection==0)
	{ 
		if (collided(x, y + frameHeight)) { //collision detection to the left
			x = oldx; 
			y= oldy;
		}

	}
	else if (animationDirection ==1)
	{ 
		if (collided(x + frameWidth, y + frameHeight)) { //collision detection to the right
			x = oldx; 
			y= oldy;
		}
	}
	else if (animationDirection == 3)
	{
		if (collided(x + frameWidth/2, y)) { //collision detection to up
			x = oldx;
			y = oldy;
		}
	}
	else if (animationDirection == 4)
	{
		if (collided(x + frameWidth/2, y + frameHeight)) { //collision detection to down
			x = oldx;
			y = oldy;
		}
	}
}

//This function determines if a sprite collides with an endblock
//Takes no parameters
//Returns a boolean
bool Sprite::CollisionEndBlock()
{
	if (endValue(x + frameWidth/2, y-5))
		return true;
	else
		return false;
}

//This function draws the bitmap from the specified region of the sprite sheet used in the InitSprite function according to the current frame
//Take two integers representing the x and y offsets
//No return
void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRows * frameHeight;

	if (animationDirection==1){
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else if (animationDirection == 0 ){
		al_draw_bitmap_region(image, fx, fy, frameWidth,frameHeight, x-xoffset, y-yoffset,0);
	}
	else if (animationDirection == 2 ){
		al_draw_bitmap_region(image,32,0,frameWidth,frameHeight,  x-xoffset, y-yoffset, 0);
	}
	else if (animationDirection == 3) {
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else if (animationDirection == 4) {
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
}
