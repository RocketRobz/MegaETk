void MoveHero(void){
	s8 movx=0;
	
	CheckHeroMapCollisions();
	HeroCheckSkills(hero.inground);

	//move only if:
	if((HeroCanDoAction())&&(!hero.crouch)&&(!Stylus.Held)){
		if((Pad.Held.Left)&&((!Pad.Held.Y)||(!data.skills[5])))if(HCola(0,-hero.movespeed) == 0)movx--;
		if((Pad.Held.Right)&&((!Pad.Held.Y)||(!data.skills[5])))if(HCola(0,hero.movespeed) == 0)movx++;
		hero.x += movx*hero.movespeed;
	}

	UpdateHeroVars();
	
	
	//JUMPS LIMITS-------------------------
	if(hero.vy>hero.jumppower)hero.vy=hero.jumppower;
	if(hero.vy<-hero.jumppower)hero.vy=-hero.jumppower;
	//saltar poco o mucho
	if((Pad.Held.A==0)&&(hero.jumppressed==1)){
		hero.jumppressed=0;
		if(hero.vy<-100)hero.vy=-100;
	}
	
	//highjump y eso
	if(hero.vy > hero.jumppower-200)hero.highjump = 1;
	if(hero.vy > hero.higherjump)hero.higherjump = hero.vy;
	//------------------------------------
	
	//shoot x,y
	if(hero.flip==0)sprites[0].shoot_x = ((sprites[1].x-sprites[0].x)>>8) + 12;
	else sprites[0].shoot_x = ((sprites[0].x-sprites[1].x)>>8) + 20;
	sprites[0].shoot_y = ((sprites[1].y-sprites[0].y)>>8) + 16;
	

	//INVINCIBILITY------------------------
	if(hero.invisiblecounter != 0){
		hero.invisiblecounter--;
		hero.blink++;
		if(hero.blink == BLINK_LOOP2)hero.blink=0;
		else if(hero.blink < BLINK_LOOP){
			PA_SetSpritePal(0,0,BLINK_PAL);
			PA_SetSpritePal(0,1,BLINK_PAL);
		}
		else if(hero.blink >= BLINK_LOOP){
			PA_SetSpritePal(0,0,HERO_PAL);
			PA_SetSpritePal(0,1,HERO_PAL);
		}
		if(hero.invisiblecounter<=1){
			PA_SetSpritePal(0,0,HERO_PAL);
			PA_SetSpritePal(0,1,HERO_PAL);
		}
	}
	else{PA_SetSpritePal(0,0,HERO_PAL);
			PA_SetSpritePal(0,1,HERO_PAL);}
	//------------------------------------
	
	//DASH--------------------------------
	if(hero.dash!=0){
		movx = 0;
		
		
		if(hero.dash > 0){
			if(HCola(0,(-hero.movespeed<<1)) == 0)movx--;
			hero.x += (movx*hero.movespeed)<<1;
			hero.dash--;
			if((!hero.inground)&&(hero.dash<2))hero.dash++;
		}
		else{
			if(HCola(0,(hero.movespeed<<1)) == 0)movx++;
			hero.x += (movx*hero.movespeed)<<1;
			hero.dash++;
			if((!hero.inground)&&(hero.dash>-2))hero.dash--;
		}
		
		if(hero.dash == 0){
			sprites[0].y = hero.y - ((HERO_SIZE + HERO_H1)<<8);
			if(VCola(0)==1){
				sprites[0].h1 = 9;
				sprites[0].h2 = 2;
				if(hero.flip == 1)hero.dash++;
				else hero.dash--;
				}
			else RestoreHeroSize();
		}
	}
	UpdateHeroVars();
	
	//------------------------------------
	
	//VX COUNTER--------------------------
	if(hero.vx!=0){//si te acaban de pegar:
		movx=0;
		PA_SetSpriteAnim(0, 0, 1);
		if(hero.vx > 0){
			if(HCola(0,(-hero.movespeed<<1)) == 0)movx--;
			hero.x += (movx*hero.movespeed)<<1;
			hero.vx--;
		}
		else{
			if(HCola(0,(hero.movespeed<<1)) == 0)movx++;
			hero.x += (movx*hero.movespeed)<<1;
			hero.vx++;
		}
	}
	//------------------------------------
	
	
	//check if dies
	if((hero.y>>8)>192)game.die=1;
	
	UpdateHeroSprites();
}

void CheckHeroMapCollisions(void){//hero colliisons
	u8 a=0;
	u8 b=0;
	u8 inground = 0;
	
	UpdateHeroVars();
	
	if(hero.vy >= hero.jumppower)hero.highjump = 1;
	
	if((hero.y>>8) > 0 ){	//para que no mire colisiones si esta fuera de la pantalla
		if(hero.vy<0){
			hero.candoublejump = 1;
		//UP collision------------------------------------
			hero.vy += GRAVITY;
			sprites[0].y = hero.y - (sprites[0].size<<8);
			
			if(VCola(0)==1){
				while(hero.vy<100)hero.vy+=50;
			}
			while(a==1){
					sprites[0].y += hero.vy;
					if(VCola(0)==1)hero.y++;
					else a=1;
			}
			hero.y += hero.vy;
			sprites[0].y = hero.y;
		//------------------------------------------------
		}
		else if(hero.vy>=0){
			hero.candoublejump = 1;
		//Down Collision-----------------------------------
			hero.vy += GRAVITY;
			if(VCola(0)==1){
				hero.vy = 0;
				inground = 1;
			}
			
			hero.y += hero.vy;
			while(a==0){
					sprites[0].y -= 1<<8;
					if(VCola(0)==1){
						hero.y-=1<<8;
						b=1;
						hero.vy=0;
						sprites[0].vy = 0;
						}
					else a=1;
			}
			if(b + hero.highjump == 2){
				CreateHumo((hero.x>>8) + HERO_SIZE - HERO_W2,(hero.y>>8) + 16, 0);
				CreateHumo((hero.x>>8) + HERO_W1 - 16,(hero.y>>8) + 16, 1);
				
				NewSound(floor_sound);
				
				hero.highjump = 0;
				}
			sprites[0].y = hero.y;

		//------------------------------------------------
		}
	}
	else{
		hero.vy += GRAVITY;
		hero.y += hero.vy;
	}
	hero.inground = inground;
	UpdateHeroVars();
}

void UpdateHeroSprites(){
	//Set Flip
	if((Pad.Held.Right)&&(!Stylus.Held))hero.flip = 0;
	else if((Pad.Held.Left)&&(!Stylus.Held))hero.flip = 1;
	PA_SetSpriteHflip(0, 0, hero.flip);
	
	//update arm rotation
	PA_SetRotsetNoZoom(0,sprites[HERO_ARM_SLOT].rot, sprites[0].shootangle*1.42);
	//---
	
	
	//Poniendo sprites------------------
	//dash
	if(hero.dash != 0){
		if(hero.ani_on)PA_StopSpriteAnim(0,0);
		PA_SetSpriteAnim(0, 0, 7);
		sprites[0].animated = 0;
		hero.ani_on = 0;		
	}
	//Jump
	else if((hero.vy != 0)&&(!hero.inground)){
		if(hero.ani_on)PA_StopSpriteAnim(0,0);
		if(hero.vy>=0)PA_SetSpriteAnim(0, 0, 5);
		else PA_SetSpriteAnim(0, 0, 6);
		sprites[0].animated = 0;
		hero.ani_on = 0;
	}
	
	//Hero damaged
	else if ((hero.vx != 0) || (hero.vy > 0)){
		if(hero.ani_on)PA_StopSpriteAnim(0,0);
		PA_SetSpriteAnim(0, 0, 6);
		sprites[0].animated = 0;
		hero.ani_on = 0;
	}
	else if(hero.crouch){
		if(hero.ani_on)PA_StopSpriteAnim(0,0);
		PA_SetSpriteAnim(0, 0, 8);
		sprites[0].animated = 0;
		hero.ani_on = 0;
	}
	//Walk
	else if(((Pad.Held.Right + Pad.Held.Left) > 0)&&(!hero.manual_aim)&&(!Stylus.Held)){
		//animation
		if(hero.ani_on == 0){
			PA_SetSpriteAnim(0, 0, 1);
			PA_StartSpriteAnim(0,0,1,4,5);
			sprites[0].animated = 1;
			hero.ani_on = 1;			
		}
	}
	//nothing
	else {
		PA_StopSpriteAnim(0,0);
		PA_SetSpriteAnim(0, 0, 0);
		PA_SetSpriteHflip(0, 0, hero.flip);
		sprites[0].animated = 0;
		hero.ani_on = 0;
	}
	
	
	//update arm location
	s8 addx=0;
	u16 angle = sprites[0].shootangle*1.42;
	u16 z = sprites[0].shootangle;
	
	if((z<30)||(z>330))addx = -1;
	else if ((z<60)||(z>300))addx = -2;
	else if ((z<75)||(z>285))addx = -3;
	else if ((z<90)||(z>260))addx = -4;
	else if ((z<120)||(z>240))addx = -4;
	else if ((z<135)||(z>225))addx = -3;
	else if ((z<150)||(z>210))addx = -2;
	else addx=-1;
	
	if(hero.flip==1)addx*=-1;
	
	sprites[HERO_ARM_SLOT].x = sprites[0].x + (addx<<8);
	sprites[HERO_ARM_SLOT].y = sprites[0].y - (PA_Sin(angle)<<3);
	
	if(hero.flip)sprites[HERO_ARM_SLOT].x -= (HERO_ARM_X + 1)<<8;
	else sprites[HERO_ARM_SLOT].x += HERO_ARM_X<<8;
	
	if((hero.dash)||(hero.crouch))sprites[HERO_ARM_SLOT].y += HERO_ARM_Y_CROUCH<<8;
	else sprites[HERO_ARM_SLOT].y += HERO_ARM_Y<<8;
}

void HeroCheckSkills(u8 inground){//skills or actions
	hero.inground = inground;
	if(inground){
		hero.doublejump=1;
		hero.candoublejump=0;
	}
	hero.manual_aim = 0;
	//speed counter
	if((hero.incmovespeedcounter>0)&&(inground)){
		hero.incmovespeedcounter--;
		if(hero.incmovespeedcounter==0)hero.movespeed=HERO_SPEED + hero.speedinc;	
	}
	UpdateHeroVars();
	//------------------------------
	if(hero.crouch){
		sprites[0].h1 = 12;
		sprites[0].h2 = 1;
		sprites[0].shoot_y=16;
	}
	else if(!hero.dash)RestoreHeroSize();
	
	//Keys
	//Down = Crouch	
	if((data.skills[2])&&(Pad.Held.Down)&&(inground)&&(!Pad.Held.Y)&&(!hero.dash)&&(!Pad.Held.Left)&&(!Pad.Held.Right))hero.crouch = 1;
	else hero.crouch = 0;

	if(Pad.Released.A)hero.crouch=0;
	//Button [A]
	//A + DOWN = DASH ..... (A + crouch)
	if((data.skills[3])&&(Pad.Newpress.A)&&(hero.crouch)&&(!hero.dash)){
		HeroDash();
		hero.crouch = 0;
	}
	//A = JUMP
	else if((Pad.Newpress.A)&&(inground)&&(HeroCanDoAction())&&(!hero.crouch)){
		if(hero.dash!=0){if(data.skills[4])hero.vy -= JUMPPOWER_DASH;}
		else hero.vy -= hero.jumppower;
		hero.jumppressed=1;
		hero.inground = 0;
	}
	else if((Pad.Newpress.A)&&(data.skills[6])&&(hero.doublejump)&&(hero.candoublejump)){//double jump
		hero.vy = -hero.jumppower-200;
		hero.jumppressed=1;
		hero.doublejump=0;//say i doublejumped
	}
	
	//na
	if((hero.autorun)&&(!hero.dash)){
		hero.movespeed = HERO_SPEED + 200 + hero.speedinc;
		hero.incmovespeedcounter=2;
	}
	
	//Button [X]
	//X = Shield
	if((Pad.Held.X)&&(inground)&&(HeroCanDoAction()==1)){
		//hero.movespeed = HERO_SPEED + 200 + hero.speedinc;
		//hero.incmovespeedcounter=2;
	}
	
	//Button [Y]
	//Y = Aim
	//Y+key = aim
		if(data.skills[5]){
			if((Pad.Held.Y)&&(!Stylus.Held)){
				hero.manual_aim = 1;
				//UP (90º)
				if(Pad.Held.Up){
					if(sprites[0].shootangle!=90){
						if((sprites[0].shootangle<90)||(sprites[0].shootangle>=(270+hero.flip)))sprites[0].shootangle+=FASTAIMSPEED;
						else sprites[0].shootangle-=FASTAIMSPEED;
						
						if((sprites[0].shootangle<(90+FASTAIMSPEED))&&(sprites[0].shootangle>(90-FASTAIMSPEED)))sprites[0].shootangle=90;
					}
				}
				//DOWN (270º)
				if(Pad.Held.Down){
					if(sprites[0].shootangle!=270){
						if((sprites[0].shootangle<=(90-hero.flip))||(sprites[0].shootangle>270))sprites[0].shootangle-=FASTAIMSPEED;
						else sprites[0].shootangle+=FASTAIMSPEED;
						
						if((sprites[0].shootangle<(270+FASTAIMSPEED))&&(sprites[0].shootangle>(270-FASTAIMSPEED)))sprites[0].shootangle=270;
					}
				}
				//RIGHT (0º)
				if(Pad.Held.Right){
					if(sprites[0].shootangle!=0){
						if(sprites[0].shootangle<180)sprites[0].shootangle-=FASTAIMSPEED;
						else sprites[0].shootangle+=FASTAIMSPEED;
						
						if((sprites[0].shootangle<(0+FASTAIMSPEED))||(sprites[0].shootangle>(360-FASTAIMSPEED)))sprites[0].shootangle=0;
					}
				}
				//Left (180º)
				if(Pad.Held.Left){
					if(sprites[0].shootangle!=180){
						if(sprites[0].shootangle<180)sprites[0].shootangle+=FASTAIMSPEED;
						else sprites[0].shootangle-=FASTAIMSPEED;
						
						if((sprites[0].shootangle<(180+FASTAIMSPEED))&&(sprites[0].shootangle>(180-FASTAIMSPEED)))sprites[0].shootangle=180;
					}
				}
				
				//FLIP?
				if(Pad.Newpress.Right){
					if((sprites[0].shootangle>90)&&(sprites[0].shootangle<270))sprites[0].shootangle = 180 - sprites[0].shootangle;
				}
				if(Pad.Newpress.Left){
					if((sprites[0].shootangle<90)||(sprites[0].shootangle>270))sprites[0].shootangle = 180 - sprites[0].shootangle;
				}
				
				if(sprites[0].shootangle<0)sprites[0].shootangle += 360;
				if(sprites[0].shootangle>360)sprites[0].shootangle -= 360;
			}
		}
	
	//Button [R]
	//R = Change weapon
	u8 a=0;
	if(Pad.Newpress.R==1){
		while(a==0){
			hero.weapon++;
			if(hero.weapon == TOTAL_WEAPONS)hero.weapon = 0;
			if(hero.maxammo[hero.weapon] > 0)a=1;
		}
		HeroChangeWeapon(hero.weapon);
	}
}

void HeroDash(){
	if(hero.flip==0){
		hero.dash = -20;
		CreateHumo((hero.x>>8) + HERO_W1 - 16,(hero.y>>8) + 16, 1);
	}
	else {
		hero.dash = 20;
		CreateHumo((hero.x>>8) + HERO_SIZE - HERO_W2,(hero.y>>8) + 16, 0);
	}
	hero.movespeed = HERO_SPEED + 75 + hero.speedinc;
	hero.incmovespeedcounter = 20;
	hero.y += 1<<8;
	sprites[0].h1 = 9;
	sprites[0].h2 = 2;
	
	NewSound(dash_sound);
}

void Hero_Die(){
	hero.hp=0;
	UpdateStats();//update status on screen
	hero.lives--;
	hero.exp=0; //no EP
	
	
	PA_StopMod();
	NewSound(die_sound);
	sound.startmod=1;
}

void NewHitHero(u8 i, u8 type){	//sprite number, type of hit (collision, shot..)
	if(type==1) HitHero(10, i);
	else HitHero(sprites[i].power, i);
	CreateParticle(0,0);
	CreateParticle(0,0);
}

void HitHero(u8 damage, u8 i){
	if((sprites[0].x + 16) < sprites[i].x)hero.vx = 5;
	else hero.vx = -5;
	
	hero.exp -= damage<<1;
	if(hero.exp<0)hero.exp=0;
	
	if(data.skills[8])damage = damage>>1;
	
	hero.hp -= damage;
	hero.vy = 0;
	hero.invisiblecounter = 20;
	
	hero.status_changed = 1;
	
	
	NewTextLine(getdmg,damage);
	NewSound(hithero_sound);
}

void RestoreHeroSize(){
	sprites[0].w1 = HERO_W1;
	sprites[0].w2 = HERO_W2;
	sprites[0].h1 = HERO_H1;
	sprites[0].h2 = HERO_H2;
	sprites[0].size = 32;
	sprites[0].shoot_y = 16;
	sprites[0].shoot_x = 16;
}

void UpdateHeroVars(){
	sprites[0].x = hero.x;
	sprites[0].y = hero.y;
	sprites[0].flip = hero.flip;
}

u8 HeroCanDoAction(){
	if(hero.vx == 0)return 1;
	else return 0;
}

void HeroChangeWeapon(u8 weapon){	//weapon = weapon id
	hero.weapon = weapon;
	switch(weapon){
		case 2:
			game.maxshots = 10;
			break;
		default:
			game.maxshots = 6;
			break;
	}
	PA_SetSpriteAnim(0, status_weapon_x_slot, weapon);
	hero.status_changed = 1;
}
