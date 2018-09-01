void UpdateStats(){	
	//para que no se quede blanco el hero
	if(hero.invisiblecounter == 0)if(PA_GetSpritePal(0,0)==WHITE_PAL)PA_SetSpritePal(0,0,sprites[0].pal);
	
	if(hero.status_changed){
		u16 i=0;
		u16 a=0;
		int tile[26]={1,2,3,4,5,6,7,8,9,10,11,12,  13,14,15,16,17,18,19,20,21,22,23,24,25,26};//tiles map ID
		u8 hpbartiles=9;
		u8 ambartiles=9;
		
		hero.status_changed = 0;
		
		//clean old
		for(i=0;i<128;i++){
			PA_SetMapTile(0,0,i,1,0);
		}
		
		//Updating HP Bar------------------------------------------
		a=hero.hp;
		PA_SetMapTile(0,0,hpbar_x-1,hpbar_y,tile[0]);
		for(i=0;i<((hero.maxhp)>>3)+1;i++){
			if(a>hpbartiles){
				PA_SetMapTile(0,0,hpbar_x+i,hpbar_y,tile[1]);
				a-=hpbartiles-1;
				}
			else if((a>0)&&(a<=hpbartiles)){
				PA_SetMapTile(0,0,hpbar_x+i,hpbar_y,tile[1+(hpbartiles-a)]);
				a=0;
			}
			else if(a==0)PA_SetMapTile(0,0,hpbar_x+i,hpbar_y,tile[10]);
		}
		PA_SetMapTile(0,0,hpbar_x+i-1,hpbar_y,tile[11]);
		
		//-----------------------------------------------------------
		//Updating AMMO Bar------------------------------------------
		PA_SetMapTile(0,0,ambar_x-2,ambar_y,tile[12 + 0]);
		PA_SetMapTile(0,0,ambar_x-1,ambar_y,tile[12 + 1]);
		//if ammo is unlimited..	
		if(hero.maxammo[hero.weapon] == UNLIMITED_AMMO){
			PA_SetMapTile(0,0,ambar_x,ambar_y,tile[12+1+1]);
			PA_SetMapTile(0,0,ambar_x+1,ambar_y,26);
			PA_SetMapTile(0,0,ambar_x+2,ambar_y,tile[12+1+1]);
			PA_SetMapTile(0,0,ambar_x+3,ambar_y,tile[12+1+11]);
		}
		else {//set normal
			a = hero.ammo[hero.weapon]>>1;
	
			for(i=0;i<((hero.maxammo[hero.weapon]>>1)>>3)+1;i++){
				if(a>ambartiles){
					PA_SetMapTile(0,0,ambar_x+i,ambar_y,tile[12+1 + 1]);
					a-=ambartiles-1;
					}
				else if((a>0)&&(a<=ambartiles)){
					PA_SetMapTile(0,0,ambar_x+i,ambar_y,tile[12+1 + 1+(ambartiles-a)]);
					a=0;
				}
				else if(a==0)PA_SetMapTile(0,0,ambar_x+i,ambar_y,tile[12+1 + 10]);
			}
			PA_SetMapTile(0,0,ambar_x+i-1,ambar_y,tile[12+1 + 11]);
		}
		//-----------------------------------------------------------
		
		//updating weapon status
		PA_SetSpriteAnim(0,status_weapon_exp_slot,hero.numshoots[hero.weapon]);
		//PA_SetSpritePrio(0,i,1);
	}
}

void UpdateXY(){
	u8 i=0;
	sprites[0].x = hero.x;
	sprites[0].y = hero.y;
	for(i=0;i<maxsprites;i++){
		if((sprites[i].free != 0)&&(sprites[i].free != 10)){
			//actualizar angulos
			//if(sprites[i].flip==1){if((sprites[i].shootangle < 90)||(sprites[i].shootangle > 270))sprites[i].shootangle=180;}
			//else if(sprites[i].flip==0){if((sprites[i].shootangle > 90)&&(sprites[i].shootangle < 270))sprites[i].shootangle=0;}
			//mirar si queda fuera de la imagen, si no queda fuera que lo ponga
			
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
	}
}

void UpdateScroll(){
	if((!boss.loaded)&&(boss.id!=4)){
		if((boss.enabled)&&(hero.scrollx>=(665<<8))&&(boss.id!=4)){//si es una pantalla de BOSS y llega a su zona..
			PauseAnim();
			LoadBoss();								//..load boss
			UnPauseAnim();
		}
		else {
			hero.scrollx = hero.x-((128-8)<<8);
			if(hero.scrollx < 0)hero.scrollx=0;
			if(hero.scrollx > (768<<8))hero.scrollx=(768<<8);
			
			PA_ParallaxScrollX(0, hero.scrollx>>8);
		}
	}
	else if((boss.id==4)&&(boss.loaded)){
		hero.scrollx = hero.x-((128-8)<<8);
		if(hero.scrollx < 0)hero.scrollx=0;
		if(hero.scrollx > (768<<8))hero.scrollx=(768<<8);
		PA_ParallaxScrollX(0, hero.scrollx>>8);
	}
}
void UpdateMapDots(){
//mapdot..
//0: none
//1: hero
//2: monsutah
//3: item
	u8 i;
	u8 color=0;
	u16 x;
	u8 y;
	for(i=0;i<50;i++){
		if(game.mapdot[i]>=0){
			switch(sprites[game.mapdot[i]].free){
				case 1:
					color=0;//blue
					break;
				case 3:
					color=1;//red
					break;
				case 8:
					color=2;//white
					break;
				case 16:
					color=3;//white
					break;
				default:
					color=4;//nahh
					break;
			}
			
			x = MAP_X + (sprites[game.mapdot[i]].x>>11);
			y = MAP_Y + (sprites[game.mapdot[i]].y>>11) - (sprites[game.mapdot[i]].size>>4);
			if(color==4)PA_SetSpriteXY(1,MAPDOTF+i,256,0);
			else PA_CreateSpriteFromGfx(1,MAPDOTF+i,gfx.mapdot[color],OBJ_SIZE_8X8,1,3,x,y);
			//PA_CreateSprite(1,2, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
		}
		else{
			PA_SetSpriteXY(1,MAPDOTF+i,256,0);
		}
	}
}
u8 GetFreeMapDot(){
	u8 i;
	for(i=1;i<50;i++){//i=1 pa saltarse el hero O.O
		if(game.mapdot[i]==-1)return i;
	}
	return 49;
}
