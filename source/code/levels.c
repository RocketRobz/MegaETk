#define NORMAL_LEVEL 0
#define NORMAL_END_LEVEL 1
#define BOSS_LEVEL 2
#define BOSS_NOEND_LEVEL 3

void LevelComplete(){
	hero.totalexp += hero.exp;
	hero.exp = 0;
}

void Load_Level(u8 level){
	u16 i=0;
	u16 a=0;
	LevelClean();//reset all
	
	sprites[0].free = 1;	//sprite number 0 is allways used! (the hero)
	sprites[1].free = 10;	//sprite number 0 is allways used! (the hero)
	sprites[2].free = 10;	//sprite number 0 is allways used! (the hero)
	LoadGFX(level);
	LoadTeleports();	

	//Set Game Status
	hero.status_changed = 1;
	
	//set hero location
	hero.x = game.levelevent[LEVELDATA_HEROX]<<11;
	hero.y = game.levelevent[LEVELDATA_HEROY]<<11;
	hero.scrollx = 0;
	hero.flip = 0;	//0=right ... 1=left
	hero.vy = 0;
	//set arm size
	sprites[1].size = 32;
	//set hero map dot
	game.mapdot[0]=1;
	//------------------
	
	UpdateStats();//update status on screen
	UpdateXY();//UPDATE ALL SPRITES COORDINATES
	PA_WaitForVBL();

	//----------------
	//clean event vars
	for(i=0;i<=maxevents;i++){
		events[i].shown=0;
		events[i].visible=0;
	}
	s32 b;
	a=8;
	for(i=0;i<game.totalevents;i++){
		if(events[i].shown==0){
			b = game.levelevent[a + 1] - (hero.x>>11);
			if((b<=32)&&(b>=-32))OpenEvent(i);
		}
		a+=4;
	}
	//----------------------


	HeroChangeWeapon(hero.weapon);
	game.ballraiseprio=1;
	game.levelwidth = 1024;
	boss.loaded=0;
	if((game.levelevent[LEVELDATA_TYPE]==BOSS_LEVEL)||(game.levelevent[LEVELDATA_TYPE]==BOSS_NOEND_LEVEL))boss.enabled = 1;
	
	LoadSound();
	SetupStatusScreen();//load top screenç
	PA_EnableSpecialFx(0,SFX_ALPHA,SFX_OBJ,SFX_BG1);
	PA_SetSFXAlpha(0,6,31);
	SpriteActions();
}

void LoadSound(){
	u8 a;
	//reset channels
	for(a=0;a<=7;a++){
		sound.id[a]=0;
		sound.counter[a]=0;
	}
	//poner los primeros 4 channels reservados para el mod
	sound.id[0]=1;
	sound.id[1]=1;
	sound.id[2]=1;
	sound.id[3]=1;
	
	if(sound.startmod){
		//select mod
		if(game.level<10)PA_PlayMod(music_world1_mod);
		else if(game.level<19)PA_PlayMod(music_world2_mod);
		else if(game.level<28)PA_PlayMod(music_world3_mod);
		else if(game.level<37)PA_PlayMod(music_world4_mod);
		sound.startmod = 0;
	}
}

void LoadMap(u8 map){
	u32 i=0;
	u8 screen = 0;
	
	switch(map){
		case 0://custom level
			game.levelmap = mel_map+512;
			game.levelevent = mel_events;
			break;
		//WORLD 1
		case 1:
			game.levelmap = level_1_Map+512;
			game.levelevent = level1_events;
			break;
		case 2:
			game.levelmap = level_2_Map+512;
			game.levelevent = level2_events;
			break;
		case 3:
			game.levelmap = level_3_Map+512;
			game.levelevent = level3_events;
			break;
		case 4:
			game.levelmap = level_4_Map+512;
			game.levelevent = level4_events;
			break;
		case 5:
			game.levelmap = level_5_Map+512;
			game.levelevent = level5_events;
			break;
		case 6:
			game.levelmap = level_6_Map+512;
			game.levelevent = level6_events;
			break;
		case 7:
			game.levelmap = level_7_Map+512;
			game.levelevent = level7_events;
			break;
		case 8:
			game.levelmap = level_8_Map+512;
			game.levelevent = level8_events;
			break;
		case 9:
			game.levelmap = level_9_Map+512;
			game.levelevent = level9_events;
			break;
		//WORLD 2
		case 10:
			game.levelmap = level_10_Map+512;
			game.levelevent = level10_events;
			break;
		case 11:
			game.levelmap = level_11_Map+512;
			game.levelevent = level11_events;
			break;
		case 12:
			game.levelmap = level_12_Map+512;
			game.levelevent = level12_events;
			break;
		case 13:
			game.levelmap = level_13_Map+512;
			game.levelevent = level13_events;
			break;
		case 14:
			game.levelmap = level_14_Map+512;
			game.levelevent = level14_events;
			break;
		case 15:
			game.levelmap = level_15_Map+512;
			game.levelevent = level15_events;
			break;
		case 16:
			game.levelmap = level_16_Map+512;
			game.levelevent = level16_events;
			break;
		case 17:
			game.levelmap = level_17_Map+512;
			game.levelevent = level17_events;
			break;
		case 18:
			game.levelmap = level_18_Map+512;
			game.levelevent = level18_events;
			break;
		//WORLD 3
		case 19:
			game.levelmap = level_19_Map+512;
			game.levelevent = level19_events;
			break;
		case 20:
			game.levelmap = level_20_Map+512;
			game.levelevent = level20_events;
			break;
		case 21:
			game.levelmap = level_21_Map+512;
			game.levelevent = level21_events;
			break;
		case 22:
			game.levelmap = level_22_Map+512;
			game.levelevent = level22_events;
			break;
		case 23:
			game.levelmap = level_23_Map+512;
			game.levelevent = level23_events;
			break;
		case 24:
			game.levelmap = level_24_Map+512;
			game.levelevent = level24_events;
			break;
		case 25:
			game.levelmap = level_25_Map+512;
			game.levelevent = level25_events;
			break;
		case 26:
			game.levelmap = level_26_Map+512;
			game.levelevent = level26_events;
			break;
		case 27:
			game.levelmap = level_27_Map+512;
			game.levelevent = level27_events;
			break;
		//WORLD 4
		case 28:
			game.levelmap = level_28_Map+512;
			game.levelevent = level28_events;
			break;
		case 29:
			game.levelmap = level_29_Map+512;
			game.levelevent = level29_events;
			break;
		case 30:
			game.levelmap = level_30_Map+512;
			game.levelevent = level30_events;
			break;
		case 31:
			game.levelmap = level_31_Map+512;
			game.levelevent = level31_events;
			break;
		case 32:
			game.levelmap = level_32_Map+512;
			game.levelevent = level32_events;
			break;
		case 33:
			game.levelmap = level_33_Map+512;
			game.levelevent = level33_events;
			break;
		case 34:
			game.levelmap = level_34_Map+512;
			game.levelevent = level34_events;
			break;
		case 35:
			game.levelmap = level_35_Map+512;
			game.levelevent = level35_events;
			break;
		case 36:
			game.levelmap = level_36_Map+512;
			game.levelevent = level36_events;
			break;
		//FINAL
		case 37:
			game.levelmap = level_37_Map+512;
			game.levelevent = level37_events;
			break;
		case 38:
			game.levelmap = level_38_Map+512;
			game.levelevent = level38_events;
			break;
		case 39:
			game.levelmap = level_39_Map+512;
			game.levelevent = level39_events;
			break;
		case 40:
			game.levelmap = level_40_Map+512;
			game.levelevent = level40_events;
			break;
		case 41:
			game.levelmap = level_41_Map+512;
			game.levelevent = level41_events;
			break;
		default:
			debug.error = 4;
			break;
	}
	//gfx
	switch(game.levelevent[LEVELDATA_TILES]){
		case 0:
			PA_LoadBgPal(screen, 1, (void*)tilegfx0_Pal);
			PA_LoadLargeBg(screen, 1, tilegfx0_Tiles, game.levelmap, 1, 128, 32);
			break;
		case 1:
			PA_LoadBgPal(screen, 1, (void*)tilegfx1_Pal);
			PA_LoadLargeBg(screen, 1, tilegfx1_Tiles, game.levelmap, 1, 128, 32);
			game.tiletransp[0]=52;
			game.tiletransp[1]=53;
			game.tiletransp[2]=54;
			game.tiletransp[3]=55;
			game.tiletransp[4]=79;
			game.tiletransp[5]=80;
			break;
		case 2:
			PA_LoadBgPal(screen, 1, (void*)tilegfx2_Pal);
			PA_LoadLargeBg(screen, 1, tilegfx2_Tiles, game.levelmap, 1, 128, 32);
			game.tiletransp[0]=45;
			game.tiletransp[1]=46;
			game.tiletransp[2]=47;
			game.tiletransp[3]=48;
			game.tiletransp[4]=58;
			game.tiletransp[5]=59;
			game.tiletransp[6]=60;
			game.tiletransp[7]=61;
			break;
		case 3:
			PA_LoadBgPal(screen, 1, (void*)tilegfx3_Pal);
			PA_LoadLargeBg(screen, 1, tilegfx3_Tiles, game.levelmap, 1, 128, 32);
			game.tiletransp[0]=39;
			game.tiletransp[1]=40;
			game.tiletransp[2]=41;
			game.tiletransp[3]=42;
			game.tiletransp[4]=52;
			game.tiletransp[5]=53;
			game.tiletransp[6]=54;
			game.tiletransp[7]=55;
			break;
		case 4:
			PA_LoadBgPal(screen, 1, (void*)tilegfx4_Pal);
			PA_LoadLargeBg(screen, 1, tilegfx4_Tiles, game.levelmap, 1, 128, 32);
			game.tiletransp[0]=33;
			break;
	}
	//
	
	game.totalevents = game.levelevent[LEVELDATA_TOTALEVENTS];
	
	//set backgrounds
	PA_LoadTiledBg(screen, 0, info);
	switch(game.levelevent[LEVELDATA_BG]){
		case 0:
			PA_LoadPAGfxLargeBg(screen, 2, bg_hills_0);
			PA_LoadPAGfxLargeBg(screen, 3, bg_back_0);
			break;
		case 1:
			PA_LoadPAGfxLargeBg(screen, 2, bg_hills_1);
			PA_LoadPAGfxLargeBg(screen, 3, bg_back_1);
			break;
		case 2:
			PA_LoadPAGfxLargeBg(screen, 2, bg_hills_2);
			PA_LoadPAGfxLargeBg(screen, 3, bg_back_0);
			break;
		case 3:
			PA_LoadPAGfxLargeBg(screen, 2, bg_hills_1);
			PA_LoadPAGfxLargeBg(screen, 3, bg_back_2);
			break;
	}
	PA_InitParallaxX(screen, 0, 256, 160, 100);
	
	//loading not-colliding tiles
	for(i=0;i<50;i++){
		game.levelmap_trans[i] = game.levelmap[3072+i];
	}	
}

void LevelClean(){
	u8 i;
	PA_DisableSpecialFx(0);
	
	PA_DeleteTiles(0,0);
	PA_DeleteTiles(0,1);
	PA_DeleteTiles(0,2);
	PA_DeleteTiles(0,3);
	PA_DeleteTiles(1,0);
	PA_DeleteTiles(2,1);
	PA_DeleteTiles(3,2);
	PA_DeleteTiles(4,3);
	
	PA_DeleteMap(0,0);
	PA_DeleteMap(0,1);
	PA_DeleteMap(0,2);
	PA_DeleteMap(0,3);
	PA_DeleteMap(1,0);
	PA_DeleteMap(2,1);
	PA_DeleteMap(3,2);
	PA_DeleteMap(4,3);
	
	//clean rot
	for(i=0;i<32;i++){
		game.freerot[i]=0;
	}
	//clean event vars
	for(i=0;i<=maxevents;i++){
		events[i].shown=0;
		events[i].visible=0;
	}
	
	//clean teleport vars
	for(i=0;i<5;i++){
		teleport[i].x=0;
		teleport[i].y=0;
		teleport[i].level=0;
		teleport[i].sprite=0;
	}
	//clean not-colliding tiles array
	for(i=0;i<20;i++){
		game.levelmap_trans[i] = 0;
	}
	
	//clean transparent tiles
	for(i=0;i<8;i++){//poner a 0...
		game.tiletransp[i]=0;
	}	
	//-----------
	//clean map pointer sprites
	for(i=0;i<50;i++){
		game.mapdot[i]=-1;
	}
	
//clean sprite vars
	for(i=0;i<maxsprites;i++){
		KillSprite(i);
	}
//hero vars---------------
	hero.x = 0;
	hero.y = 0;
	hero.dash = 0;
	hero.crouch = 0;
	hero.scrollx = 0;
	hero.vy = 0;
	hero.vx = 0;
	hero.flip = 0;
	hero.jumppressed = 0;
	hero.shotcounter = 0;
	hero.shotspeed = DEFAULT_SHOT_SPEED;
	hero.movespeed = HERO_SPEED;
	hero.ani_on = 0;
	hero.invisiblecounter = 0;
	hero.blink = 0;
	hero.shotsonscreen = 0;
	hero.monster_aimed = 0;
	hero.last_monster_aimed = 0;
	hero.updatebossdata = 0;
	hero.updatemonsterdata = 0;
	hero.doublejump = 0;
	hero.candoublejump = 0;
	//-------------------------
//boss vars
	boss.enabled = 0;
	boss.part = 0;
	boss.sprite = 0;
	boss.loaded = 0;
	boss.id = 0;
	boss.hidepart = 0;
	boss.hp=0;
	boss.die=0;
	boss.lastaction=0;
	boss.action=0;
	boss.inground=0;
	boss.shootcounter = 0;
	boss.movcounter = 0;
//cleaning GFXs and sprites
	if(game.firstrun==1){//if not first run
		PA_DeleteGfx(0,gfx.editor_bg);
		PA_DeleteGfx(0,gfx.editor_tg[0]);
		PA_DeleteGfx(0,gfx.editor_tg[1]);
		
		PA_DeleteGfx(0,gfx.weapon1[0]);
		PA_DeleteGfx(0,gfx.weapon1[1]);
		PA_DeleteGfx(0,gfx.weapon1[2]);
		
		PA_DeleteGfx(0,gfx.weapon2[0]);
		PA_DeleteGfx(0,gfx.weapon2[1]);
		PA_DeleteGfx(0,gfx.weapon2[2]);
		PA_DeleteGfx(0,gfx.weapon2[3]);
		PA_DeleteGfx(0,gfx.weapon2[4]);
		
		PA_DeleteGfx(0,gfx.weapon3);
		PA_DeleteGfx(0,gfx.weapon4);
		PA_DeleteGfx(0,gfx.weapon5);
		PA_DeleteGfx(0,gfx.weapon6);
		PA_DeleteGfx(0,gfx.weapon7);
		PA_DeleteGfx(0,gfx.weapon8[0]);
		PA_DeleteGfx(0,gfx.weapon8[1]);
		PA_DeleteGfx(0,gfx.weapon8[2]);
		
		PA_DeleteGfx(0,gfx.particle[0]);
		PA_DeleteGfx(0,gfx.particle[1]);
		PA_DeleteGfx(0,gfx.particle[2]);
		PA_DeleteGfx(0,gfx.particle[3]);
		PA_DeleteGfx(0,gfx.particle[4]);
		PA_DeleteGfx(0,gfx.particle[5]);
		PA_DeleteGfx(0,gfx.raiseparticle);
		PA_DeleteGfx(0,gfx.ballraiseparticle[0]);
		PA_DeleteGfx(0,gfx.ballraiseparticle[1]);
		PA_DeleteGfx(0,gfx.ballraiseparticle[2]);
		PA_DeleteGfx(0,gfx.ballraiseparticle[3]);
		PA_DeleteGfx(0,gfx.ballraiseparticle[4]);
		PA_DeleteGfx(0,gfx.items);
		
		PA_DeleteGfx(0,gfx.mapdot[0]);
		PA_DeleteGfx(0,gfx.mapdot[1]);
		PA_DeleteGfx(0,gfx.mapdot[2]);
		PA_DeleteGfx(0,gfx.mapdot[3]);
	}
	//clean background
	PA_ResetBgSys();
	PA_ResetSpriteSys();
}

void LoadGFX(u8 level){
	LoadMap(level);	
	LoadPal();
	LoadSprites();
}
void LoadTeleports(){
	u8 i=0;
	u16 a=0;
	u8 tp=0;
	u8 s=0;
	for(i=0;i<game.totalevents;i++){
		if(game.levelevent[8 + a] == 2){//if event is a door/teleport
			s=GetFreeSprite();
			totalsprites++;
			events[i].shown = 1;
			teleport[tp].x = game.levelevent[8 + a + 1];
			teleport[tp].y = game.levelevent[8 + a + 2];
			
			u8 id = game.levelevent[8 + a + 3];
			teleport[tp].level = id>>1;
			teleport[tp].sprite = s;
			tp++;
			sprites[s].free = 11 - (id - ((id>>1)<<1));
			sprites[s].x = (game.levelevent[8 + a + 1])<<11;
			sprites[s].y = (game.levelevent[8 + a + 2] - 2)<<11;
			sprites[s].size = 32;
			sprites[s].speed = game.levelevent[8 + a + 3];
			if(sprites[s].free == 11){
				PA_CreateSprite(0,s,(void*)door_Sprite,OBJ_SIZE_16X32,1,ITEMS_PAL,256,0);
				PA_SetSpritePrio(0,s,SPRITES_PRIO);
			}
		}
		a+=4;
	}
}
void LoadPal(){
	if(!data.skills[8])PA_LoadSpritePal(0,HERO_PAL,(void*)player_Pal);	//hero sprite
	else PA_LoadSpritePal(0,HERO_PAL,(void*)superplayer_Pal);	//superplayer
	
	PA_LoadSpritePal(0,SHOOTS_PAL,(void*)weapon_Pal);	//preload weapon 1 pal
	PA_LoadSpritePal(0,EFFECTS_PAL,(void*)effects_Pal);	//effect sprites
	PA_LoadSpritePal(0,MONSTERS_PAL,(void*)monster_Pal);	//monster pal
	PA_LoadSpritePal(0,BLINK_PAL,(void*)white_Pal);	//para cuando parpadea en blanco
	PA_LoadSpritePal(0,HUMO_PAL,(void*)effects_Pal);	//humoh
	PA_LoadSpritePal(0,STATUS_WEAPON_PAL,(void*)weaponstatus_Pal);	//items
	PA_LoadSpritePal(0,ITEMS_PAL,(void*)itempal_Pal);	//items
	PA_LoadSpritePal(0,OTHERS_PAL,(void*)otherpal_Pal);	//items
}

void LoadSprites(){
	u8 a;
	//loading status gfx
		gfx.statusweapon = PA_CreateGfx(0,(void*)status_weapon_Sprite,OBJ_SIZE_16X16,1);
		PA_CreateSpriteFromGfx(0,status_weapon_slot,gfx.statusweapon,OBJ_SIZE_16X16,1,STATUS_WEAPON_PAL,STATUS_WEAPON_X,STATUS_WEAPON_Y);
		sprites[status_weapon_slot].free = 10;
		
		gfx.statusweaponx = PA_CreateGfx(0,(void*)status_weapon_1_Sprite,OBJ_SIZE_16X8,1);
		PA_CreateSpriteFromGfx(0,status_weapon_x_slot,gfx.statusweaponx,OBJ_SIZE_16X8,1,STATUS_WEAPON_PAL,STATUS_WEAPON_X,STATUS_WEAPON_Y);
		sprites[status_weapon_x_slot].free = 10;
		
		gfx.statusweaponexp = PA_CreateGfx(0,(void*)status_weapon_2_Sprite,OBJ_SIZE_16X8,1);
		PA_CreateSpriteFromGfx(0,status_weapon_exp_slot,gfx.statusweaponexp,OBJ_SIZE_16X8,1,STATUS_WEAPON_PAL,STATUS_WEAPON_X+16,STATUS_WEAPON_Y);
		sprites[status_weapon_exp_slot].free = 10;
		
		totalsprites+=3;
	
	//shoot gfx:
		gfx.weapon1[0] = PA_CreateGfx(0,(void*)weapon_1_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon1[1] = PA_CreateGfx(0,(void*)weapon_1_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon1[2] = PA_CreateGfx(0,(void*)weapon_1_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon2[0] = PA_CreateGfx(0,(void*)weapon_2_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon2[1] = PA_CreateGfx(0,(void*)weapon_2_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon2[2] = PA_CreateGfx(0,(void*)weapon_2_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon2[3] = PA_CreateGfx(0,(void*)weapon_2_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon2[4] = PA_CreateGfx(0,(void*)weapon_2_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon3 = PA_CreateGfx(0,(void*)weapon_3_Sprite,OBJ_SIZE_8X8,1);
		gfx.weapon4 = PA_CreateGfx(0,(void*)weapon_4_Sprite,OBJ_SIZE_8X8,1);
		gfx.weapon5 = PA_CreateGfx(0,(void*)weapon_5_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon6 = PA_CreateGfx(0,(void*)weapon_6_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon7 = PA_CreateGfx(0,(void*)weapon_7_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon8[0] = PA_CreateGfx(0,(void*)weapon_8_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon8[1] = PA_CreateGfx(0,(void*)weapon_8_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon8[2] = PA_CreateGfx(0,(void*)weapon_8_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon9[0] = PA_CreateGfx(0,(void*)weapon_9_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon9[1] = PA_CreateGfx(0,(void*)weapon_9_Sprite,OBJ_SIZE_16X16,1);
		gfx.weapon9[2] = PA_CreateGfx(0,(void*)weapon_9_Sprite,OBJ_SIZE_16X16,1);
		
	//raise particle gfx:
		gfx.raiseparticle = PA_CreateGfx(0,(void*)effect_raise_Sprite,OBJ_SIZE_8X8,1);
		
	//ball raise particles
		gfx.ballraiseparticle[0] = PA_CreateGfx(0,(void*)effect_ballraise_Sprite,OBJ_SIZE_8X8,1);
		gfx.ballraiseparticle[1] = PA_CreateGfx(0,(void*)effect_ballraise_Sprite+64,OBJ_SIZE_8X8,1);
		gfx.ballraiseparticle[2] = PA_CreateGfx(0,(void*)effect_ballraise_Sprite+128,OBJ_SIZE_8X8,1);
		gfx.ballraiseparticle[3] = PA_CreateGfx(0,(void*)effect_ballraise_Sprite+192,OBJ_SIZE_8X8,1);
		gfx.ballraiseparticle[4] = PA_CreateGfx(0,(void*)effect_ballraise_Sprite+256,OBJ_SIZE_8X8,1);
		
	//particles gfx:
	for(a=0;a<TOTALPARTICLES;a++){
		gfx.particle[a] = PA_CreateGfx(0,(void*)effects_Sprite,OBJ_SIZE_8X8,1);
	}
		
	//items palete:
		gfx.items = PA_CreateGfx(0,(void*)items_Sprite,OBJ_SIZE_16X16,1);
	
	//info screen
		sprites[AUTORUN_slot].free = 10;
		PA_CreateSprite(0,AUTORUN_slot,(void*)autorun_Sprite, OBJ_SIZE_32X16,1,ITEMS_PAL,AUTORUN_X,AUTORUN_Y);
		PA_SetSpriteAnim(0,AUTORUN_slot,hero.autorun);
	
	//HERO------------------------
		if(!data.skills[8])PA_CreateSprite(0,0,(void*)player_Sprite,OBJ_SIZE_32X32,1,HERO_PAL,hero.x>>8,hero.y>>8); // hero sprite
		else PA_CreateSprite(0,0,(void*)superplayer_Sprite,OBJ_SIZE_32X32,1,HERO_PAL,hero.x>>8,hero.y>>8); // superplayer
		totalsprites++;
		PA_SetSpritePrio(0,0,SPRITES_PRIO);
		sprites[HERO_SLOT].free = 1;
		
		sprites[HERO_SLOT].shoot_x = 24;
		sprites[HERO_SLOT].shoot_y = 17;
		
		
		//hero arm
		gfx.hero_arm = PA_CreateGfx(0,(void*)player_arm_Sprite,OBJ_SIZE_32X32,1);
		PA_CreateSpriteFromGfx(0,HERO_ARM_SLOT,gfx.hero_arm,OBJ_SIZE_32X32,1,HERO_PAL,0,0);
		totalsprites++;
		PA_SetSpritePrio(0,HERO_ARM_SLOT,SPRITES_PRIO);
		sprites[HERO_ARM_SLOT].free = 1;
		u8 rot=GetFreeRot();
		PA_SetSpriteRotEnable(0,HERO_ARM_SLOT,rot);
		game.freerot[rot]=1;
		sprites[HERO_ARM_SLOT].rot=rot;
	//--------------------------------

}

void CleanScreen(u8 screen){
	PA_DisableSpecialFx(screen);
	PA_DeleteTiles(screen,0);
	PA_DeleteTiles(screen,1);
	PA_DeleteTiles(screen,2);
	PA_DeleteTiles(screen,3);
	
	PA_DeleteMap(screen,0);
	PA_DeleteMap(screen,1);
	PA_DeleteMap(screen,2);
	PA_DeleteMap(screen,3);
	
	PA_ResetBg(screen);
	
	u8 i;
	for(i=0;i<maxsprites;i++){
		PA_SetSpriteXY(screen,i,256,0);
	}
}
