//BOSS ACTIONS
#define BOSS_STAY 0
#define BOSS_WALK 1
#define BOSS_JUMP 2
#define BOSS_AIM_COUNTER 3
#define BOSS_SHOT 4
#define BOSS_FALL 5
#define BOSS_COUNTER 6
#define BOSS_RESTORE 7
#define BOSS_GO_TELEPORT 8
#define BOSS_WAIT_TELEPORT 9
#define BOSS_WAIT_TELEPORT2 10 //appearing

void LoadBoss(){
	u8 i;
	u8 z;
	u8 rot;
	u8 a=0;
	
	PA_StopMod();
	
//free=16 -> BOSS
//free=17 -> BOSS part
//load boss sprite + gfx
	switch(game.level){
		case 9:
			boss.id = 0;
			break;
		case 18:
			boss.id = 1;
			break;
		case 27:
			boss.id = 2;
			break;
		case 36:
			boss.id = 3;
			break;
		//final zz
		case 37:
			boss.id = 0;
			break;
		case 38:
			boss.id = 1;
			break;
		case 39:
			boss.id = 2;
			break;
		case 40:
			boss.id = 3;
			break;
		case 41:
			boss.id = 4;
			break;
	}

	i = GetFreeSprite();
	totalsprites++;
	boss.sprite = i;
	boss.die=0;
	boss.hidepart=0;
	boss.movcounter = 0;
	boss.shootcounter = 0;
	sprites[i].free = 16;
	sprites[i].size = 32;
	sprites[i].flip = 1;
	sprites[i].pal = MONSTERS_PAL;
	sprites[i].shoot_x=16;
	sprites[i].shoot_y=16;
	
	//load map dot
	u8 m=GetFreeMapDot();
	game.mapdot[m]=i;
	sprites[i].mapdot=m;
	
	
	//prepare status info
	hero.updatebossdata = 1;
	PA_StopSpriteAnim(1,2);
	PA_StopSpriteAnim(1,3);
	PA_SetSpriteXY(1,2,256,0);
	PA_SetSpriteXY(1,3,256,0);
	game.monsterimgloaded=0;
	
	switch(boss.id){
		case 0://Bubbleman
			//POSICIONAR
			sprites[i].x = 960<<8;
			sprites[i].y = (128+sprites[i].h2)<<8;
			//-------------------------
			
			
			//reservar rotacion
			rot = GetFreeRot();
			sprites[i].rot = rot;
			sprites[i].rotangle=0;
			game.freerot[rot]=1;
			PA_SetRotsetNoZoom(0, rot, 0);
			//------------
			
			boss.hp = 1000;
			boss.maxhp = 1000;
			sprites[i].exp = 8000;
			sprites[i].speed = 300;
			sprites[i].power = 10;
			
			sprites[i].h1=2;
			sprites[i].h2=1;
			sprites[i].w1=7;
			sprites[i].w2=8;
			boss.action = BOSS_STAY;
			PA_CreateSprite(0,i, (void*)boss_0_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpriteHflip(0,i,sprites[i].flip);
			break;
		case 1://Screwman
			//tiene otro sprite, asi que a cargarlo..
			z = GetFreeSprite();
			totalsprites++;
			rot = GetFreeRot();
			sprites[z].free = 17;
			sprites[z].pal = MONSTERS_PAL;
			boss.part = z;
			
			u8 f=z;
			
			if(z<i){
				z=i;
				i=f;
			}
			
			//POSICIONAR
			sprites[i].x = 940<<8;
			sprites[i].y = (168-32+sprites[i].h2)<<8;
			//-------------------------
			
			rot = GetFreeRot();
			sprites[i].rot = rot;
			sprites[i].rotangle=0;
			game.freerot[rot]=1;
			
			
			boss.hp = 1500;
			boss.maxhp = 1500;
			sprites[i].exp = 16000;
			sprites[i].speed = 256;
			sprites[i].power = 10;
			
			sprites[i].h1=2;
			sprites[i].h2=1;
			sprites[i].w1=9;
			sprites[i].w2=9;
			boss.action = BOSS_STAY;
			PA_CreateSprite(0,i, (void*)boss_1_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetRotsetNoZoom(0,rot,0);
			PA_SetSpriteHflip(0,i,sprites[i].flip);

			sprites[z].power = 20;
			
			sprites[z].h1=10;
			sprites[z].h2=9;
			sprites[z].w1=13;
			sprites[z].w2=14;
			sprites[z].size=32;
			sprites[z].rot = rot;
			
			sprites[z].x = sprites[i].x - (16<<8);
			sprites[z].y = sprites[i].y + (sprites[i].	h1<<8) + ((sprites[z].size - sprites[z].h2)<<8);
			PA_CreateSprite(0,z, (void*)boss_1_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[z].x-hero.scrollx)>>8,sprites[z].y>>8);
			PA_SetSpriteAnim(0, z, 1);
			break;
		case 2://IcyMan
			//POSICIONAR
			sprites[i].x = 962<<8;
			sprites[i].y = 113<<8;
			//-------------------------

			boss.hp = 2000;
			boss.maxhp = 2000;
			sprites[i].exp = 30000;
			sprites[i].speed = 420;
			sprites[i].power = 10;
			
			sprites[i].h1=2;
			sprites[i].h2=1;
			sprites[i].w1=7;
			sprites[i].w2=8;
			boss.action = BOSS_STAY;
			PA_CreateSprite(0,i, (void*)boss_2_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpriteHflip(0,i,sprites[i].flip);
			sprites[i].shootangle=180;
			break;
		case 3://Ghoste
			//POSICIONAR
			sprites[i].x = 964<<8;
			sprites[i].y = (67+sprites[i].h2)<<8;
			//-------------------------
			
			boss.hp = 2500;
			boss.maxhp = 2500;
			sprites[i].exp = 50000;
			sprites[i].speed = 0;
			sprites[i].power = 15;
			
			sprites[i].h1=0;
			sprites[i].h2=1;
			sprites[i].w1=8;
			sprites[i].w2=8;
			boss.action = BOSS_STAY;
			PA_CreateSprite(0,i, (void*)boss_3_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 0, 3, 8);
			PA_SetSpriteHflip(0,i,sprites[i].flip);
			break;
		case 4://Ghoste Final
			//POSICIONAR
			sprites[i].x = 504<<8;
			sprites[i].y = 88<<8;
			//-------------------------
			
			boss.hp = 5000;
			boss.maxhp = 5000;
			sprites[i].exp = 150000;
			sprites[i].speed = 0;
			sprites[i].power = 15;
			
			sprites[i].h1=0;
			sprites[i].h2=1;
			sprites[i].w1=8;
			sprites[i].w2=8;
			boss.action = BOSS_STAY;
			PA_CreateSprite(0,i, (void*)boss_3_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 0, 3, 8);
			PA_SetSpriteHflip(0,i,sprites[i].flip);
			game.disable_outscreen=1;
			break;
	}
	
	
	if(boss.id!=4){//if not final boss..
	//---------------
	//SCROLLING
		//get door sprite
		u8 door=0;
		for(i=0;i<maxsprites;i++){
			if(sprites[i].free == 21){door = i;break;}
		}
		//------
		NewSound(door_sound);
		while(a<2){
			a=0;
			if(sprites[door].y>sprites[door].vy)sprites[door].y-=2<<7;
			else{ PA_SetSpritePrio(0,door,0);a++;}
			
			PA_ParallaxScrollX(0, hero.scrollx>>8);
			
			if(hero.scrollx < (768<<8))hero.scrollx += 2<<8;
			else a++;
			
			UpdateXY();
			SpriteActions();
			PA_WaitForVBL();
		}
		hero.scrollx = (768<<8);
	//------------------------
	}//end ifnot final boss
	
	//remove shoots from screen
	hero.invisiblecounter = 0;
	hero.status_changed = 1;
	hero.blink=0;
	PA_SetSpritePal(0,0,HERO_PAL);
	PA_SetSpritePal(0,1,HERO_PAL);
	for(a=0;a<128;a++){
		if((sprites[a].free==2)||(sprites[a].free==12))KillSprite(i);
	}
	//------------------------
	
	boss.loaded = 1;
	hero.dash=0;
	Wait(50);
	NewSound(haha_sound);
	Wait(100);
	if(boss.id!=4)PA_PlayMod(music_boss_mod);
	else PA_PlayMod(music_finalboss_mod);
	
	sprites[i].vx = 0;
	boss.action = BOSS_STAY;
}

void BossActions(){
	if(boss.die==0){
		switch(boss.id){
			case 0:
				Boss_Bubbleman();
				BossHeroCollision();
				break;
			case 1:
				Boss_Screwman();
				BossHeroCollision();
				break;
			case 2:
				Boss_Icyman();
				BossHeroCollision();
				break;
			case 3:
				Boss_Ghoste();
				BossHeroCollision();
				break;
			case 4:
				Boss_GhosteFINAL();
				BossHeroCollision();
				break;
		}
	}
	else if(boss.die==1){
		Boss_Dies();
	}
}

void Boss_Bubbleman(){
//u8 sprite;
//u8 id;
//u16 hp;
//u8 camino;
//u16 movcounter;
//u16 shootcounter;
	u8 i = boss.sprite;
	
	switch(boss.action){
		case BOSS_STAY:
			boss.movcounter++;
			if(boss.movcounter>150){
				boss.movcounter=0;
				boss.action = BOSS_AIM_COUNTER;	
			}
			
			if(VCola2(i,1<<8)){
				sprites[i].y-=1<<8;
				sprites[i].vy=0;
			}
			
			break;
		case BOSS_AIM_COUNTER://hacerse bola
			if(sprites[i].animated==0){//activar animacion..
				sprites[i].animated = 1;
				PA_StartSpriteAnim(0,i,0,6,8);
			}
			else{//mirar si a acabao animasion
				if(PA_GetSpriteAnimFrame(0,i)==6){
					PA_StopSpriteAnim(0,i);
					sprites[i].animated = 0;
					boss.action = BOSS_FALL;
					
					sprites[i].h1=9;
					sprites[i].h2=9;
					sprites[i].w1=8;
					sprites[i].w2=9;
					//activar rotacion pa bola
					PA_SetSpriteRotEnable(0,i,sprites[i].rot);
				}
			}
			break;
		case BOSS_FALL:
			if(VCola(i))boss.action = BOSS_COUNTER;
			break;
			
		case BOSS_COUNTER:
			boss.movcounter++;
			if(boss.movcounter>50){
				boss.movcounter=0;
				boss.action = BOSS_JUMP;
			}
			break;
			
		case BOSS_JUMP:
			if(sprites[i].x>880<<10)sprites[i].vx = -512;
			else sprites[i].vx = 512;
			sprites[i].vy = 1400;
			boss.action = BOSS_SHOT;
			sprites[i].y-=sprites[i].vy;
			break;
			
		case BOSS_SHOT:
			if(sprites[i].vx<0)sprites[i].rotangle+=8;
			else sprites[i].rotangle-=8;
			
			
			if(sprites[i].rotangle>360)sprites[i].rotangle-=360;
			else if(sprites[i].rotangle<0)sprites[i].rotangle+=360;
			
			PA_SetRotsetNoZoom(0,sprites[i].rot, sprites[i].rotangle);
			
			if(HCola(i,sprites[i].vx)){
				sprites[i].vx*=-1;
				sprites[i].y-=sprites[i].vy;
			}
			else if(VCola2(i,sprites[i].vy)){
				sprites[i].vy*=-1;
				sprites[i].y-=sprites[i].vy;
				if(sprites[i].gravity!=0)sprites[i].vy-=200;
				
				boss.shootcounter++;
				if(boss.shootcounter==6){
					boss.action = BOSS_RESTORE;
					boss.shootcounter=0;
					sprites[i].vy = 1200;
					
					sprites[i].h1=2;
					sprites[i].h2=1;
					sprites[i].w1=7;
					sprites[i].w2=8;
					
					sprites[i].rotangle=0;
					PA_SetRotsetNoZoom(0,sprites[i].rot, 0);
					PA_SetSpriteRotDisable(0,i);
				}
			}
			break;
		case BOSS_RESTORE:
			if(sprites[i].vx>10)sprites[i].vx-=5;
			else if(sprites[i].vx<-10)	sprites[i].vx+=5;
			else sprites[i].vx=0;
			
			boss.movcounter++;
			if(boss.movcounter==4){
				if(PA_GetSpriteAnimFrame(0,i)>0)PA_SetSpriteAnimFrame(0,i,(PA_GetSpriteAnimFrame(0,i))-1);
				else {
					boss.action = BOSS_STAY;
					while(VCola(i)){
						PA_SetSpriteAnimFrame(0,i,0);
						sprites[i].y-=1<<8;
						sprites[i].vy=0;
					}
				}
				boss.movcounter=0;
				sprites[i].vx=0;
			}
			break;
	}
	
	
	//gravedad
	if((!VCola(i))&&(!HCola(i,sprites[i].vx)))sprites[i].vy-=GRAVITY;
	else if(boss.action!=BOSS_SHOT){
		sprites[i].vy = 0;
	}
	
	sprites[i].x+=sprites[i].vx;
	sprites[i].y-=sprites[i].vy;
	
	//antibug o_O
	if((sprites[i].y>>8)>(140)){
		while(VCola(i)){
			sprites[i].y-=1<<8;
			sprites[i].vy=0;
		}
	}
}

void Boss_Screwman(){
//u8 sprite;
//u8 id;
//u16 hp;
//u8 camino;
//u16 movcounter;
//u16 shootcounter;
	u8 i = boss.sprite;
	u8 z = boss.part;
	u8 a=0;
	s16 b=0;
	
	//para activar rotacion->>>>> PA_SetSpriteRotEnable(0,i,rot);
	//actualiza tornillo
	if(boss.hidepart==0){
		sprites[z].x = sprites[i].x+(1<<8);
		sprites[z].y = sprites[i].y + (sprites[i].	h1<<8) - ((sprites[z].size - sprites[z].h2 - 2)<<8);
	}
	
	
	switch(boss.action){
		case BOSS_STAY:
			boss.movcounter++;
			if(boss.movcounter>50){
				boss.movcounter=0;
				boss.action = BOSS_WALK;			
			}
			break;
		case BOSS_AIM_COUNTER:
			if(boss.shootcounter<10){
				if(sprites[i].ballraise==0){
					boss.lastaction = boss.action;
					boss.shootcounter++;
				}
			}
			else if(boss.shootcounter==10){
				sprites[i].vy = 1300;
				boss.shootcounter++;
			}
			else if((boss.shootcounter==11)||(boss.shootcounter==12)||(boss.shootcounter==13)){
				if(sprites[i].vy>0){
					sprites[i].vy -= GRAVITY;
					sprites[i].y-=sprites[i].vy;
				}
				else sprites[i].vy = 0;
				
				if(sprites[i].vy==0){
					if(boss.shootcounter==11){//escondiendo tornillo
						boss.hidepart=1;
						if(sprites[z].y>=sprites[i].y)boss.shootcounter++;
						else sprites[z].y+=1<<8;
					}
					else if(boss.shootcounter==12){
						PA_SetSpriteRotEnable(0,i,sprites[i].rot);
						PA_SetSpriteRotEnable(0,z,sprites[z].rot);
						boss.shootcounter++;
					}
					else{
						b = (PA_GetAngle( (sprites[i].x>>8)+16, (sprites[i].y>>8)+16, (sprites[0].x>>8)+16, (sprites[0].y>>8)+16));
						b -= 128;
						if(b<0)b+=512;
						
						
						for(a=0;a<6;a++){
							if(sprites[i].shootangle<b)sprites[i].shootangle++;
							else if(sprites[i].shootangle>b)sprites[i].shootangle--;
							else {
								sprites[i].shootangle=b;
								boss.shootcounter=14;
								break;
							}
						}
						
						if(sprites[i].shootangle<0)sprites[i].shootangle+=512;
						
						PA_SetRotsetNoZoom(0,sprites[i].rot, sprites[i].shootangle);
						PA_SetRotsetNoZoom(0,sprites[z].rot, sprites[i].shootangle);
					}
				}
			}
			else if(boss.shootcounter==14){
				sprites[i].shootangle+=128;
				if(sprites[i].shootangle>512)sprites[i].shootangle-=512;
				
				sprites[i].shootangle/=1.42;
				NewShot(8,i);
				sprites[i].shootangle = 0;
				PA_SetSpriteRotDisable(0,i);
				PA_SetSpriteRotDisable(0,z);
				boss.shootcounter=0;
				boss.action=BOSS_JUMP;
				boss.hidepart=0;
				
				
				PA_SetSpriteHflip(0,i,sprites[i].flip);
			}
			break;	
	}
	
	if((boss.action==BOSS_WALK)&&(boss.shootcounter==3)){
		if(sprites[i].vy == 0){
			boss.lastaction = boss.action;
			boss.action = BOSS_AIM_COUNTER;
			boss.shootcounter = 0;
			boss.movcounter = 0;
			sprites[i].ballraise = 20;
		}	
	}
	
	//moviendo, saltando etc..
	if((boss.action!=BOSS_AIM_COUNTER)&&(boss.action!=BOSS_STAY)&&(boss.action!=BOSS_SHOT)){
		if(sprites[i].flip==0){
			if(!HCola(i,sprites[i].speed)){
				sprites[i].x += sprites[i].speed;
				boss.lastaction = boss.action;
				boss.action = BOSS_WALK;
			}
			else{
				sprites[i].flip = 1;
				PA_SetSpriteHflip(0,i,1);
			}
		}
		else{
			if(!HCola(i,-sprites[i].speed)){
				sprites[i].x -= sprites[i].speed;
				boss.lastaction = boss.action;
				boss.action = BOSS_WALK;
			}
			else {
				sprites[i].flip = 0;
				PA_SetSpriteHflip(0,i,0);
			}
		}
		boss.movcounter++;
	}//----------------------

	//gravity y eso
	if((boss.action!=BOSS_AIM_COUNTER)&&(boss.action!=BOSS_SHOT)){
		sprites[i].y-=sprites[i].vy;
		if(VCola(i)){
			sprites[i].vy=0;
			while(a==0){
				if(VCola(i)){
					sprites[i].y-=1<<8;
				}
				else{
					sprites[i].y+=1<<8;
					boss.inground=1;
					a=1;			
				}
			}
		}
		else {
			sprites[i].vy-=GRAVITY;
			boss.lastaction = boss.action;
			boss.action = BOSS_JUMP;
			boss.inground=0;
		}
	}
	//-----------------
	
	//acciones de saltar
	if(boss.action == BOSS_WALK){
		if((sprites[i].x>>8)==929){
			if(sprites[i].flip==1){
				sprites[i].vx=45;
				sprites[i].vy=1300;
				sprites[i].y-=sprites[i].vy;
				boss.shootcounter++;
			}
		}
		else if((sprites[i].x>>8)==845){
			if(sprites[i].flip==0){
				sprites[i].vx=-45;
				sprites[i].vy=1300;
				boss.shootcounter++;
				sprites[i].y-=sprites[i].vy;
			}
		}//------------------
	}

	//IMPULSO (VX)
	if(sprites[i].vx>0){
		sprites[i].x-=sprites[i].speed;
		sprites[i].vx--;
	}
	else if(sprites[i].vx<0){
		sprites[i].x+=sprites[i].speed;
		sprites[i].vx++;
	}
	//----------
	
	//ANIMATION
	if(boss.action == BOSS_WALK){
		if(boss.lastaction != boss.action){
			PA_SetSpriteAnim(0, i, 2);
			PA_StartSpriteAnimEx(0,i,2,4,5,ANIM_UPDOWN,0);
		}	
	}
	else if(boss.action == BOSS_JUMP){
		if(boss.lastaction == BOSS_WALK)PA_StopSpriteAnim(0,i);
		PA_SetSpriteAnim(0, i, 6);
	}
	else if(boss.action == BOSS_AIM_COUNTER){
		if(boss.lastaction == BOSS_WALK)PA_StopSpriteAnim(0,i);
		PA_SetSpriteAnim(0, i, 5);	
	}
	else{
		if(boss.lastaction == BOSS_WALK)PA_StopSpriteAnim(0,i);
		PA_SetSpriteAnim(0, i, 0);
	}
}

void Boss_Icyman(){
//u8 sprite;
//u8 id;
//u16 hp;
//u8 camino;
//u16 movcounter;
//u16 shootcounter;
	u8 i = boss.sprite;
	u8 a=0;
	//gravity y eso
	sprites[i].y-=sprites[i].vy;
	if(VCola(i)){
		sprites[i].vy=0;
		if(boss.action == BOSS_JUMP){
			boss.action = BOSS_WALK;
			sprites[i].animated=0;
			NewShot(9,i);
		}
		while(a==0){
			if(VCola(i)){
				sprites[i].y-=1<<8;
			}
			else{
				sprites[i].y+=1<<8;
				boss.inground=1;
				a=1;			
			}
		}
	}
	else {
		sprites[i].vy-=GRAVITY;
		boss.lastaction = boss.action;
		boss.action = BOSS_JUMP;
		boss.inground=0;
	}
	//-----------------
	
	//shootcounter
	if(boss.shootcounter==100){
		NewShot(9,i);
		boss.shootcounter=0;
	}
	else boss.shootcounter++;
	
	
	switch(boss.action){
		case BOSS_STAY:
			boss.movcounter++;
			if(boss.movcounter>50){
				boss.movcounter=0;
				boss.action = BOSS_WALK;
				sprites[i].animated=0;
				NewShot(9,i);
			}
			break;
		default:
			break;
	}
	
	if((boss.action==BOSS_WALK)||(boss.action==BOSS_JUMP)){
			if(sprites[i].flip==1){
				if(!HCola(i,-sprites[i].speed))sprites[i].x-=sprites[i].speed;
				else {
					sprites[i].flip=0;
					sprites[i].shootangle=0;
					PA_SetSpriteHflip(0,i,sprites[i].flip);
					NewShot(9,i);
				}
			}
			else{
				if(!HCola(i,sprites[i].speed))sprites[i].x+=sprites[i].speed;
				else {
					sprites[i].flip=1;
					sprites[i].shootangle=180;
					PA_SetSpriteHflip(0,i,sprites[i].flip);
					NewShot(9,i);
				}
			}
	}
	
	//if((boss.action == BOSS_JUMP)&&((sprites[i].vy<=GRAVITY>>1)||(sprites[i].vy>=-GRAVITY>>1)))NewShot(9,i);
	
	//acciones de saltar
	if(boss.action == BOSS_WALK){
		if((sprites[i].x>>8)==950){
			if(sprites[i].flip==1){//mirando a <-
				sprites[i].vy=1150;
				sprites[i].y-=sprites[i].vy;
				boss.action = BOSS_JUMP;
			}
		}
		else if((sprites[i].x>>8)<=790){
			if(sprites[i].flip==0){
				sprites[i].vy=1150;
				sprites[i].y-=sprites[i].vy;
				boss.action = BOSS_JUMP;
			}
		}//------------------
	}	
	
	//ANIMATION
	if(boss.action == BOSS_WALK){
		if(sprites[i].animated==0){
			PA_SetSpriteAnim(0, i, 5);
			PA_StartSpriteAnimEx(0,i,5,7,5,ANIM_UPDOWN,0);
			sprites[i].animated=1;
		}	
	}
	else if(boss.action == BOSS_JUMP){
		if(sprites[i].animated==1){
			PA_StopSpriteAnim(0,i);
			sprites[i].animated=0;
		}
		PA_SetSpriteAnim(0, i, 8);
	}
}

void Boss_Ghoste(){
	u8 i = boss.sprite;
	
	//apunter boss al heroLOL
	if(sprites[i].x>hero.x+(32<<8)){//si esta a su izq, apuntar pa <---
		sprites[i].flip=1;
		PA_SetSpriteHflip(0,i,sprites[i].flip);
	}
	else if(sprites[i].x+(32<<8)<hero.x){//si esta a su der, apuntar pa ->
		sprites[i].flip=0;
		PA_SetSpriteHflip(0,i,sprites[i].flip);
	}
	
	switch(boss.action){
		case BOSS_STAY://wait counter, then teleport and shoott
			boss.movcounter++;
			if(boss.movcounter==100){
				boss.action = BOSS_GO_TELEPORT;
				boss.movcounter=0;
			}
			break;
		case BOSS_GO_TELEPORT:
			sprites[i].h1=16;
			sprites[i].h2=16;
			sprites[i].w1=16;
			sprites[i].w2=16;
			PA_StopSpriteAnim(0, i);
			PA_StartSpriteAnimEx(0, i, 4, 10, 16,ANIM_UPDOWN,0);
			boss.action = BOSS_WAIT_TELEPORT;
			break;
		case BOSS_WAIT_TELEPORT:
			if(PA_GetSpriteAnimFrame(0,i)==10){
				if(boss.movcounter==0){
					PA_SpriteAnimPause(0,i,1);
					boss.movcounter++;
				}
				else if(boss.movcounter==30){
					PA_SetSpriteXY(0,i,256,0);
					sprites[i].x=256<<8;
					sprites[i].h1=0;
					sprites[i].h2=1;
					sprites[i].w1=8;
					sprites[i].w2=8;
					
					u8 random = PA_RandMinMax(0,2);
					switch(random){
						case 0:
							sprites[i].x=964<<8;
							sprites[i].y=68<<8;
							break;
						case 1:
							sprites[i].x=875<<8;
							sprites[i].y=105<<8;
							break;
						case 2:
							sprites[i].x=792<<8;
							sprites[i].y=75<<8;
							break;
						default:
							sprites[i].x=964<<8;
							sprites[i].y=68<<8;
							break;
					}
					boss.action = BOSS_WAIT_TELEPORT2;
					PA_SpriteAnimPause(0,i,0);
					boss.movcounter=0;
				}
				else boss.movcounter++;
			}
			break;
		case BOSS_WAIT_TELEPORT2://apareciending
			if(PA_GetSpriteAnimFrame(0,i)==4){
				PA_StopSpriteAnim(0, i);
				boss.action = BOSS_AIM_COUNTER;
				PA_StartSpriteAnim(0, i, 0, 3, 8);
				boss.shootcounter=0;
			}
			break;
		case BOSS_AIM_COUNTER://esperando pa apuntar
			boss.shootcounter++;
			if(boss.shootcounter>=30){
				if((boss.shootcounter==30)||(boss.shootcounter==40)||(boss.shootcounter==50)||(boss.shootcounter==60)){
					sprites[i].shootangle = PA_GetAngle( ((sprites[i].x-hero.scrollx)>>8)+sprites[i].shoot_x, (sprites[i].y>>8)+sprites[i].shoot_y, ((hero.x-hero.scrollx)>>8)+(HERO_SIZE-12), (hero.y>>8)+((HERO_SIZE-12)))/1.42;
					NewShot(1,i);
				}
				else if(boss.shootcounter==61){
					boss.action = BOSS_STAY;
					boss.shootcounter=0;
				}
			}
			break;
	}
}

void Boss_GhosteFINAL(){
	u8 i = boss.sprite;
	
	//apunter boss al heroLOL
	if(sprites[i].x>hero.x+(32<<8)){//si esta a su izq, apuntar pa <---
		sprites[i].flip=1;
		PA_SetSpriteHflip(0,i,sprites[i].flip);
	}
	else if(sprites[i].x+(32<<8)<hero.x){//si esta a su der, apuntar pa ->
		sprites[i].flip=0;
		PA_SetSpriteHflip(0,i,sprites[i].flip);
	}
	
	switch(boss.action){
		case BOSS_STAY://wait counter, then teleport and shoott
			boss.movcounter++;
			if(boss.movcounter==100){
				boss.action = BOSS_GO_TELEPORT;
				boss.movcounter=0;
			}
			break;
		case BOSS_GO_TELEPORT:
			sprites[i].h1=16;
			sprites[i].h2=16;
			sprites[i].w1=16;
			sprites[i].w2=16;
			PA_StopSpriteAnim(0, i);
			PA_StartSpriteAnimEx(0, i, 4, 10, 16,ANIM_UPDOWN,0);
			boss.action = BOSS_WAIT_TELEPORT;
			break;
		case BOSS_WAIT_TELEPORT:
			if(PA_GetSpriteAnimFrame(0,i)==10){
				if(boss.movcounter==0){
					PA_SpriteAnimPause(0,i,1);
					boss.movcounter++;
				}
				else if(boss.movcounter==30){
					PA_SetSpriteXY(0,i,256,0);
					sprites[i].x=256<<8;
					sprites[i].h1=0;
					sprites[i].h2=1;
					sprites[i].w1=8;
					sprites[i].w2=8;
					
					u8 random = PA_RandMinMax(0,5);
					switch(random){
						case 0:
							sprites[i].x=226<<8;
							sprites[i].y=44<<8;
							break;
						case 1:
							sprites[i].x=297<<8;
							sprites[i].y=75<<8;
							break;
						case 2:
							sprites[i].x=225<<8;
							sprites[i].y=120<<8;
							break;
						case 3:
							sprites[i].x=225<<8;
							sprites[i].y=64<<8;
							break;
						case 4:
							sprites[i].x=525<<8;
							sprites[i].y=44<<8;
							break;
						case 5:
							sprites[i].x=507<<8;
							sprites[i].y=120<<8;
							break;
						default:
							sprites[i].x=225<<8;
							sprites[i].y=75<<8;
							break;
					}
					boss.action = BOSS_WAIT_TELEPORT2;
					PA_SpriteAnimPause(0,i,0);
					boss.movcounter=0;
				}
				else boss.movcounter++;
			}
			break;
		case BOSS_WAIT_TELEPORT2://apareciending
			if(PA_GetSpriteAnimFrame(0,i)==4){
				PA_StopSpriteAnim(0, i);
				
				boss.movcounter = PA_RandMinMax(0,10);//movcounter = action
														//0-5: shoot
														//6: summon red monster
														//7: summon green flying imp
														//8: summon green ball
														//9: summon mouze
														//10: blumon
				boss.action = BOSS_AIM_COUNTER;
				PA_StartSpriteAnim(0, i, 0, 3, 8);
				boss.shootcounter=0;
			}
			break;
		case BOSS_AIM_COUNTER://esperando pa accion
			boss.shootcounter++;
			if(boss.shootcounter>=30){
				if((boss.shootcounter==30)||(boss.shootcounter==45)||(boss.shootcounter==60)||(boss.shootcounter==75)||(boss.shootcounter==90)||(boss.shootcounter==105)){
					sprites[i].shootangle = PA_GetAngle( ((sprites[i].x-hero.scrollx)>>8)+sprites[i].shoot_x, (sprites[i].y>>8)+sprites[i].shoot_y, ((hero.x-hero.scrollx)>>8)+(HERO_SIZE-12), (hero.y>>8)+((HERO_SIZE-12)))/1.42;
					switch(boss.movcounter){
						case 0:
							MultipleShot(1,i,3);
							break;
						case 1:
							MultipleShot(1,i,3);
							break;
						case 2:
							MultipleShot(1,i,3);
							break;
						case 3:
							MultipleShot(1,i,3);
							break;
						case 4:
							MultipleShot(1,i,3);
							break;
						case 5:
							MultipleShot(1,i,3);
							break;
						case 6:
							if(totalsprites<90)SummonMonster(sprites[i].x>>8,144,0);
							break;
						case 7:
							if(totalsprites<90)SummonMonster(sprites[i].x>>8,144,2);
							break;
						case 8:
							if(totalsprites<90)SummonMonster(sprites[i].x>>8,144,8);
							break;
						case 9:
							if(totalsprites<90)SummonMonster(sprites[i].x>>8,144,7);
							break;
						case 10:
							if(totalsprites<90)SummonMonster(sprites[i].x>>8,144,5);
							break;
					}
				}
				else if(boss.shootcounter==61){
					boss.action = BOSS_STAY;
					boss.shootcounter=0;
					boss.movcounter=0;
				}
			}
			break;
	}
}
void BossHeroCollision(){
	u8 i=boss.sprite;
	u8 z=boss.part;
	
	//Collision Monster<->hero (if invisible=0)
	if(hero.invisiblecounter==0){
		if(SCol(0,i)!=0){//boss body
			NewHitHero(i,0);
			PA_SetSpriteAnim(0, 0, 6);
		}
		
		if(z!=0){
			if(SCol(0,z)!=0){//boss part
				NewHitHero(z,0);
				PA_SetSpriteAnim(0, 0, 6);
			}
		}
	}
	//---------------------------

}
void HitBoss(u8 dmg){
	u8 i = boss.sprite;
	u8 z = boss.part;
	if((boss.hp-dmg)<=0)boss.die=1;
	else boss.hp -= dmg;
	
	CreateParticle(boss.sprite,0);
	
	//blinkear
	sprites[i].blink = BLINK_COUNTER;
	PA_SetSpritePal(0,i,WHITE_PAL);
	
	if(z!=0){
		sprites[z].blink = BLINK_COUNTER;
		PA_SetSpritePal(0,z,WHITE_PAL);
	}
	
	hero.updatebossdata = 1;
	NewSound(hitmonster_sound);
}

void Boss_Dies(){
	u16 a=0;
	u8 i=boss.sprite;
	u8 z=boss.part;
	
	UpdateStatusScreen();

	//unlock weapon :?
	if(boss.id==0){
		if(hero.numshoots[3]==0){
			hero.numshoots[3] = 1;
			hero.maxammo[3] = defaultAMMO + hero.incammo;
			hero.ammo[3] = defaultAMMO + hero.incammo;
		}
	}
	else if(boss.id==1){
		if(hero.numshoots[8]==0){
			hero.numshoots[8] = 1;
			hero.maxammo[8] = defaultAMMO + hero.incammo;
			hero.ammo[8] = defaultAMMO + hero.incammo;
		}
	}
	else if(boss.id==2){
		if(hero.numshoots[9]==0){
			hero.numshoots[9] = 1;
			hero.maxammo[9] = defaultAMMO + hero.incammo;
			hero.ammo[9] = defaultAMMO + hero.incammo;
		}
	}
	else if(boss.id==3){
		if(hero.numshoots[5]==0){
			hero.numshoots[5] = 1;
			hero.maxammo[5] = defaultAMMO + hero.incammo;
			hero.ammo[5] = defaultAMMO + hero.incammo;
		}
	}



	//rotationg
	u8 rot=sprites[i].rot;
	if(rot==0)rot=GetFreeRot();//por si esta usando el rot del mano...
	
	PA_SetSpriteRotEnable(0,i,rot);
	game.freerot[rot]=1;
	
	sprites[i].kill=1;
	sprites[i].killcnt=200;
	sprites[i].rot=rot;
	sprites[i].rotangle=0;
	sprites[i].zoom=256;
	PA_SetSpriteAnim(0, i, 0);
	sprites[i].animated = 0;
	
	if(z!=0)KillSprite(z);
	//---------------
	

	boss.die=2;
	NewSound(boss_die_sound);

	while(sprites[i].killcnt>0){
		if(sprites[i].rotangle<1000)sprites[i].rotangle+=10;
		else sprites[i].killcnt = 1;
		
		sprites[i].zoom += 20;
		PA_SetRotset(0,sprites[i].rot,sprites[i].rotangle,sprites[i].zoom, 256);
		sprites[i].killcnt--;
	
		CreateParticle(i,0);
		SpriteActions();
		UpdateXY();
		PA_WaitForVBL();
	}
	KillSprite(i);
	
	while(a<50){
		a++;
		SpriteActions();
		UpdateXY();
		PA_WaitForVBL();
	}
	
	LevelComplete();
	
	if(game.levelevent[LEVELDATA_TYPE]!=BOSS_NOEND_LEVEL){
		data.unlocked[level_unlocks_stage[game.level]]=1;
		game.die = 3;
		game.screen = GAME_MENU;
	}
	else{
		game.screen = GAME_PLAY;
		game.die = 2;
		game.teleport = game.level+1;
	}
	
	
	//IF FINAL BOSS LEVEL..
	if(boss.id==4){
		PA_StopMod();
		FadeIn(1);
		PA_PlayMod(music_end_mod);
		LevelClean();
		
		PA_InitCustomText(0,1,font);
		PA_EnableSpecialFx(0,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
		PA_SetSFXAlpha(0,16,16);
		
		PA_LoadTiledBg(1,3,menu_bg);
		
		PA_OutputText(0,0,12,"      The End       ");
		
		Wait(500);
		FadeOut(1);
		
		Wait_or_skip(5000);
		CleanText(1);
		SaveData();
		Wait_or_skip(200);
		LevelComplete();
		game.totaltime += game.timecounter/60;
		game.timecounter=0;
	}
	
	PA_StopMod();
}
