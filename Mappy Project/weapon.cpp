#include "weapon.h"

weapon::weapon() {
	image = al_load_bitmap("bullet.png");
	shot = al_load_sample("02 Arms (S.E. Collection).wav");
	live = false;
	speed = 15;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
}

weapon::~weapon() {
	al_destroy_bitmap(image);
	al_destroy_sample(shot);
}

void weapon::drawWeapon(int xoffset, int yoffset) {
	if (live) {
		switch (dir) {
		case 0:
			al_draw_rotated_bitmap(image, boundx / 2, boundy / 2, x - xoffset, y - yoffset, 0, 0);
			break;

		case 1:
			al_draw_rotated_bitmap(image, boundx / 2, boundy / 2, x - xoffset, y - yoffset, 3.14, 0);
			break;
		case 2:
			al_draw_rotated_bitmap(image, boundx / 2, boundy / 2, x - xoffset, y - yoffset, -1.57, 0);
			break;
		case 3:
			al_draw_rotated_bitmap(image, boundx / 2, boundy / 2, x - xoffset, y - yoffset, -1.57, 0);
			break;
		case 4:
			al_draw_rotated_bitmap(image, boundx / 2, boundy / 2, x - xoffset, y - yoffset, 1.57, 0);

		}
	}
}

void weapon::fireWeapon(Sprite &player) {
	if (!live)
	{
		dir = player.getDir();
		switch (dir) {
		case 0:
			x = player.getX();
			y = player.getY() + (player.getHeight() / 2);
			break;
		case 1:
			x = player.getX() + player.getWidth();
			y = player.getY() + (player.getHeight() / 2);
			break;
		case 2:
			x = player.getX() + (player.getWidth() / 2);
			y = player.getY() + player.getHeight();
			break;
		case 3:
			x = player.getX() + (player.getWidth() / 2);
			y = player.getY();
			break;
		case 4:
			x = player.getX() + (player.getWidth() / 2);
			y = player.getY() + player.getHeight();
			break;
		}
		al_play_sample(shot, .6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		live = true;
	}
}

void weapon::updateWeapon(int width, int height) {
	if (live)
	{
		switch (dir) {
		case 0:
			x -= speed;
			if (x < 0 || collided(x, y+boundy/2))
				live = false;
			break;
		case 1:
			x += speed;
			if (x > width || collided(x + boundx, y+boundy/2))
				live = false;
			break;
		case 2:
			y += speed;
			if (y > height || collided(x+boundx/2, y))
				live = false;
			break;
		case 3:
			y -= speed;
			if (y < 0 || collided(x+boundx/2, y))
				live = false;
			break;
		case 4:
			y += speed;
			if (y + boundy > height || collided(x + boundx/2, y + boundy))
				live = false;
			break;
		}
	}
}

void weapon::collideWeapon(Enemy e[], int csize) {
	if (live) {
		for (int i = 0; i < csize; i++) {
			if (e[i].getlive()) {
				if (x > (e[i].getX() - e[i].getWidth()) &&
					x < (e[i].getX() + e[i].getWidth()) &&
					y >(e[i].getY() - e[i].getHeight()) &&
					y < (e[i].getY() + e[i].getHeight()))
				{
					live = false;
					e[i].setLive(false);
					break;
				}
			}
		}
		
	}
}