void Debug(){
	/*alpha debuggzzz
	if((Pad.Held.Up)&&debug.a2<31)debug.a2++;
	if((Pad.Held.Down)&&debug.a2>0)debug.a2--;
	if((Pad.Held.Right)&&debug.a1<31)debug.a1++;
	if((Pad.Held.Left)&&debug.a1>0)debug.a1--;	
	
	PA_SetSFXAlpha(0,debug.a1,debug.a2);*/



	if(Pad.Newpress.Select){
		debug.option++;
		if(debug.option==15)debug.option=0;
		CleanText(1);
		}
	if(debug.counter>10){//update debug screen frame rate
		CleanText(1);
		debug.counter=0;
		switch(debug.option){
			case 0:
				GeneralInfoDebug();		
				break;
			case 1:
				SoundDebug();
				break;			
			case 2:
				BossDebug();
				break;
			case 3:
				ShowData();
				break;
			case 4:
				AvailableSpriteDebug();
				break;
			case 5:
				ItemDebug();
				break;
			case 6:
				RaiseParticleDebug();
				break;
			case 7:
				TeleportDebug();
				break;
			case 8:
				RotDebug();
				break;
			case 9:
				ParticleDebug();
				break;
			case 10:
				CollisionDebug();
				break;
			case 11:
				CheckEventDebug();
				break;
			case 12:
				MonsterDebug();
				break;
			case 13:
				SpriteIDDebug();
				break;
			case 14:
				ShootDebug();
				break;
		}
		PA_OutputText(1,0,23,"%c1ETkPG Engine 26-05-2006              ");
		//----------------------------------------------------------XX|
	}
	debug.counter++;
}

void GeneralInfoDebug(){
	PA_OutputText(1,0,0,"%c7Hero:", hero.x);
	PA_OutputText(1,0,1,"%c2xy:%c0 %d, %d      %c2scrollx:%c0 %d   ", hero.x>>8, hero.y>>8, hero.scrollx>>8);
	PA_OutputText(1,0,2,"%c2tiles xy:%c0 %d,%d    ", hero.x>>11, hero.y>>11);
	PA_OutputText(1,0,3,"%c2vy:%c0 %d   %c2vx:%c0 %d   %c2flip:%c0 %d ", hero.vy, hero.vx, hero.flip);
	PA_OutputText(1,0,4,"%c2Invincibility:%c0 %d %c2blink:%c0 %d", hero.invisiblecounter, hero.blink);
	PA_OutputText(1,0,5,"%c2raise:%c0 %d %c2movspeed:%c0 %d %c2(%c0%d%c2)%c0  ", sprites[0].raise, hero.movespeed, hero.incmovespeedcounter);

	PA_OutputText(1,0,6,"%c2Autorun:%c0 %d", hero.autorun);
	PA_OutputText(1,0,7,"%c2Stylus:%c0 %d,%d %c2(%c0%d%c2)%c0", Stylus.X, Stylus.Y, Stylus.Held);
	PA_OutputText(1,0,8,"%c2Angle:%c0 %d", sprites[0].shootangle);

	PA_OutputText(1,0,9,"%c2crouch:%c0 %d ", hero.crouch);
	PA_OutputText(1,0,10,"%c2w1:%c0 %d %c2w2:%c0 %d %c2h1:%c0 %d %c2h2:%c0 %d ", sprites[0].w1, sprites[0].w2, sprites[0].h1, sprites[0].h2);

	PA_OutputText(1,0,15,"%c2HP:%c0 %d%c1/%c0%d  %c2Lives:%c0 %d", hero.hp, hero.maxhp, hero.lives);
	PA_OutputText(1,0,16,"%c2Ammo:%c0 %d/%d", hero.ammo[hero.weapon], hero.maxammo[hero.weapon]);
	PA_OutputText(1,0,17,"%c2Weapon:%c0 %d %c2num:%c0 %d %c2shots:%c0 %d  ", hero.weapon, hero.numshoots[hero.weapon], hero.shotsonscreen);

	PA_OutputText(1,0,18,"%c2EP:%c0 %d   ", hero.exp);
	PA_OutputText(1,0,19,"%c2lvl:%c0 %d   ", game.level);
	
	PA_OutputText(1,0,21,"a1:  %d     a2:  %d ", debug.a1, debug.a2);
	
	PA_OutputText(1,0,22,"Debug mode: General Info            ");
}

void ShowData(){
	u8 y=0;
	u8 x=0;
	u16 a;
	for(a=0;y<23;a++){
		PA_OutputText(1,x,y,"%d%c2,%c0", data.preview[a]);
		x+=4;
		if(x>28){x=0;y++;}
	}
	
	PA_OutputText(1,0,22,"Debug mode: Show Save Data         ");
}

void BossDebug(){
	u8 i=boss.sprite;
	u8 z=boss.part;
	
	PA_OutputText(1,0,0,"%c7Boss:");
	PA_OutputText(1,0,1,"%c2xy:%c0 %d, %d  ", sprites[i].x>>8, sprites[i].y>>8);
	PA_OutputText(1,0,2,"%c2tiles xy:%c0 %d,%d    ", sprites[i].x>>11, sprites[i].y>>11);
	PA_OutputText(1,0,3,"%c2vy:%c0 %d   %c2vx:%c0 %d   %c2flip:%c0 %d ", sprites[i].vy, sprites[i].vx, sprites[i].flip);
	PA_OutputText(1,0,4,"%c2action:%c0 %d  %c2movc:%c0 %d   ", boss.action, boss.movcounter);
	PA_OutputText(1,0,5,"%c2shotc:%c0 %d   ",boss.shootcounter);
	
	PA_OutputText(1,0,7,"%c2angle:%c0 %d  %c2part:%c0 %d  ", sprites[i].shootangle, sprites[z].shootangle);
	PA_OutputText(1,0,22,"Debug mode: Boss Info");
}

void SoundDebug(){
	u8 i=0;
	u8 a=0;
	for(i=0;i<7;i++){
		if(sound.id[i] == 0)PA_OutputText(1,0,a,"Channel %d: free:  ", i);
		else PA_OutputText(1,0,a,"Channel %d: %d,counter %d", i, sound.id[i],sound.counter[i]);
		a++;
	}
	
	PA_OutputText(1,0,22,"Debug mode: Sound Debug");
}

void RotDebug(){
	u8 i=0;
	u8 a=0;
	for(i=0;i<32;i++){
		PA_OutputText(1,0,a,"%c1Rot%c0 %d - %c2free:%c0 %d", i, game.freerot[i]);
		a++;
	}
	PA_OutputText(1,0,22,"Debug mode: Free Rot");
}

void TeleportDebug(){
	u8 i=0;
	u8 a=0;
	for(i=0;i<5;i++){
		if((teleport[i].x!=0)||(teleport[i].y!=0)){
			PA_OutputText(1,0,a,"%c1Teleport%c0 %d:", i);
			PA_OutputText(1,0,a+1,"%c2X:%c0 %d %c2Y:%c0 %d        ", teleport[i].x,teleport[i].y);
			PA_OutputText(1,0,a+2,"%c2Teleports to Level%c0 %d %c2.  ", teleport[i].level);
			a+=4;
		}
	}
	PA_OutputText(1,0,22,"Debug mode: Teleport Location");
}

void ParticleDebug(){
	u8 i=0;
	u8 a=0;
	for(i=0;i<maxsprites;i++){
		if(sprites[i].free==6){
			PA_OutputText(1,0,a,"%c2Particle%c0 %d:", i);
			PA_OutputText(1,0,a+1,"%c2vy:%c0 %d, %c2vx:%c0 %d  ", sprites[i].vy, sprites[i].vx);
			a+=3;
		}
	}
	PA_OutputText(1,0,22,"Debug mode: Particle Info           ");
}

void RaiseParticleDebug(){
	u8 i=0;
	u8 a=0;
	for(i=0;i<maxsprites;i++){
		if(sprites[i].free==9){
			PA_OutputText(1,0,a,"%c2RPar%c0 %d:", i);
			PA_OutputText(1,0,a+1,"%c2x:%c0 %d, %c2y:%c0 %d    ", sprites[i].x>>8, sprites[i].y>>8);
			a+=3;
		}
	}
	PA_OutputText(1,0,22,"Debug mode: RaiseParticle Info      ");
}

void ItemDebug(){
	u8 i=0;
	u8 a=0;
	for(i=0;i<maxsprites;i++){
		if(sprites[i].free==8){
			PA_OutputText(1,0,a,"%c1Item%c0 %d:", i);
			PA_OutputText(1,0,a+1,"%c2(x,y,xfinal):%c0 %d,%d,%d        ", sprites[i].x>>8,sprites[i].y>>8,(sprites[i].x-hero.scrollx)>>8);
			PA_OutputText(1,0,a+2,"%c2tiles (x,y):%c0 %d,%d  ", sprites[i].x>>11, sprites[i].y>>11);
			a+=5;
		}
	}
	PA_OutputText(1,0,22,"Debug mode: Item                   ");
}

void SpriteIDDebug(){
	u8 i=0;
	u8 x=0,y=0;
		for(i=0;i<=maxsprites;i++){
			PA_OutputText(1,x,y, "%c2%d:%c0 %d ", i, sprites[i].id);
			x+=10;
			if(x==30){x=0;y++;}
		}
	PA_OutputText(1,0,22,"Debug mode: Sprite ID Debug         ");
}

void CleanText(u8 screen){
	u8 line=0;
	for(line=0;line<23;line++){
		PA_OutputText(screen,0,line,"                                      ");
	}
}

void AvailableSpriteDebug(){
	u8 i=0;
	u8 x=0,y=0;
		for(i=0;i<=maxsprites;i++){
			PA_OutputText(1,x,y, "%c2t%d:%c0 %d ", i, sprites[i].free);
			x+=10;
			if(x==30){x=0;y++;}
		}
	PA_OutputText(1,0,22,"Debug mode: Available Sprite         ");
}

void CollisionDebug(){
	u8 cx=0,cy=0;
	
	//escribiendo mapa normal
	while(cy<32){
		if((game.levelmap[(cy<<7)+((hero.scrollx>>8)>>3)+cx]) == 0)PA_OutputText(1,cx,cy, "%c3%d", game.levelmap[(cy<<7)+((hero.scrollx>>8)>>3)+cx]);
		else PA_OutputText(1,cx,cy, "%d", game.levelmap[(cy<<7)+((hero.scrollx>>8)>>3)+cx]);
		cx++;
		if(cx==32){
			cx=0;
			cy++;
		}
	}
	
	//poniendo donde esta el tio
	cy=0;
	cx=0;
	while(cy<4){
		PA_OutputText(1,((hero.x-hero.scrollx)>>11)+cx+1,(hero.y>>11)+cy,"%c1X");
		cx++;
		if(cx==2){cy++;cx=0;}
	}
	
	PA_OutputText(1,0,22,"Debug mode: Map collision 1         ");
}

void CheckEventDebug(){
	u8 i=0;
	u8 a=0;
	for(i=0;i<=game.totalevents;i++){
		PA_OutputText(1,0,i,"%c2type:%c0 %d, %c2x:%c0 %d %c2y:%c0 %d %c2id:%c0 %d %c2S:%c0 %d ", game.levelevent[mapinfo + a],game.levelevent[mapinfo + a + 1],game.levelevent[mapinfo + a + 2],game.levelevent[mapinfo + a + 3], events[i].shown);
		a+=4;
	}
	PA_OutputText(1,0,22,"Debug mode: next Event                  ");
}

void MonsterDebug(){
	u8 i=0;
	u8 a=0;
	for(i=0;i<maxsprites;i++){
		if(sprites[i].free==3){
			PA_OutputText(1,0,a,"%c1Monster%c0 %d:", i);
			PA_OutputText(1,0,a+1,"%c2(x,y,xfinal):%c0 %d,%d,%d        ", sprites[i].x>>8,sprites[i].y>>8,(sprites[i].x-hero.scrollx)>>8);
			PA_OutputText(1,0,a+2,"%c2tiles (x,y):%c0 %d,%d  %c2flip:%c0 %d  ", sprites[i].x>>11, sprites[i].y>>11,sprites[i].flip);
			PA_OutputText(1,0,a+3,"%c2HP:%c0 %d  %c2ID:%c0 %d  %c2event:%c0 %d  ", sprites[i].hp,sprites[i].id,sprites[i].event);
			PA_OutputText(1,0,a+4,"%c2angle:%c0 %d ", sprites[i].shootangle);
			a+=5;
		}
	}
	PA_OutputText(1,0,22,"Debug mode: Monster Info            ");
}

void ShootDebug(){
	u8 i=0;
	u8 a=0;
	for(i=0;i<maxsprites;i++){
		if(sprites[i].free==2){
			PA_OutputText(1,0,a,"%c1Shoot %c0%d:", i);
			PA_OutputText(1,0,a+1,"%c2(x,y,xfinal):%c0 %d,%d,%d        ", sprites[i].x>>8,sprites[i].y>>8,(sprites[i].x-hero.scrollx)>>8);
			PA_OutputText(1,0,a+2,"%c2tiles (x,y):%c0 %d,%d  %c2flip:%c0 %d  ", sprites[i].x>>11, sprites[i].y>>11,sprites[i].flip);
			PA_OutputText(1,0,a+3,"%c2ID:%c0 %d  %c2vx,vy:%c0 %d,%d", sprites[i].id,sprites[i].vx,sprites[i].vy,sprites[i].rot);
			PA_OutputText(1,0,a+4,"%c2rot:%c0 %d %c2angle:%c0 %d", sprites[i].rot, sprites[i].rotangle);
			a+=5;
		}
	}
	PA_OutputText(1,0,22,"Debug mode: Shoot Info              ");
}

void ErrorScreen(){
	u8 a=0;
	CleanText(1);
	
	PA_OutputText(1,0,1,"%c1Error%c0 %d%c1!!%c0", debug.error);
	
	switch(debug.error){
		case 1://error 0: no free sprite slot
			PA_OutputText(1,0,3,"%c2Not any free %c1Sprites%c2 slots available%c0", debug.error);
			break;
		case 2://error 1: no free rotation slot
			PA_OutputText(1,0,3,"%c2Not any free %c1Rotation%c2 slots available%c0", debug.error);
			break;
		case 3://no screen selected
			PA_OutputText(1,0,3,"%c2Error! There is no game screen found, Press Start to go to Title Screen");
			while(!Pad.Newpress.Start){
				PA_WaitForVBL();
			}
			debug.error = 0;
			game.screen = TITLE_SCREEN;
			return;
		case 4://Level not found
			PA_OutputText(1,0,3,"Level %c2%d%c0 not found", game.level);
			break;
		default:
			PA_OutputText(1,0,3,"Unknown Error", debug.error);
			break;
	}
	
	PA_OutputText(1,0,10,"Commands: ");
	PA_OutputText(1,0,11,"  %c2Start%c0 - go to Debug Mode ");
	PA_OutputText(1,0,12,"  %c2Select%c0 - go to Main screen");
	PA_OutputText(1,0,13,"  %c2any other key%c0 - continue");
	
	debug.error = 0;
	
	while(a==0){
		if(Pad.Newpress.Start)a = 1;
		else if(Pad.Newpress.Select) a = 2;
		else if((Pad.Newpress.A)||(Pad.Newpress.B)||(Pad.Newpress.X)||(Pad.Newpress.Y)||(Pad.Newpress.X)
				||(Pad.Newpress.R)||(Pad.Newpress.L)||(Pad.Newpress.Left)||(Pad.Newpress.Down)
				||(Pad.Newpress.Right)||(Pad.Newpress.Up))a = 3;
		
		PA_WaitForVBL();
	}
	//--small pause
	Wait(10);		
	//--small pause ends
	
	switch(a){
		case 1://debug
			while(Pad.Newpress.Start==0){
				Debug();
				PA_WaitForVBL();
			}
			break;
		case 2://go to main screen
			game.screen = TITLE_SCREEN;
			break;
		case 3://continue
			break;
	}
}
