void CheckEvents(){
	u8 i=0;
	u16 a=8;
	s32 b;
	for(i=0;i<game.totalevents;i++){
		if(events[i].shown==0){
			b = game.levelevent[a + 1] - (hero.x>>11);
			if((b==32)||(b==-32))OpenEvent(i);
		}
		a+=4;
	}
}

void OpenEvent(u8 i){	//i = nº ofevent
	u16 a=i<<2; // a = i*4
	u8 s = GetFreeSprite();
	a+=8;
	switch(game.levelevent[a]){	//checking event type
		case 0:	// NONE
			events[i].shown=1;
			sprites[s].event = i+1;
			sprites[s].free = 10;
			break;
		case 1: // HERO START
			events[i].shown=1;
			sprites[s].event = i+1;
			break;
		case 2: // DOOR
			events[i].shown=1;
			sprites[s].event = i+1;
			sprites[s].free = 10;
			break;
		case 3: // MONSTER
			events[i].shown=1;
			sprites[s].event = i+1;
			LoadMonster(i,s);
			break;
		case 4: // ITEM
			events[i].shown=1;
			sprites[s].event = i+1;
			LoadItem(i,s);
			break;
		case 5: // OTHER
			events[i].shown=1;
			sprites[s].event = i+1;
			LoadOther(i,s);
			break;
	}
}

void DisplayOff(i){
	events[sprites[i].event].shown = 0;
	KillSprite(i);
}

void LoadOther(u8 s, u8 i){
	u16 a=s<<2;
	
	a+=8;
	
	sprites[i].x = game.levelevent[a + 1]<<11;
	sprites[i].y = game.levelevent[a + 2]<<11;
	sprites[i].vy = 0;
	sprites[i].id = game.levelevent[a + 3];
	
	sprites[i].free=19;

	switch(sprites[i].id){
		case 0://instant death
			sprites[i].w1 = 0;
			sprites[i].w2 = 0;
			sprites[i].h1 = 0;
			sprites[i].h2 = 0;
			sprites[i].size = 8;
			sprites[i].pal = ITEMS_PAL;
			sprites[i].y+=8<<8;
			PA_CreateSprite(0,i, (void*)blank_Sprite, OBJ_SIZE_8X8,1,ITEMS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			break;
			
		case 1://Arrow Right
			sprites[i].w1 = 0;
			sprites[i].w2 = 0;
			sprites[i].h1 = 0;
			sprites[i].h2 = 0;
			
			sprites[i].size = 32;
			sprites[i].pal = OTHERS_PAL;
			
			sprites[i].y -= 16<<8;
			
			PA_CreateSprite(0,i, (void*)other_1_Sprite, OBJ_SIZE_32X32,1,OTHERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpritePrio(0,i,SPRITES_PRIO);
			break;
			
		case 2://Arrow Down 1
			sprites[i].w1 = 0;
			sprites[i].w2 = 0;
			sprites[i].h1 = 0;
			sprites[i].h2 = 0;
			sprites[i].size = 32;
			sprites[i].pal = OTHERS_PAL;
			
			sprites[i].x -= 16<<8;
			
			PA_CreateSprite(0,i, (void*)other_2_Sprite, OBJ_SIZE_32X32,1,OTHERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpritePrio(0,i,SPRITES_PRIO);
			break;
		case 3://Arrow Down 2
			sprites[i].w1 = 0;
			sprites[i].w2 = 0;
			sprites[i].h1 = 0;
			sprites[i].h2 = 0;
			
			sprites[i].size = 32;
			sprites[i].pal = OTHERS_PAL;
			
			sprites[i].x -= 16<<8;
			
			PA_CreateSprite(0,i, (void*)other_3_Sprite, OBJ_SIZE_32X32,1,OTHERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpritePrio(0,i,SPRITES_PRIO);
			break;
		case 4://Boss Door(se cierra cuando pasas por delante)
			sprites[i].free = 21;
			sprites[i].w1 = 24;
			sprites[i].w2 = 24;
			sprites[i].h1 = 0;
			sprites[i].h2 = 24;
			
			sprites[i].size = 64;
			sprites[i].pal = OTHERS_PAL;
			
			sprites[i].x -= 5<<8;
			sprites[i].y += 16<<8;// (ponerlo escondido)
			
			//usar otra variable para saber donde ha de ir la y cuando se cierre
			sprites[i].vy = sprites[i].y - (40<<8);
			
			PA_CreateSprite(0,i, (void*)other_4_Sprite, OBJ_SIZE_32X64,1,OTHERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpritePrio(0,i,SPRITES_PRIO);
			break;
		default:
			break;
	}
}
