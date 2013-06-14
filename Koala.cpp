#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <list>

#include "GameState.h"
#include "Menu/Menu.cpp"
#include "LeafPuzzle/LeafPuzzle.cpp"
#include "TreePunch/LeafPunch.cpp"
#include "CaveGame/CaveGame.cpp"

GameState *gameState;
const int WIDTH = 1920;
const int HEIGHT = 1080;

void changeState(int newState, int &oldState);
int levelNumber = 0;
int koalaSize = 0;

bool keys[] = {false,false,false,false,false,false,false};
int timeSinceDown[] = {0,0,0,0,0,0,0};

int main(void){
	//PRIMITIVES==============
	bool done = false;
	bool redraw = true;
	int curState = MENU;
	int timeAfterWinning = 10;
	int windowWidth = WIDTH;
	int windowHeight = HEIGHT;
	const int FPS = 60;
	const int RESERVED_SAMPLES = 10;
	
	//ALLEGRO variables============
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font36;
	ALLEGRO_SAMPLE *end;
	ALLEGRO_BITMAP *koala;
	
	//Initializers
	if(!al_init()) return -1;
	
	display = al_create_display(WIDTH, HEIGHT);							//Initialize before flags to make window start at desired size instead of at most recent size
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	display = al_create_display(WIDTH, HEIGHT);
	al_set_window_position(display, 0, 0);
	al_set_window_title(display, "MOTHERTRUCKING KOALAGAME");
	
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	
	//object variables================
	gameState = new Menu();
	gameState->Init(WIDTH, HEIGHT, levelNumber, 0);
	
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0/FPS);
	font36 = al_load_font("Audio and Images/AAJAX.ttf", 36, 0);
	end = al_load_sample("Audio and Images/YouSuck.wav");
	koala = al_load_bitmap("Audio and Images/Koala.bmp");
	al_convert_mask_to_alpha(koala, al_map_rgb(255,255,255));
	
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	
	gameState->Init(WIDTH, HEIGHT, levelNumber, 0);
	
	al_reserve_samples(RESERVED_SAMPLES);
	
	al_start_timer(timer);
	
	while(!(gameState->getState() == EXIT || done)){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if(ev.type == ALLEGRO_EVENT_TIMER){				//Next sixtieth of a second
			gameState->Update();
			for(int i=UP;i<Q+1;i++){
				if(keys[i]){
					timeSinceDown[i]++;
					if(timeSinceDown[i] > 20 || curState == CAVE_GAME)
						gameState->Move(i);
				}
			}
			redraw = true;
			timeAfterWinning++;
			if(gameState->getState() != curState && timeAfterWinning > 1)		//Allows graphics to update before game moves on to next state 
				timeAfterWinning = 0;
			if(timeAfterWinning == 1){
				if(levelNumber % 3 == 0)
					changeState(gameState->getState(), curState);
				else
					changeState(LEAF_PUZZLE, curState);
				al_rest(.4);																									//Small pause so you can see completed stage
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){	//Red 'X' is clicked
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					gameState->Move(UP);
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					gameState->Move(DOWN);
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					gameState->Move(LEFT);
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					gameState->Move(RIGHT);
					break;
				case ALLEGRO_KEY_W:
					keys[UP] = true;
					gameState->Move(UP);
					break;
					keys[DOWN] = true;
				case ALLEGRO_KEY_S:
					keys[DOWN] = true;
					gameState->Move(DOWN);
					break;
				case ALLEGRO_KEY_A:
					keys[LEFT] = true;
					gameState->Move(LEFT);
					break;
				case ALLEGRO_KEY_D:
					keys[RIGHT] = true;
					gameState->Move(RIGHT);
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = true;
					gameState->Enter();
					break;
				case ALLEGRO_KEY_ENTER:
					keys[ENTER] = true;
					gameState->Enter();
					break;
				case ALLEGRO_KEY_Q:
					keys[SPACE] = true;
					gameState->Move(Q);
					break;
				case ALLEGRO_KEY_E:
					keys[ENTER] = true;
					gameState->Move(E);
					break;
				case ALLEGRO_KEY_P:
					keys[P] = true;
					gameState->setState(MENU);
					break;
				case ALLEGRO_KEY_R:
					changeState(LEAF_PUZZLE, curState);
					break;
				case ALLEGRO_KEY_T:
					changeState(CAVE_GAME, curState);
					break;
			}
		}else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
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
				case ALLEGRO_KEY_W:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_S:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_A:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_D:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = false;
					break;
				case ALLEGRO_KEY_ENTER:
					keys[ENTER] = false;
					break;
				case ALLEGRO_KEY_Q:
					keys[SPACE] = false;
					break;
				case ALLEGRO_KEY_E:
					keys[ENTER] = false;
					break;
			}
		}else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
			gameState->SetMousePos((ev.mouse.x * WIDTH) / windowWidth, (ev.mouse.y * HEIGHT) / windowHeight);
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			gameState->Enter();
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
			windowWidth = ev.display.width;
			windowHeight = ev.display.height;
		}
		if(redraw & al_is_event_queue_empty(event_queue)){			//Draw stuff
			redraw = false;
			gameState->Render();
			al_draw_scaled_bitmap(koala, 0, 0, 250, 250, WIDTH-250-(25*koalaSize), HEIGHT-250, 250+(koalaSize*50), 250, 0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	al_play_sample(end,1,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);
	//al_rest(1);
	delete gameState;
	al_destroy_bitmap(koala);
	al_destroy_timer(timer);
	al_destroy_sample(end);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font36);
	al_destroy_display(display);
	
	return 0;
}

void changeState(int newState, int &oldState){
	int tempScore = gameState->getScore();
	for(int i=UP;i<ESCAPE;i++){
		keys[i] = false;
		timeSinceDown[i] = 0;
	}
	if(newState == LEAF_PUZZLE){
		delete gameState;
		gameState = new LeafPuzzle();
		gameState->Init(WIDTH, HEIGHT, levelNumber, tempScore);
		gameState->Move(RIGHT);
		levelNumber++;
	}
	else if(newState == LEAF_PUNCH){
		delete gameState;
		gameState = new LeafPunch();
		gameState->Init(WIDTH, HEIGHT, 0, tempScore);
		gameState->Move(-1);
		if(oldState == LEAF_PUZZLE)
			koalaSize++;
	}
	else if(newState == MENU){
		delete gameState;
		gameState = new Menu();
		gameState->Init(WIDTH, HEIGHT, 0, 0);
	}
	else if(newState == CAVE_GAME){
		delete gameState;
		gameState = new CaveGame();
		gameState->Init(WIDTH, HEIGHT, 0, tempScore);
	}
	oldState = newState;
}