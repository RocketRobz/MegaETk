void NewGame(){
	u8 b;
	ResetGameVars();
//setup hero vars
	game.maxshots = 0;
	game.level = 1;
	game.totaltime = 0;
	hero.totalexp = 0;
	
	hero.incammo = 0;
	hero.weapon = 0;
	sprites[0].shootangle = 0;
	
	if(data.mode==0){
		hero.lives = 5;
		hero.totalexp = 5000;
	}
	else if(data.mode==1){
		hero.lives = 2;
		hero.totalexp = 2000;
	}
	else if(data.mode==2){
		hero.lives = 0;
		hero.totalexp = 0;
	}
	
	hero.maxhp = HERO_HP;
	hero.hp = HERO_HP;

	hero.jumppower = defaultJUMPPOWER;
	
	hero.numshoots[1] = 1;
	hero.maxammo[1] = UNLIMITED_AMMO;
	hero.ammo[1] = UNLIMITED_AMMO;
	
	hero.speedinc = 0;

	ResetShopValues();

//default data values
	u8 a;
	//lock all levels
	for(a=0;a<MENULVLTOTAL;a++){
		data.unlocked[a]=0;	
	}
	data.unlocked[0]=1;	
	
	
	//skills
	for(b=0;b<10;b++){
		data.skills[b] = 0;
	}
	hero.speedinc = 0;
	hero.jumppower = defaultJUMPPOWER;
	
	//extras
	for(b=0;b<5;b++){
		data.extras[b] = 0;
	}
	
	
	//shop items bought
	for(b=0;b<22;b++){
		data.shop[b] = 0;
	}
	
	//weapon ammo & level
	for(a=0;a<TOTAL_WEAPONS;a++){
		data.numshoots[a]=hero.numshoots[a];
		data.ammo[a]=hero.ammo[a];
		data.maxammo[a]=hero.maxammo[a];
	}
	//hp, ep...
	data.hp = hero.hp;
	data.maxhp = hero.maxhp;
	data.incammo = 0;
	data.exp = hero.totalexp;
	data.timeplayed = game.totaltime;
	data.lenght = 0;
	
	Updateincammo();
	hero.weapon=1;
	
	//enable dash and crouch
	data.skills[2]=1;
	data.skills[3]=1;
	
	
//-------------------------
//DEBUGGGGGGGGGGGGGGGGG
	if(UNLOCK_ALL){
		hero.totalexp = 500000;
		
		hero.maxhp += 24;
		
		hero.speedinc = SKILL_SPEED_INC;
		data.skills[0]=1;
		hero.jumppower = defaultJUMPPOWER + SKILL_JUMP_INC;
		data.skills[1]=1;
		data.skills[2]=1;
		data.skills[3]=1;
		data.skills[4]=1;
		data.skills[5]=1;
		data.skills[6]=1;
		data.skills[7]=1;
		//data.skills[8]=1;
		//data.skills[9]=1;
		data.extras[0] = 1;
		data.extras[1] = 1;
		
		data.unlocked[12]=1;
		//unlock all levels
		for(a=0;a<MENULVLTOTAL;a++){
			data.unlocked[a]=1;	
		}
	
		//all weaponsz
		hero.incammo = UNLIMITED_AMMO;
		for(b=1;b<9;b++){
			hero.numshoots[b] = 1;
			hero.maxammo[b] = hero.incammo;
			hero.ammo[b] = hero.maxammo[b];
		}
	}
//-------------------------
//-------------------------
}

void ResetShopValues(){
	u8 b;
	for(b=0;b<22;b++){
		data.shop_unlocked[b] = shop_unlocked[b];
		data.shop[b] = 0;
	}
}

void GamePlay(){
	LevelClean();
	//text
	game.teleport=0;
	PA_SetBrightness(0,-31);
	PA_InitCustomText(0,0,font);
	PA_EnableSpecialFx(0,SFX_ALPHA,SFX_BG0,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(0,16,16);
	
	PA_OutputText(0,0,8,"         - Get Ready -         ");
	u8 world = game.level/9 + 1;
	u8 level = game.sl+1;
	u8 stage = game.level - game.sl*3;
	
	PA_OutputText(0,0,10,"            World %d         ", world);
	PA_OutputText(0,0,12,"           Level %d-%d        ", level, stage);
	
	//lives
	PA_LoadSpritePal(0,HERO_PAL,(void*)player_Pal);
	PA_CreateSprite(0,0,(void*)player_head_Sprite,OBJ_SIZE_16X16,1,0,88,115);
	PA_OutputText(0,14,15,"= %d", hero.lives);
	
	FadeOut(4);
	if(stage==1)Wait(100);
	else Wait(40);
	FadeIn(3);
	
	
	Load_Level(game.level); //load level	
	
	//PA_InitText(1,0);//debugu
	
	game.timecounter=0;
	hero.doublejump = 0;
	game.disable_outscreen=0;
	
	game.die=0;
	UpdateScroll();
	
	
	//check if final boss level
	if(game.level==41){
		LoadBoss();
		FadeOut(1);
	}
	else FadeOut(4);
	
	//god mode
	if(GODMODE==1){
		hero.lives=9;
		hero.incammo = UNLIMITED_AMMO - defaultAMMO;
		Updateincammo();
	}//god mode
	
	while(game.die==0){//start game
		//god mode
		if(GODMODE==1){
			hero.candoublejump=1;
			hero.doublejump=1;
		}//god mode
	
	
		game.timecounter++;
		
		MoveHero();
		UpdateScroll();
		
		UseWeapon();
		
		CheckEvents();//check if there's any monster or item to be shown
		CheckStats();//check hero status, options changes etc..
		CheckTeleport();
		
		SpriteActions();//do all sprite actions
		
		UpdateHeroSprites();
		Stylus_Actions();
		
		
		if(boss.loaded)BossActions();
		
		UpdateSoundVars();
		UpdateStatusScreen();//update screen status (TOP SCREEN)
		UpdateStats();//update status on screen
		if(data.extras[0])UpdateMapDots();
		
		//UpdateXY();//UPDATE ALL SPRITES COORDINATES
		//updatexy quitado para ahorrar un for(0-127), se hace ahora en spriteactions..
		//-----------------------------------------------
		//COSAS RARAS (TEMP)
		/*
		if((Pad.Newpress.Up)&&(Pad.Held.Select)){
			hero.x=744<<8;
			hero.y=100<<8;
		}
		*/
		//-----------------------------------------------
		
		//starto
		if(Pad.Newpress.Start)Pause();	//si pausa, no sale de aqui hasta despausaz
		//---------------------------------
		
		//Debug();
		if((debug.disableerror==0)&&(debug.error!=0))ErrorScreen();
		
		//LoopMod();
		PA_WaitForVBL();
	}
	game.totaltime += game.timecounter/60;
	
	//HERO DIES
	if(game.die==1){
		Hero_Die();
		Wait(50);
		if(hero.lives<0){game.screen = GAME_MENU;FadeIn(2);}
		else FadeIn(4);
		hero.hp=hero.maxhp;
	}
	//HERO TELEPORTS		
	else if(game.die==2){
		//desbloquea stage (si desbloquea)
		if((game.levelevent[LEVELDATA_TYPE]==NORMAL_END_LEVEL)||(game.levelevent[LEVELDATA_TYPE]==BOSS_LEVEL))data.unlocked[level_unlocks_stage[game.level]]=1;
		//------------------
		
		game.level = game.teleport;
		//ahora ir a donde toque
		if(game.levelcomplete==1)LevelComplete();
		else FadeIn(4);
	}
	else FadeIn(4);//level ends
}
