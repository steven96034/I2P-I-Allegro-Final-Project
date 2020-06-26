//final project template
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define GAME_TERMINATE -1

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;

ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *image2 = NULL;
ALLEGRO_BITMAP *image3 = NULL;

ALLEGRO_KEYBOARD_STATE keyState;

ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TIMER *timer2 = NULL;
ALLEGRO_TIMER *timer3 = NULL;

ALLEGRO_SAMPLE *menu_bgm = NULL;
ALLEGRO_SAMPLE *village_bgm = NULL;
ALLEGRO_SAMPLE *INN_bgm = NULL;
ALLEGRO_SAMPLE *grocerystore_bgm = NULL;

ALLEGRO_SAMPLE_ID menu_bgm_id = { 0 };
ALLEGRO_SAMPLE_ID village_bgm_id = { 0 };
ALLEGRO_SAMPLE_ID INN_bgm_id = { 0 };
ALLEGRO_SAMPLE_ID grocerystore_bgm_id = { 0 };

ALLEGRO_BITMAP *menu_bg = NULL;
ALLEGRO_BITMAP *village_bg = NULL;
ALLEGRO_BITMAP *INN_bg = NULL;
ALLEGRO_BITMAP *grocerystore_bg = NULL;

ALLEGRO_FONT *menu_font = NULL;




//Custom Definition
const char *title = "Final Project 108030001 108030027";
const float FPS = 60;
const int WIDTH = 900;
const int HEIGHT = 900;
typedef struct character
{
	int x;
	int y;
	ALLEGRO_BITMAP *image_path;

}Character;

Character character1;
Character character2;
Character character3;

int imageWidth = 0;
int imageHeight = 0;
int draw = 0;
int done = 0;
int window = 1;
bool pop_up_window = false;
bool judge_next_window = false;
bool ture = true; //true: appear, false: disappear
bool next = false; //true: trigger
bool dir = true; //true: left, false: right

bool key_state[ALLEGRO_KEY_MAX];

void show_err_msg(int msg);
void game_init();
void load_data();
void game_begin();
int process_event();
void event_window();
int game_run();
void game_destroy();

//bool pnt_in_rect(int px, int py, int x, int y, int w, int h);



int main(int argc, char *argv[]) {
	int msg = 0;

	game_init();
	game_begin();

	while (msg != GAME_TERMINATE) {
		msg = game_run();
		if (msg == GAME_TERMINATE)
			printf("Game Over\n");
	}

	game_destroy();
	return 0;
}

void show_err_msg(int msg) {
	fprintf(stderr, "unexpected msg: %d\n", msg);
	game_destroy();
	exit(9);
}

void game_init() {
	if (!al_init()) {
		show_err_msg(-1);
	}
	if (!al_install_audio()) {
		fprintf(stderr, "failed to initialize audio!\n");
		show_err_msg(-2);
	}
	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize audio codecs!\n");
		show_err_msg(-3);
	}
	if (!al_reserve_samples(10)) {
		fprintf(stderr, "failed to reserve samples!\n");
		show_err_msg(-4);
	}
	// Create display
	display = al_create_display(WIDTH, HEIGHT);
	event_queue = al_create_event_queue();
	if (display == NULL || event_queue == NULL) {
		show_err_msg(-5);
	}
	// Initialize Allegro settings
	al_set_window_position(display, 0, 0);
	al_set_window_title(display, title);
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_image_addon();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	// Register event
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void load_data() {
	//bgm
	menu_bgm = al_load_sample("Undertale OST_ 002 - Start Menu.mp3");
	village_bgm = al_load_sample("01_True.mp3");
	INN_bgm = al_load_sample("Undertale OST_ 012 - Home.mp3");
	if (INN_bgm == NULL)
		show_err_msg(56);
	grocerystore_bgm = al_load_sample("Undertale OST_ 023 - Shop.mp3");

	//se

	//map
	menu_bg = al_load_bitmap("menu.jpg");
	village_bg = al_load_bitmap("map_village.png");
	INN_bg = al_load_bitmap("map_village_INN.png");
	grocerystore_bg = al_load_bitmap("map_village_grocerystore.jpg");

	//font
	menu_font = al_load_ttf_font("PAPYRUS.ttf", 20, 0);

}

void game_begin() {
	load_data();
	/* Load sound
	if (!song) {
		printf("Audio clip sample not loaded!\n");
		show_err_msg(-6);
	}*/
	// Loop the song until the display closes
	al_play_sample(menu_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	//haven't solve the problem that change the background of title scene
	//al_draw_bitmap(menu_bg, 0, 0, 0);
	al_clear_to_color(al_map_rgb(100, 100, 100));


	// Load and draw text

	al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 200, ALLEGRO_ALIGN_CENTRE,
		"Press  'Enter'  to start");
	al_draw_rectangle(WIDTH / 2 - 150, 645, WIDTH / 2 + 150, 685, al_map_rgb(255, 255, 255), 0);
	al_flip_display();
}

int process_event() {
	// Request the event
	ALLEGRO_EVENT event;
	al_wait_for_event(event_queue, &event);

	// Our setting for controlling animation
	if (event.timer.source == timer) {
		if (character2.x < - 150) dir = false;
		else if (character2.x > WIDTH + 50) dir = true;

		if (dir) character2.x -= 10;
		else character2.x += 10;
	}
	if (event.timer.source == timer2) {
		ture = false;
		next = true;
	}
	if (event.timer.source == timer3) {
		if (next) next = false;
		else ture = true;
	}

	// Keyboard
	if (event.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (event.keyboard.keycode)
		{
			// Control
		case ALLEGRO_KEY_W:
			if (character1.y > 0)
				character1.y -= 25;
			break;
		case ALLEGRO_KEY_S:
			if (character1.y < HEIGHT - 100)
				character1.y += 25;
			break;
		case ALLEGRO_KEY_A:
			if (character1.x > 0)
				character1.x -= 25;
			break;
		case ALLEGRO_KEY_D:
			if (character1.x < WIDTH - 75)
				character1.x += 25;
			break;

			// For Start Menu
		case ALLEGRO_KEY_ENTER:
			judge_next_window = true;
			break;
		}
	}
	// Shutdown our program
	else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		return GAME_TERMINATE;
	event_window();
	return 0;
}

void event_window(){
	if (window == 2) {//in the village
		if (character1.x == 300 && character1.y == HEIGHT - 150 - 75) {//walk into INN
			window = 3;
			//al_draw_bitmap(INN_bg, 0, 0, 0);
			al_stop_sample(&village_bgm_id);
			//al_destroy_sample(village_bgm);
			if (!al_play_sample(INN_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &INN_bgm_id))
				show_err_msg(4);
			character1.x = WIDTH / 2 - 25;
			character1.y = 800 - 25;
		}
		else if (character1.x == 300 - 200 && character1.y == HEIGHT - 150 - 75) {//walk into grocery store
			window = 4;
			//al_draw_bitmap(grocerystore_bg, 0, 0, 0);
			al_stop_sample(&village_bgm_id);
			//al_destroy_sample(village_bgm);
			al_play_sample(grocerystore_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &grocerystore_bgm_id);
			character1.x = 675;
			character1.y = 800 - 275;
		}
		//else if...
	}
	else if (window == 3) {
		if (character1.x == WIDTH / 2 - 25 && character1.y == 800) {//from INN back to village
			window = 2;
			//al_draw_bitmap(village_bg, 0, 0, 0);
			al_stop_sample(&INN_bgm_id);
			//al_destroy_sample(INN_bgm);
			al_play_sample(village_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &village_bgm_id);
			character1.x = 300;
			character1.y = HEIGHT - 150 - 50;
		}

		//還沒完成，二樓不得上去
		else if (/*(character1.x == 300 + 9 * 25 || character1.x == 300 + 10 * 25) && */character1.y == 800 - 24 * 25) {
			pop_up_window = true;

			/*if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				if ()
			}*/
	

			/*if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				// Event for keyboard key down.
				game_log("Key with keycode %d down", event.keyboard.keycode);
				key_state[event.keyboard.keycode] = true;

			}*/
		}
	}
	else if (window == 4 && character1.y == 800 - 250 && character1.x == 675) {//from grocery store back to village
		window = 2;
		//al_draw_bitmap(village_bg, 0, 0, 0);
		al_stop_sample(&grocerystore_bgm_id);
		//al_destroy_sample(grocerystore_bgm);
		al_play_sample(village_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &village_bgm_id);
		character1.x = 300 - 200;
		character1.y = HEIGHT - 150 - 50;
	}

	/*else if (window == 5) {
		background = al_load_bitmap("map_village_bar.png");

	}
	else if (window == 6) {
		background = al_load_bitmap("map_village_defensewearstore.png");

	}
	else if (window == 7) {
		background = al_load_bitmap("map_village_weaponstore.png");

	}
	else if (window == 8) {
		background = al_load_bitmap("map_village_specialhouse.png");

	}*/

}

int game_run() {
	int error = 0;
	// First window(Menu)
	if (window == 1) {
		if (!al_is_event_queue_empty(event_queue)) {
			//al_stop_sample(&menu_bgm_id);
			//al_play_sample(village_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &village_bgm_id);
			error = process_event();
			if (judge_next_window) {
				window = 2;
				al_stop_sample(&menu_bgm_id);
				al_play_sample(village_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &village_bgm_id);
				// Setting Character
				character1.x = 300;
				character1.y = HEIGHT - 150;
				character2.x = WIDTH + 100;
				character2.y = HEIGHT / 2 - 280;
				character1.image_path = al_load_bitmap("tower.png");
				character2.image_path = al_load_bitmap("teemo_left.png");
				character3.image_path = al_load_bitmap("teemo_right.png");
				//village_bg;

				//Initialize Timer
				timer = al_create_timer(1.0 / 15.0);
				timer2 = al_create_timer(1.0);
				timer3 = al_create_timer(1.0 / 10.0);
				al_register_event_source(event_queue, al_get_timer_event_source(timer));
				al_register_event_source(event_queue, al_get_timer_event_source(timer2));
				al_register_event_source(event_queue, al_get_timer_event_source(timer3));
				al_start_timer(timer);
				al_start_timer(timer2);
				al_start_timer(timer3);
			}
		}
	}
	// Second window(Main Game)
	else if (window > 1) {
		// Change Image for animation
		if (window == 2) {
			al_draw_bitmap(village_bg, 0, 0, 0);
		}
		if (window == 3) {
			al_draw_bitmap(INN_bg, 0, 0, 0);
			if (pop_up_window == 1) {
				al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 210, ALLEGRO_ALIGN_CENTRE,
					"Please pay for DLC! Press 'Enter' to continue");
				al_draw_rectangle(WIDTH / 2 - 150, 645, WIDTH / 2 + 150, 685, al_map_rgb(255, 255, 255), 0);
				al_flip_display();
			}
		}
		if (window == 4)
			al_draw_bitmap(grocerystore_bg, 0, 0, 0);
		
		//if (1)
		al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);

		//if (dir) al_draw_bitmap(character2.image_path, character2.x, character2.y, 0);
		//else al_draw_bitmap(character3.image_path, character2.x, character2.y, 0);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		// Listening for new event
		if (!al_is_event_queue_empty(event_queue)) {
			error = process_event();
		}
	}

	
	return error; 
}

void game_destroy() {
	// Make sure you destroy all things
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_timer(timer2);
	al_destroy_bitmap(image);

	//al_stop_sample(song);
	//al_destroy_sample(song);
}



/*bool pnt_in_rect(int px, int py, int x, int y, int w, int h)
{
	if (px >= x && px <= x + w && py >= y && py <= y + h)
		return true;
	else
		return false;
}*/