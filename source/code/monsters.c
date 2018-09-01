void MonsterActions(u8 i){
	//doing the action
	switch(sprites[i].id){
	//red monster
		case 0:	
			sprites[i].counter++;
			if(sprites[i].counter>200){
				PA_SetSpriteAnim(0,i,5);
				sprites[i].animated = 0;
				if(sprites[i].counter == 210)NewShot(sprites[i].weapon,i);
				else if(sprites[i].counter == 220)NewShot(sprites[i].weapon,i);
				else if(sprites[i].counter == 230)NewShot(sprites[i].weapon,i);
				else if(sprites[i].counter > 250){
					sprites[i].counter = 0;
					PA_StartSpriteAnim(0, i, 1, 4, 6);
					sprites[i].animated = 1;
				}
			}
			else MoveMonster(i);
			break;
	//bee
		case 1:
			MoveFlyingMonster(i);
			sprites[i].counter++;
			if(sprites[i].counter==400){
				NewShot(sprites[i].weapon,i);
				sprites[i].counter = 0;
			}
			break;
	//green flying imp
		case 2:
			MoveFlyingMonster(i);
			sprites[i].counter++;
			if(sprites[i].counter==100){
				NewShot(sprites[i].weapon,i);
				sprites[i].counter = 0;
			}
			break;	
	//green imp
		case 3:
			MoveMonster(i);
			sprites[i].counter++;
			if(sprites[i].counter==100){
				NewShot(sprites[i].weapon,i);
				sprites[i].counter = 0;
			}
			break;
	//roteye
		case 4:
			MoveMonster(i);
			sprites[i].counter++;
			if(sprites[i].counter==200){
				NewShot(sprites[i].weapon,i);
				sprites[i].counter = 0;
			}
			break;
	//bluemon
		case 5:
			MoveMonster(i);
			sprites[i].counter++;
			if(sprites[i].counter==100){
				MultipleShot(sprites[i].weapon,i,3);
				sprites[i].counter = 0;
			}
			break;
	//shoot launcher
		case 6:
			AimShotLauncher(i);
			sprites[i].counter++;
			if(sprites[i].counter>=100){
				if(sprites[i].counter == 100)NewShot(sprites[i].weapon,i);
				else if(sprites[i].counter == 110)NewShot(sprites[i].weapon,i);
				else if(sprites[i].counter == 120)NewShot(sprites[i].weapon,i);
				else if(sprites[i].counter == 130)NewShot(sprites[i].weapon,i);
				else if(sprites[i].counter == 140)NewShot(sprites[i].weapon,i);
				else if(sprites[i].counter > 150)sprites[i].counter = 0;
			}
			break;
	//mouzze
		case 7:
			if(sprites[i].counter==1)MoveMonster(i);
			else{
				if(((sprites[i].x - sprites[0].x)>>11 < 11)
					&&((sprites[i].x - sprites[0].x)>>11 > -11))sprites[i].counter++;
			}
			break;
	//greball
		case 8:
			MoveMonster(i);
			if(sprites[i].counter==30){
				sprites[i].vy-=800;
				sprites[i].counter++;
				sprites[i].y+=sprites[i].vy;
				sprites[i].speed = monsterdata[MONSTERDATA_SPEED + 8 + 8 * MONSTERDATA_TOTAL];
			}
			else if(sprites[i].counter==31){
				if(VCola(i)){
					sprites[i].counter = 0;
					sprites[i].speed = 0;
					if(sprites[i].flip==1)sprites[i].flip=0;
					else sprites[i].flip=1;
				}
			}
			else{
				sprites[i].counter++;
				sprites[i].speed = 0;
			}
			break;
	//end of switch
	}
}

u8 MonsterColCheck_Wall(u8 i){
	s8 a=0;
	if(sprites[i].flip==1)a = -1;
	else a = 1;
	
	if(HCola(i, a*sprites[i].speed))return 1;
	else return 0;
}

u8 MonsterColCheck_Floor(u8 i){
	u8 a = 0;
	if(sprites[i].flip==0){
		sprites[i].x += (sprites[i].size - sprites[i].w2 - sprites[i].w1)<<8;
		if(VCola(i)==0)a = 1;
		sprites[i].x -= (sprites[i].size - sprites[i].w2 - sprites[i].w1)<<8;	
	}
	else{
		sprites[i].x -= sprites[i].w1<<8;
		if(VCola(i)==0)a = 1;
		sprites[i].x += sprites[i].w1<<8;
	}
	
	return a;
}

void MoveMonster(u8 i){
	s8 a=0;
	u8 b=0;
	u8 jump=0;
	if(sprites[i].flip==1)a = -1;
	else a = 1;
	
	
	//gravity
		sprites[i].vy += GRAVITY;
		if(sprites[i].vy>MAX_VY)sprites[i].vy=MAX_VY;
	//--------------
	//V COLLISION
		if(VCola(i)){
			sprites[i].vy = 0;
			sprites[i].y-=1<<8;
			if(VCola(i)){
				while(b==0){
					if(VCola(i)==1)sprites[i].y-=1<<8;
					else b=1;
				}
			}
			sprites[i].y+=1<<8;
		}
		else sprites[i].y += sprites[i].vy;
	//--------------
	
	
	
	if(sprites[i].flip==1)sprites[i].shootangle = 180;
	else sprites[i].shootangle = 0;
	
	sprites[i].x += a*8;
	//collision---------------------
		switch(sprites[i].collision){
			case 0://no
				break;
			case 1://flip (WALL)
				if(MonsterColCheck_Wall(i))sprites[i].flip = -sprites[i].flip+1;
				else sprites[i].x += a*sprites[i].speed;
				
				break;
			case 2://flip (WALL + FLOOR)
				if(MonsterColCheck_Wall(i))sprites[i].flip = -sprites[i].flip+1;
				else sprites[i].x += a*sprites[i].speed;
				
				if(MonsterColCheck_Floor(i))sprites[i].flip = -sprites[i].flip+1;
				
				break;
			case 3://Jump (FLOOR), flip (HIGH WALLS)
				if(MonsterColCheck_Wall(i)){
					if(sprites[i].vy==0)sprites[i].flip = -sprites[i].flip+1;
				}
				else {
					//mirando si tiene algo delante
					sprites[i].x+=a*(sprites[i].speed<<2);
					if(MonsterColCheck_Wall(i)){
						sprites[i].y-=32<<8;
						if(!MonsterColCheck_Wall(i))jump=1;
						sprites[i].y+=32<<8;						
						
					}
					sprites[i].x-=a*(sprites[i].speed<<2);
					
					sprites[i].x += a*sprites[i].speed;
				}
				
				sprites[i].x+=a*sprites[i].size<<8;
				if(MonsterColCheck_Floor(i))jump = 0;
				sprites[i].x-=a*sprites[i].size<<8;
				
				if((jump==1)&&(sprites[i].vy==0)){
					sprites[i].vy -= 1000;
					sprites[i].y += sprites[i].vy;		
				}
				
				break;
		}
	//-----------------------------
	
	sprites[i].x -= a*8;

	PA_SetSpriteHflip(0, i, sprites[i].flip);
}

void MoveFlyingMonster(u8 i){
	u16 speed=sprites[i].speed;
	if(speed<512)speed=512;
	if(sprites[i].flip==1)
	{
		sprites[i].shootangle = 180;
		sprites[i].x+=8;
		if(!HCola(i,-sprites[i].speed)) sprites[i].x-=sprites[i].speed;
		else sprites[i].flip=0;
		PA_SetSpriteHflip(0, i, 1);
		sprites[i].x-=8;
	}
	else if(sprites[i].flip==0)
	{
		sprites[i].shootangle = 0;
		sprites[i].x-=8;
		if(!HCola(i,sprites[i].speed)) sprites[i].x+=sprites[i].speed;
		else sprites[i].flip=1;
		PA_SetSpriteHflip(0, i, 0);
		sprites[i].x+=8;
	}
	
	if(sprites[i].vy > 170)sprites[i].vy = -190;
	sprites[i].vy += 10;
	sprites[i].y += sprites[i].vy;
	
}

void LoadMonster(u8 e, u8 i){	//e = event number ... i = free sprite num
	u16 a=e<<2; //i*4
	u8 z=0;
	a+=8;
	sprites[i].x = (game.levelevent[a + 1]<<11);
	sprites[i].y = (game.levelevent[a + 2]<<11) + (16<<8);
	sprites[i].vy = 0;
	sprites[i].flip = 1;
	sprites[i].pal = MONSTERS_PAL;
	sprites[i].free=3; //save sprite num "freesprite" is used by a monster :)

	totalsprites++;
	//check monster type
	sprites[i].id = game.levelevent[a + 3];
	switch(sprites[i].id){
		case 0://red monster
			sprites[i].shoot_x = 24;
			sprites[i].shoot_y = 17;
			sprites[i].collision = 2;
			sprites[i].exp = 20;
			
			PA_CreateSprite(0,i, (void*)monster_0_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 1, 4, 6);
			sprites[i].animated = 1;
			break;
		case 1://bee			
			sprites[i].shoot_x = 24;
			sprites[i].shoot_y = 16;
			sprites[i].collision = 3;
			sprites[i].exp = 15;
			
			PA_CreateSprite(0,i, (void*)monster_1_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 0, 3, 20);
			sprites[i].animated = 1;
			break;
		case 2://green flying imp			
			sprites[i].shoot_x = 22;
			sprites[i].shoot_y = 18;
			sprites[i].collision = 1;
			sprites[i].exp = 150;
			
			PA_CreateSprite(0,i, (void*)monster_2_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 0, 3, 14);
			sprites[i].animated = 1;
			break;
		case 3://green imp			
			sprites[i].shoot_x = 22;
			sprites[i].shoot_y = 18;
			sprites[i].collision = 3;
			sprites[i].exp = 80;
			
			PA_CreateSprite(0,i, (void*)monster_3_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 1, 3, 8);
			sprites[i].animated = 1;
			break;
		case 4://Roteye			
			sprites[i].shoot_x = 50;
			sprites[i].shoot_y = 32;
			sprites[i].collision = 2;
			sprites[i].exp = 500;
			
			PA_CreateSprite(0,i, (void*)monster_4_Sprite, OBJ_SIZE_64X64,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 0, 4, 7);
			sprites[i].animated = 1;
			break;
		case 5://BlueMon
			sprites[i].shoot_x = 20;
			sprites[i].shoot_y = 8;
			sprites[i].collision = 2;
			sprites[i].exp = 100;
			
			PA_CreateSprite(0,i, (void*)monster_5_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 0, 3, 20);
			sprites[i].animated = 1;
			break;
		case 6://Shot Launcher
			sprites[i].shoot_x = 16;
			sprites[i].shoot_y = 16;
			sprites[i].collision = 1;
			sprites[i].exp = 70;
			
			PA_CreateSprite(0,i, (void*)monster_6_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpriteAnim(0,i,0);
			
			//poniendo el otro sprite para k pueda girar
				z=GetFreeSprite();
				sprites[i].group = z;
				sprites[z].size = 32;
				sprites[z].free = 13;
				sprites[z].pal = MONSTERS_PAL;
				
				sprites[z].x-=4<<8;
				sprites[z].y-=4<<8;
				
				PA_CreateSprite(0,z,(void*)monster_6_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim(0,z,1);
				//set rotation
				u8 rot=GetFreeRot();
				PA_SetSpriteRotEnable(0,z,rot);
				game.freerot[rot]=1;
				sprites[z].rot=rot;
				sprites[z].rotangle=0;
				sprites[z].zoom = 256;
			//----------
			
			break;
		case 7://Greball
			//sprites[i].shoot_x = 0;
			//sprites[i].shoot_y = 0;
			sprites[i].collision = 1;
			sprites[i].exp = 40;
			
			PA_CreateSprite(0,i, (void*)monster_7_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpriteHflip(0, i, 1);
			//PA_StartSpriteAnim(0, i, 0, 3, 20);
			//sprites[i].animated = 1;
			break;
		case 8://Greball
			//sprites[i].shoot_x = 0;
			//sprites[i].shoot_y = 0;
			sprites[i].collision = 1;
			sprites[i].exp = 50;
			PA_CreateSprite(0,i, (void*)monster_8_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpriteHflip(0, i, 1);
			//PA_StartSpriteAnim(0, i, 0, 3, 20);
			//sprites[i].animated = 1;
			break;
	}
	a = 8 + sprites[i].id * MONSTERDATA_TOTAL;
	
	sprites[i].counter = 0;
	sprites[i].hp = monsterdata[MONSTERDATA_HP + a];
	sprites[i].speed = monsterdata[MONSTERDATA_SPEED + a];
	sprites[i].weapon = monsterdata[MONSTERDATA_WEAPON + a];
	sprites[i].particles_when_die = monsterdata[MONSTERDATA_PARTICLES + a];
	
	sprites[i].w1 = monsterdata[MONSTERDATA_W1 + a];
	sprites[i].w2 = monsterdata[MONSTERDATA_W2 + a];
	sprites[i].h1 = monsterdata[MONSTERDATA_H1 + a];
	sprites[i].h2 = monsterdata[MONSTERDATA_H2 + a];
	
	if(monsterdata[MONSTERDATA_SIZE + a]==0)sprites[i].size = 16;
	else if(monsterdata[MONSTERDATA_SIZE + a]==1)sprites[i].size = 32;
	else if(monsterdata[MONSTERDATA_SIZE + a]==2)sprites[i].size = 64;
	
	sprites[i].x = sprites[i].x - (sprites[i].w1<<8);
	sprites[i].y -= ((sprites[i].size - sprites[i].h2)<<8);
	if(z!=0){
		sprites[z].x += sprites[i].x;
		sprites[z].y += sprites[i].y;
	}
	
	PA_SetSpritePrio(0,i,SPRITES_PRIO);
	
	VCola(i);//pa lo del aqqua
	if(z!=0)VCola(z);
	
	//load map dot
	u8 m=GetFreeMapDot();
	game.mapdot[m]=i;
	sprites[i].mapdot=m;
}

void SummonMonster(u16 x, u16 y, u8 id){
	u8 i = GetFreeSprite();
	u8 z=0;
	sprites[i].x = x<<8;
	sprites[i].y = (y<<8) + (16<<8);
	sprites[i].vy = 0;
	sprites[i].flip = sprites[boss.sprite].flip;
	sprites[i].pal = MONSTERS_PAL;
	sprites[i].free=3; //save sprite num "freesprite" is used by a monster :)
	
	totalsprites++;

	//check monster type
	sprites[i].id = id;
	switch(sprites[i].id){
		case 0://red monster
			sprites[i].shoot_x = 24;
			sprites[i].shoot_y = 17;
			sprites[i].collision = 2;
			sprites[i].exp = 20;
			
			PA_CreateSprite(0,i, (void*)monster_0_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 1, 4, 6);
			sprites[i].animated = 1;
			break;
		case 1://bee			
			sprites[i].shoot_x = 24;
			sprites[i].shoot_y = 16;
			sprites[i].collision = 3;
			sprites[i].exp = 15;
			
			PA_CreateSprite(0,i, (void*)monster_1_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 0, 3, 20);
			sprites[i].animated = 1;
			break;
		case 2://green flying imp			
			sprites[i].shoot_x = 22;
			sprites[i].shoot_y = 18;
			sprites[i].collision = 1;
			sprites[i].exp = 150;
			
			sprites[i].y-=64<<8;
			
			PA_CreateSprite(0,i, (void*)monster_2_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 0, 3, 14);
			sprites[i].animated = 1;
			break;
		case 3://green imp			
			sprites[i].shoot_x = 22;
			sprites[i].shoot_y = 18;
			sprites[i].collision = 3;
			sprites[i].exp = 80;
			
			PA_CreateSprite(0,i, (void*)monster_3_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 1, 3, 8);
			sprites[i].animated = 1;
			break;
		case 4://Roteye			
			sprites[i].shoot_x = 50;
			sprites[i].shoot_y = 32;
			sprites[i].collision = 2;
			sprites[i].exp = 500;
			
			PA_CreateSprite(0,i, (void*)monster_4_Sprite, OBJ_SIZE_64X64,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 0, 4, 7);
			sprites[i].animated = 1;
			break;
		case 5://BlueMon
			sprites[i].shoot_x = 20;
			sprites[i].shoot_y = 8;
			sprites[i].collision = 2;
			sprites[i].exp = 100;
			
			PA_CreateSprite(0,i, (void*)monster_5_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_StartSpriteAnim(0, i, 0, 3, 20);
			sprites[i].animated = 1;
			break;
		case 6://Shot Launcher
			sprites[i].shoot_x = 16;
			sprites[i].shoot_y = 16;
			sprites[i].collision = 1;
			sprites[i].exp = 70;
			
			PA_CreateSprite(0,i, (void*)monster_6_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpriteAnim(0,i,0);
			
			//poniendo el otro sprite para k pueda girar
				z=GetFreeSprite();
				sprites[i].group = z;
				sprites[z].size = 32;
				sprites[z].free = 13;
				sprites[z].pal = MONSTERS_PAL;
				
				sprites[z].x-=4<<8;
				sprites[z].y-=4<<8;
				
				PA_CreateSprite(0,z,(void*)monster_6_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim(0,z,1);
				//set rotation
				u8 rot=GetFreeRot();
				PA_SetSpriteRotEnable(0,z,rot);
				game.freerot[rot]=1;
				sprites[z].rot=rot;
				sprites[z].rotangle=0;
				sprites[z].zoom = 256;
			//----------
			
			break;
		case 7://Greball
			//sprites[i].shoot_x = 0;
			//sprites[i].shoot_y = 0;
			sprites[i].collision = 1;
			sprites[i].exp = 40;
			
			PA_CreateSprite(0,i, (void*)monster_7_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpriteHflip(0, i, 1);
			//PA_StartSpriteAnim(0, i, 0, 3, 20);
			//sprites[i].animated = 1;
			break;
		case 8://Greball
			//sprites[i].shoot_x = 0;
			//sprites[i].shoot_y = 0;
			sprites[i].collision = 1;
			sprites[i].exp = 50;
			PA_CreateSprite(0,i, (void*)monster_8_Sprite, OBJ_SIZE_32X32,1,MONSTERS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
			PA_SetSpriteHflip(0, i, 1);
			//PA_StartSpriteAnim(0, i, 0, 3, 20);
			//sprites[i].animated = 1;
			break;
	}
	u16 a = 8 + sprites[i].id * MONSTERDATA_TOTAL;
	
	sprites[i].counter = 0;
	sprites[i].hp = monsterdata[MONSTERDATA_HP + a];
	sprites[i].speed = monsterdata[MONSTERDATA_SPEED + a];
	sprites[i].weapon = monsterdata[MONSTERDATA_WEAPON + a];
	sprites[i].particles_when_die = monsterdata[MONSTERDATA_PARTICLES + a];
	
	sprites[i].w1 = monsterdata[MONSTERDATA_W1 + a];
	sprites[i].w2 = monsterdata[MONSTERDATA_W2 + a];
	sprites[i].h1 = monsterdata[MONSTERDATA_H1 + a];
	sprites[i].h2 = monsterdata[MONSTERDATA_H2 + a];
	
	if(monsterdata[MONSTERDATA_SIZE + a]==0)sprites[i].size = 16;
	else if(monsterdata[MONSTERDATA_SIZE + a]==1)sprites[i].size = 32;
	else if(monsterdata[MONSTERDATA_SIZE + a]==2)sprites[i].size = 64;
	
	sprites[i].x = sprites[i].x - (sprites[i].w1<<8);
	sprites[i].y -= ((sprites[i].size - sprites[i].h2)<<8);
	if(z!=0){
		sprites[z].x += sprites[i].x;
		sprites[z].y += sprites[i].y;
	}
	
	PA_SetSpritePrio(0,i,SPRITES_PRIO);
	
	VCola(i);//pa lo del aqqua
	if(z!=0)VCola(z);
	
	sprites[i].ballraise=30;///SZUMMONNN
	
	//load map dot
	u8 m=GetFreeMapDot();
	game.mapdot[m]=i;
	sprites[i].mapdot=m;
}
void SetKillMonster(u8 a){
	u8 rot=GetFreeRot();
	PA_SetSpriteRotEnable(0,a,rot);
	game.freerot[rot]=1;
	sprites[a].hp = 0;
	sprites[a].kill=1;
	sprites[a].killcnt=200;
	sprites[a].free=4;
	sprites[a].rot=rot;
	sprites[a].rotangle=0;
	//PA_SetSpriteAnim(0, a, 1);
	sprites[a].animated = 0;
	
	if(sprites[a].group!=0)SetKillMonster(sprites[a].group);
	hero.monster_aimed = a;
	hero.updatemonsterdata = 1;
}

void HitMonster(u8 m, u8 dmg){//monster sprite, damage
	u8 z=sprites[m].group;
	if(z!=0){
		sprites[z].blink = BLINK_COUNTER;
		PA_SetSpritePal(0,z,WHITE_PAL);
	}

	sprites[m].blink = BLINK_COUNTER;
	PA_SetSpritePal(0,m,WHITE_PAL);
	if(sprites[m].hp <= dmg)SetKillMonster(m);
	else sprites[m].hp -= dmg;
	
	
	hero.monster_aimed = m;
	hero.updatemonsterdata = 1;
	
	NewSound(hitmonster_sound);
}
