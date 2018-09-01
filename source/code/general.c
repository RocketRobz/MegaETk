void Wait(u32 counter){
	u32 a=0;
	while(a<counter){
		a++;
		SpriteActions();
		UpdateSoundVars();
		PA_WaitForVBL();
	}
}

void Wait_or_skip(u32 counter){
	u32 a=0;
	while(a<counter){
		a++;
		SpriteActions();
		UpdateSoundVars();
		if((Pad.Newpress.Start)||(Pad.Newpress.A)||(Pad.Newpress.B))a=counter;
		PA_WaitForVBL();
	}
}

void WaitForPressStart(){
	PA_WaitForVBL();
	while(!Pad.Newpress.Start){
		//Debug();
		PA_WaitForVBL();
	}
}

u8 CheckTransparency(u8 tile){
	u8 a;
	u8 prio = SPRITES_PRIO;
	if(tile!=0){
		for(a=0;a<8;a++){
			if(tile==game.tiletransp[a])prio = 0;
		}
	}
	
	return prio;
}


#define PTEXT_X 96
#define PTEXT_Y 80

#define PSEL_X 87
#define PSEL_Y 82
void Pause(){
	s8 option=0;
	u8 exitpause=0;
	PauseAnim();
	
	PA_DisableSpecialFx(0);
	
	u8 ti=GetFreeSprite();//text sprite
	totalsprites++;
	sprites[ti].free = 10;
	u8 si=GetFreeSprite();//select sprite
	totalsprites++;
	sprites[si].free = 10;
	u8 si2=GetFreeSprite();//select sprite2
	totalsprites++;
	sprites[si2].free = 10;
	
	PA_CreateSprite(0, ti,(void*)pause_text_Sprite, OBJ_SIZE_64X32,1,EFFECTS_PAL,PTEXT_X, PTEXT_Y);
	PA_CreateSprite(0, si,(void*)pause_select_Sprite, OBJ_SIZE_8X8,1,EFFECTS_PAL,PSEL_X, PSEL_Y);
	PA_CreateSprite(0, si2,(void*)pause_select_Sprite, OBJ_SIZE_8X8,1,EFFECTS_PAL,PSEL_X+64+8, PSEL_Y);
	PA_SetSpriteHflip(0,si2,1);
	Wait(1);
	while(!exitpause){
		if(Pad.Newpress.Down){
			option++;
			NewSound(select_sound);
			if(option>2)option=0;
			
			//update arrows position
			PA_SetSpriteXY(0,si,PSEL_X,PSEL_Y+10*option);
			PA_SetSpriteXY(0,si2,PSEL_X+64+8,PSEL_Y+10*option);
		}
		else if(Pad.Newpress.Up){
			option--;
			NewSound(select_sound);
			if(option<0)option=2;
			
			
			//update arrows position
			PA_SetSpriteXY(0,si,PSEL_X,PSEL_Y+10*option);
			PA_SetSpriteXY(0,si2,PSEL_X+64+8,PSEL_Y+10*option);
		}
		
		if((Pad.Newpress.A)||(Pad.Newpress.Start)){
			switch(option){
				case 0://continue
					exitpause=1;
					break;
				case 1://select level
					game.screen = GAME_MENU;
					game.die=3;
					exitpause=1;
					break;
				case 2://Quit game
					game.screen = TITLE_SCREEN;
					game.die=3;
					exitpause=1;
					break;
			}
		}
		UpdateSoundVars();
		PA_WaitForVBL();
	}
	
	
	PA_SetSpriteXY(0,ti,256,0);
	sprites[ti].free = 0;
	PA_SetSpriteXY(0,si,256,0);
	sprites[si].free = 0;
	PA_SetSpriteXY(0,si2,256,0);
	sprites[si2].free = 0;
	UnPauseAnim();
	
	PA_EnableSpecialFx(0,SFX_ALPHA,SFX_OBJ,SFX_BG1);
	PA_SetSFXAlpha(0,6,31);
}

void PauseAnim(){
	u8 i;
	for(i=0;i<maxsprites;i++){
		if(sprites[i].animated==1)PA_SpriteAnimPause(0,i,1);
	}
}

void UnPauseAnim(){
	u8 i;
	for(i=0;i<maxsprites;i++){
		if(sprites[i].animated==1)PA_SpriteAnimPause(0,i,0);
	}
}

void SpriteActions(){
	u8 i=0;
	
	sprites[0].x = hero.x;
	sprites[0].y = hero.y;
	
	for(i=0;i<=maxsprites;i++){
		if(sprites[i].free != 0){//SOLO MIRAR ACCIONES SI ES ALGO
		//OTROS
			//raise effect
			if(sprites[i].raise>0){	//if the sprite has raise mode, then create raise particle
				sprites[i].raise--;
				if( (((sprites[i].raise)>>1)<<1) == sprites[i].raise){
					CreateRaiseParticle(sprites[i].x>>8, sprites[i].y>>8);
					}
			}
			//-------------
			
			//ball raise effect
			if(sprites[i].ballraise>0){	//if the sprite has ball raise mode, then create ball raise particle
				sprites[i].ballraise--;
				if( (((sprites[i].ballraise)>>3)<<3) == sprites[i].ballraise){
					CreateBallRaiseParticle(sprites[i].x>>8, sprites[i].y>>8);
					}
			}
			//-------------
			
			//kill monster
			if(sprites[i].kill==1){
				if(sprites[i].killcnt>0){
					if(sprites[i].free==4)KillMonsterEffect(i);
				}
				else KillSprite(i);
			}
			//-------------
			
			//blink?
			if(sprites[i].blink>0)CheckBlink(i);
			//-----------
			
			
		//el switch para sus cosas
			switch(sprites[i].free){
				//SHOT
				case 2:
					MoveShots(i,1);
					break;
					
				//MONSTERS
				case 3:	
					//Monster Actions (move, shot, etc..)
					MonsterActions(i);
					
					//Collision Monster<->hero (if invisible=0)
					if(hero.invisiblecounter==0){
						if(SCol(0,i)!=0){
							NewHitHero(i,1);
							PA_SetSpriteAnim(0, 0, 1);
						}
					}
					//si se cae muere
					if((sprites[i].y>>8)>192){
						sprites[i].exp = 0;
						SetKillMonster(i);
					}
					break;
				//PARTICLE
				case 6:
					sprites[i].x+=sprites[i].vx;
					sprites[i].vy+=GRAVITY;
					if(sprites[i].vy>MAX_VY)sprites[i].vy = MAX_VY;
					sprites[i].y+=sprites[i].vy;
					//check if dies
					if(((sprites[i].y>>8)>192)
						|| (((sprites[i].x-hero.scrollx)>>8)>256)
						|| (((sprites[i].x-hero.scrollx)>>8)<0))KillSprite(i);
					break;
					
				//HUMO
				case 7:
					if(PA_GetSpriteAnimFrame(0,i)==7)KillSprite(i);
					break;
					
					
				//ITEM
				case 8:
					//EFFECT (ROTATION)
					ItemEffect(i);
					
					//Collision Item<->Hero
					if(SCol(0,i)!=0)UseItem(i);
					break;
				
				//RAISE EFFECT
				case 9:
					sprites[i].y-= 3<<8;
					sprites[i].killcnt--;
					
					//check if dies
					if( ((sprites[i].y>>8) < 10) || (sprites[i].killcnt == 0) ) KillSprite(i);			
					break;
					
				//MONSTER SHOOT
				case 12:
					MoveShots(i,0);
					break;
				//MONSTER PART OF GROUP
				case 13:
					//nothing...
					break;
				//BALL RAISE EFFECT
				case 14:
					//fases (usando variable "counter":
					//0-9: vx++
					//10-29: vx--
					//30-39: vx++ (hasta 0)
					//40-x: keep vx=vy (hasta morir)
					sprites[i].counter++;
					sprites[i].y-=1<<7;
					if(sprites[i].counter>40){
						if(sprites[i].flip==0)sprites[i].vx=sprites[i].vy;
						else sprites[i].vx=-sprites[i].vy;
					}
					else if((sprites[i].counter<10)||(sprites[i].counter>29))sprites[i].vx+=sprites[i].vy;
					else sprites[i].vx-=sprites[i].vy;
					
					switch(sprites[i].counter){
						case 6:
							PA_SetSpriteGfx(0,i,gfx.ballraiseparticle[1]);
							break;
						case 10:
							PA_SetSpriteGfx(0,i,gfx.ballraiseparticle[2]);
							break;
						case 14:
							PA_SetSpriteGfx(0,i,gfx.ballraiseparticle[3]);
							break;
						case 19:
							PA_SetSpriteGfx(0,i,gfx.ballraiseparticle[2]);
							break;
						case 22:
							PA_SetSpriteGfx(0,i,gfx.ballraiseparticle[1]);
							break;
						case 28:
							PA_SetSpriteGfx(0,i,gfx.ballraiseparticle[2]);
							break;
						case 34:
							PA_SetSpriteGfx(0,i,gfx.ballraiseparticle[3]);
							break;
						case 45:
							PA_SetSpriteGfx(0,i,gfx.ballraiseparticle[4]);
							break;
						default:
							break;
					}
					
					if(sprites[i].flip==1)sprites[i].x+=sprites[i].vx;
					else sprites[i].x-=sprites[i].vx;
					sprites[i].killcnt--;
					
					//check if dies
					if( ((sprites[i].y>>8) < 10) || (sprites[i].killcnt == 0) ) KillSprite(i);
					break;
				
				//EXPLOSION 1 (boss and hero)
				case 18:
					sprites[i].x+=sprites[i].vx;
					sprites[i].y+=sprites[i].vy;
					//check if dies
					if(PA_GetSpriteAnimFrame(0,i)==6)KillSprite(i);
					break;
					
				//OTHERS
				case 19:
					if(sprites[i].id == 0){//instant death
						if(SCol(0,i))hero.hp = 0;
					}
					break;
				//BOSS DOOR
				/*case 21:
					if(sprites[i].vx==1){
						if(sprites[i].y>sprites[i].vy)sprites[i].y-=1<<7;
						else PA_SetSpritePrio(0,i,0);
					}
					break;*/
				
				default:
					break;
			}//switch end
			
			//UPDATE XY
			if((sprites[i].free!=10)&&(sprites[i].free!=0)){
				if(!OutScreen(i))PA_SetSpriteXY(0,i,(sprites[i].x-hero.scrollx)>>8, (sprites[i].y>>8));
				else{
					PA_SetSpriteXY(0,i,256,192);
					if(sprites[i].event != 0){//poniendo en off el sprite si es un evento
						if( (((sprites[i].x-hero.scrollx)>>11) > 50)
							|| (((sprites[i].x-hero.scrollx)>>11) < -50) ){
								events[sprites[i].event - 1].shown = 0;
								sprites[i].exp = 0;
								KillSprite(i);
							}
					}
				}
			}
			//--------
			
		}//if(sprites[i].free!=0) end
	}//for end
}

u8 GetFreeRot(){
	u8 i=0;
	for(i=0;i<32;i++){
		if(game.freerot[i]==0)return i;
	}
	
	debug.error = 2;
	return i;
}
void CheckStats(){
	u8 somethingwrong=0;
	
	//CHECKING HERO HP
	if(hero.hp<=0)game.die=1;	//if hp=0 -> die
	
	else if(hero.hp>hero.maxhp){//HP cant be bigger than MaxHP, so if it's bigger it fixs it :P 
		somethingwrong=1;
		hero.hp=hero.maxhp;
	}
	
	if(hero.ammo[hero.weapon]>hero.maxammo[hero.weapon]){//Ammo cant be bigger than MaxAmmo
		somethingwrong=1;
		hero.ammo[hero.weapon]=hero.maxammo[hero.weapon];
	}
	
	if(somethingwrong==1)UpdateStats();//if something is wrong, update stats screen :)
	//-----------------------------------
	
	//change autorun
	if((Stylus.X>AUTORUN_X)&&(Stylus.X<(AUTORUN_X+32))
		&&(Stylus.Y>(AUTORUN_Y+2))&&(Stylus.Y<(AUTORUN_Y+16-2))
		&&(Stylus.Newpress)){
			hero.autorun = hero.autorun*-1 + 1;
			PA_SetSpriteAnim(0,AUTORUN_slot,hero.autorun);
	}
}

void KillSprite(u8 i){
	u8 a;
	if(sprites[i].particles_when_die>0){
		for(a=0;a!=sprites[i].particles_when_die;a++){
			CreateParticle(i,sprites[i].particletype);
		}
	}
	if(sprites[i].rot!=0){
		game.freerot[sprites[i].rot]=0;
		PA_SetSpriteRotDisable(0,i);
	}
	
	//delete map dot
	if(sprites[i].mapdot!=0)game.mapdot[sprites[i].mapdot]=-1;

	//add EPs
	if(game.die==0){
		hero.exp += sprites[i].exp;
		if(sprites[i].exp>0)NewTextLine(getep,sprites[i].exp);
	}
	
	//kill the other sprite in the group
	if(sprites[i].group!=0)KillSprite(sprites[i].group);
	
	//if shoot by hero:
	if(sprites[i].free==2)hero.shotsonscreen--;
	
	//clean all values
	sprites[i].vy=0;
	sprites[i].vx=0;
	sprites[i].speed=0;
	sprites[i].size=0;
	sprites[i].hp=0;
	sprites[i].flip=0;
	sprites[i].weapon=0;
	sprites[i].id=0;
	sprites[i].free=0;
	sprites[i].power = 0;
	sprites[i].kill = 0;
	sprites[i].killcnt = 0;
	sprites[i].rot=0;
	sprites[i].rotangle=0;
	sprites[i].zoom=256;
	sprites[i].w1=0;
	sprites[i].w2=0;
	sprites[i].h1=0;
	sprites[i].h2=0;
	sprites[i].shoot_x=0;
	sprites[i].shoot_y=0;
	sprites[i].blink = 0;
	sprites[i].ballraise=0;
	sprites[i].particles_when_die = 0;
	sprites[i].particletype = 0;
	sprites[i].x = 0;
	sprites[i].y = 0;
	sprites[i].event = 0;
	sprites[i].counter = 0;
	sprites[i].shootangle = 0;
	sprites[i].collision = 0;
	sprites[i].colcounter = 0;
	sprites[i].gravity=0;
	sprites[i].group=0;
	sprites[i].exp=0;
	sprites[i].animated=0;
	sprites[i].mapdot=0;
	PA_SetSpriteXY(0,i,256,0);
	PA_StopSpriteAnim(0,i);
	PA_SetSpritePal(0,i,0);
	totalsprites--;
}

u8 GetFreeSprite(){//0: monster, weapon etc.. 1: particle (if there is no space, delete particle)
	u8 i=0;
	u8 p=127;//por si no encuentra, que se cargue una particula...
	for(i=0;i<maxsprites;i++){
		if(sprites[i].free==0)return i;
		else if(sprites[i].free == 6)p = i;
	}


	//if it didn't return yet ->> ERROR
	//debug.error = 1;
	return p;
}

u8 OutScreen(u8 i){
	//if(game.disable_outscreen)return 0;
	
	if(((sprites[i].x-hero.scrollx)>>8 > 256)	|| ((sprites[i].x-hero.scrollx)>>8 < -sprites[i].size)
		|| (sprites[i].y>>8 < -sprites[i].size))return 1;
	else return 0;
}
u8 PalUsed(u8 pal){
	u8 i=0;
	for(i=0;i<maxsprites;i++){
		if(PA_GetSpritePal(0,i) == pal)return 1;
	}
	return 0;
}

void CheckTeleport(){
	s16 tpx;
	s16 tpy;
	u8 i;
	for(i=0;i<5;i++){
		tpx = (hero.x>>11) +2 - teleport[i].x;
		tpy = (hero.y>>11) +2 - teleport[i].y;
		
		if((tpx <= 1) && (tpx >= 0) && (tpy <= 1) && (tpy >= 0)){
				switch(game.levelevent[LEVELDATA_TYPE]){
					case NORMAL_LEVEL:
						game.die=2;
						game.teleport=teleport[i].level;
						break;
					case NORMAL_END_LEVEL:
						game.die=2;
						game.teleport=0;
						game.levelcomplete=1;
						game.screen = GAME_MENU;
						break;
					case BOSS_LEVEL://en teoria no tendria k llegar aki pero weno..
						game.die=2;
						game.teleport=0;
						game.levelcomplete=1;
						game.screen = GAME_MENU;
						break;
				}
			}
		}
}
