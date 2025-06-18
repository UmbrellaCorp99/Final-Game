#ifndef SPRITEH
#define SPRITEH

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
using namespace std;
class Sprite
{
	friend int collided(int x, int y);
	friend bool endValue( int x, int y );
public:
	Sprite();
	~Sprite();
	void InitSprites(int xstart, int ystart);
	void UpdateSprites(int width, int height, int dir); //dir 1 = right, 0 = left, 2 = Standing Still
	void DrawSprites(int xoffset, int yoffset);
	bool CollideSprite();
	float getX() {return x;}
	float getY() {return y;}
	void setX(int newx) { x = newx; }
	void setY(int newy) { y = newy; }
	int getWidth() {return frameWidth;}
	int getHeight() {return frameHeight;}
	int getDir() { return animationDirection; }
	bool CollisionEndBlock();
	void removeLife() { lives--; }
	int getLives() { return lives; }
	void resetLives() { lives = 6; }
	int getKills() { return kills;}
	void addKill() { kills++; }
	int getStagesCleared() { return stagesCleared; }
	void addStageCleared() { stagesCleared++; }
	void setObjective(bool b) { objective = b; }
	bool getObjective() { return objective; }
private:
	int stagesCleared;
	int kills;
	bool objective;
	float x;
	float y;
	int lives;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationRows;
	int animationDirection;

	ALLEGRO_BITMAP *image;
};
#endif