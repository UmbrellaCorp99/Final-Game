//Alexander Young
//Assignment 5
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
#include "ammo.h"
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
	int score = 0;
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
	ALLEGRO_SAMPLE* intro = NULL;
	ALLEGRO_BITMAP* results = NULL;
	ALLEGRO_BITMAP* herbPic = NULL;
	ALLEGRO_BITMAP* keyPic = NULL;
	ALLEGRO_BITMAP* ammoPic = NULL;
	ALLEGRO_BITMAP* introBackground = NULL;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_FONT* rankFont = NULL;
	ALLEGRO_FONT* bulletCountFont = NULL;
	ALLEGRO_SAMPLE_INSTANCE* instance1 = NULL;
	ALLEGRO_SAMPLE_INSTANCE* instance2 = NULL;
	ALLEGRO_BITMAP* bulletCountPic = NULL;
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
	if (!al_reserve_samples(20)) {
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

	//varioys fonts and bitmaps to use throughout
	font = al_load_font("NeoBulletin Trash.ttf", 24, 0);
	bulletCountFont = al_load_font("NeoBulletin Trash.ttf", 32, 0);
	rankFont = al_load_font("NeoBulletin Trash.ttf", 64, 0);
	died = al_load_bitmap("you died.png");
	results = al_load_bitmap("results.png");
	herbPic = al_load_bitmap("G_herb2.png");
	keyPic = al_load_bitmap("Diamond_Key.png");
	ammoPic = al_load_bitmap("hand-gun-bullets2.png");
	bulletCountPic = al_load_bitmap("bulletCount.png");
	introBackground = al_load_bitmap("Resident-Evil-Code-Veronica-X-feature-1038x576.png");

	//instantiating objects
	Sprite player;
	Enemy enemy[numEnemies];
	weapon bullet[numBullets];
	status fine;
	status2 caution;
	status3 danger;
	herb Herb;
	ammo Ammo;
	objective item;
	finalboss boss;

	//Setting up first map
	player.InitSprites(360,50);
	player.setBullets(25);
	fine.load_animated_status(54, WIDTH, HEIGHT);
	caution.load_animated_status(54, WIDTH, HEIGHT);
	danger.load_animated_status(54, WIDTH, HEIGHT);
	Herb.startHerb(350, 600);
	Ammo.startAmmo(730, 550);
	item.startObjective(250, 800);
	
	int xOff = 0;
	int yOff = 0;
	//load first map
	if(MapLoad("FinalProjectMap1.FMP", 1))
		return -5;

	//This is the intro. It plays background music and displays varioys text and images to tell user how to play and give info on the game
	intro = al_load_sample("music/intro.wav");
	al_play_sample(intro, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_draw_tinted_bitmap(introBackground, al_map_rgb(64, 64, 64), 0, 0, 0);
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 33, ALLEGRO_ALIGN_CENTER, "Welcome to my game!");
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 99, ALLEGRO_ALIGN_CENTER, "This game is inspired by Resident Evil Code: Veronica,");
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 132, ALLEGRO_ALIGN_CENTER, "which released on the Sega Dreamcast in the year 2000");
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_rest(11);
	al_draw_tinted_bitmap(introBackground, al_map_rgb(64, 64, 64), 0, 0, 0);
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 33, ALLEGRO_ALIGN_CENTER, "You must survive 3 rounds against the terrifying creatures");
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 133, ALLEGRO_ALIGN_CENTER, "The final boss will kill you in one hit, be careful!");
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 233, ALLEGRO_ALIGN_CENTER, "Move with the arrow keys, and shoot with space");
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_rest(11);
	al_draw_tinted_bitmap(introBackground, al_map_rgb(64, 64, 64), 0, 0, 0);
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 33, ALLEGRO_ALIGN_CENTER, "Each level has one key item that you must obtain before you can proceed");
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 99, ALLEGRO_ALIGN_CENTER, "You will fully heal between levels and when collecting herbs");
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 165, ALLEGRO_ALIGN_CENTER, "Ammo is limited, but you replenish it once per area");
	al_draw_scaled_bitmap(herbPic, 0, 0, 100, 80, 0, HEIGHT*.45, 300, 240, 0);
	al_draw_scaled_bitmap(keyPic, 0, 0, 332, 211, WIDTH * .7, HEIGHT / 2, 265, 169, 0);
	al_draw_scaled_bitmap(ammoPic, 0, 0, 450, 360, WIDTH*.4, HEIGHT / 2, 225, 180, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_rest(11);
	al_draw_tinted_bitmap(introBackground, al_map_rgb(64, 64, 64), 0, 0, 0);
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 165, ALLEGRO_ALIGN_CENTER, "You have once again entered the world of survival horror");
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 198, ALLEGRO_ALIGN_CENTER, "Good Luck...");
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 397, ALLEGRO_ALIGN_CENTER, "The Audio used in this game belong to Capcom, as does the");
	al_draw_text(font, al_map_rgb(200, 0, 0), WIDTH / 2, 430, ALLEGRO_ALIGN_CENTER, "Resident Evil franchise. This game is not for sale.");
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_rest(10);
	//End of introduction

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	//play the background music on a loop
	al_play_sample(sample, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	//draw the background tiles
	MapDrawBG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1);

	//draw foreground tiles
	MapDrawFG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1, 0);
	
	//draw the bullet indicator with the current ammount for the player's HUD
	al_draw_rotated_bitmap(bulletCountPic, al_get_bitmap_width(bulletCountPic) / 2, al_get_bitmap_height(bulletCountPic) / 2, WIDTH*.05, HEIGHT * .9, 1.57, 0);
	al_draw_textf(font, al_map_rgb(255, 255, 0), WIDTH*.1, HEIGHT*.9, 0,  "x %i", player.getBullets());
	//draw things to the display for the first time
	player.DrawSprites(xOff,yOff);
	Herb.drawHerb(xOff, yOff);
	Ammo.drawAmmo(xOff, yOff);
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
			//Only runs if the player it touching an endblock and they have gotten the objective
			if (player.CollisionEndBlock() && player.getObjective())
				if (count == 0) {
					player.addStageCleared();	//increment stagesCleared player variable
					player.resetLives();	//give player full health
					player.setBullets(player.getBullets() + 25);	//give player 25 bullets
					player.setObjective(false);	//reset player objective variable
					Herb.setLive(false);	//clear the herb from map
					Ammo.setLive(false);	//clear the ammo from map
					item.incrementStage();	//change the image displayed for the objective
					al_stop_samples();	//stop the background music
					door = al_load_sample("music/doorOpen.wav");	
					al_play_sample(door, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);	//play door open sound effect
					if (MapLoad("FinalProjectMap2.FMP", 1))	//load next map
						return -5;
					MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);
					MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
					//set up new herb, ammo, objective placements
					Herb.startHerb(600, 600);
					Ammo.startAmmo(700, 1150);
					Herb.drawHerb(xOff, yOff);
					Ammo.drawAmmo(xOff, yOff);
					//reset any live enemies and reset all currently live bullets
					for (int i = 0; i < numEnemies; i++) {
						enemy[i].setLive(false);
					}
					for (int i = 0; i < numBullets; i++) {
						bullet[i].setLive(false);
					}
					item.startObjective(450, 700);	//place the new objective on the map
					item.drawObjective(xOff, yOff);
					//place the player in the specified location in the new map
					player.setX(WIDTH*.75);
					player.setY((mapheight*32) - (player.getHeight()*2));
					player.DrawSprites(xOff, yOff);
					door = al_load_sample("music/doorClose.wav");
					al_play_sample(door, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);	//play door closing sound effecet
					sample = al_load_sample("music/07 - The Palace Of Insane.wav");
					al_play_sample(sample, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);	//play new background music on a loop
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
					count++;
				}
				else if (count == 1) {
					player.addStageCleared(); //increment stagesCleared player stat
					player.resetLives();	//give player full health
					Herb.setLive(false);	//clear herb from map
					Ammo.setLive(false);	//clear ammo from map
					player.setBullets(player.getBullets() + 30);	//give player 30 bullets
					al_stop_samples();	//stop background music
					door = al_load_sample("music/doorOpen.wav");	//play door opening sound effect
					al_play_sample(door, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					if (MapLoad("FinalProjectMap3.FMP", 1))	//load next map
						return -5;
					//start new bacground music. This sample is being used to create a sample instance that is attatched to the mixer so the music can switch mid-program on its own
					if (!track1Started) {
						sample = al_load_sample("music/Nosferatu first.wav");
						instance1 = al_create_sample_instance(sample);
						al_attach_sample_instance_to_mixer(instance1, al_get_default_mixer());
						al_set_sample_instance_playmode(instance1, ALLEGRO_PLAYMODE_ONCE);
						door = al_load_sample("music/doorClose.wav");	//play door closing sound effect
						al_play_sample(door, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						al_play_sample_instance(instance1);

						track1Started = true;
					}
					MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);
					MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
					//clear enemies and live bullets
					for (int i = 0; i < numEnemies; i++) {
						enemy[i].setLive(false);
					}
					for (int i = 0; i < numBullets; i++) {
						bullet[i].setLive(false);
					}
					//spawn the player at the specified location in the new map
					player.setX((mapwidth*32)/2);
					player.setY((mapheight * 32)/2);
					player.DrawSprites(xOff, yOff);
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
					count++;
				}
			//The following only happens for the first two maps since the last map should only contain the final boss
			if (count == 0 || count == 1) {
				//spawn new enemies
				for (int i = 0; i < numEnemies; i++) {
					enemy[i].InitSprites(mapwidth * 32, mapheight * 32, count, player);
				}
				//update enemy locations
				for (int i = 0; i < numEnemies; i++) {
					enemy[i].UpdateSprites(WIDTH, HEIGHT, player);
				}
				//update weapon location
				for (int i = 0; i < numBullets; i++) {
					bullet[i].updateWeapon(mapwidth * 32, mapheight * 32);
				}
				//check for weapon collision
				for (int i = 0; i < numBullets; i++) {
					bullet[i].collideWeapon(enemy, numEnemies, player);
				}
				//check for enemy collision with player
				for (int i = 0; i < numEnemies; i++) {
					enemy[i].CollideSprite(player);
				}
				//check if player collides with herb, ammo, or the objective
				Herb.collideHerb(player);
				Ammo.collideAmmo(player);
				item.collideObjective(player);
			}
			//The following only happens for the third map
			else if (count == 2) {
				//checks to see if the first sample instance in the mixer is finished and the second track has not started. If so, play the second sample instance on a loop for the remainder of the map
				if (track1Started && !track2Started && !al_get_sample_instance_playing(instance1)) {
					sample2 = al_load_sample("music/nosferatu loop.wav");
					instance2 = al_create_sample_instance(sample2);
					al_attach_sample_instance_to_mixer(instance2, al_get_default_mixer());
					al_set_sample_instance_playmode(instance2, ALLEGRO_PLAYMODE_LOOP);
					al_play_sample_instance(instance2);
					track2Started = true;
				}
				//spawn boss, update boss location
				boss.initBoss((mapwidth * 32) / 3, (mapheight * 32) / 3);
				boss.updateBoss(WIDTH, HEIGHT, player);
				//update weapon location
				for (int i = 0; i < numBullets; i++) {
					bullet[i].updateWeapon(mapwidth * 32, mapheight * 32);
				}
				//check for bullet collision with final boss
				for (int i = 0; i < numBullets; i++) {
					bullet[i].collideWeaponBoss(boss, player);
				}
				//check if boss touches player
				boss.collideBoss(player);
				//if boss dies, increment player stagesCleared stat
				if (!boss.getlive()) {
					player.addStageCleared();
					//Stop whichever sample instance is playing currently
					if (track2Started) {
						al_stop_sample_instance(instance2);
					}
					else {
						al_stop_sample_instance(instance1);
					}
					//set win to true
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
				//if space is pressed, fire a bullet that is not live
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
			Ammo.drawAmmo(xOff, yOff);
			//draw the bullet indicator with the current ammount for the player's HUD
			al_draw_rotated_bitmap(bulletCountPic, al_get_bitmap_width(bulletCountPic) / 2, al_get_bitmap_height(bulletCountPic) / 2, WIDTH * .05, HEIGHT * .9, 1.57, 0);
			al_draw_textf(font, al_map_rgb(255, 255, 0), WIDTH * .1, HEIGHT * .9, 0, "x %i", player.getBullets());
			//draw the objective
			item.drawObjective(xOff, yOff);
			//draw the enemies
			for (int i = 0; i < numEnemies; i++) {
				enemy[i].DrawSprites(xOff, yOff);
			}
			//draw the player
			player.DrawSprites(xOff, yOff);
			//draw the weapons
			for (int i = 0; i < numBullets; i++) {
				bullet[i].drawWeapon(xOff, yOff);

			}
			//draw the boss
			boss.drawBoss(xOff, yOff);
			//The following draws a different status bar depending on the value of the player's getLives
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
			//If the player dies, draw the corresponding bitmap to the screen, along with text with results and play a special audio. End the game after 10 seconds
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
			//If the player kills the final boss, playa special audio and wait 6 seconds
			else if (win == true) {
				sample = al_load_sample("music/bossDefeat.wav");
				al_play_sample(sample, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_rest(6);
				//calculate a score (rank) for the player based on the levels cleared, kills, and damage taken
				score = ((player.getStagesCleared() * 1000) + (player.getKills() * 100) - (player.getDamageTaken() * 50));
				//play background music, draw a scaled bitmap for the background, and draw text for the stats
				resultScreen = al_load_sample("music/2-37 - Set Free (Ranking BGM1).wav");
				al_play_sample(resultScreen, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_draw_scaled_bitmap(results, 0, 0, 1080, 607, 0, 0, WIDTH, HEIGHT, 0);
				al_draw_textf(font, al_map_rgb(255, 0, 0), WIDTH, HEIGHT*.1, ALLEGRO_ALIGN_RIGHT, "Enemies killed: %i", player.getKills());
				al_draw_textf(font, al_map_rgb(255, 0, 0), WIDTH, HEIGHT * .2, ALLEGRO_ALIGN_RIGHT, "Damage Taken: %i", player.getDamageTaken());
				al_draw_textf(font, al_map_rgb(255, 0, 0), WIDTH, HEIGHT * .3, ALLEGRO_ALIGN_RIGHT, "Stages Cleared: %i", player.getStagesCleared());
				//draw the rank dependant on the value of the score obtained
				if (score > 5600) {
					al_draw_text(rankFont, al_map_rgb(255, 0, 0), WIDTH, HEIGHT * .6, ALLEGRO_ALIGN_RIGHT, "Rank: S");
				}
				else if (score > 5100) {
					al_draw_text(rankFont, al_map_rgb(255, 0, 0), WIDTH, HEIGHT * .6, ALLEGRO_ALIGN_RIGHT, "Rank: A");
				}
				else if (score > 4600) {
					al_draw_text(rankFont, al_map_rgb(255, 0, 0), WIDTH, HEIGHT * .6, ALLEGRO_ALIGN_RIGHT, "Rank: B");
				}
				else if (score > 4100) {
					al_draw_text(rankFont, al_map_rgb(255, 0, 0), WIDTH, HEIGHT * .6, ALLEGRO_ALIGN_RIGHT, "Rank: C");
				}
				else {
					al_draw_text(rankFont, al_map_rgb(255, 0, 0), WIDTH, HEIGHT * .6, ALLEGRO_ALIGN_RIGHT, "Rank: D");
				}
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				//pause for 48 seconds (for music to finish, allows player to review stats). End game
				al_rest(48);
				done = true;
			}
		}
	}
	MapFreeMem();
	//destoy allegro objects to clear up memory
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_bitmap(herbPic);
	al_destroy_bitmap(introBackground);
	al_destroy_bitmap(keyPic);
	al_destroy_bitmap(ammoPic);
	al_destroy_bitmap(bulletCountPic);
	al_destroy_font(rankFont);
	al_destroy_sample(sample);
	al_destroy_sample(sample2);
	al_destroy_sample(resultScreen);
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