//Alexander Young
//Assignment 5
#include "weapon.h"

//This is a constructor for the weapon class
//Takes no parameters
//No return
weapon::weapon() {
	image = al_load_bitmap("bullet.png");
	shot = al_load_sample("music/02 Arms (S.E. Collection).wav");
	empty = al_load_sample("music/emptyMag.wav");
	live = false;
	speed = 15;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
}

//This is a deconstructor for the weapon class
//Takes no parameters
//No return
weapon::~weapon() {
	al_destroy_bitmap(image);
	al_destroy_sample(shot);
	al_destroy_sample(empty);
}

//This function draws a rotated bitmap to the display with the x and y offsets taken into account, rotation is based on the dir, retrieved from fireWeapon
//Takes two integers representing the x and y offsets
//No return
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

//This function sets a weapon object that isn't live to live and sets the x and y based on the user direction and plays a sound. Sound played dependand on player's getBullets return value
//Takes a Sprite object reference as a parameter
//No return
void weapon::fireWeapon(Sprite &player) {
	if (!live)
	{
		if (player.getBullets() > 0) {
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
			al_play_sample(shot, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			live = true;
			player.loseBullet();
		}
		else {
			al_play_sample(empty, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	}
}

//This function updates a live weapon's x and y position on the map. If it collides with a foreground tile, set live to false
//Takes two integers representing the map width and height as parameters
//No return
void weapon::updateWeapon(int width, int height) {
	if (live)
	{
		switch (dir) {
		case 0:
			x -= speed;
			if (x < 0 || collided(x, y + boundy / 2))
				live = false;
			break;
		case 1:
			x += speed;
			if (x > width || collided(x + boundx, y + boundy / 2))
				live = false;
			break;
		case 2:
			y += speed;
			if (y > height || collided(x + boundx / 2, y))
				live = false;
			break;
		case 3:
			y -= speed;
			if (y < 0 || collided(x + boundx / 2, y))
				live = false;
			break;
		case 4:
			y += speed;
			if (y + boundy > height || collided(x + boundx / 2, y + boundy))
				live = false;
			break;
		}
	}
}

//This function determines if a weapon collides with an Enemy. If so, remove an enemy life, set the weapon live value to false. If enemy life is 0, set enemy live to false as well and increment the player kills
//Takes an Enemy object reference, an integer representing how many Enemies there are, and a Sprite object reference as parameters
//No return
void weapon::collideWeapon(Enemy e[], int csize, Sprite &p) {
	if (live) {
		for (int i = 0; i < csize; i++) {
			if (e[i].getlive()) {
				if ((((x > e[i].getX()) && x < (e[i].getX() + e[i].getWidth()) ||
					(((x + boundx) > e[i].getX()) && ((x + boundx) < (e[i].getX() + e[i].getWidth())))) &&
					(y > e[i].getY()) && (y < (e[i].getY() + e[i].getHeight()))) || (((x > e[i].getX()) && x < (e[i].getX() + e[i].getWidth()) ||
						(((x + boundx) > e[i].getX()) && ((x + boundx) < (e[i].getX() + e[i].getWidth())))) &&
						(y < (e[i].getY())) && ((y + boundy) > (e[i].getY()))) || (((y > e[i].getY()) && y < (e[i].getY() + e[i].getHeight()) ||
							(((y + boundy) > e[i].getY()) && ((y + boundy) < (e[i].getY() + e[i].getHeight())))) &&
							(x > (e[i].getX())) && (x < (e[i].getX() + e[i].getWidth()))) || (((y > e[i].getY()) && y < (e[i].getY() + e[i].getHeight()) ||
								(((y + boundy) > e[i].getY()) && ((y + boundy) < (e[i].getY() + e[i].getHeight())))) &&
								(x < e[i].getX()) && ((x + boundx) > (e[i].getX()))))
				{
					e[i].removeLives();
					live = false;
					if(e[i].getLives() == 0) {
						e[i].setLive(false);
						p.addKill();
					}
				}
			}
		}
		
	}
}

//This function determines if a weapon collides with an finalboss. If so, remove a life from finalboss, set the weapon live value to false. If finalboss life is 0, set enemy live to false as well and increment the player kills
//Takes an finalboss object reference and a Sprite object reference as parameters
//No return
void weapon::collideWeaponBoss(finalboss &e, Sprite& p) {
	if (live) {
		if ((((x > e.getX()) && x < (e.getX() + e.getWidth()) ||
			(((x + boundx) > e.getX()) && ((x + boundx) < (e.getX() + e.getWidth())))) &&
			(y > e.getY()) && (y < (e.getY() + e.getHeight()))) || (((x > e.getX()) && x < (e.getX() + e.getWidth()) ||
				(((x + boundx) > e.getX()) && ((x + boundx) < (e.getX() + e.getWidth())))) &&
				(y < (e.getY())) && ((y + boundy) > (e.getY()))) || (((y > e.getY()) && y < (e.getY() + e.getHeight()) ||
					(((y + boundy) > e.getY()) && ((y + boundy) < (e.getY() + e.getHeight())))) &&
					(x > (e.getX())) && (x < (e.getX() + e.getWidth()))) || (((y > e.getY()) && y < (e.getY() + e.getHeight()) ||
						(((y + boundy) > e.getY()) && ((y + boundy) < (e.getY() + e.getHeight())))) &&
						(x < e.getX()) && ((x + boundx) > (e.getX()))))
		{
			e.removeLives();
			live = false;
			if (e.getLives() == 0) {
				e.setLive(false);
				p.addKill();
			}
		}
	}
}