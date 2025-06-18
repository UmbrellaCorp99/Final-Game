#include "EnemySprite.h"

Enemy::Enemy()
{
	image = al_load_bitmap("player.png");
	injured = al_load_sample("music/05 PC-Voice (S.E. Collection).wav");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));

	maxFrame = 3;
	curFrame = 48;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 3;
	animationRows = 8;
	animationDirection = 1;
	live = false;
}
Enemy::~Enemy()
{
	al_destroy_bitmap(image);
	al_destroy_sample(injured);
}
void Enemy::InitSprites(int width, int height)
{
	if (!live) {
		x = (rand() % width);
		y = (rand() % width);

		live = true;
	}
}

void Enemy::UpdateSprites(int width, int height, Sprite &player)
{
	if (live) {
		int oldx = x;
		int oldy = y;

		if (x < player.getX()) { //right
			animationDirection = 1;
			animationRows = 6;
			x += 1;
			if (++frameCount > frameDelay)
			{
				frameCount = 0;
				if (++curFrame > 74)
					curFrame = 72;
			}
		}
		else if (x > player.getX()) { //left
			animationDirection = 2;
			animationRows = 5;
			x -= 1;
			if (++frameCount > frameDelay)
			{
				frameCount = 0;
				if (++curFrame > 62)
					curFrame = 60;
			}
		}
		if (y < player.getY()) { //down
			animationDirection = 3;
			animationRows = 4;
			y += 1;
			if (++frameCount > frameDelay)
			{
				frameCount = 0;
				if (++curFrame > 50)
					curFrame = 48;
			}
		}
		else if (y > player.getY()) { //up
			animationDirection = 4;
			animationRows = 7;
			y -= 1;
			if (++frameCount > frameDelay)
			{
				frameCount = 0;
				if (++curFrame > 74)
					curFrame = 72;
			}
		}
	}
}

void Enemy::DrawSprites(int xoffset, int yoffset)
{
	if (live) {
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = animationRows * frameHeight;

		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	
}

void Enemy::CollideSprite(Sprite &p) {
	if (live) {
		if (x > (p.getX() - p.getWidth()) &&
			x < (p.getX() + p.getWidth()) &&
			y >(p.getY() - p.getHeight()) &&
			y < (p.getY() + p.getHeight())) 
		{
			p.removeLife();
			live = false;
			if (p.getLives() != 0) {
				al_play_sample(injured, 1.4, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
	}
}