#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include "SpriteSheet.h"
#include "EnemySprite.h"
#include "weapon.h"
#include "mappy_A5.h"
#include <iostream>
using namespace std;

int collided(int x, int y);  //Tile Collision
bool endValue( int x, int y ); //End Block with the User Value = 8
int main(void)
{
	const int WIDTH = 900;
	const int HEIGHT = 480;
	bool keys[] = {false, false, false, false, false};
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	//variables
	bool done = false;
	bool render = false;
	//Player Variable
	Sprite player;
	Enemy enemy;
	


	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_SAMPLE* sample = NULL;

	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	al_install_audio();
	if (!al_install_audio) {
		al_show_native_message_box(NULL, "Error", "Audio failed to initialize", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_init_acodec_addon();
	if (!al_init_acodec_addon()) {
		al_show_native_message_box(NULL, "Error", "Acodec failed to initialize", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	if (!al_reserve_samples(1)) {
		exit(9);
	}
	sample = al_load_sample("07 - The Palace Of Insane.wav");

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_image_addon();
	al_init_primitives_addon();

	weapon bullet;
	player.InitSprites(WIDTH,HEIGHT);
	enemy.InitSprites(WIDTH, HEIGHT);

	int xOff = 0;
	int yOff = 0;
	if(MapLoad("FinalProjectMap1.FMP", 1))
		return -5;

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	al_play_sample(sample, .6, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	//draw the background tiles
	MapDrawBG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1);

	//draw foreground tiles
	MapDrawFG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1, 0);
	player.DrawSprites(0,0);
	enemy.DrawSprites(0,0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			if (keys[UP])
				player.UpdateSprites(WIDTH, HEIGHT, 3);
			else if (keys[DOWN])
				player.UpdateSprites(WIDTH, HEIGHT, 4);
			else if(keys[LEFT])
				player.UpdateSprites(WIDTH,HEIGHT,0);
			else if(keys[RIGHT])
				player.UpdateSprites(WIDTH,HEIGHT,1);
			else
				player.UpdateSprites(WIDTH,HEIGHT,2);
			if (player.CollisionEndBlock())
				cout<<"Hit an End Block\n";
			bullet.updateWeapon(WIDTH, HEIGHT);
			enemy.UpdateSprites(WIDTH, HEIGHT, player);
			render = true;

		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				bullet.fireWeapon(player);
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			//update the map scroll position
			xOff = player.getX()+player.getWidth() - WIDTH/2 ;
			yOff = player.getY()+player.getHeight()   - HEIGHT/2 ;

			//avoid moving beyond the map edge
			if (xOff < 0) xOff = 0;

			if (xOff > (mapwidth * mapblockwidth - WIDTH))
				xOff = mapwidth * mapblockwidth - WIDTH;
			if (yOff < 0) 
				yOff = 0;
			if (yOff > (mapheight * mapblockheight - HEIGHT)) 
				yOff = mapheight * mapblockheight - HEIGHT;

			//draw the background tiles
			MapDrawBG(xOff,yOff, 0, 0, WIDTH, HEIGHT);

			//draw foreground tiles
			MapDrawFG(xOff,yOff, 0, 0, WIDTH, HEIGHT, 0);
			enemy.DrawSprites(xOff, yOff);
			player.DrawSprites(xOff, yOff);
			bullet.drawWeapon(xOff, yOff);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	MapFreeMem();
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object
	al_destroy_sample(sample);
	return 0;
}

int collided(int x, int y)
{
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	return blockdata->tl;
}

bool endValue( int x, int y )
{

	BLKSTR* data;
	data = MapGetBlock( x/mapblockwidth, y/mapblockheight );

	if( data->user1 == 8 )
	{
		return true;
	}else
		return false;
}