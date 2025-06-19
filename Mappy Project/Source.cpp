#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "SpriteSheet.h"
#include "EnemySprite.h"
#include "weapon.h"
#include "mappy_A5.h"
#include "status.h"
#include "status2.h"
#include "status3.h"
#include "herb.h"
#include "finalboss.h"
#include <iostream>
#include "objective.h"
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
	bool win = false;
	//Player Variable
	const int numEnemies = 10;
	const int numBullets = 5;
	int count = 0;
	bool track1Started = false;
	bool track2Started = false;
	srand(time(NULL));
	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_SAMPLE* sample = NULL;
	ALLEGRO_SAMPLE* sample2 = NULL;
	ALLEGRO_SAMPLE* dead = NULL;
	ALLEGRO_SAMPLE* door = NULL;
	ALLEGRO_BITMAP* died = NULL;
	ALLEGRO_SAMPLE* resultScreen = NULL;
	ALLEGRO_BITMAP* results = NULL;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_SAMPLE_INSTANCE* instance1 = NULL;
	ALLEGRO_SAMPLE_INSTANCE* instance2 = NULL;
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
	if (!al_reserve_samples(14)) {
		exit(9);
	}
	sample = al_load_sample("music/06 - Death Siege.wav");
	dead = al_load_sample("music/death.wav");

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	font = al_load_font("NeoBulletin Trash.ttf", 32, 0);
	died = al_load_bitmap("you died.png");
	results = al_load_bitmap("results.png");
	Sprite player;
	Enemy enemy[numEnemies];
	weapon bullet[numBullets];
	status fine;
	status2 caution;
	status3 danger;
	herb Herb;
	objective item;
	finalboss boss;

	player.InitSprites(360,50);
	fine.load_animated_status(54, WIDTH, HEIGHT);
	caution.load_animated_status(54, WIDTH, HEIGHT);
	danger.load_animated_status(54, WIDTH, HEIGHT);
	Herb.startHerb(350, 600);
	item.startObjective(250, 800);
	
	int xOff = 0;
	int yOff = 0;
	if(MapLoad("FinalProjectMap1.FMP", 1))
		return -5;

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	al_play_sample(sample, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	//draw the background tiles
	MapDrawBG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1);

	//draw foreground tiles
	MapDrawFG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1, 0);
	player.DrawSprites(xOff,yOff);
	Herb.drawHerb(xOff, yOff);
	item.drawObjective(xOff, yOff);
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
			if (player.CollisionEndBlock() && player.getObjective())
				if (count == 0) {
					player.addStageCleared();
					player.resetLives();
					player.setObjective(false);
					Herb.setLive(false);
					item.incrementStage();
					al_stop_samples();
					door = al_load_sample("music/doorOpen.wav");
					al_play_sample(door, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					if (MapLoad("FinalProjectMap2.FMP", 1))
						return -5;
					MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);
					MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
					Herb.startHerb(600, 600);
					Herb.drawHerb(xOff, yOff);
					for (int i = 0; i < numEnemies; i++) {
						enemy[i].setLive(false);
					}
					for (int i = 0; i < numBullets; i++) {
						bullet[i].setLive(false);
					}
					item.startObjective(450, 700);
					item.drawObjective(xOff, yOff);
					player.setX(WIDTH*.75);
					player.setY((mapheight*32) - (player.getHeight()*2));
					player.DrawSprites(xOff, yOff);
					door = al_load_sample("music/doorClose.wav");
					al_play_sample(door, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					sample = al_load_sample("music/07 - The Palace Of Insane.wav");
					al_play_sample(sample, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
					count++;
				}
				else if (count == 1) {
					player.addStageCleared();
					player.resetLives(); 
					Herb.setLive(false);
					al_stop_samples();
					door = al_load_sample("music/doorOpen.wav");
					al_play_sample(door, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					if (MapLoad("FinalProjectMap3.FMP", 1))
						return -5;
					if (!track1Started) {
						sample = al_load_sample("music/Nosferatu first.wav");
						instance1 = al_create_sample_instance(sample);
						al_attach_sample_instance_to_mixer(instance1, al_get_default_mixer());
						al_set_sample_instance_playmode(instance1, ALLEGRO_PLAYMODE_ONCE);
						door = al_load_sample("music/doorClose.wav");
						al_play_sample(door, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						al_play_sample_instance(instance1);

						track1Started = true;
					}
					MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);
					MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
					for (int i = 0; i < numEnemies; i++) {
						enemy[i].setLive(false);
					}
					for (int i = 0; i < numBullets; i++) {
						bullet[i].setLive(false);
					}
					player.setX((mapwidth*32)/2);
					player.setY((mapheight * 32)/2);
					player.DrawSprites(xOff, yOff);
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
					count++;
				}

			if (count == 0 || count == 1) {
				for (int i = 0; i < numEnemies; i++) {
					enemy[i].InitSprites(mapwidth * 32, mapheight * 32, count, player);
				}
				for (int i = 0; i < numEnemies; i++) {
					enemy[i].UpdateSprites(WIDTH, HEIGHT, player);
				}
				
				for (int i = 0; i < numBullets; i++) {
					bullet[i].updateWeapon(mapwidth * 32, mapheight * 32);
				}
				for (int i = 0; i < numBullets; i++) {
					bullet[i].collideWeapon(enemy, numEnemies, player);
				}
				for (int i = 0; i < numEnemies; i++) {
					enemy[i].CollideSprite(player);
				}
				Herb.collideHerb(player);
				item.collideObjective(player);
			}
			else if (count == 2) {
				if (track1Started && !track2Started && !al_get_sample_instance_playing(instance1)) {
					sample2 = al_load_sample("music/nosferatu loop.wav");
					instance2 = al_create_sample_instance(sample2);
					al_attach_sample_instance_to_mixer(instance2, al_get_default_mixer());
					al_set_sample_instance_playmode(instance2, ALLEGRO_PLAYMODE_LOOP);
					al_play_sample_instance(instance2);
					track2Started = true;
				}
				boss.initBoss((mapwidth * 32) / 3, (mapheight * 32) / 3);
				boss.updateBoss(WIDTH, HEIGHT, player);
				for (int i = 0; i < numBullets; i++) {
					bullet[i].updateWeapon(mapwidth * 32, mapheight * 32);
				}
				for (int i = 0; i < numBullets; i++) {
					bullet[i].collideWeaponBoss(boss, player);
				}
				boss.collideBoss(player);
				Herb.collideHerb(player);
				if (!boss.getlive()) {
					player.addStageCleared();
					if (track2Started) {
						al_stop_sample_instance(instance2);
					}
					else {
						al_stop_sample_instance(instance1);
					}
					win = true;
				}
			}
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
				for (int i = 0; i < numBullets; i++) {
					if (!bullet[i].getLive()) {
						bullet[i].fireWeapon(player);
						break;  // Only fire one bullet per press
					}
				}
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
			Herb.drawHerb(xOff, yOff);
			item.drawObjective(xOff, yOff);
			for (int i = 0; i < numEnemies; i++) {
				enemy[i].DrawSprites(xOff, yOff);
			}
			player.DrawSprites(xOff, yOff);
			for (int i = 0; i < numBullets; i++) {
				bullet[i].drawWeapon(xOff, yOff);

			}
			boss.drawBoss(xOff, yOff);
			if (player.getLives() > 4) {
				fine.updateStatus();
				fine.drawStatus(xOff, yOff);
			}
			else if (player.getLives() > 2) {
				caution.updateStatus();
				caution.drawStatus(xOff, yOff);
			}
			else if (player.getLives() > 0) {
				danger.updateStatus();
				danger.drawStatus(xOff, yOff);
			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
			if (player.getLives() <= 0) {
				al_draw_bitmap(died, WIDTH / 5, 0, 0);
				al_draw_textf(font, al_map_rgb(200, 0, 0), WIDTH/2, HEIGHT*.8, ALLEGRO_ALIGN_CENTER, "Enemies killed: %i", player.getKills());
				al_draw_textf(font, al_map_rgb(200, 0, 0), WIDTH / 2, HEIGHT * .9, ALLEGRO_ALIGN_CENTER, "Stages Cleared: %i", player.getStagesCleared());
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_play_sample(dead, .6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_rest(10);
				done = true;
			}
			else if (win == true) {
				sample = al_load_sample("music/bossDefeat.wav");
				al_play_sample(sample, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_rest(6);
				resultScreen = al_load_sample("music/2-37 - Set Free (Ranking BGM1).wav");
				al_play_sample(resultScreen, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_draw_scaled_bitmap(results, 0, 0, 1080, 607, 0, 0, WIDTH, HEIGHT, 0);
				al_draw_textf(font, al_map_rgb(255, 0, 0), 0, HEIGHT/2, 0, "Enemies killed: %i", player.getKills());
				al_draw_textf(font, al_map_rgb(255, 0, 0), 0, HEIGHT * .7, 0, "Stages Cleared: %i", player.getStagesCleared());
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_rest(48);
				done = true;
			}
		}
	}
	MapFreeMem();
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object
	al_destroy_sample(sample);
	al_destroy_sample(sample2);
	al_destroy_sample(door);
	al_destroy_sample_instance(instance1);
	al_destroy_sample_instance(instance2);
	al_destroy_sample(dead);
	al_destroy_bitmap(died);
	al_destroy_font(font);
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