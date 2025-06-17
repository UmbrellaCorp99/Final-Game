#include "weapon.h"

weapon::weapon() {
	image = al_load_bitmap("bullet.png");
	live = false;
	speed = 15;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
}

weapon::~weapon() {
	al_destroy_bitmap(image);
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

void weapon::collideWeapon(Enemy &e) {
	if (live) {
		if (x > (e.getX() - e.getWidth()) &&
			x < (e.getX() + e.getWidth()) &&
			y >(e.getY() - e.getHeight()) &&
			y < (e.getY() + e.getHeight()))
		{
			live = false;
			e.setLive(false);
		}
	}
}