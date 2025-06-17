#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "SpriteSheet.h"

Sprite::Sprite()
{
	image=NULL;
	walk = al_load_sample("04 PC-Walk (S.E. Collection).wav");
}
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
	al_destroy_sample(walk);
}
void Sprite::InitSprites(int width, int height)
{
	x = 120;
	y = 160;


	maxFrame = 3;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 3;
	animationRows = 8;
	animationDirection = 1;

	image = al_load_bitmap("player.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if(dir == 1){ //right key
		animationDirection = 1;
		animationRows = 2;
		x+=2;
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
		x-=2; 
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
		y -= 2;
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
		y += 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 2)
				curFrame = 0;
		}
	}
	else //represent that they hit the space bar and that mean direction = 0
		animationDirection = dir;

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

bool Sprite::CollisionEndBlock()
{
	if (endValue(x + frameWidth/2, y + frameHeight + 5))
		return true;
	else
		return false;
}

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
