void KillMonsterEffect(u8 a){
	if(sprites[a].rotangle<1000)sprites[a].rotangle+=30;
	else sprites[a].killcnt = 1;
	sprites[a].zoom += 20;
	
	PA_SetRotset(0, //screen
				sprites[a].rot, // rotset
				sprites[a].rotangle, // Angle...
				sprites[a].zoom, 256);//zoom X,Y
	
	sprites[a].killcnt--;
}

void FadeIn(u8 speed){ //1=default
	s16 a=0;
	
	while((a>>2)>-32){
		PA_SetBrightness(0,a>>2);
		PA_SetBrightness(1,a>>2);
		a-=speed;
		UpdateSoundVars();
		PA_WaitForVBL();
	}
}

void FadeInScreen(u8 speed, u8 screen){ //1=default
	s8 a=0;
	
	while((a>>2)>-32){
		PA_SetBrightness(screen,a>>2);
		a-=speed;
		UpdateSoundVars();
		PA_WaitForVBL();
	}
}

void FadeOut(u8 speed){ //1= default
	s8 a=-32;
	
	while((a>>2)<0){
		PA_SetBrightness(0,a>>2);
		PA_SetBrightness(1,a>>2);
		a+=speed;
		UpdateSoundVars();
		PA_WaitForVBL();
	}
}

void FadeOutScreen(u8 speed, u8 screen){ //1= default
	s8 a=-32;
	
	while((a>>2)<0){
		PA_SetBrightness(screen,a>>2);
		a+=speed;
		//UpdateSoundVars();
		PA_WaitForVBL();
	}
}

void HideButtonEffect(u8 screen, u8 i, u16 x, u16 y){
	u16 c;
	PA_SetSpriteAnim(screen,i,1);
	Wait(3);
	PA_SetSpriteAnim(screen,i,0);
	Wait(2);
	PA_SetSpriteAnim(screen,i,1);
	Wait(1);
	PA_SetSpriteAnim(screen,i,0);
	for(c = 0; y < 200 ;y += c>>5){
		c+=10;
		PA_SetSpriteXY(screen,i,x,y);
		PA_WaitForVBL();
	}
}

void HideButtonEffect2(u8 screen, u8 i, u16 x, u16 y){
	u16 c;
	PA_SetSpriteAnim(screen,i,1);
	Wait(3);
	PA_SetSpriteAnim(screen,i,0);
	Wait(2);
	PA_SetSpriteAnim(screen,i,1);
	Wait(1);
	PA_SetSpriteAnim(screen,i,0);
	for(c = 0; x < 256 ;x += c>>5){
		c+=10;
		PA_SetSpriteXY(screen,i,x,y);
		PA_WaitForVBL();
	}
}


//-------------------------------
//-------------------------------
//---------------------------ITEM
//-------------------------------
//-------------------------------
void ItemEffect(u8 i){
	if(sprites[i].rot!=0){
		sprites[i].rotangle+=5;
		if(sprites[i].rotangle==361)sprites[i].rotangle=360;
		PA_SetRotsetNoZoom(0, sprites[i].rot,sprites[i].rotangle); //screen, rot nº, angle
	}
}

//-------------------------------
//-------------------------------
//-------------------------RAISE-
//-------------------------------
//-------------------------------
void SetRaise(u8 i, u8 counter){
	sprites[i].raise = counter;
}

void CreateRaiseParticle(u16 x, u16 y){
	u8 a = GetFreeSprite();
	if(a!=0){
		totalsprites++;
		s8 ran = PA_RandMinMax(-10,10);
		s8 ran2 = PA_RandMinMax(-10,5);
		sprites[a].x = (x + 16 + ran)<<8;
		sprites[a].y = (y + 16 + ran2)<<8;
		sprites[a].size = 8;
		
		if(OutScreen(a)==1)KillSprite(a);
		else{	
			sprites[a].free=9;
			sprites[a].killcnt=13;
			PA_CreateSpriteFromGfx(0, a, gfx.raiseparticle,OBJ_SIZE_8X8,1,BLINK_PAL,(sprites[a].x-hero.scrollx)>>8,sprites[a].y>>8);
			PA_SetSpritePrio(0,a,SPRITES_PRIO);
		}
	}
}

//-------------------------------
//-------------------------------
//------------------BALL RAISING-
//-------------------------------
//-------------------------------
void CreateBallRaiseParticle(u16 x, u16 y){
	u8 i = GetFreeSprite();
	
	if(i!=0){
		totalsprites++;
		s8 ran = PA_RandMinMax(-10,10);
		s8 ran2 = PA_RandMinMax(-16,16);
		sprites[i].x = (x + 16 + ran - 6)<<8;
		sprites[i].y = (y + 16 + ran2 - 4)<<8;
		
		sprites[i].size = 8;
		sprites[i].flip = PA_RandMinMax(0,1);
		sprites[i].vy = PA_RandMinMax(20,60);	//no es vy, se usa aqui para la extension del efecto...
		
		if(OutScreen(i)==1)KillSprite(i);
		else{	
			sprites[i].free=14;
			sprites[i].killcnt=70;
			PA_CreateSpriteFromGfx(0, i, gfx.ballraiseparticle[0],OBJ_SIZE_8X8,1,EFFECTS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpritePrio(0,i,game.ballraiseprio);
		}
	}
}


//-------------------------------
//-------------------------------
//------------------EXPLOSION 1-
//-------------------------------
//-------------------------------
void CreateExplosion1(u16 x, u16 y){
	u8 i = GetFreeSprite();
	
	if(i!=0){
		totalsprites++;
		sprites[i].x = x<<8;
		sprites[i].y = y<<8;
		
		sprites[i].vx = PA_RandMinMax(-256,256);
		sprites[i].vy = PA_RandMinMax(-256,256);
		
		sprites[i].size = 16;		
		if(OutScreen(i)==1)KillSprite(i);
		else{	
			sprites[i].free=18;
			PA_CreateSprite(0, i,(void*)effect_explosion1_Sprite, OBJ_SIZE_16X16,1,EFFECTS_PAL,x<<8, y<<8);
			PA_StartSpriteAnimEx(0, i, 0, 6, 15, ANIM_ONESHOT);
		}
	}
}

//-------------------------------
//-------------------------------
//---------------------PARTICULAS
//-------------------------------
//-------------------------------
void CreateParticle(u8 i,u8 type){ // m = sprite nº ... type: 	0=default (random vx and vy)
									//							1=realistic (si hay paret a la izq que vayan para
									//										 la derecha, si hay en la derecha que
									//										 vayan hacia la izq, etc..
	u8 a = GetFreeSprite();
	if(a!=0){
		totalsprites++;
		u8 colour = PA_RandMinMax(0,TOTALPARTICLES-1-6);
		sprites[a].x = sprites[i].x+(sprites[i].size<<7);
		sprites[a].y = sprites[i].y+(sprites[i].size<<7);
		sprites[a].size = 8;
		
		if(OutScreen(a)==1)KillSprite(a);
		else{
			sprites[a].free=6;
			
			
			//particle mov type
			if(type==0){
				sprites[a].vx = (PA_RandMinMax(-10,10))<<6;
				sprites[a].vy = (-PA_RandMinMax(50,150))<<3;
			}
			else if(type==1){
				s8 x1=0,x2=0,xc=0;
				
				if(sprites[i].vx>0){
					x1=-10;
					x2=-2;
				}
				else {
					x1=2;
					x2=10;
				}
				
				//si es colision vertical k lo arregle
				if((VCola2(i,sprites[i].vy))&&(!HCola(i,sprites[i].vx))){
					xc=x1;
					x1=-x2;
					x2=-xc;
				}
				
				sprites[a].vx = (PA_RandMinMax(x1,x2))<<6;
				sprites[a].vy = (-PA_RandMinMax(50,150))<<3;
			}
			//----------------
			
			PA_CreateSpriteFromGfx(0, a, gfx.particle[colour],OBJ_SIZE_8X8,1,EFFECTS_PAL,(sprites[a].x-hero.scrollx)>>8,sprites[a].y>>8);
			PA_SetSpriteAnim(0, a, colour);
			PA_SetSpritePrio(0,a,1);
		}
	}
}
//-------------------------------
//-------------------------------
//---------------------HUMO------
//-------------------------------
//-------------------------------
void CreateHumo(u16 x, u16 y, u8 face){
	u8 a = GetFreeSprite();
	if(a!=0){
		totalsprites++;
		sprites[a].free=7;
		sprites[a].x = x<<8;
		sprites[a].y = y<<8;
		PA_CreateSprite(0, a,(void*)effect_humo_Sprite, OBJ_SIZE_16X16,1,HUMO_PAL,x<<8, y<<8);
		PA_SetSpriteHflip(0, a, face);
		PA_StartSpriteAnimEx(0, a, 0, 7, 15, ANIM_ONESHOT);
		PA_SetSpritePrio(0,a,SPRITES_PRIO);
	}
}

//-------------------------------
//-------------------------------
//---------------------BLINK------
//-------------------------------
//-------------------------------

void CheckBlink(u8 i){
	sprites[i].blink--;
	if(sprites[i].blink == 0){
		sprites[i].blink = 0;
		PA_SetSpritePal(0,i,sprites[i].pal);
	}
}
//-------------------------------
//-------------------------------
//---------------------OTROS
//-------------------------------
//-------------------------------
u8 GetSpriteFreeType(u8 a){
	u8 i=0;
	for(i=0;i<maxsprites;i++){
		if(sprites[i].free==a)return i;
	}
	return 0;
}
