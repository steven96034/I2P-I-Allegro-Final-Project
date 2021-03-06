//final project template
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define LOG_ENABLED

#define GAME_TERMINATE -1

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

//character
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *image2 = NULL;
ALLEGRO_BITMAP *image3 = NULL;
ALLEGRO_BITMAP *Light_Dot = NULL;

//picture
ALLEGRO_BITMAP *Healing_Potion = NULL;
ALLEGRO_BITMAP *An_One_Thousand_Dollar_Paper_Banknote = NULL;
ALLEGRO_BITMAP *Samurai_Sword = NULL;
ALLEGRO_BITMAP *Gods_Sword_Plastic_Bottle = NULL;
ALLEGRO_BITMAP *UnderArmor = NULL;
ALLEGRO_BITMAP *Maples_Shield = NULL;
ALLEGRO_BITMAP *The_Boardshort_Stuffed_with_One_Million_Dollars = NULL;
ALLEGRO_BITMAP *victorypicture = NULL;
ALLEGRO_BITMAP *defeatedpicture = NULL;
ALLEGRO_BITMAP *Potion1 = NULL;
ALLEGRO_BITMAP *Potion2 = NULL;
ALLEGRO_BITMAP *Potion3 = NULL;
ALLEGRO_BITMAP *Potion4 = NULL;
ALLEGRO_BITMAP *POtion1 = NULL;
ALLEGRO_BITMAP *POtion2 = NULL;
ALLEGRO_BITMAP *POtion3 = NULL;
ALLEGRO_BITMAP *POtion4 = NULL;
ALLEGRO_BITMAP *Teach = NULL;

//keyboard
ALLEGRO_KEYBOARD_STATE keyState;

//timer
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TIMER *timer2 = NULL;
ALLEGRO_TIMER *timer3 = NULL;
ALLEGRO_TIMER* game_update_timer;

//bgm
ALLEGRO_SAMPLE *title_bgm = NULL;
ALLEGRO_SAMPLE *village_bgm = NULL;
ALLEGRO_SAMPLE *INN_bgm = NULL;
ALLEGRO_SAMPLE *grocerystore_bgm = NULL;
ALLEGRO_SAMPLE *Bossmusic = NULL;
ALLEGRO_SAMPLE *Dungeonmusic = NULL;
ALLEGRO_SAMPLE *victory = NULL;
ALLEGRO_SAMPLE *defeated = NULL;
ALLEGRO_SAMPLE *strikesound = NULL; 
ALLEGRO_SAMPLE *strikesound2 = NULL;

//bgm id
ALLEGRO_SAMPLE_ID title_bgm_id = { 0 };
ALLEGRO_SAMPLE_ID village_bgm_id = { 0 };
ALLEGRO_SAMPLE_ID INN_bgm_id = { 0 };
ALLEGRO_SAMPLE_ID grocerystore_bgm_id = { 0 };
ALLEGRO_SAMPLE_ID Bossmusic_id = { 0 };
ALLEGRO_SAMPLE_ID Dungeonmusic_id = { 0 };
ALLEGRO_SAMPLE_ID victory_id = { 0 };
ALLEGRO_SAMPLE_ID defeated_id = { 0 };

//background
ALLEGRO_BITMAP *title_bg = NULL;
ALLEGRO_BITMAP *menu_bg = NULL;
ALLEGRO_BITMAP *village_bg = NULL;
ALLEGRO_BITMAP *INN_bg = NULL;
ALLEGRO_BITMAP *grocerystore_bg = NULL;
ALLEGRO_BITMAP *dungeon_map = NULL;

//setting(battle)
ALLEGRO_BITMAP* backgroud = NULL;
ALLEGRO_BITMAP* Board = NULL;
ALLEGRO_BITMAP* hero = NULL;

//mon
ALLEGRO_BITMAP* Chosen = NULL;
ALLEGRO_BITMAP* Cultist = NULL;
ALLEGRO_BITMAP* Louse = NULL;

//card
ALLEGRO_BITMAP* Bash = NULL;
ALLEGRO_BITMAP* Cleave = NULL;
ALLEGRO_BITMAP* Defend = NULL;
ALLEGRO_BITMAP* Ironwave = NULL;
ALLEGRO_BITMAP* Strike = NULL;

//setting of Boss
ALLEGRO_BITMAP* Boss = NULL;
ALLEGRO_BITMAP* Bossroom = NULL;

//font
ALLEGRO_FONT *menu_font = NULL;
ALLEGRO_FONT *font = NULL;
ALLEGRO_FONT *title_font_a = NULL;
ALLEGRO_FONT *title_font_b = NULL;



//Custom Definition
const char *title = "Final Project 108030001 108030027";
const float FPS = 60;
const int WIDTH = 900;
const int HEIGHT = 900;
const int SCREEN_W = 900;
const int SCREEN_H = 900;

//set the game direction
int turn = 1;
int tower=1;

typedef struct character
{
	int x;
	int y;
	ALLEGRO_BITMAP *image_path;

}Character;

Character character1;
Character character2;
Character character3;
Character light_dot;

typedef struct {
	int valid;
	int cost;
	int armour;
	int damage;
	int vulnerable;
	int aoe;
	int index;

}card;

typedef struct {
	int hp;
	int atk;
	int interval;
	int money;

}mon;

typedef struct {
	int hp;
	int atk;
	int buff;
	int armour;
	int mana;
	int aoe;
	int money;
}warrior;

// set the card
card bash;
card cleave;
card  defend;
card  ironwave;
card  strike;

//set the potion
card potion1;
card potion2;
card potion3;
card potion4;

//set the random
card card1;
card card2;
card card3;
card card4;
card card5;

//set the monsters  
// hp;atk;interval;money;
mon  louse;           
mon  cultist;
mon  chosen;
mon boss;

//set the stage
int stage;

//set the hero
warrior man;


int imageWidth = 0;
int imageHeight = 0;
int draw = 0;
int done = 0;
int judge_next_window = 0;
int window = 1;
int message_number = 0;
int menu_number_chose = 0;


bool pop_up_window = false;
bool check_boundary(int x, int y);
bool check_purchase = false;
bool check_purchase_frame = false;
bool check_purchase_final = false;
bool money_shortage = false;
bool ture = true; //true: appear, false: disappear
bool next = false; //true: trigger
bool dir = true; //true: left, false: right
bool key_state[ALLEGRO_KEY_MAX];

float x, y;
int check_mana();
void on_key_down(int keycode);
void resetmonster();

void game_abort(const char* format, ...);
void game_init();
void load_data();
void game_set();
void game_begin();
int process_event();
void event_window();
int game_run();
void game_destroy();

void game_log(const char* format, ...);
void game_vlog(const char* format, va_list arg);


//Main Status
int money = 1000;//set initial amount
int hp_max = 50;//set initial amount
int hp_now = 40;//set initial amount

//Main Inventory
int amount_of_Healing_Potion = 0;
int amount_of_An_One_Thousand_Dollar_Paper_Banknote = 0;
int amount_of_Samurai_Sword = 0;
int amount_of_Gods_Sword_Plastic_Bottle = 0;
int amount_of_UnderArmor = 0;
int amount_of_Maples_Shield = 0;
int amount_of_The_Boardshort_Stuffed_with_One_Million_Dollars = 0;


int main(int argc, char *argv[]) {
	int msg = 0;
	game_set();
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

void game_init() {
	if (!al_init()) {
		game_abort("Initialize error.\n");
	}
	if (!al_install_audio()) {
		fprintf(stderr, "failed to initialize audio!\n");
		game_abort("Install audio error.\n");
	}
	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize audio codecs!\n");
		game_abort("Initialize audio codecs error.\n");
	}
	if (!al_reserve_samples(10)) {
		fprintf(stderr, "failed to reserve samples!\n");
		game_abort("Reserve samples error.\n");
	}
	// Create display
	display = al_create_display(WIDTH, HEIGHT);
	event_queue = al_create_event_queue();
	if (display == NULL || event_queue == NULL) {
		game_abort("display or event_queue equal to null.\n");
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
	title_bgm = al_load_sample("Undertale OST_ 002 - Start Menu.mp3");
	if (!title_bgm)
		game_abort("failed to load bgm: title_bgm");
	Bossmusic = al_load_sample("battle in boss.mp3");
	if (!Bossmusic)
		game_abort("failed to load bgm: Bossmusic");
	Dungeonmusic = al_load_sample("battle.mp3");
	if (!Dungeonmusic)
		game_abort("failed to load bgm: Dungeonmusic");
	village_bgm = al_load_sample("01_True.mp3");
	if (!village_bgm)
		game_abort("failed to load bgm: village_bgm");
	INN_bgm = al_load_sample("Undertale OST_ 012 - Home.mp3");
	if (!INN_bgm)
		game_abort("failed to load bgm: INN_bgm");
	grocerystore_bgm = al_load_sample("Undertale OST_ 023 - Shop.mp3");
	if (!grocerystore_bgm)
		game_abort("failed to load bgm: grocerystore_bgm");
	victory = al_load_sample("victory.mp3");
	if (!victory)
		game_abort("failed to load bgm: victory");
	defeated = al_load_sample("defeated.mp3");
	if (!defeated)
		game_abort("failed to load bgm: defeated");
	strikesound = al_load_sample("strike2.mp3");
	strikesound2 = al_load_sample("strike sound.mp3");

	//se

	//map
	title_bg = al_load_bitmap("menu.jpg");
	if (!title_bg)
		game_abort("failed to load map: title_bg");
	village_bg = al_load_bitmap("map_village.png");
	if (!village_bg)
		game_abort("failed to load map: village_bg");
	INN_bg = al_load_bitmap("map_village_INN.png");
	if (!INN_bg)
		game_abort("failed to load map: INN_bg");
	grocerystore_bg = al_load_bitmap("map_village_grocerystore.jpg");
	if (!grocerystore_bg)
		game_abort("failed to load map: grocerystore_bg");
	//load the battle background
	backgroud = al_load_bitmap("dungeon.jpg");
	if (!backgroud)
		game_abort("failed to load image: dungeon");
	Board = al_load_bitmap("Board.jpg");
	if (!Board)
		game_abort("failed to load image:  Board");
	hero = al_load_bitmap("hero.png");
	if (!hero)
		game_abort("failed to load image: hero");
	dungeon_map = al_load_bitmap("dungeon_map.png");
	if (!dungeon_map)
		game_abort("failed to load image: hero");


	//picture
	Healing_Potion = al_load_bitmap("Healing_Potion.jpg");
	if (!Healing_Potion)
		game_abort("failed to load picture: Healing_Potion");
	An_One_Thousand_Dollar_Paper_Banknote = al_load_bitmap("An_One_Thousand_Dollar_Paper_Banknote.jpg");
	if (!An_One_Thousand_Dollar_Paper_Banknote)
		game_abort("failed to load picture: An_One_Thousand_Dollar_Paper_Banknote");
	Samurai_Sword = al_load_bitmap("Samurai_Sword.jpg");
	if (!Samurai_Sword)
		game_abort("failed to load picture: Samurai_Sword");
	Gods_Sword_Plastic_Bottle = al_load_bitmap("Gods_Sword_Plastic_Bottle.jpg");
	if (!Gods_Sword_Plastic_Bottle)
		game_abort("failed to load picture: Gods_Sword_Plastic_Bottle");
	UnderArmor = al_load_bitmap("UnderArmor.jpg");
	if (!UnderArmor)
		game_abort("failed to load picture: UnderArmor");
	Maples_Shield = al_load_bitmap("Maples_Shield.jpg");
	if (!Maples_Shield)
		game_abort("failed to load picture: Maples_Shield");
	The_Boardshort_Stuffed_with_One_Million_Dollars = al_load_bitmap("The_Boardshort_Stuffed_with_One_Million_Dollars.jpg");
	if (!The_Boardshort_Stuffed_with_One_Million_Dollars)
		game_abort("failed to load picture: The_Boardshort_Stuffed_with_One_Million_Dollars");
	Potion1 = al_load_bitmap("potion1.png");
	if (!Potion1)
		game_abort("failed to load picture: Potion1");
	Potion2 = al_load_bitmap("potion2.png");
	if (!Potion2)
		game_abort("failed to load picture: Potion2");
	Potion3 = al_load_bitmap("potion3.png");
	if (!Potion3)
		game_abort("failed to load picture: Potion3");
	Potion4 = al_load_bitmap("potion4.png");
	if (!Potion4)
		game_abort("failed to load picture: Potion4");
	POtion1 = al_load_bitmap("potion_big1.png");
	if (!POtion1)
		game_abort("failed to load picture: POtion1");
	POtion2 = al_load_bitmap("potion_big2.png");
	if (!POtion2)
		game_abort("failed to load picture: POtion2");
	POtion3 = al_load_bitmap("potion_big3.png");
	if (!POtion3)
		game_abort("failed to load picture: POtion3");
	POtion4 = al_load_bitmap("potion_big4.png");
	if (!POtion4)
		game_abort("failed to load picture: POtion4");
	victorypicture = al_load_bitmap("victorypicture.jpg");
	if (!victorypicture)
		game_abort("failed to load picture: victorypicture");
	defeatedpicture = al_load_bitmap("defeatedpicture.png");
	if (!defeatedpicture)
		game_abort("failed to load picture: defeatedpicture");
	Teach = al_load_bitmap("teach.png");
	if (!Teach)
		game_abort("failed to load picture: teach");

	//font
	menu_font = al_load_ttf_font("NotoSansCJKtc-Medium.otf", 20, 0);
	if (!menu_font)
		game_abort("failed to load font: menu_font");
	font = al_load_ttf_font("pirulen.ttf", 12, 0);
	if (!font)
		game_abort("failed to load font: pirulen.ttf");
	title_font_a = al_load_ttf_font("PAPYRUS.ttf",42, 2);
	if (!title_font_a)
		game_abort("failed to load font: title_font_a");
	title_font_b = al_load_ttf_font("PAPYRUS.ttf", 16, 2);
	if (!title_font_b)
		game_abort("failed to load font: title_font_b");


	//load the mon
	Chosen = al_load_bitmap("Chosen.png");
	if (!Chosen)
		game_abort("failed to load image: Chosen");
	Cultist = al_load_bitmap("Cultist.png");
	if (!Cultist)
		game_abort("failed to load image: Cultist");
	Louse = al_load_bitmap("Louse.png");
	if (!Louse)
		game_abort("failed to load image: Louse");
	//Boss
	Boss = al_load_bitmap("Boss.png");
	if (!Boss)
		game_abort("failed to load image: Boss");
	Bossroom = al_load_bitmap("Bossroom.jpg");
	if (!Bossroom)
		game_abort("failed to load image: Bossroom");

	//card
	Bash = al_load_bitmap("Bash.png");
	if (!Bash)
		game_abort("failed to load image: Bash");
	Cleave = al_load_bitmap("Cleave.png");
	if (!Cleave)
		game_abort("failed to load image: Cleave");
	Defend = al_load_bitmap("Defend.png");
	if (!Defend)
		game_abort("failed to load image: Defend");
	Ironwave = al_load_bitmap("Ironwave.png");
	if (!Ironwave)
		game_abort("failed to load image: Ironwave");
	Strike = al_load_bitmap("Strike.png");
	if (!Strike)
		game_abort("failed to load image: Strike");
}

void game_set() {
	//tell what monster is fighting now!!
	stage = 3;

	bash.valid = 1;
	bash.cost = 2;
	bash.armour = 0;
	bash.damage = 8;
	bash.vulnerable = 2;
	bash.aoe = 0;
	bash.index = 1;


	cleave.valid = 1;
	cleave.cost = 1;
	cleave.armour = 0;
	cleave.damage = 8;
	cleave.vulnerable = 0;
	cleave.aoe = 1;
	cleave.index = 2;


	defend.valid = 1;
	defend.cost = 1;
	defend.armour = 5;
	defend.damage = 0;
	defend.vulnerable = 0;
	defend.aoe = 0;
	defend.index = 3;


	ironwave.valid = 1;
	ironwave.cost = 1;
	ironwave.armour = 5;
	ironwave.damage = 5;
	ironwave.vulnerable = 0;
	ironwave.aoe = 0;
	ironwave.index = 4;


	strike.valid = 1;
	strike.cost = 1;
	strike.armour = 0;
	strike.damage = 6;
	strike.vulnerable = 0;
	strike.aoe = 0;
	strike.index = 5;

	potion1.valid = 1;
	potion1.cost = 0;
	potion1.armour = 0;
	potion1.damage = 0;
	potion1.vulnerable = 4;
	potion1.aoe = 0;
	potion1.index = 6;

	potion2.valid = 1;
	potion2.cost = 0;
	potion2.armour = 0;
	potion2.damage = 100;
	potion2.vulnerable = 0;
	potion2.aoe = 0;
	potion2.index = 6;


	potion3.valid = 1;
	potion3.cost = 0;
	potion3.armour = 20;
	potion3.damage = 0;
	potion3.vulnerable = 0;
	potion3.aoe = 0;
	potion3.index = 6;

	potion4.valid = 1;
	potion4.cost = 0;
	potion4.armour = 0;
	potion4.damage = 0;
	potion4.vulnerable = 0;
	potion4.aoe = 100;  //hp �W�� !
	potion4.index = 6;


	louse.hp = 75;
	louse.atk = 10;
	louse.interval = 1;
	louse.money = 100;

	cultist.hp = 120;
	cultist.atk = 20;
	cultist.interval = 2;
	cultist.money = 200;


	chosen.hp = 210;
	chosen.atk = 35;
	chosen.interval = 3;
	chosen.money = 400;

	boss.hp = 500;
	boss.atk = 50;
	boss.interval = 4;
	boss.money = 1000;


	man.hp = 300;
	man.atk = 0;
	man.armour = 0;
	man.buff = 0;
	man.mana = 4;
	man.aoe = 0;
	man.money = money;

}
card  shuffle(int x) {

	if (x >= 1 && x <= 3) {

		card y;
		y = bash;
		y.index = 1;
		return y;
	}

	if (x >= 4 && x <= 6) {
		card y;
		y = cleave;
		y.index = 2;
		return y;
	}

	if (x >= 7 && x <= 11) {
		card y;
		y = defend;
		y.index = 3;
		return y;
	}

	if (x >= 12 && x <= 15) {
		card y;
		y = ironwave;
		y.index = 4;
		return y;
	}

	if (x >= 16 && x <= 20) {
		card y;
		y = strike;
		y.index = 5;
		return y;
	}
}




int random(void) {
	int a;
	a = (rand() % 20) + 1;
	printf("%d\n", a);
	return a;
}

void game_begin() {
	load_data();
	al_play_sample(title_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	al_draw_bitmap(title_bg, 0, 0, 0);
	al_draw_text(title_font_a, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 300, ALLEGRO_ALIGN_CENTRE,
		"Monster Chaser");
	al_draw_text(title_font_b, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 200, ALLEGRO_ALIGN_CENTRE,
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
		if (character2.x < -150) dir = false;
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
	on_key_down(event.keyboard.keycode);
	
	// Shutdown our program
	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		return GAME_TERMINATE;
	event_window();
	return 0;
}


void resetmonster() {
	if (boss.hp <= 0) {
		al_stop_sample(&Dungeonmusic_id);
		al_play_sample(victory, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);		
		al_draw_bitmap(victorypicture, 0, 0, 0);
		al_draw_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(255, 255, 255), 5);
		al_draw_text(title_font_a, al_map_rgb(125, 255, 125), WIDTH / 2 , HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE,
			"You win!!!");
		al_flip_display();
		process_event;
	}
	louse.hp = 75;
	louse.atk = 10;
	louse.interval = 1;
	louse.money = 100;

	cultist.hp = 120;
	cultist.atk = 20;
	cultist.interval = 2;
	cultist.money = 200;

	chosen.hp = 210;
	chosen.atk = 35;
	chosen.interval = 3;
	chosen.money = 400;

	boss.hp = 500;
	boss.atk = 50;
	boss.interval = 4;
	boss.money = 1000;
	turn = 1;
	tower++;
	return;
}

void on_key_down(int keycode) {
	if ((boss.hp <= 0 || man.hp <= 0) && keycode == ALLEGRO_KEY_ENTER) {
		window = 1;
		judge_next_window = 0;
		stage = 1;
		game_begin();		
	}
	if (window == 1 && judge_next_window == 0) {
		if (keycode == ALLEGRO_KEY_ENTER)
			window = 2;
	}
	if (window == 2 && judge_next_window == 0) {
		if (keycode == ALLEGRO_KEY_ENTER)
			judge_next_window = 1;
	}
	if (judge_next_window == 1) {
		if ((window == 2 || window == 3 || window == 4) && pop_up_window == false) {
			switch (keycode) {
			case ALLEGRO_KEY_W:
				if (character1.y > 0 && check_boundary(character1.x, character1.y - 25)) {
					character1.y -= 25;
					printf("(%d,%d)\n", character1.x, character1.y);
				}
				break;
			case ALLEGRO_KEY_S:
				if (character1.y < HEIGHT - 100 && check_boundary(character1.x, character1.y + 25)) {
					character1.y += 25;
					printf("(%d,%d)\n", character1.x, character1.y);
				}
				break;
			case ALLEGRO_KEY_A:
				if (character1.x > 0 && check_boundary(character1.x - 25, character1.y)) {
					character1.x -= 25;
					printf("(%d,%d)\n", character1.x, character1.y);
				}
				break;
			case ALLEGRO_KEY_D:
				if (character1.x < WIDTH - 75 && check_boundary(character1.x + 25, character1.y)) {
					character1.x += 25;
					printf("(%d,%d)\n", character1.x, character1.y);
				}
			}
		}
		else if (window == 3 && character1.y == 175) {
			if (keycode == ALLEGRO_KEY_ENTER) {
				pop_up_window = false;
				character1.y += 25;
			}
		}
		else if (window == 3 && character1.x == 525 && character1.y == 375) {
			if (message_number == 0 && keycode == ALLEGRO_KEY_ENTER)
				message_number++;
			else if (message_number == 1) {
				if (keycode == ALLEGRO_KEY_Z) {
					message_number = 4;
					printf("heal(need to check enough money)~~~~~~\n");
				}
				else if (keycode == ALLEGRO_KEY_X) {
					message_number = 3;
					printf("no~~~~~\n");
				}
			}
			else if (message_number == 2 && keycode == ALLEGRO_KEY_ENTER) {
				message_number = 5;
				printf("just before in yes scene~~~\n");

			}
			else if (message_number == 3 && keycode == ALLEGRO_KEY_ENTER) {
				message_number = 5;
				printf("just before in no scene~~~\n");
			}
			else if (message_number == 11) {
				if (money >= 81000)
					money -= 81000;
				else
					money -= 1200;
				hp_now = hp_max;
				message_number = 2;
			}
			else if (message_number == 5 && keycode == ALLEGRO_KEY_ENTER) {
				message_number = 0;
				pop_up_window = false;
				printf("final~~\n");
				character1.y += 25;
			}
		}
		else if (window == 4 && character1.x == 675 && character1.y == 300) {
			if (message_number == 0 && keycode == ALLEGRO_KEY_ENTER)
				message_number++;
			else if (message_number == 1) {
				if (menu_number_chose == 0) {
					if (keycode == ALLEGRO_KEY_1 || keycode == ALLEGRO_KEY_PAD_1) {
						menu_number_chose = 1;
						printf("choose 1\n");
					}
					else if (keycode == ALLEGRO_KEY_2 || keycode == ALLEGRO_KEY_PAD_2) {
						menu_number_chose = 2;
						printf("choose 2\n");
					}
					else if (keycode == ALLEGRO_KEY_3 || keycode == ALLEGRO_KEY_PAD_3) {
						menu_number_chose = 3;
						printf("choose 3\n");
					}
					else if (keycode == ALLEGRO_KEY_4 || keycode == ALLEGRO_KEY_PAD_4) {
						menu_number_chose = 4;
						printf("choose 4\n");
					}
					else if (keycode == ALLEGRO_KEY_5 || keycode == ALLEGRO_KEY_PAD_5) {
						menu_number_chose = 5;
						printf("choose 5\n");
					}
					else if (keycode == ALLEGRO_KEY_6 || keycode == ALLEGRO_KEY_PAD_6) {
						menu_number_chose = 6;
						printf("choose 6\n");
					}
					else if (keycode == ALLEGRO_KEY_7 || keycode == ALLEGRO_KEY_PAD_7) {
						menu_number_chose = 7;
						printf("choose 7\n");
					}
					else if (keycode == ALLEGRO_KEY_X) {
						message_number++;
						printf("exit\n");
					}
				}
				else if (menu_number_chose != 0) {
					if (check_purchase == false) {
						if (keycode == ALLEGRO_KEY_Z) {
							check_purchase = true;
							printf("check_purchase = true\n");
						}
						else if (keycode == ALLEGRO_KEY_X) {
							menu_number_chose = 0;
							printf("menu_number_chose = 0\n");
							printf("exit\n");
						}
					}
					else if (check_purchase == true) {
						if (money_shortage == true && keycode == ALLEGRO_KEY_Z) {
							money_shortage = false;
							check_purchase_final = false;
							check_purchase = false;
							printf("money_shortage = false\n");
							printf("check_purchase_final = false\n");
						}
						else if (keycode == ALLEGRO_KEY_Z) {
							check_purchase_final = true;
							printf("check_purchase_final = true\n");
						}
						else if (keycode == ALLEGRO_KEY_X) {
							check_purchase = false;
							printf("check_purchase = false\n");
							printf("exit\n");
						}
					}
				}
			}
			else if (message_number == 2) {
				if (keycode == ALLEGRO_KEY_ENTER) {
					message_number = 0;
					pop_up_window = false;
					printf("final~~~\n");
					character1.y += 25;
				}
			}
		}
	}
	//battle
	else if (judge_next_window == 2) {
		//attack from heros!
		if (turn == 1) {
			card1 = bash;
			card2 = cleave;
			card3 = defend;
			card4 = ironwave;
			card5 = strike;
		}
		if (keycode == ALLEGRO_KEY_Q && potion1.valid > 0) {

			potion1.valid = potion1.valid - 1;
			man.buff = man.buff + 4;
		}
		if (keycode == ALLEGRO_KEY_W && potion2.valid > 0) {
			potion2.valid = potion2.valid - 1;
			if (stage == 1)louse.hp = louse.hp - 100;
			if (louse.hp <= 0) {
				man.money = man.money + louse.money;
				money = man.money;
				judge_next_window = 3;
				window = 0;
				character1.x = 425;
				character1.y = 800;
				resetmonster();
			}
			if (stage == 2)cultist.hp = cultist.hp - 100;
			if (cultist.hp <= 0) {
				man.money = man.money + cultist.money;
				money = man.money;
				judge_next_window = 3;
				window = 0;
				character1.x = 425;
				character1.y = 800;
				resetmonster();
			}
			if (stage == 3)chosen.hp = chosen.hp - 100;
			if (chosen.hp <= 0) {
				man.money = man.money + chosen.money;
				money = man.money;
				judge_next_window = 3;
				window = 0;
				character1.x = 425;
				character1.y = 800;
				resetmonster();
			}
			if (stage == 4)boss.hp = boss.hp - 100;
			if (boss.hp <= 0) {
				man.money = man.money + boss.money;
				money = man.money;
				judge_next_window = 3;
				window = 1;
				resetmonster();
				//win
			}
		}
		if (keycode == ALLEGRO_KEY_E && potion3.valid > 0) {
			potion3.valid = potion3.valid - 1;
			man.armour = man.armour + potion3.armour;
		}
		if (keycode == ALLEGRO_KEY_R && potion4.valid > 0) {
			potion4.valid = potion4.valid - 1;
			man.hp = man.hp + potion4.aoe;
		}

		if (keycode == ALLEGRO_KEY_1) {
			if (man.mana - card1.cost >= 0 && card1.valid == 1) {
				card1.valid = 0;
				man.mana = man.mana - card1.cost;
				man.armour = card1.armour + man.armour;
				man.atk = card1.damage;
				man.buff = card1.vulnerable;
				al_play_sample(strikesound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				printf("Use card1!\n");
				if (stage == 1) {
					if (man.buff >= 1)man.buff--;
					louse.hp = louse.hp - man.atk - man.buff*man.atk;
					
					if (louse.hp <= 0) {
						man.money = man.money + louse.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						louse.interval--;
						if (louse.interval == 0) {
							man.hp = man.hp - louse.atk + man.armour;
							louse.interval = 1;
						}
					}
				}
				if (stage == 2) {
					if (man.buff >= 1)man.buff--;
					cultist.hp = cultist.hp - man.atk - man.buff*man.atk;
					if (cultist.hp <= 0) {
						man.money = man.money + cultist.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0||(man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						cultist.interval--;
						if (cultist.interval == 0) {
							man.hp = man.hp - cultist.atk + man.armour;
							cultist.interval = 2;
						}
					}
				}
				if (stage == 3) {
					if (man.buff >= 1)man.buff--;
					chosen.hp = chosen.hp - man.atk - man.buff*man.atk;
					if (chosen.hp <= 0) {
						man.money = man.money + chosen.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						chosen.interval--;
						if (chosen.interval == 0) {
							man.hp = man.hp - chosen.atk + man.armour;
							chosen.interval = 3;
						}
					}
				}
				if (stage == 4) {
					if (man.buff >= 1)man.buff--;
					boss.hp = boss.hp - man.atk - man.buff*man.atk;
					if (boss.hp <= 0) {
						man.money = man.money + boss.money;
						money = man.money;
						judge_next_window = 3;
						window = 1;
						resetmonster();
						//win
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());
						turn++;
						boss.interval--;
						if (boss.interval == 0) {
							man.hp = man.hp - boss.atk + man.armour;
							boss.interval = 4;
						}
					}
				}
			}
			else if (bash.valid == 0 && man.mana > 0)printf("You have used the card1!\n");
			else if (man.mana <= 0) {

				printf("You have no mana!\n");
			}
		}
		else if (keycode == ALLEGRO_KEY_2) {
			if (man.mana - card2.cost >= 0 && card2.valid == 1) {

				card2.valid = 0;
				man.mana = man.mana - card2.cost;
				man.armour = card2.armour + man.armour;
				man.atk = card2.damage;
				man.buff = card2.vulnerable;
				al_play_sample(strikesound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				printf("Use card2!\n");
				if (stage == 1) {
					if (man.buff >= 1)man.buff--;
					louse.hp = louse.hp - man.atk - man.buff*man.atk;
					if (louse.hp <= 0) {
						man.money = man.money + louse.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {

						turn++;
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());
						louse.interval--;
						if (louse.interval == 0) {
							man.hp = man.hp - louse.atk + man.armour;
							louse.interval = 1;
						}
					}
				}
				if (stage == 2) {
					if (man.buff >= 1)man.buff--;
					cultist.hp = cultist.hp - man.atk - man.buff*man.atk;
					if (cultist.hp <= 0) {
						man.money = man.money + cultist.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						cultist.interval--;
						if (cultist.interval == 0) {
							man.hp = man.hp - cultist.atk + man.armour;
							cultist.interval = 2;
						}
					}
				}
				if (stage == 3) {
					if (man.buff >= 1)man.buff--;
					chosen.hp = chosen.hp - man.atk - man.buff*man.atk;
					if (chosen.hp <= 0) {
						man.money = man.money + chosen.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						chosen.interval--;
						if (chosen.interval == 0) {
							man.hp = man.hp - chosen.atk + man.armour;
							chosen.interval = 3;
						}
					}
				}
				if (stage == 4) {
					if (man.buff >= 1)man.buff--;
					boss.hp = boss.hp - man.atk - man.buff*man.atk;
					if (boss.hp <= 0) {
						man.money = man.money + boss.money;
						money = man.money;
						judge_next_window = 3;
						window = 1;
						resetmonster();
						//win scene
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						boss.interval--;
						if (boss.interval == 0) {
							man.hp = man.hp - boss.atk + man.armour;
							boss.interval = 4;
						}
					}
				}
			}
			else if (cleave.valid == 0 && man.mana > 0)printf("You have used the card2!\n");
			else if (man.mana <= 0) {

				printf("You have no mana!\n");
			}

		}
		else if (keycode == ALLEGRO_KEY_3) {
			if (man.mana - card3.cost >= 0 && card3.valid == 1) {
				card3.valid = 0;
				man.mana = man.mana - card3.cost;
				man.armour = card3.armour + man.armour;
				man.atk = card3.damage;
				man.buff = card3.vulnerable;
				al_play_sample(strikesound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				printf("Use card3!\n");
				if (stage == 1) {
					if (man.buff >= 1)man.buff--;
					louse.hp = louse.hp - man.atk - man.buff*man.atk;
					if (louse.hp <= 0) {
						man.money = man.money + louse.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {

						turn++;
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());
						louse.interval--;
						if (louse.interval == 0) {
							man.hp = man.hp - louse.atk + man.armour;
							louse.interval = 1;
						}
					}
				}
				if (stage == 2) {
					if (man.buff >= 1)man.buff--;
					cultist.hp = cultist.hp - man.atk - man.buff*man.atk;
					if (cultist.hp <= 0) {
						man.money = man.money + cultist.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						cultist.interval--;
						if (cultist.interval == 0) {
							man.hp = man.hp - cultist.atk + man.armour;
							cultist.interval = 2;
						}
					}
				}
				if (stage == 3) {
					if (man.buff >= 1)man.buff--;
					chosen.hp = chosen.hp - man.atk - man.buff*man.atk;
					if (chosen.hp <= 0) {
						man.money = man.money + chosen.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						chosen.interval--;
						if (chosen.interval == 0) {
							man.hp = man.hp - chosen.atk + man.armour;
							chosen.interval = 3;
						}
					}
				}
				if (stage == 4) {
					if (man.buff >= 1)man.buff--;
					boss.hp = boss.hp - man.atk - man.buff*man.atk;
					if (boss.hp <= 0) {
						man.money = man.money + boss.money;
						money = man.money;
						judge_next_window = 3;
						window = 1;
						resetmonster();
						//win scene
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						boss.interval--;
						if (boss.interval == 0) {
							man.hp = man.hp - boss.atk + man.armour;
							boss.interval = 4;
						}
					}
				}
			}
			else if (defend.valid == 0 && man.mana > 0)printf("You have used the card3!\n");
			else if (man.mana <= 0) {

				printf("You have no mana!\n");
			}
		}
		else if (keycode == ALLEGRO_KEY_4) {
			if (man.mana - card4.cost >= 0 && card4.valid == 1) {
				card4.valid = 0;
				man.mana = man.mana - card4.cost;
				man.armour = card4.armour + man.armour;
				man.atk = card4.damage;
				man.buff = card4.vulnerable;
				al_play_sample(strikesound, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				printf("Use card4!\n");

				if (stage == 1) {
					if (man.buff >= 1)man.buff--;
					louse.hp = louse.hp - man.atk - man.buff*man.atk;
					if (louse.hp <= 0) {
						man.money = man.money + louse.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {

						turn++;
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());
						louse.interval--;
						if (louse.interval == 0) {
							man.hp = man.hp - louse.atk + man.armour;
							louse.interval = 1;
						}
					}
				}
				if (stage == 2) {
					if (man.buff >= 1)man.buff--;
					cultist.hp = cultist.hp - man.atk - man.buff*man.atk;
					if (cultist.hp <= 0) {
						man.money = man.money + cultist.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						cultist.interval--;
						if (cultist.interval == 0) {
							man.hp = man.hp - cultist.atk + man.armour;
							cultist.interval = 2;
						}
					}
				}
				if (stage == 3) {
					if (man.buff >= 1)man.buff--;
					chosen.hp = chosen.hp - man.atk - man.buff*man.atk;
					if (chosen.hp <= 0) {
						man.money = man.money + chosen.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						chosen.interval--;
						if (chosen.interval == 0) {
							man.hp = man.hp - chosen.atk + man.armour;
							chosen.interval = 3;
						}
					}
				}
				if (stage == 4) {
					if (man.buff >= 1)man.buff--;
					boss.hp = boss.hp - man.atk - man.buff*man.atk;
					if (boss.hp <= 0) {
						man.money = man.money + boss.money;
						money = man.money;
						judge_next_window = 3;
						window = 1;
						resetmonster();
						//win scene
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());
						turn++;
						boss.interval--;
						if (boss.interval == 0) {
							man.hp = man.hp - boss.atk + man.armour;
							boss.interval = 4;
						}
					}
				}
			}
			else if (ironwave.valid == 0 && man.mana > 0)printf("You have used the card4!\n");
			else if (man.mana <= 0) {

				printf("You have no mana!\n");
			}
		}
		else if (keycode == ALLEGRO_KEY_5) {
			if (man.mana - card5.cost >= 0 && card5.valid == 1) {
				card5.valid = 0;
				man.mana = man.mana - card5.cost;
				man.armour = card5.armour + man.armour;
				man.atk = card5.damage;
				man.buff = card5.vulnerable;
				al_play_sample(strikesound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				printf("Use card5!");
				if (stage == 1) {
					if (man.buff >= 1)man.buff--;
					louse.hp = louse.hp - man.atk - man.buff*man.atk;
					if (louse.hp <= 0) {
						man.money = man.money + louse.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {

						turn++;
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());
						louse.interval--;
						if (louse.interval == 0) {
							man.hp = man.hp - louse.atk + man.armour;
							louse.interval = 1;
						}
					}
				}
				if (stage == 2) {
					if (man.buff >= 1)man.buff--;
					cultist.hp = cultist.hp - man.atk - man.buff*man.atk;
					if (cultist.hp <= 0) {
						man.money = man.money + cultist.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						cultist.interval--;
						if (cultist.interval == 0) {
							man.hp = man.hp - cultist.atk + man.armour;
							cultist.interval = 2;
						}
					}
				}
				if (stage == 3) {
					if (man.buff >= 1)man.buff--;
					chosen.hp = chosen.hp - man.atk - man.buff*man.atk;
					if (chosen.hp <= 0) {
						man.money = man.money + chosen.money;
						money = man.money;
						judge_next_window = 3;
						window = 0;
						character1.x = 425;
						character1.y = 800;
						resetmonster();
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						chosen.interval--;
						if (chosen.interval == 0) {
							man.hp = man.hp - chosen.atk + man.armour;
							chosen.interval = 3;
						}
					}
				}
				if (stage == 4) {
					if (man.buff >= 1)man.buff--;
					boss.hp = boss.hp - man.atk - man.buff*man.atk;
					if (boss.hp <= 0) {
						man.money = man.money + boss.money;
						money = man.money;
						judge_next_window = 3;
						resetmonster();
						window = 1;
						//win scene
					}
					if (man.mana <= 0 || (man.mana == 1 && check_mana() == 0)) {
						man.mana = 4;
						man.armour = 0;
						man.atk = 0;
						card1 = shuffle(random());
						card2 = shuffle(random());
						card3 = shuffle(random());
						card4 = shuffle(random());
						card5 = shuffle(random());

						turn++;
						boss.interval--;
						if (boss.interval == 0) {
							man.hp = man.hp - boss.atk + man.armour;
							boss.interval = 4;
						}
					}
				}
			}
			else if (strike.valid == 0 && man.mana > 0)printf("You have used the card5!\n");
			else if (man.mana <= 0) {

				printf("You have no mana!\n");
			}
		}
		else if (keycode == ALLEGRO_KEY_ESCAPE) {
			printf("You can't escape from battle!\n");
		}
	}
	if (judge_next_window == 3) {
		if (window == 0) {
			switch (keycode) {
			case ALLEGRO_KEY_W:
				if (check_boundary(character1.x, character1.y - 25)) {
					character1.y -= 25;
					printf("(%d,%d)\n", character1.x, character1.y);
				}
				break;
			case ALLEGRO_KEY_S:
				if (check_boundary(character1.x, character1.y + 25)) {
					character1.y += 25;
					printf("(%d,%d)\n", character1.x, character1.y);
				}
				break;
			case ALLEGRO_KEY_A:
				if (check_boundary(character1.x - 25, character1.y)) {
					character1.x -= 25;
					printf("(%d,%d)\n", character1.x, character1.y);
				}
				break;
			case ALLEGRO_KEY_D:
				if (check_boundary(character1.x + 25, character1.y)) {
					character1.x += 25;
					printf("(%d,%d)\n", character1.x, character1.y);
				}
				break;
			}
		}
	}
}


void event_window() {

	
	if (judge_next_window == 1) {
		if (window == 2) {//in the village
			if (character1.x == 300 && character1.y == HEIGHT - 150 - 75) {//walk into INN
				window = 3;
				al_stop_sample(&village_bgm_id);
				if (!al_play_sample(INN_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &INN_bgm_id))
					game_abort("INN_bgm sample plays error.\n");
				character1.x = WIDTH / 2 - 25;
				character1.y = 800 - 25;
				printf("In INN:\n");
			}
			else if (character1.x == 300 - 200 && character1.y == HEIGHT - 150 - 75) {//walk into grocery store
				window = 4;
				al_stop_sample(&village_bgm_id);
				al_play_sample(grocerystore_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &grocerystore_bgm_id);
				character1.x = 675;
				character1.y = 800 - 275;
				printf("In grocery store:\n");
			}
			else if (character1.x == 300 && character1.y == HEIGHT - 100) {
				judge_next_window = 3;
				window = 0;
				character1.x = 425;
				character1.y = 800;
				al_stop_sample(&village_bgm_id);
				al_play_sample(Dungeonmusic, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &Dungeonmusic_id);
			}
		}
		else if (window == 3) {
			if (character1.x == WIDTH / 2 - 25 && character1.y == 800) {//from INN back to village
				window = 2;
				al_stop_sample(&INN_bgm_id);
				al_play_sample(village_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &village_bgm_id);
				character1.x = 300;
				character1.y = HEIGHT - 150 - 50;
				printf("In village:\n");
			}
			else if ((character1.x == 650 || character1.x == 675) && character1.y == 175) //INN 2nd floor
				pop_up_window = true;
			else if (character1.x == 425 && character1.y == 175)//fire place
				pop_up_window = true;
			else if (character1.x == 525 && character1.y == 375)//host
				pop_up_window = true;
		}
		else if (window == 4) {
			if (character1.y == 800 - 250 && character1.x == 675) {//from grocery store back to village
				window = 2;
				al_stop_sample(&grocerystore_bgm_id);
				al_play_sample(village_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &village_bgm_id);
				character1.x = 300 - 200;
				character1.y = HEIGHT - 150 - 50;
				printf("In village:\n");
			}

			else if (character1.x == 675 && character1.y == 300)
				pop_up_window = true;			
		}
	}
	else if (judge_next_window == 3) {
		if (window == 0) {
			if (character1.y == -25) {
				if(tower==1) {
					judge_next_window = 2;
					window = 1;
					stage = 4;
				}
				else {
					int x = random() % 4 + 1;//random monster
					if (x == 1) {
						judge_next_window = 2;
						window = 1;
						stage = 1;
					}
					else if (x == 2) {
						judge_next_window = 2;
						window = 1;
						stage = 2;
					}
					else if (x == 3) {
						judge_next_window = 2;
						window = 1;
						stage = 3;
					}
					else if (x == 4) {
						character1.x = 300;
						character1.y = HEIGHT - 150;
						judge_next_window = 1;
						window = 2;
						al_stop_sample(&Dungeonmusic_id);
						
					}
				}		
			}
		}
	}
}

int game_run() {
	int error = 0;
	// First window(title)
	
	if (window == 1) {
		if (!al_is_event_queue_empty(event_queue)) {
			error = process_event();
			if (window == 2) {
				if (judge_next_window == 0 && window == 2) {
					al_draw_bitmap(Teach, 0, -18, 0);
					al_flip_display();
					error = process_event();
				}
			}

			else if (judge_next_window == 1) {
				window = 2;
				al_stop_sample(&title_bgm_id);
				al_play_sample(village_bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &village_bgm_id);
				// Setting Character
				character1.x = 800;
				character1.y = 100;
				light_dot.x = 435;
				light_dot.y = 235;
				character1.image_path = al_load_bitmap("tower.png");
				light_dot.image_path = al_load_bitmap("Light_Dot.png");

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
	else if (window == 2) {

	}
	// Second window(Main Game)
	if (judge_next_window == 1) {
		if (window > 1) {
			// Change Image for animation
			if (window == 2) {
				al_draw_bitmap(village_bg, 0, 0, 0);
			}
			if (window == 3) {
				al_draw_bitmap(INN_bg, 0, 0, 0);
				if (ture)
					al_draw_bitmap(light_dot.image_path, light_dot.x, light_dot.y, 0);
				if (character1.x == 525 && character1.y == 375) {
					while (pop_up_window == true) {
						while (message_number == 0) {
							al_draw_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(255, 255, 255), 5);
							al_draw_filled_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(61, 89, 171));
							al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 - 200, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE,
								"Hotel Owner, Toriel:");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTRE,
								"Hello, welcome to my fantastic hotel!");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 210, ALLEGRO_ALIGN_CENTRE,
								"Do you want to rest here?");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 270, ALLEGRO_ALIGN_CENTRE,
								"Press ' Enter ' to continue!");

							al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);
							al_flip_display();
							error = process_event();
							//press enter to continue
						}
						while (message_number == 1) {
							al_draw_bitmap(INN_bg, 0, 0, 0);
							al_draw_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(255, 255, 255), 5);
							al_draw_filled_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(61, 89, 171));
							al_draw_textf(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 + 200, HEIGHT / 2 + 80, ALLEGRO_ALIGN_CENTRE,
								"Your HP now %d/%d.", hp_now, hp_max);
							al_draw_textf(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 + 200, HEIGHT / 2 + 110, ALLEGRO_ALIGN_CENTRE,
								"You have %d.", money);
							al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 - 200, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE,
								"Hotel Owner, Toriel:");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTRE,
								"You only need to pay $81000 for HEALing your HP.Or...for only $1200.");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 210, ALLEGRO_ALIGN_CENTRE,
								"(press 'z' for YES and 'x' for NO)");
							al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);
							al_flip_display();
							error = process_event();
						}//press z for yes and x for no				
						while (message_number == 2) {
							//if (z) heal and reduce money 
							al_draw_bitmap(INN_bg, 0, 0, 0);
							al_draw_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(255, 255, 255), 5);
							al_draw_filled_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(61, 89, 171));
							al_draw_textf(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 + 200, HEIGHT / 2 + 80, ALLEGRO_ALIGN_CENTRE,
								"Your HP now %d/%d.", hp_now, hp_max);
							al_draw_textf(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 + 200, HEIGHT / 2 + 110, ALLEGRO_ALIGN_CENTRE,
								"You have %d.", money);
							al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 - 200, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE,
								"Hotel Owner, Toriel:");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTRE,
								"Thank you for coming my hotel!Have a nice day!");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 270, ALLEGRO_ALIGN_CENTRE,
								"Press ' Enter ' to continue!");
							al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);
							al_flip_display();
							message_number = 5;
							error = process_event();
						}
						while (message_number == 3) {//if (x) no heal
							al_draw_bitmap(INN_bg, 0, 0, 0);
							al_draw_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(255, 255, 255), 5);
							al_draw_filled_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(61, 89, 171));
							al_draw_textf(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 + 200, HEIGHT / 2 + 80, ALLEGRO_ALIGN_CENTRE,
								"Your HP now %d/%d.", hp_now, hp_max);
							al_draw_textf(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 + 200, HEIGHT / 2 + 110, ALLEGRO_ALIGN_CENTRE,
								"You have %d.", money);
							al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 - 200, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE,
								"Hotel Owner, Toriel:");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTRE,
								"That's okay.Remember to come here for one day!");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 270, ALLEGRO_ALIGN_CENTRE,
								"Press ' Enter ' to continue!");
							al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);
							al_flip_display();
							error = process_event();
						}
						while (message_number == 10) {
							message_number = 2;
						}
						while (message_number == 4) {
							if (money >= 1200) {
								message_number = 11;
								error = process_event();
							}
							else {
								message_number = 12;
							}
						}
						while (message_number == 12) {
							al_draw_bitmap(INN_bg, 0, 0, 0);
							al_draw_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(255, 255, 255), 5);
							al_draw_filled_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(61, 89, 171));
							money_shortage = true;
							al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
							al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
							al_draw_textf(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 + 200, HEIGHT / 2 + 80, ALLEGRO_ALIGN_CENTRE,
								"Your HP now %d/%d.", hp_now, hp_max);
							al_draw_textf(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 + 200, HEIGHT / 2 + 110, ALLEGRO_ALIGN_CENTRE,
								"You have %d.", money);
							al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 - 200, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE,
								"Hotel Owner, Toriel:");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTRE,
								"You only need to pay $81000 for HEALing your HP.Or...for only $100.");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 210, ALLEGRO_ALIGN_CENTRE,
								"(press 'z' for YES and 'x' for NO)");
							al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
								"You don't have enough money to rest!Get out of here!");

							al_flip_display();
							message_number = 5;
							error = process_event();
						}
						while (message_number == 5)
							error = process_event();
					}
				}
				else if (character1.y == 175) {
					while (pop_up_window == true) {
						al_draw_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(255, 255, 255), 5);
						al_draw_filled_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(61, 89, 171));
						if ((character1.x == 650 || character1.x == 675) && character1.y == 175) {
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTRE,
								"If you want to play more, please pay for the DLC of this game!");
						}
						else if (character1.x == 425 && character1.y == 175) {
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTRE,
								"There's NOTHING in this fireplace ! WHY are you seeking something here?");
						}
						al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 210, ALLEGRO_ALIGN_CENTRE,
							"Press ' Enter ' to continue!");
						al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);
						al_flip_display();
						error = process_event();
						if (pop_up_window == false) {
							al_draw_bitmap(INN_bg, 0, 0, 0);
							al_flip_display();
							break;
						}
					}
				}
			}
			if (window == 4) {
				al_draw_bitmap(grocerystore_bg, 0, 0, 0);
				if (character1.x == 675 && character1.y == 300) {
					while (pop_up_window == true) {
						while (message_number == 0) {
							al_draw_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(255, 255, 255), 5);
							al_draw_filled_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(61, 89, 171));
							al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 - 200, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE,
								"Grocery Store Owner, Mizuha:");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTRE,
								"Hi, do you want some Kuchikamizake?It tastes really great!");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 210, ALLEGRO_ALIGN_CENTRE,
								"We have some special accessories for you to choose!");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 270, ALLEGRO_ALIGN_CENTRE,
								"Press ' Enter ' to continue!");
							al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);
							al_flip_display();
							error = process_event();
							//press enter to continue
						}
						while (message_number == 1) {
							al_draw_bitmap(grocerystore_bg, 0, 0, 0);
							al_draw_rectangle(50, 100, WIDTH - 50, HEIGHT - 100, al_map_rgb(255, 255, 255), 5);
							al_draw_filled_rectangle(50, 100, WIDTH - 50, HEIGHT - 100, al_map_rgb(61, 89, 171));
							al_draw_line(50, 550, 850, 550, al_map_rgb(0, 0, 0), 5);
							al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, 125, ALLEGRO_ALIGN_CENTRE,
								"Accessories List:");
							al_draw_textf(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 + 250, 125, ALLEGRO_ALIGN_CENTRE,
								"You now have %d.", money);
							al_draw_line(50, 175, 850, 175, al_map_rgb(0, 0, 0), 5);
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 200, ALLEGRO_ALIGN_LEFT,
								"1.Healing Potion										$250");
							al_draw_textf(menu_font, al_map_rgb(255, 255, 255), 675, 200, ALLEGRO_ALIGN_LEFT,
								"You now have %d.", potion4.valid);
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 250, ALLEGRO_ALIGN_LEFT,
								"2.Shielding  Potion							        $100");
							al_draw_textf(menu_font, al_map_rgb(255, 255, 255), 675, 250, ALLEGRO_ALIGN_LEFT,
								"You now have %d.", potion3.valid);
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 300, ALLEGRO_ALIGN_LEFT,
								"3.Samurai Sword										$500");
							al_draw_textf(menu_font, al_map_rgb(255, 255, 255), 675, 300, ALLEGRO_ALIGN_LEFT,
								"You now have %d.", amount_of_Samurai_Sword);
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 350, ALLEGRO_ALIGN_LEFT,
								"4.God's Sword - Plastic Bottle							$5000");
							al_draw_textf(menu_font, al_map_rgb(255, 255, 255), 675, 350, ALLEGRO_ALIGN_LEFT,
								"You now have %d.", amount_of_Gods_Sword_Plastic_Bottle);
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 400, ALLEGRO_ALIGN_LEFT,
								"5.Debuff Potion										$300");
							al_draw_textf(menu_font, al_map_rgb(255, 255, 255), 675, 400, ALLEGRO_ALIGN_LEFT,
								"You now have %d.", potion1.valid);
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 450, ALLEGRO_ALIGN_LEFT,
								"6.Harming Potion										$400");
							al_draw_textf(menu_font, al_map_rgb(255, 255, 255), 675, 450, ALLEGRO_ALIGN_LEFT,
								"You now have %d.", potion2.valid);
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 500, ALLEGRO_ALIGN_LEFT,
								"7.The Boardshort Stuffed with One Million Dollars		$800");
							al_draw_textf(menu_font, al_map_rgb(255, 255, 255), 675, 500, ALLEGRO_ALIGN_LEFT,
								"You now have %d.", amount_of_The_Boardshort_Stuffed_with_One_Million_Dollars);
							al_draw_text(menu_font, al_map_rgb(0, 0, 0), 75, 125, ALLEGRO_ALIGN_LEFT,
								"Press 'x' to exit.");
							if (menu_number_chose == 1) {
								al_draw_bitmap(POtion1, 600, 575, 0);
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 600, ALLEGRO_ALIGN_LEFT,
									"1.Healing Potion");
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 700, ALLEGRO_ALIGN_LEFT,
									"Max HP + 100 (in battle)");
								if (check_purchase == true) {
									al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
									al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
									al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
										"Do you really want to buy: Healing Potion * 1");
									if (check_purchase_final == true) {
										if (money >= 250) {
											potion4.valid++;//inventory + 1
											money -= 250;
											menu_number_chose = 0;
											check_purchase = false;
											check_purchase_final = false;
											printf("potion4.valid + 1\n");
										}
										else {
											money_shortage = true;
											al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
											al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
											al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
												"You don't have enough money to buy this product!");
										}
									}
								}
							}
							else if (menu_number_chose == 2) {
								al_draw_bitmap(POtion2, 575, 575, 0);
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 600, ALLEGRO_ALIGN_LEFT,
									"2.Shielding  Potion");
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 700, ALLEGRO_ALIGN_LEFT,
									"Armour + 4 (in battle)");
								if (check_purchase == true) {
									al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
									al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
									al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
										"Do you really want to buy: Shielding  Potion * 1");
									if (check_purchase_final == true) {
										if (money >= 100) {
											potion3.valid++;//inventory + 1
											money -= 100;
											menu_number_chose = 0;
											check_purchase = false;
											check_purchase_final = false;
											printf("potion3.valid++\n");
										}
										else {
											money_shortage = true;
											al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
											al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
											al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
												"You don't have enough money to buy this product!");
										}
									}
								}
							}
							else if (menu_number_chose == 3) {
								al_draw_bitmap(Samurai_Sword, 600, 575, 0);
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 600, ALLEGRO_ALIGN_LEFT,
									"3.Samurai Sword");
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 700, ALLEGRO_ALIGN_LEFT,
									"A not bad weapon for close quarters battle.");
								if (check_purchase == true) {
									al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
									al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
									al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
										"Do you really want to buy: Samurai Sword * 1");
									if (check_purchase_final == true) {
										if (money >= 500) {
											amount_of_Samurai_Sword++;//inventory + 1
											money -= 500;
											menu_number_chose = 0;
											check_purchase = false;
											check_purchase_final = false;
											printf("amount_of_Samurai_Sword + 1\n");
										}
										else {
											money_shortage = true;
											al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
											al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
											al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
												"You don't have enough money to buy this product!");
										}
									}
								}
							}
							else if (menu_number_chose == 4) {
								al_draw_bitmap(Gods_Sword_Plastic_Bottle, 550, 600, 0);
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 600, ALLEGRO_ALIGN_LEFT,
									"4.God's Sword - Plastic Bottle");
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 700, ALLEGRO_ALIGN_LEFT,
									"For the glory of Rome!");
								if (check_purchase == true) {
									al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
									al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
									al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
										"Do you really want to buy: God's Sword - Plastic Bottle * 1");
									if (check_purchase_final == true) {
										if (money >= 5000) {
											amount_of_Gods_Sword_Plastic_Bottle++;//inventory + 1
											money -= 5000;
											menu_number_chose = 0;
											check_purchase = false;
											check_purchase_final = false;
											printf("amount_of_Gods_Sword_Plastic_Bottle + 1\n");
										}
										else {
											money_shortage = true;
											al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
											al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
											al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
												"You don't have enough money to buy this product!");
										}
									}
								}
							}
							else if (menu_number_chose == 5) {
								al_draw_bitmap(POtion3, 600, 575, 0);
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 600, ALLEGRO_ALIGN_LEFT,
									"5.Debuff Potion");
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 700, ALLEGRO_ALIGN_LEFT,
									"Enemy's vulnerable + 4 (in battle)");
								if (check_purchase == true) {
									al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
									al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
									al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
										"Do you really want to buy: Debuff Potion * 1");
									if (check_purchase_final == true) {
										if (money >= 300) {
											potion1.valid++;//inventory + 1
											money -= 300;
											menu_number_chose = 0;
											check_purchase = false;
											check_purchase_final = false;
											printf("potion1.valid++\n");
										}
										else {
											money_shortage = true;
											al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
											al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
											al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
												"You don't have enough money to buy this product!");
										}
									}
								}
							}
							else if (menu_number_chose == 6) {
								al_draw_bitmap(POtion4, 600, 575, 0);
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 600, ALLEGRO_ALIGN_LEFT,
									"6.Harming Potion");
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 700, ALLEGRO_ALIGN_LEFT,
									"Enemy's HP - 100");
								if (check_purchase == true) {
									al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
									al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
									al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
										"Do you really want to buy: Harming Potion * 1");
									if (check_purchase_final == true) {
										if (money >= 400) {
											potion2.valid++;//inventory + 1
											money -= 400;
											menu_number_chose = 0;
											check_purchase = false;
											check_purchase_final = false;
											printf("potion2.valid++\n");
										}
										else {
											money_shortage = true;
											al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
											al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
											al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
												"You don't have enough money to buy this product!");
										}
									}
								}
							}
							else if (menu_number_chose == 7) {
								al_draw_bitmap(The_Boardshort_Stuffed_with_One_Million_Dollars, 600, 560, 0);
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 600, ALLEGRO_ALIGN_LEFT,
									"7.The Boardshort Stuffed with One Million Dollars");
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 700, ALLEGRO_ALIGN_LEFT,
									"The symbol of a DonFan.");
								al_draw_text(menu_font, al_map_rgb(255, 255, 255), 75, 750, ALLEGRO_ALIGN_LEFT,
									"If you have one, you can make a great deal of money![UC's Boardshort]");
								if (check_purchase == true) {
									al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
									al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
									al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
										"Do you really want to buy: The Boardshort Stuffed with One Million Dollars * 1");
									if (check_purchase_final == true) {
										if (money >= 800) {
											amount_of_The_Boardshort_Stuffed_with_One_Million_Dollars++;//inventory + 1
											money -= 800;
											menu_number_chose = 0;
											check_purchase = false;
											check_purchase_final = false;
											printf("amount_of_The_Boardshort_Stuffed_with_One_Million_Dollars + 1\n");
										}
										else {
											money_shortage = true;
											al_draw_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(255, 255, 255), 5);
											al_draw_filled_rectangle(WIDTH / 2 - 375, HEIGHT / 2 + 50, WIDTH / 2 + 375, HEIGHT / 2 - 50, al_map_rgb(178, 34, 34));
											al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
												"You don't have enough money to buy this product!");
										}
									}
								}

							}
							al_flip_display();
							error = process_event();
						}//choose			
						while (message_number == 2) {
							//if (z) heal and reduce money 
							al_draw_bitmap(grocerystore_bg, 0, 0, 0);
							al_draw_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(255, 255, 255), 5);
							al_draw_filled_rectangle(WIDTH / 2 - 350, HEIGHT / 2 + 70, WIDTH / 2 + 350, HEIGHT / 2 + 320, al_map_rgb(61, 89, 171));
							al_draw_text(menu_font, al_map_rgb(125, 255, 125), WIDTH / 2 - 200, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE,
								"Grocery Store Owner, Mizuha:");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTRE,
								"Thank you for buying somthing here!See ya!");
							al_draw_text(menu_font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 270, ALLEGRO_ALIGN_CENTRE,
								"Press ' Enter ' to continue!");
							al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);
							al_flip_display();
							error = process_event();
						}
					}
				}
			}
			al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));

			// Listening for new event
			if (!al_is_event_queue_empty(event_queue)) {
				error = process_event();
			}
		}
	}
	//battle
	if (judge_next_window == 2) {
		while (window == 1) {
	
			// draw the battlefield and indicate the turn
			al_draw_bitmap(Board, 0, 0, 0);
			if (stage == 4) {
				al_draw_bitmap(Bossroom, 0, 0, 0);
			}

			if (stage != 4)al_draw_bitmap(backgroud, 0, 0, 0);
			al_draw_rectangle(3, 429, 897, 897, al_map_rgb(255, 255, 255), 6);
			al_draw_rectangle(3, 690, 897, 897, al_map_rgb(255, 255, 255), 6);
			al_draw_rectangle(770, 0, 899, 429, al_map_rgb(255, 255, 255), 2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 810, 10,
				ALLEGRO_ALIGN_CENTER, "System");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 810, 230,
				ALLEGRO_ALIGN_CENTER, "turn:%d", turn);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 830, 200,
				ALLEGRO_ALIGN_CENTER, "money:%d", man.money);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 830, 40,
				ALLEGRO_ALIGN_CENTER, "tower:(%d/5)", tower);
			
			//load the potion
			al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 850,
				ALLEGRO_ALIGN_CENTER, "potion1:(%d/6)", potion1.valid);
			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 825,
				ALLEGRO_ALIGN_CENTER, "Vulnerable+4");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 350, 850,
				ALLEGRO_ALIGN_CENTER, "potion2:(%d/6)", potion2.valid);
			al_draw_text(font, al_map_rgb(255, 255, 255), 350, 825,
				ALLEGRO_ALIGN_CENTER, "Damage +100pt");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 550, 850,
				ALLEGRO_ALIGN_CENTER, "potion3:(%d/6)", potion3.valid);
			al_draw_text(font, al_map_rgb(255, 255, 255), 550, 825,
				ALLEGRO_ALIGN_CENTER, "Armour+20");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 750, 850,
				ALLEGRO_ALIGN_CENTER, "potion4:(%d/6)", potion4.valid);
			al_draw_text(font, al_map_rgb(255, 255, 255), 750, 825,
				ALLEGRO_ALIGN_CENTER, "Hp+100");
			al_draw_bitmap(Potion1, 115, 750, 0);
			al_draw_bitmap(Potion2, 315, 750, 0);
			al_draw_bitmap(Potion3, 515, 750, 0);
			al_draw_bitmap(Potion4, 715, 750, 0);


			//draw the monster 
			if (stage == 1 && louse.hp > 0) {

				al_draw_bitmap(Louse, 390, 250, 0);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 50,
					ALLEGRO_ALIGN_CENTER, "vulnerable:%d", man.buff);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 100,
					ALLEGRO_ALIGN_CENTER, "Hp:%d", louse.hp);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 150,
					ALLEGRO_ALIGN_CENTER, "Attack:%d", louse.atk);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 200,
					ALLEGRO_ALIGN_CENTER, "Attack Inteval:%d", louse.interval);
			}


			if (stage == 2 && cultist.hp > 0) {
				al_draw_bitmap(Cultist, 390, 150, 0);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 50,
					ALLEGRO_ALIGN_CENTER, "vulnerable:%d", man.buff);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 100,
					ALLEGRO_ALIGN_CENTER, "Hp:%d", cultist.hp);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 150,
					ALLEGRO_ALIGN_CENTER, "Attack:%d", cultist.atk);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 200,
					ALLEGRO_ALIGN_CENTER, "Attack Inteval:%d", cultist.interval);
			}

			if (stage == 3 && chosen.hp > 0) {
				al_draw_bitmap(Chosen, 390, 150, 0);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 50,
					ALLEGRO_ALIGN_CENTER, "vulnerable:%d", man.buff);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 100,
					ALLEGRO_ALIGN_CENTER, "Hp:%d", chosen.hp);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 150,
					ALLEGRO_ALIGN_CENTER, "Attack:%d", chosen.atk);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 200,
					ALLEGRO_ALIGN_CENTER, "Attack Inteval:%d", chosen.interval);
			}
			if (stage == 4 && boss.hp > 0) {
				al_draw_bitmap(Boss, 390, 100, 0);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 50,
					ALLEGRO_ALIGN_CENTER, "vulnerable:%d", man.buff);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 100,
					ALLEGRO_ALIGN_CENTER, "Hp:%d", boss.hp);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 150,
					ALLEGRO_ALIGN_CENTER, "Attack:%d", boss.atk);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 200,
					ALLEGRO_ALIGN_CENTER, "Attack Inteval:%d", boss.interval);
			}


			// draw the hero and the indicate the data of hero
			al_draw_bitmap(hero, 0, 150, 0);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 100,
				ALLEGRO_ALIGN_CENTER, "Hp:%d", man.hp);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 150,
				ALLEGRO_ALIGN_CENTER, "Attack:%d", man.atk);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 200,
				ALLEGRO_ALIGN_CENTER, "armour:%d", man.armour);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 250,
				ALLEGRO_ALIGN_CENTER, "mana:%d", man.mana);
			if (man.hp <= 0) {
				al_draw_text(font, al_map_rgb(255, 255, 255), 815, 300,
					ALLEGRO_ALIGN_CENTER, "You died.");
				printf("You died.\n");
				
				int i = 1;
				al_stop_sample(&Dungeonmusic_id);
				al_play_sample(defeated, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				while (i) {
					al_draw_bitmap(defeatedpicture, 0, 0, 0);
					al_flip_display();
				}
				
				card1.valid = 0;
				card2.valid = 0;
				card3.valid = 0;
				card4.valid = 0;
				card5.valid = 0;
				
			}
			if (card1.valid != 0) {
				if (card1.index == 1)al_draw_bitmap(Bash, 0, 430, 0);
				if (card1.index == 2)al_draw_bitmap(Cleave, 0, 430, 0);
				if (card1.index == 3)al_draw_bitmap(Defend, 0, 430, 0);
				if (card1.index == 4) al_draw_bitmap(Ironwave, 0, 430, 0);
				if (card1.index == 5)al_draw_bitmap(Strike, 0, 430, 0);

			}

			if (card2.valid != 0) {
				if (card2.index == 1)al_draw_bitmap(Bash, 175, 430, 0);
				if (card2.index == 2)al_draw_bitmap(Cleave, 175, 430, 0);
				if (card2.index == 3)al_draw_bitmap(Defend, 175, 430, 0);
				if (card2.index == 4) al_draw_bitmap(Ironwave, 175, 430, 0);
				if (card2.index == 5)al_draw_bitmap(Strike, 175, 430, 0);

			}

			if (card3.valid != 0) {
				if (card3.index == 1)al_draw_bitmap(Bash, 350, 430, 0);
				if (card3.index == 2)al_draw_bitmap(Cleave, 350, 430, 0);
				if (card3.index == 3)al_draw_bitmap(Defend, 350, 430, 0);
				if (card3.index == 4) al_draw_bitmap(Ironwave, 350, 430, 0);
				if (card3.index == 5)al_draw_bitmap(Strike, 350, 430, 0);

			}

			if (card4.valid != 0) {
				if (card4.index == 1)al_draw_bitmap(Bash, 525, 430, 0);
				if (card4.index == 2)al_draw_bitmap(Cleave, 525, 430, 0);
				if (card4.index == 3)al_draw_bitmap(Defend, 525, 430, 0);
				if (card4.index == 4) al_draw_bitmap(Ironwave, 525, 430, 0);
				if (card4.index == 5)al_draw_bitmap(Strike, 525, 430, 0);


			}

			if (card5.valid != 0) {
				if (card5.index == 1)al_draw_bitmap(Bash, 700, 430, 0);
				if (card5.index == 2)al_draw_bitmap(Cleave, 700, 430, 0);
				if (card5.index == 3)al_draw_bitmap(Defend, 700, 430, 0);
				if (card5.index == 4) al_draw_bitmap(Ironwave, 700, 430, 0);
				if (card5.index == 5)al_draw_bitmap(Strike, 700, 430, 0);


			}

			al_flip_display();
			error = process_event();
			if (judge_next_window != 2)
				break;
		}
	}

	if (judge_next_window == 3) {
		while (window == 0) {
			al_draw_bitmap(dungeon_map, 0, 0, 0);
			al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);

			al_flip_display();
			error = process_event();
			if (judge_next_window != 3)
				break;
		}
	}
	return error;
}



bool check_boundary(int x, int y)
{
	if (judge_next_window == 1) {
		if (window == 2) {
			if (x == 100 && y == 675)
				return true;
			else if (x >= 100 && x <= 500 && y == 700)
				return true;
			else if (x == 500 && y >= 625 && y <= 675)
				return true;
			else if (x == 300 && y == 675)
				return true;
			else if (x == 175 && y >= 500 && y <= 675)
				return true;
			else if (x >= 50 && x <= 425 && y == 475)
				return true;
			else if (x == 375 && y == 450)
				return true;
			else if (x == 250 && y == 450)
				return true;
			else if (x >= 125 && x <= 150 && y >= 400 && y <= 450)
				return true;
			else if (x >= 150 && x <= 175 && y == 375)
				return true;
			else if (x == 100 && y == 400)
				return true;
			else if (x == 75 && y == 400)
				return true;
			else if (x == 75 && y == 425)
				return true;
			else if (x == 150 && y == 350)
				return true;
			else if (x == 425 && y >= 175 && y <= 675)
				return true;
			else if (x >= 175 && x <= 400 && y == 175)
				return true;
			else if (x >= 450 && x <= 700 && y == 400)
				return true;
			else if (x >= 725 && x <= 800 && y >= 375 && y <= 425)
				return true;
			else if (x >= 725 && x <= 750 && y == 450)
				return true;
			else if (x == 725 && y == 475)
				return true;
			else if (x == 700 && y >= 475 && y <= 625)
				return true;
			else if (x >= 725 && x <= 800 && y >= 600 && y <= 675)
				return true;
			else if (x == 800 && y >= 525 && y <= 575)
				return true;
			else if (x == 775 && y >= 550 && y <= 575)
				return true;
			else if (x == 800 && y >= 75 && y <= 350)
				return true;
			else if (x == 775 && y >= 100 && y <= 125)
				return true;
			else if (x >= 750 && x <= 775 && y >= 200 && y <= 300)
				return true;
			else if (x == 300 && y >= 725 && y <= 800)
				return true;
			else
				return false;
		}
		if (window == 3) {
			if (x == 700 && y >= 300 && y <= 600)
				return true;
			else if (x >= 650 && x <= 675 && y >= 175 && y <= 650)
				return true;
			else if (x >= 575 && x <= 625 && y >= 300 && y <= 650)
				return true;
			else if (x == 525 && y >= 375 && y <= 650)
				return true;
			else if (x >= 375 && x <= 475 && y >= 375 && y <= 650)
				return true;
			else if (x == 425 && y >= 675 && y <= 800)
				return true;
			else if (x >= 150 && x <= 350 && y >= 375 && y <= 575)
				return true;
			else if (x >= 150 && x <= 325 && y == 600)
				return true;
			else if (x >= 175 && x <= 325 && y >= 625 && y <= 650)
				return true;
			else if (x == 500 && x >= 375 && y <= 575)
				return true;
			else if (x == 550 && y >= 375 && y <= 650)
				return true;
			else if (x >= 175 && x <= 500 && y == 275)
				return true;
			else if (x >= 325 && x <= 500 && y >= 200 && y <= 275)
				return true;
			else if (x == 425 && y == 175)
				return true;
			else if (x == 500 && y < 200)
				return false;
			else
				return false;
		}
		else if (window == 4) {
			if (x == 675 && y >= 425 && y <= 550)
				return true;
			else if (x >= 525 && x <= 825 && y >= 300 && y <= 400)
				return true;
			else if (x >= 350 && x <= 500 && y == 400)
				return true;
			else if (x == 325 && y == 400)
				return true;
			else if (x >= 325 && x <= 400 && y >= 425 && y <= 675)
				return true;
			else if (x >= 150 && x <= 300 && y == 675)
				return true;
			else if (x >= 150 && x <= 300 && y == 450)
				return true;
			else if (x >= 50 && x <= 125 && y >= 200 && y <= 675)
				return true;
			else if (x >= 150 && x <= 550 && y >= 200 && y <= 250)
				return true;
			else if (x == 325 && y >= 275 && y <= 350)
				return true;
			else if (x >= 450 && x <= 550 && y >= 150 && y <= 175)
				return true;
			else if (x >= 575 && x <= 700 && y == 150)
				return true;
			else if (x >= 700 && x <= 825 && y == 200)
				return true;
			else if (x == 700 && y == 175)
				return true;
			else if (x == 800 && y == 175)
				return true;
			else if (x == 825 && y == 175)
				return true;
			else if (x >= 150 && x <= 300 && y == 475)
				return true;
			else if (x == 525 && y == 275)
				return true;
			else if (x == 550 && y == 275)
				return true;
			else
				return false;
		}
	}
	if (judge_next_window == 3) {
		if (x == 425 && y >= -25 && y <= 800)
			return true;
		else if (x >= 375 && x <= 475 && y >= 550 && y <= 725)
			return true;
		else if (x >= 100 && x <= 750 && y >= 475 && y <= 525)
			return true;
		else if (x == 100 && y >= -25 && y <= 450)
			return true;
		else if (x == 750 && y >= -25 && y <= 450)
			return true;
		else
			return false;
	}
	else
		return true;
}

int check_mana() {
	if (card1.valid && card1.cost == 1)
		return 1;
	else if (card2.valid && card2.cost == 1)
		return 1;
	else if (card3.valid && card3.cost == 1)
		return 1;
	else if (card4.valid && card4.cost == 1)
		return 1;
	else if (card5.valid && card5.cost == 1)
		return 1;
	else
		return 0;
}



void game_abort(const char* format, ...) {
	va_list arg;
	va_start(arg, format);
	game_vlog(format, arg);
	va_end(arg);
	fprintf(stderr, "error occured, exiting after 2 secs");
	// Wait 2 secs before exiting.
	al_rest(2);
	// Force exit program.
	exit(1);
}

void game_log(const char* format, ...) {
#ifdef LOG_ENABLED
	va_list arg;
	va_start(arg, format);
	game_vlog(format, arg);
	va_end(arg);
#endif
}

void game_vlog(const char* format, va_list arg) {
#ifdef LOG_ENABLED
	static bool clear_file = true;
	vprintf(format, arg);
	printf("\n");
	// Write log to file for later debugging.
	FILE* pFile = fopen("log.txt", clear_file ? "w" : "a");
	if (pFile) {
		vfprintf(pFile, format, arg);
		fprintf(pFile, "\n");
		fclose(pFile);
	}
	clear_file = false;
#endif
}

void game_destroy() {
	// Make sure you destroy all things
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_timer(timer2);
	al_destroy_bitmap(image);
}