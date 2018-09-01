void LoadItem(u8 e, u8 i){	//e = event number ... i = free sprite num
	u16 a=e<<2; //i*4
	
	u8 enable_rotation=0;
	u8 rot;
	
	
	//mirar que no sea special item
	a+=8;
	sprites[i].id = game.levelevent[a + 3];
	if((!ItemisSpecial(sprites[i].id))||((ItemisSpecial(sprites[i].id))&&(data.specialitems[game.level]==0))){
		sprites[i].x = game.levelevent[a + 1]<<11;
		sprites[i].y = game.levelevent[a + 2]<<11;
		sprites[i].vy = 0;
	
		sprites[i].speed = 0;
		sprites[i].w1 = 0;
		sprites[i].w2 = 0;
		sprites[i].h1 = 4;
		sprites[i].h2 = 4;
		sprites[i].size = 16;
		sprites[i].pal = ITEMS_PAL;
		PA_CreateSprite(0,i, (void*)items_Sprite, OBJ_SIZE_16X16,1,ITEMS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
		totalsprites++;
		PA_SetSpriteAnim(0, i, sprites[i].id);
	
		switch(sprites[i].id){
			case 0:
				enable_rotation = 1;
				break;
			case 1:
				enable_rotation = 1;
				break;
			default:
				enable_rotation = 0;
				break;
		}
		
		sprites[i].free=8;
		
		if(enable_rotation){
			rot = GetFreeRot();
			PA_SetSpriteRotEnable(0,i,rot);
			game.freerot[rot]=1;
			sprites[i].rot=rot;
			sprites[i].rotangle=0;
		}
		
		PA_SetSpritePrio(0,i,SPRITES_PRIO);
		//load map dot
		u8 m=GetFreeMapDot();
		game.mapdot[m]=i;
		sprites[i].mapdot=m;
	}
}

u8 ItemisSpecial(u8 id){
	switch(id){
		case 2:
			return 1;
			break;
		default:
			return 0;
			break;
	}
}

void UseItem(u8 i){
	u8 cancel=0;
	switch(sprites[i].id){
		case 0: //heals 20 HP
				if(hero.hp<hero.maxhp){
					hero.hp += 50;
					if(hero.hp>hero.maxhp)hero.hp=hero.maxhp;
					NewTextLine(recoverhp,50);
					NewSound(item_sound);
				}
				else cancel = 1;
			break;
		case 1: //heals 10 ammo
				if(hero.maxammo[hero.weapon] == UNLIMITED_AMMO) cancel = 1;
				else if(hero.ammo[hero.weapon]<hero.maxammo[hero.weapon]){
					hero.ammo[hero.weapon] += 40;
					if(hero.ammo[hero.weapon]>hero.maxammo[hero.weapon])hero.ammo[hero.weapon]=hero.maxammo[hero.weapon];
					NewTextLine(recoverap,40);
					NewSound(item_sound);
				}
				else cancel = 1;
			break;
		case 2: //nº de disparos que tira + 1
				if((CanMultipleShot(hero.weapon)) && (hero.numshoots[hero.weapon]<3)){
					hero.numshoots[hero.weapon]++;
					NewTextLine(powerupwsx2,hero.weapon);
					NewSound(itemp_sound);
					
					//lock it pa k no lo puedan cojer otra vez
					data.specialitems[game.level] = 1;
				}
				else cancel = 1;
			break;	
	}
	if(!cancel){
		SetRaise(0,25);//sprite nº, counter
		CreateHumo((hero.x>>8) + HERO_SIZE - HERO_W2,(hero.y>>8) + 16, 0);
		CreateHumo((hero.x>>8) + HERO_W1 - 16,(hero.y>>8) + 16, 1);		
		hero.invisiblecounter = 5;
		KillSprite(i);
	}
	hero.status_changed = 1;
}
