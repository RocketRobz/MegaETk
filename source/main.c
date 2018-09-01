#include <PA9.h>
#include <string.h>

#define GODMODE 0
#define FAT_ENABLED 0
#define UNLOCK_ALL 1

#define LOADCOMMENT_X 2
#define LOADCOMMENT_Y 10

#include "fat/gba_nds_fat.h"
#include "fat/disc_io.h"

u8 na=0;
FAT_FILE* file=0;

//Gfx data
#include "levels/all_gfx.c"
#include "levels/all_gfx.h"
#include "gfx/all_gfx.c"
#include "gfx/all_gfx.h"
#include "splash/all_gfx.c"
#include "splash/all_gfx.h"
#include "othergfx/all_gfx.c"
#include "othergfx/all_gfx.h"
#include "gfx/customized.c"
#include "menugfx/all_gfx.c"
#include "menugfx/all_gfx.h"
#include "editorgfx/all_gfx.c"
#include "editorgfx/all_gfx.h"
#include "font/all_gfx.c"
#include "font/all_gfx.h"

//Sound data
#include "music_title_mod.h"
#include "music_end_mod.h"
#include "music_shop_mod.h"
#include "music_selectlevel_mod.h"
#include "music_boss_mod.h"
#include "music_finalboss_mod.h"
#include "music_world1_mod.h"
#include "music_world2_mod.h"
#include "music_world3_mod.h"
#include "music_world4_mod.h"
#include "snd_shot1_raw.h"
#include "snd_item_raw.h"
#include "snd_floor_raw.h"
#include "snd_die_raw.h"
#include "snd_dash_raw.h"
#include "snd_boss_die_raw.h"
#include "snd_itemp_raw.h"
#include "snd_laser_raw.h"
#include "snd_huya_raw.h"
#include "snd_select_raw.h"
#include "snd_haha_raw.h"
#include "snd_door_raw.h"
#include "snd_accept_raw.h"
#include "snd_back_raw.h"
#include "snd_hithero_raw.h"
#include "snd_hitmonster_raw.h"

//event
#include "level_events/all_events.c"
//monster data
#include "monster/monster.c"
//item data
#include "shop/data.c"

//------------------------------------------------------------------------------
#define mapinfo 0 // nº of bytes reserved for map propierties

#define TITLE_SCREEN 0
#define GAME_MENU 1
#define GAME_PLAY 2
#define GAME_SHOP 3
#define GAME_LOAD 4
#define GAME_NEWFILE 5
#define GAME_EXTRAS 6
#define GAME_OPENMEL 7
#define GAME_LEVELEDITOR 8


#define GRAVITY 60
#define MAX_VY 1300

#define SKILL_SPEED_INC 200
#define SKILL_JUMP_INC 100

#define defaultAMMO 100

#define defaultJUMPPOWER 1300

#define AIMSPEED 5	//speed to change angle
#define FASTAIMSPEED 5	//speed to change angle (FAST)
#define JUMPPOWER_DASH 1000
#define JUMP_SMOKE_LIMIT 1300
#define BLINK_COUNTER 2
#define BLINK_LOOP 5	//de 0 a BLINK_LOOP paleta blanca
#define BLINK_LOOP2 10	//de BLINK_LOOP a BLINK_LOOP2 paleta normal
#define TOTAL_TRANS 50	//total no-collision tiles
#define SPRITES_PRIO_T 1	//sprites priority on screen (transparente)
#define SPRITES_PRIO 2	//sprites priority on screen

#define TOTALPARTICLES 18

//OPTIONS
#define UNLIMITED_AMMO 999

//LEVEL INFO
#define LEVELDATA_TOTALEVENTS 0
#define LEVELDATA_HEROX 1
#define LEVELDATA_HEROY 2
#define LEVELDATA_BG 3
#define LEVELDATA_MAPWIDTH 4
#define LEVELDATA_TILES 5
#define LEVELDATA_TYPE 7

//MONSTER INFO
#define MONSTERDATA_TOTAL 11
#define MONSTERDATA_ID 0
#define MONSTERDATA_HP 1
#define MONSTERDATA_WEAPON 2
#define MONSTERDATA_SPEED 3
#define MONSTERDATA_MOVTYPE 4
#define MONSTERDATA_PARTICLES 5
#define MONSTERDATA_SIZE 6
#define MONSTERDATA_W1 7
#define MONSTERDATA_W2 8
#define MONSTERDATA_H1 9
#define MONSTERDATA_H2 10


#define MaxShots 5
#define MaxTypes 3	//types of weapon
#define maxsprites 128
#define maxevents 50

//global game info
#define totalmonstertypes 3
#define TOTAL_WEAPONS 10

//PALETES
#define HERO_PAL 0
#define SHOOTS_PAL 1
#define UNKNOWN_PAL 2
#define BLINK_PAL 3
#define WHITE_PAL 3
#define HUMO_PAL 4
#define STATUS_WEAPON_PAL 5
#define MONSTERS_PAL 6
#define ITEMS_PAL 10
#define EFFECTS_PAL 11
#define OTHERS_PAL 12

//MUSIC DEFINES
#define MUSIC_TITLE 0
#define MUSIC_LEVEL1 1

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//OPCIONES HERO
#define HERO_SIZE 32

#define HERO_H1 5
#define HERO_H2 1
#define HERO_W1 10
#define HERO_W2 10

#define HERO_SPEED 256
#define HERO_HP 64

#define DEFAULT_SHOT_SPEED 20

#define HERO_ARM_X (19-11)
#define HERO_ARM_Y (14-13)
#define HERO_ARM_Y_CROUCH (17-13)

//STATUS COORDINATES
#define hpbar_x 2
#define hpbar_y 1
#define ambar_x 3
#define ambar_y 2
#define STATUS_WEAPON_X 8
#define STATUS_WEAPON_Y 24
#define AUTORUN_X 222
#define AUTORUN_Y 0

//sprites reservados
#define HERO_SLOT 0
#define HERO_ARM_SLOT 1
#define status_weapon_x_slot 2
#define status_weapon_slot 3
#define status_weapon_exp_slot 4
#define AUTORUN_slot 6

//sprites pre-define
#define hero_slot 0
//------------------------------------------------------------------------------

#include "code/vars.c"
#include "code/funciones.h"

int main(int argc, char ** argv){
	PA_Init();
	PA_InitVBL();
	PA_InitSound();
	PA_SetDefaultSound(100,11025,0);
	
	PA_InitRand();
	
	totalsprites=0;
	
	debug.counter=0;
	debug.option=0;
	debug.a1=16;
	debug.a2=16;
	
	game.slotread[0]=0;
	game.slotread[1]=0;
	game.slotread[2]=0;
	
	game.firstrun=0;
	game.screen = TITLE_SCREEN;
	
	//FadeIn(4);
	
	//game starts
	//game.screen = GAME_MENU; NewGame();
	//game.screen = GAME_SHOP;
	
	//GotoSplash();
	
	while(1)
	{
		if(game.screen==TITLE_SCREEN)GotoTitle();
		else if(game.screen==GAME_MENU)GotoMenu();
		else if(game.screen==GAME_PLAY)GamePlay();
		else if(game.screen==GAME_SHOP)GotoShop();
		else if(game.screen==GAME_EXTRAS)GotoExtras();
		else if(game.screen==GAME_LEVELEDITOR)GotoLevelEditor();
		else if(game.screen==GAME_LOAD){
			game.slotmode = 0;
			GotoSelectSlot();
		}
		else if(game.screen==GAME_NEWFILE){
			game.slotmode = 1;
			GotoSelectSlot();
		}
		else {
			debug.error = 3;
			ErrorScreen();		
		}
		PA_WaitForVBL();
	}
}

#include "code/sound.c"
#include "code/menu.c"
#include "code/collision.c"
#include "code/hero_actions.c"
#include "code/weapons.c"
#include "code/events.c"
#include "code/monsters.c"
#include "code/monster_actions.c"
#include "code/levels.c"
#include "code/debug.c"
#include "code/effects.c"
#include "code/items.c"
#include "code/stylus.c"
#include "code/general.c"
#include "code/update.c"
#include "code/gameplay.c"
#include "code/saveload.c"
#include "code/boss.c"
#include "code/leveleditor.c"

