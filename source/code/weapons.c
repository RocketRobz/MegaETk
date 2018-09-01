void Updateincammo(){
	u8 b;
	for(b=2;b<TOTAL_WEAPONS;b++){
		if(hero.maxammo[b]>0)hero.maxammo[b] = defaultAMMO + hero.incammo;
	}
}

void UseWeapon(){
	if((hero.ammo[hero.weapon]!=0)||(hero.maxammo[hero.weapon]==UNLIMITED_AMMO)){
		if(hero.shotsonscreen<game.maxshots){
			//using weapon
			if((Pad.Newpress.B)||(Pad.Newpress.L)){
				if(hero.numshoots[hero.weapon] > 1) MultipleShot(hero.weapon, 0, hero.numshoots[hero.weapon]);
				else NewShot(hero.weapon, 0);
				hero.ammo[hero.weapon]-=hero.numshoots[hero.weapon];
				hero.shotsonscreen+=hero.numshoots[hero.weapon];
				PA_StartSpriteAnimEx(0, HERO_ARM_SLOT, 0, 3, 20, ANIM_ONESHOT);
				hero.status_changed = 1;
			}
			
			//Holding button
			else if((Pad.Held.B)||(Pad.Held.L)){
				hero.shotcounter++;
				if(hero.shotcounter == hero.shotspeed){
					if(hero.numshoots[hero.weapon] > 1)MultipleShot(hero.weapon, 0, hero.numshoots[hero.weapon]);
					else NewShot(hero.weapon, 0);
					hero.shotcounter = 0;
					hero.ammo[hero.weapon]-=hero.numshoots[hero.weapon];
					hero.shotsonscreen+=hero.numshoots[hero.weapon];
					PA_StartSpriteAnimEx(0, HERO_ARM_SLOT, 0, 3, 20, ANIM_ONESHOT);
					hero.status_changed = 1;
				}
			}
		}
	}
	if((Pad.Released.B)||(Pad.Released.L))hero.shotcounter = 0;
	if(hero.ammo[hero.weapon]<0)hero.ammo[hero.weapon] = 0;
}

void RefreshInfiniteAmmo(u8 i){
	hero.ammo[i]=hero.maxammo[i];
	hero.status_changed = 1;
}

u8 CanMultipleShot(u8 weapon){
	return 1;
	if((weapon==1)
		||(weapon==3)
		||(weapon==4)
		||(weapon==6)
		)return 1;
	return 0;
}

void MultipleShot(u8 weapon, u8 i, u8 shoots){//weapon id, sprite, number of shoots
	//if weapon can do multiple shoots, then:
	if(CanMultipleShot(weapon)){
		if(shoots==2){
			NewShot(weapon, i);				
			sprites[i].shootangle += 10;
			NewShot(weapon, i);
			sprites[i].shootangle -= 10;
		}
		else if(shoots>=3){
			NewShot(weapon, i);
			sprites[i].shootangle += 10;
			NewShot(weapon, i);
			sprites[i].shootangle -= 20;
			NewShot(weapon, i);
			sprites[i].shootangle += 10;
		}
	}
	else {
		NewShot(weapon,i);
	}
}
void NewShot(u8 weapon, u8 a){
	u8 i = GetFreeSprite();
	s16 angle=sprites[a].shootangle*1.42;
	u8 anim = 0;
	u8 flip = 0;//enable sprite flip?
	
	sprites[i].x = sprites[a].x;
	sprites[i].y = sprites[a].y;
	sprites[i].flip = sprites[a].flip;
	sprites[i].id = weapon;
	sprites[i].particletype = 1;
	totalsprites++;
	
	//select Hero shot or monster shot
	if(sprites[a].free == 1)sprites[i].free=2;	//hero shoot
	else sprites[i].free = 12;
	
	if(sprites[a].free == 1)hero.shotspeed = DEFAULT_SHOT_SPEED;

	//situandolo al agujero del que dispara (luego se ha de ajustar dependiendo del tamaño del disparo)
		if(sprites[a].flip==0){
			sprites[i].x += sprites[a].shoot_x<<8;
			sprites[i].y += sprites[a].shoot_y<<8;
			}
		else {
			sprites[i].x += (sprites[a].size - sprites[a].shoot_x)<<8;
			sprites[i].y += sprites[a].shoot_y<<8;
		}
	//----------
	
	if(((sprites[i].x-hero.scrollx)>>8 < 0)||((sprites[i].x-hero.scrollx)>>8 > 256))KillSprite(i);
	else{
		switch(weapon){
		//DEFAULT WEAPON------------------------------------
			case 1:	
				sprites[i].collision = 1;
				sprites[i].power = 10;
				sprites[i].speed = 1200;
				
				flip = 1;
				
				sprites[i].particles_when_die = 2;
				
				//select gfx
				
				if(sprites[a].shootangle<30)anim = 0;
				else if(sprites[a].shootangle<60)anim = 1;
				else if(sprites[a].shootangle<120)anim = 2;
				else if(sprites[a].shootangle<150)anim = 1;
				else if(sprites[a].shootangle<210)anim = 0;
				else if(sprites[a].shootangle<240)anim = 1;
				else if(sprites[a].shootangle<300)anim = 2;
				else if(sprites[a].shootangle<330)anim = 1;
				else anim = 0;
				
				if(anim == 0){
					sprites[i].w1=6;
					sprites[i].w2=2;
					sprites[i].h1=6;
					sprites[i].h2=6;
					}
				else if(anim == 1){
					sprites[i].w1=6;
					sprites[i].w2=6;
					sprites[i].h1=6;
					sprites[i].h2=6;
					}
				else if(anim == 2){
					sprites[i].w1=6;
					sprites[i].w2=6;
					sprites[i].h1=6;
					sprites[i].h2=6;
					}
				
				sprites[i].size = 16;
				
				PA_CreateSpriteFromGfx(0,i,gfx.weapon1[anim],OBJ_SIZE_16X16,1,SHOOTS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim (0, i, anim);
				
				NewSound(shot1_sound);
				//--------------
				break;
				
		//Laser------------------------------------------
			case 2:					
				flip = 1;
				
				sprites[i].power = 5;
				sprites[i].speed = 2048;
				sprites[i].size = 16;
				sprites[i].collision = 5;//5 = bounce + sub hp
				sprites[i].hp = 4;	//4 bounces
				
				if(sprites[a].free == 1){
					hero.shotspeed = 2;
					hero.weaponcounter[2]++;
					if(hero.weaponcounter[2]==4){
						sprites[i].particles_when_die = 1;
						hero.weaponcounter[2]=0;
						NewSound(laser_sound);
					}
				}
				
				//selecting the correct gfx
				if(sprites[a].shootangle<18)anim = 0;
				else if(sprites[a].shootangle<36)anim = 1;
				else if(sprites[a].shootangle<54)anim = 2;
				else if(sprites[a].shootangle<72)anim = 3;
				else if(sprites[a].shootangle<108)anim = 4;
				else if(sprites[a].shootangle<126)anim = 3;
				else if(sprites[a].shootangle<144)anim = 2;
				else if(sprites[a].shootangle<162)anim = 1;
				else if(sprites[a].shootangle<198)anim = 0;
				else if(sprites[a].shootangle<216)anim = 1;
				else if(sprites[a].shootangle<234)anim = 2;
				else if(sprites[a].shootangle<252)anim = 3;
				else if(sprites[a].shootangle<288)anim = 4;
				else if(sprites[a].shootangle<306)anim = 3;
				else if(sprites[a].shootangle<324)anim = 2;
				else if(sprites[a].shootangle<342)anim = 1;
				else anim = 0;
				
				if(anim == 0){
					sprites[i].w1=0;
					sprites[i].w2=0;
					sprites[i].h1=6;
					sprites[i].h2=6;
					}
				else if(anim == 1){
					sprites[i].w1=1;
					sprites[i].w2=1;
					sprites[i].h1=5;
					sprites[i].h2=5;
					}
				else if(anim == 2){
					sprites[i].w1=3;
					sprites[i].w2=4;
					sprites[i].h1=3;
					sprites[i].h2=4;
					}
				else if(anim == 3){
					sprites[i].w1=5;
					sprites[i].w2=5;
					sprites[i].h1=1;
					sprites[i].h2=1;
					}
				else if(anim == 4){
					sprites[i].w1=6;
					sprites[i].w2=6;
					sprites[i].h1=0;
					sprites[i].h2=0;
					}
				//--------------
				PA_CreateSpriteFromGfx(0,i,gfx.weapon2[anim],OBJ_SIZE_16X16,1,SHOOTS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim (0, i, anim);
				break;

		//RED BALL--------------------------------------
			case 3:
				sprites[i].power = 5;
				sprites[i].speed = 768;
				sprites[i].collision = 1;
				
				flip = 0;
				
				sprites[i].particles_when_die = 1;
				
				//gfx
				PA_CreateSpriteFromGfx(0,i,gfx.weapon3,OBJ_SIZE_8X8,1,SHOOTS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim (0, i, 0);
				
				//size
				sprites[i].size = 8;
				sprites[i].w1=0;
				sprites[i].w2=0;
				sprites[i].h1=0;
				sprites[i].h2=0;
				//--------------
				NewSound(shot1_sound);
				break;
		//thorn--------------------------------------
			case 4:
				sprites[i].power = 10;
				sprites[i].speed = 756;
				sprites[i].collision = 1;
				
				flip = 1;
				
				sprites[i].particles_when_die = 0;
				
				//gfx
				PA_CreateSpriteFromGfx(0,i,gfx.weapon4,OBJ_SIZE_8X8,1,SHOOTS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim (0, i, 0);
				
				//size
				sprites[i].size = 8;
				sprites[i].w1=0;
				sprites[i].w2=0;
				sprites[i].h1=1;
				sprites[i].h2=2;
				//--------------
				NewSound(shot1_sound);
				break;
		//green circle
			case 5:
				sprites[i].power = 15;
				sprites[i].speed = 650;
				sprites[i].collision = 1;
				
				sprites[i].flip = 0;
				
				sprites[i].particles_when_die = 3;
				
				//gfx
				PA_CreateSpriteFromGfx(0,i,gfx.weapon5,OBJ_SIZE_16X16,1,SHOOTS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim (0, i, 0);
				
				//size
				sprites[i].size = 16;
				sprites[i].w1=3;
				sprites[i].w2=3;
				sprites[i].h1=3;
				sprites[i].h2=3;
				//--------------
				NewSound(shot1_sound);
				break;
		//Lanzallamas
			case 6:
				sprites[i].x=hero.x;
				if(sprites[i].flip==0)sprites[i].x+=(21<<8);
				else sprites[i].x += (3<<8);
				
				flip = 0;
				
				sprites[i].power = 25;
				sprites[i].speed = 800;
				sprites[i].collision = 2;
				
				sprites[i].killcnt = 25;
				
				sprites[i].size = 16;
				sprites[i].h1 = 4;
				sprites[i].h2 = 4;
				sprites[i].w1 = 4;
				sprites[i].w2 = 4;
				
				if(sprites[a].free == 1)hero.shotspeed = 4;
				
				PA_CreateSpriteFromGfx(0,i,gfx.weapon6,OBJ_SIZE_16X16,1,SHOOTS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim (0, i, anim);
				NewSound(shot1_sound);
				break;
				
		//BOLA VERDE QUE REBOTA
			case 7:
				sprites[i].power = 50;
				sprites[i].speed = 950;
				sprites[i].collision = 5;
				sprites[i].hp = 30;
				sprites[i].gravity = 40;
				
				sprites[i].flip = 0;
				
				sprites[i].particles_when_die = 5;
				
				//gfx
				PA_CreateSpriteFromGfx(0,i,gfx.weapon7,OBJ_SIZE_16X16,1,SHOOTS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim (0, i, 0);
				
				//size
				sprites[i].size = 16;
				sprites[i].w1=2;
				sprites[i].w2=2;
				sprites[i].h1=2;
				sprites[i].h2=2;
				//--------------
				NewSound(shot1_sound);
				break;
		//TORNILLO------------------------------------
			case 8:	
				sprites[i].collision = 1;
				sprites[i].power = 25;
				sprites[i].speed = 2200;
				
				flip = 1;
				
				sprites[i].particles_when_die = 5;
				
				//select gfx
				
				if(sprites[a].shootangle<30)anim = 0;
				else if(sprites[a].shootangle<60)anim = 1;
				else if(sprites[a].shootangle<120)anim = 2;
				else if(sprites[a].shootangle<150)anim = 1;
				else if(sprites[a].shootangle<210)anim = 0;
				else if(sprites[a].shootangle<240)anim = 1;
				else if(sprites[a].shootangle<300)anim = 2;
				else if(sprites[a].shootangle<330)anim = 1;
				else anim = 0;
				
				if(anim == 0){
					sprites[i].w1=0;
					sprites[i].w2=1;
					sprites[i].h1=5;
					sprites[i].h2=6;
					}
				else if(anim == 1){
					sprites[i].w1=4;
					sprites[i].w2=4;
					sprites[i].h1=4;
					sprites[i].h2=4;
					}
				else if(anim == 2){
					sprites[i].w1=5;
					sprites[i].w2=6;
					sprites[i].h1=1;
					sprites[i].h2=0;
					}
				
				sprites[i].size = 16;
				
				PA_CreateSpriteFromGfx(0,i,gfx.weapon8[anim],OBJ_SIZE_16X16,1,SHOOTS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim (0, i, anim);
				//--------------
				NewSound(shot1_sound);
				break;
		//ICYSHOT------------------------------------
			case 9:	
				sprites[i].collision = 1;
				sprites[i].power = 20;
				sprites[i].speed = 1500;
				
				flip = 1;
				
				sprites[i].particles_when_die = 4;
				
				//select gfx
				
				if(sprites[a].shootangle<30)anim = 0;
				else if(sprites[a].shootangle<60)anim = 1;
				else if(sprites[a].shootangle<120)anim = 2;
				else if(sprites[a].shootangle<150)anim = 1;
				else if(sprites[a].shootangle<210)anim = 0;
				else if(sprites[a].shootangle<240)anim = 1;
				else if(sprites[a].shootangle<300)anim = 2;
				else if(sprites[a].shootangle<330)anim = 1;
				else anim = 0;
				
				if(anim == 0){
					sprites[i].w1=1;
					sprites[i].w2=2;
					sprites[i].h1=5;
					sprites[i].h2=4;
					}
				else if(anim == 1){
					sprites[i].w1=3;
					sprites[i].w2=3;
					sprites[i].h1=4;
					sprites[i].h2=3;
					}
				else if(anim == 2){
					sprites[i].w1=4;
					sprites[i].w2=5;
					sprites[i].h1=2;
					sprites[i].h2=1;
					}
				
				sprites[i].size = 16;
				
				PA_CreateSpriteFromGfx(0,i,gfx.weapon9[anim],OBJ_SIZE_16X16,1,SHOOTS_PAL,(sprites[i].x-hero.scrollx)>>8,sprites[i].y>>8);
				PA_SetSpriteAnim (0, i, anim);
				
				NewSound(shot1_sound);
				//--------------
				break;
			//NONE
			default:	
				KillSprite(i);
				break;
		}
		
		//end of switch
		if(sprites[i].flip == 1)sprites[i].x -= (sprites[i].size - sprites[i].w1 - sprites[i].w2)<<8;
		sprites[i].y -= sprites[i].size<<7;//ajustando situacion
		
		//calculate vx and vy
		sprites[i].vy = (PA_Sin(angle)*sprites[i].speed)>>8;
		sprites[i].vx = (PA_Cos(angle)*sprites[i].speed)>>8;
		//----------------------------
		PA_SetSpritePrio(0,i,SPRITES_PRIO);
		
		if((weapon!=0)&&(weapon!=3)&&(weapon!=5)&&(weapon!=6)&&(weapon!=8)){
			PA_SetSpriteHflip(0, i, sprites[i].flip);
			if(sprites[i].vy>0)PA_SetSpriteVflip(0, i, 0);
			else PA_SetSpriteVflip(0, i, 1);
		}
		
		sprites[i].flip = flip;
		
		
		//if hero shoot and black arm. inrcease atk
		if((data.skills[9])&&(sprites[a].free==1))sprites[i].power += sprites[i].power>>1;
		
		
		//check collision!
		if(HCola(i,sprites[i].vx)){
			sprites[i].particles_when_die = 0;
			KillSprite(i);
			if(sprites[a].free == 1)hero.ammo[hero.weapon]++;
		}
	}
}

void MoveShots(u8 i, u8 byhero){//sprite number, shoot made by hero (0=no,1=yes)
	u8 kill=0;
	u8 hcol=0;
	u8 vcol=0;
	u8 a=0;
	
	//GRAVITY
	sprites[i].vy-=sprites[i].gravity;
	
	//COLLISION WITH MAP
			
		//tile collision X
		if(HCola(i,sprites[i].vx)){
			hcol=1;
			kill=1;
			}
			
		//tile collision Y
		if(VCola2(i,sprites[i].vy)){
			vcol=1;
			kill=1;
		}
			
	//COLLISION WITH SPRITES
		//shoot colisiona con heroe? (solo si lo ha disparado el hero)
			if(byhero == 0){
				if(!hero.invisiblecounter){
					if(SCol(i,0)!=0){//i = shot sprite .. a = hero sprite
						kill=3;//kill shoot
						HitHero(sprites[i].power, i); //Hit Hero
					}
				}
			}
		//-------------------------------------
		//shoot colision with monster or boss
			else{
				//check boss (solo si hay)
					if(boss.loaded==1){
						if(SCol(i,boss.sprite)){
							kill=3;
							sprites[i].hp=1;
							HitBoss(sprites[i].power);
						}
					}
				//check monster
					for(a=0;a<maxsprites;a++){//looking for a monster
						if(sprites[a].free==3){//if monster type = 3, then check collision
							if(SCol(i,a)!=0){//i = shot sprite .. a = monster sprite
								kill=3;//kill shoot
								sprites[i].hp=1;
								HitMonster(a,sprites[i].power); //hit monster .. a = sprite nº, not monster id!!	
							}
						}
					}
				//
			}
		//------------------------------------

	//kill counter
	if(sprites[i].killcnt > 0){
		sprites[i].killcnt--;
		if(sprites[i].killcnt==0){
			kill = 3;
			KillSprite(i);
			}
	}
	
	if((hcol)||(vcol)){
		/*sfx = GetSoundChannel();
		sound.channel[sfx] = 1;
		sound.counter[sfx] = 30;
		//PA_PlaySimpleSound(sfx,(void*)snd_wallhit);*/
	}
	//MOVING
	//kill:
	//0 -> no
	//1 -> H map
	//2 -> V map
	//3 -> forced kill
	if(kill!=0){
		switch(sprites[i].collision){
			//NADA
			case 0:
				break;
				
			//KILL SPRITE
			case 1:
				KillSprite(i);
				break;
				
			//sub HP
			case 2:
				sprites[i].hp--;
				if((sprites[i].hp==0)||(kill==3))KillSprite(i);
				break;
				
			//Stay
			case 3:
				break;
				
			//Rebota (solo con mapa)
			case 4:
				if(hcol==1){
					sprites[i].vx*=-1;
					sprites[i].y-=sprites[i].vy;
				}
				else if(vcol==1){
					sprites[i].vy*=-1;
					sprites[i].y-=sprites[i].vy;
					if(sprites[i].gravity!=0)sprites[i].vy/=1.5;
				}
				if(kill==3)KillSprite(i);//si no choca contra mapa pos muere
				break;
				
			//Rebota + sub HP
			case 5:
				if(hcol){
					sprites[i].vx*=-1;
					sprites[i].y-=sprites[i].vy;
				}
				else if(vcol){
					sprites[i].vy*=-1;
					sprites[i].y-=sprites[i].vy;
					if(sprites[i].gravity!=0)sprites[i].vy-=200;
				}
				
				sprites[i].hp--;
				if(sprites[i].hp==0)KillSprite(i);
				break;
		}
	}
	else if((((sprites[i].x-hero.scrollx)>>8)>256)
		||(((sprites[i].x-hero.scrollx)>>8)<(-sprites[i].size))
		||((sprites[i].y>>8)<-sprites[i].size)
		||((sprites[i].y>>8)>192))KillSprite(i);
	else{
		sprites[i].x+=sprites[i].vx;
		sprites[i].y-=sprites[i].vy;
		
	if(sprites[i].flip == 1){
		if(sprites[i].vx>0)PA_SetSpriteHflip(0,i,0);
		else PA_SetSpriteHflip(0,i,1);
		
		if(sprites[i].vy>0)PA_SetSpriteVflip(0,i,0);
		else PA_SetSpriteVflip(0,i,1);
		}
	}	
}
