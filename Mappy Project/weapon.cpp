#include "weapon.h"

weapon::weapon() {
	image = al_load_bitmap("bullet.png");
	live = false;
	speed = 15;
}

weapon::~weapon() {
	al_destroy_bitmap(image);
}

void weapon::drawWeapon(int xoffset, int yoffset) {
	if (live) {
		al_draw_bitmap(image,x-xoffset, y-yoffset,0);
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
			if (x < 0)
				live = false;
			break;
		case 1:
			x += speed;
			if (x > width)
				live = false;
			break;
		case 2:
			y += speed;
			if (y > height)
				live = false;
			break;
		case 3:
			y -= speed;
			if (y < 0)
				live = false;
			break;
		case 4:
			y += speed;
			if (y > height)
				live = false;
			break;
		}
	}
}

void weapon::collideWeapon() {

}