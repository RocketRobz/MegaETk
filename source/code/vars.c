//editor
//init level arrays
u16 mel_map[4096];
u16 mel_events[208];
u8 mel_slot;
char mel_file[256];//current mel file

int totalsprites;

typedef struct{
	char fName[256];
	FILE_TYPE fType;
	bool mel;//0: not mel file, 1: mel file!
}fll;
fll FileList[1024];


//------------------------------------------------------------
//------------HERO-----------------------------------------------
typedef struct{
	s32 x,y,scrollx;
	s8 vx;	//counter to go <- or ->
	s16 vy;
	u8 flip;
	
	u16 speedinc;
	s16 jumppower;
	
//skill vars
	u8 doublejump;//0:no, 1: yes .. if already doublejumped
	u8 candoublejump;//0:no, 1: yes
	
	s8 dash;
	u8 highjump;
	u16 higherjump;
	u8 jumppressed;
	u8 autorun;
	u8 crouch;
	u8 manual_aim;
	u8 monster_aimed;
	u8 last_monster_aimed;
	u8 updatemonsterdata;//0=no - 1=yes
	u8 updatebossdata;//0=no - 1=yes
	u16 incammo;

//effects
	u8 blink;//blink counter
	u8 invisiblecounter;
	u8 ani_on;

//counter & speeds
	s16 movespeed;
	u8 incmovespeedcounter;
	
	u32 shotcounter;
	u32 shotspeed;
	
	u8 shotsonscreen;
	
	u8 weaponcounter[TOTAL_WEAPONS];	//every weapon uses it differente

//status
	s16 hp;
	s16 maxhp;
	
	u8 status_changed;
	u8 weapon;
	u8 numshoots[TOTAL_WEAPONS];
	s16 ammo[TOTAL_WEAPONS];
	s16 maxammo[TOTAL_WEAPONS];
	s8 lives;
	s32 exp;
	u32 totalexp;
	s16 a;	//temp
	
	s8 inground;
} player;
player hero;
//---------------------------------------------------------------
//------------------------------------------------------------


//------------------------------------------------------------
//------------BOSS---------------------------------------------
typedef struct{
	u8 enabled;
	u8 loaded;
	u8 sprite;
	u8 part;
	u8 id;
	u8 hidepart;
	u16 hp;
	u16 maxhp;
	u8 die;
	u8 lastaction;
	u8 action;
	u8 inground;
	u16 movcounter;
	u16 shootcounter;
}bss;
bss boss;
//---------------------------------------------------------------


//------------------------------------------------------------
//------------GAME-----------------------------------------------
typedef struct{
	u8 level;
	u8 level_type;//0:normal .. 1: boss
	u8 levelcomplete;
	u16 levelwidth;
	
	u8 teleport;
	u8 data_ok;
	
	u8 slotmode;
	
	u8 slotread[3];//0=empty, 1=ok, 2=broken
	
	s8 slot;	//para grabar la partida o leer...
	u8 fat;//0: not found, 1: found
	
	u16 levelmap_trans[50];//tiles not colliding
	u16 tiletransp[8];//transparentsss
	u8 total_trans;
	u8 die;
	u8 firstrun;
	
	u8 screen;//title, in game, etc..
	u8 option_selected;
	u8 stopcheck;//stop checking options
	
	//status screen
	u8 monsterimgloaded;//0:no , 1:yes ... para actualizar la imagen del monstruo en la pantalla de arriba
	//map vars
	s8 mapdot[50];//50 points max..(apunta a sprite)
	
	//shop vars
	s8 shop_sel;
	u8 listed[6];
	u8 numlist;
	
	//selected level vars (sl)
	u8 arrow_held;
	u8 arrow_held_counter;
	u8 sl_row;
	s8 sl;
	//-----------------	
	
	u32 timecounter;
	u32 time;
	u32 totaltime;
	
	u8 freerot[32];
	
	u16 totalevents;
	u8 maxshots;
	
	u8 ballraiseprio;
	
	//level pointers
	u16 const* levelgfx;
	u16 const* levelmap;
	const unsigned short* levelevent;
	//u16 const* tilepal = 0;
	//u16 const* tilegfx = 0;
	
	u8 disable_outscreen;
}general;
general game;
//---------------------------------------------------------------
//------------------------------------------------------------

//------------------------------------------------------------
//------------DATA-----------------------------------------------
typedef struct{
	//level data
	u8 unlocked[MENULVLTOTAL];	//0: locked
								//1: unlocked (unfinished)
								//2: unlocked (finished)
	u8 specialitems[TOTAL_LEVELS];	//0: show .. 1: not show
	
	//hero data
	u16 hp;
	u16 maxhp;
	u16 incammo;
	
	u8 numshoots[TOTAL_WEAPONS];
	s16 ammo[TOTAL_WEAPONS];
	s16 maxammo[TOTAL_WEAPONS];
	
	u32 exp;
	
	u8 extras[5];//extras.. map, monster info etc..
	u8 skills[10];//skills unlocked/locked
					//0:speed increment
					//1:jump power up
					//2:
	u8 shop[22];//items bought on shop
	u8 shop_unlocked[22];//items unlocked
	

	u8 mode;// 0:easy - 1:normal - 2:hard
	
	//game data
	//char name[5];
	u32 timeplayed;	
	
	u16 lenght;
	u32 preview[500];
}save;
save data;//3 huecos para grabar
//---------------------------------------------------------------
//------------------------------------------------------------




//------------------------------------------------------------
//------------GFX-----------------------------------------------
typedef struct{
	u16 weapon1[3];
	u16 weapon2[5];
	u16 weapon3;
	u16 weapon4;
	u16 weapon5;
	u16 weapon6;
	u16 weapon7;
	u16 weapon8[3];
	u16 weapon9[3];
	
	u16 mapdot[4];
	
	u16 hero_arm;
	u16 statusweapon;
	u16 statusweaponx;
	u16 statusweaponexp;
	u16 statusammo;
	
	u16 items;
	u16 coin[3];
	
	u16 raiseparticle;
	u16 ballraiseparticle[5];
	u16 particle[TOTALPARTICLES];
	
	u16 editor_bg;
	u16 editor_tg[2];
}graphics;
graphics gfx;
//---------------------------------------------------------------
//------------------------------------------------------------


//------------------------------------------------------------
//------------SOUNDS---------------------------------------------
typedef struct{
	u32 counter[8]; //counter
	u8 id[8];//used by..
			//0=FREE
			//1=MOD FILE
			//2=SHOT SOUND
			//3=DAMAGE SOUND
			//4=OTHERS
	u8 startmod;
}sfx;
sfx sound;
//---------------------------------------------------------------

//------------------------------------------------------------
//------------EVENTS---------------------------------------------
typedef struct{
	u8 shown; //0= not shown, 1=already shown
	u8 visible; //0=true, 1=false
}event;
event events[maxevents+1];
//---------------------------------------------------------------


//------------------------------------------------------------
//------------TELEPORT---------------------------------------------
typedef struct{
	u8 x;
	u8 y;
	u8 level;
	u8 sprite;
}tp;
tp teleport[5];
//---------------------------------------------------------------


//MONSTERS
typedef struct{
	u8 shoot_x;
	u8 shoot_y;
}monst;
monst monsters[50];

//------------------------------------------------------------
//------------SPRITES--------------------------------------------
typedef struct{
	//general vars
	s32 x,y;
	
	s32 vy;
	s32 vx;	
	
	//size & flip
	u8 w1;
	u8 w2;
	u8 h1;
	u8 h2;
	
	s8 shoot_x;	//start shoot location X for monster/hero
	s8 shoot_y;	//start shoot location Y for monster/hero
	
	u8 size;	//sprite size (8,16,32..)
	s8 flip;	//enable flip ... usado por ball raise tb (para direccion)
	u8 animated; //0:none .. 1:enabled
	
	//id etc..
	u8 free;//if it's free or not (sprites.free.txt)
	u8 event; //which event nº it cames from
	u8 id;	//type of shoot/monster
	u8 mapdot;//which mapdot is using

	//status
	s8 power;
	u8 weapon;
	s16 hp;		//hp of the monster
	u16 speed;
	u8 particles_when_die;
	u8 particletype;
	u32 exp;
	
	u8 kill;
	s16 killcnt;
	u8 group;	//grupo de sprites (ej. group=50 ... sprite[i] y sprite[50] son como uno
	
//effect vars
	u8 rot;
	s16 rotangle;
	s16 shootangle;
	u16 zoom;
	u8 pal;
	
	u8 blink;
	u8 raise;
	u8 ballraise;
	
	s8 gravity;
	
	u8 collision; //action when collision
	u8 colcounter;//para que no cambie 40 veces de golpe
	//1 = kill
	//2 = sub HP (sprite has HP)
	//3 = stay
	//4 = rebota
	//5 = rebota + sub HP
	//
	//if hp=0 -> die
	
	u16 counter;	//other stuff (counter for monster shoots etc..)
} spritestuff;
spritestuff sprites[maxsprites+1];
//---------------------------------------------------------------
//------------------------------------------------------------






//------------------------------------------------------------
//------------DEBUG----------------------------------------------
typedef struct{
	u8 counter;
	u8 option;
	u8 a;	//temp var
	u8 a1,a2;
	
	u8 error;
	u8 disableerror;
} dbg;
dbg debug;
//---------------------------------------------------------------
//------------------------------------------------------------
