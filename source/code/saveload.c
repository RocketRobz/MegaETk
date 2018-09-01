void UpdateData(){
	u16 a=0;
	u16 b;
	//update data vars
		//weapon ammo & level
		for(b=0;b<TOTAL_WEAPONS;b++){
			data.numshoots[b]=hero.numshoots[b];
			data.ammo[b]=hero.ammo[b];
			data.maxammo[b]=hero.maxammo[b];
		}
		//hp, ep...
		data.hp = hero.hp;
		data.maxhp = hero.maxhp;
		data.incammo = hero.incammo;
		data.exp = hero.totalexp;
		data.timeplayed = game.totaltime;
		
		if(data.skills[0]==1)hero.speedinc = SKILL_SPEED_INC;
		if(data.skills[1]==1)hero.jumppower = defaultJUMPPOWER + SKILL_JUMP_INC;
		else hero.jumppower = defaultJUMPPOWER;
		
	//---------------------
	
	//levels unlocked
	for(b=0;b<MENULVLTOTAL;b++){
		data.preview[a] = data.unlocked[b];
		a++;
	}
	
	
	//special items unlocked on level
	for(b=0;b<TOTAL_LEVELS;b++){
		data.preview[a] = data.specialitems[b];
		a++;
	}

	data.preview[a] = data.hp;
	a++;
	data.preview[a] = data.maxhp;
	a++;
	data.preview[a] = data.incammo;
	a++;

	for(b=0;b<TOTAL_WEAPONS;b++){
		data.preview[a] = data.numshoots[b];
		a++;
		data.preview[a] = data.ammo[b];
		a++;
		if((b>1)&&(data.maxammo[b]>0))data.preview[a] = defaultAMMO;
		else data.preview[a] = data.maxammo[b];
		a++;
	}
	
	data.preview[a] = data.exp/10;
	a++;
	
	//skills
	for(b=0;b<10;b++){
		data.preview[a] = data.skills[b];
		a++;
	}
	
	//extra items
	for(b=0;b<5;b++){
		data.preview[a] = data.extras[b];
		a++;
	}
	
	//shop items bought
	for(b=0;b<22;b++){
		data.preview[a] = data.shop[b];
		a++;
	}
	
	//shop items unlocked
	for(b=0;b<22;b++){
		data.preview[a] = data.shop_unlocked[b];
		a++;
	}
	
	data.preview[a] = data.mode;
	a++;
	
	data.preview[a] = data.timeplayed;
	a++;
	
	//decir k a acabauuu
	data.preview[a] = 1234;
	a++;
	data.preview[a] = 8765;
	a++;
	data.lenght = a;
}

void UpdateDataLoaded(){
	u8 a=0,b=0;
	
	//unlocked levels
	for(b=0;b<MENULVLTOTAL;b++){
		data.unlocked[b] = data.preview[a];
		a++;
	}
	
	//special items unlocked on level
	for(b=0;b<TOTAL_LEVELS;b++){
		data.specialitems[b] = data.preview[a];
		a++;
	}

	data.hp = data.preview[a];
	a++;
	
	data.maxhp = data.preview[a];
	a++;
	
	data.incammo = data.preview[a];
	a++;

	for(b=0;b<TOTAL_WEAPONS;b++){
		data.numshoots[b] = data.preview[a];
		a++;
		data.ammo[b] = data.preview[a];
		a++;
		data.maxammo[b] = data.preview[a];
		if((b>1)&&(data.maxammo[b]==defaultAMMO))data.maxammo[b] += data.incammo;
		a++;
	}
	
	data.exp = data.preview[a]*10;
	a++;
	
	//skills
	for(b=0;b<10;b++){
		data.skills[b] = data.preview[a];
		a++;
	}
	
	//extra items
	for(b=0;b<5;b++){
		data.extras[b] = data.preview[a];
		a++;
	}
	
	//shop items bought
	for(b=0;b<22;b++){
		data.shop[b] = data.preview[a];
		a++;
	}
	
	//shop items unlocked
	for(b=0;b<22;b++){
		data.shop_unlocked[b] = data.preview[a];
		a++;
	}
	
	data.mode = data.preview[a];
	a++;
	
	data.timeplayed = data.preview[a];
	a++;
	
	//decir k a acabauuu
	if((data.preview[a] == 1234)&&(data.preview[a+1] == 8765)){
		//acabo :)
		game.data_ok = 1;
		//PA_OutputText(1,COMMENT_X,COMMENT_Y,"Data Read OK      ");
	}
	else{
		game.data_ok = 2;
		//PA_OutputText(1,COMMENT_X,COMMENT_Y-1,"Error: Data file is broken ");
	}
	
	
	//update hero vars
			//weapon ammo & level
			for(a=0;a<TOTAL_WEAPONS;a++){
				hero.numshoots[a] = data.numshoots[a];
				hero.ammo[a] = data.ammo[a];
				hero.maxammo[a] = data.maxammo[a];
			}
			//hp, ep...
			hero.hp = data.hp;
			hero.maxhp = data.maxhp;
			hero.totalexp = data.exp;
			game.totaltime = data.timeplayed;
		//---------------------
		hero.lives = 3;
		hero.weapon = 1;
		hero.incammo = data.incammo;
		sprites[0].shootangle = 0;
		hero.autorun = 1;
		Updateincammo();
		
		if(data.skills[0]==1)hero.speedinc = SKILL_SPEED_INC;
		if(data.skills[1]==1)hero.jumppower = defaultJUMPPOWER + SKILL_JUMP_INC;
		else hero.jumppower = defaultJUMPPOWER;
	//--------------------------------
}
void SaveData(){
	//bool system_file;
	//char buffer[32] = { 0 };
	file = 0;
	
	if(FAT_ENABLED){
		if (FAT_InitFiles()==false){PA_OutputText(1,COMMENT_X,COMMENT_Y,"Error. No device found  ");
		}else{
			//system ok
			switch(game.slot){
				case 0:
					file=FAT_fopen("/METK1.SAV","w");
					break;
				case 1:
					file=FAT_fopen("/METK2.SAV","w");
					break;
				case 2:
					file=FAT_fopen("/METK3.SAV","w");
					break;
				default:
					break;
			}
			//encrypt data
			//ConvertSave(data.preview, 500);
			
			// check fp: if (!fp) then error
			if(file!=0){
				FAT_fwrite(&data.preview, sizeof(u32), 500, file); //write 3 integer from adress buf
				FAT_fclose(file);
				PA_OutputText(1,COMMENT_X,COMMENT_Y,"Save Complete!                   ");
				
			}
			else PA_OutputText(1,COMMENT_X,COMMENT_Y,"Error. Save file not found         ");
		}
	}
	else PA_OutputText(1,COMMENT_X,COMMENT_Y,"FAT disabled.");
}

void LoadData(){
	CleanText(1);
	file = 0;
	u8 loadmsg=0;
	PA_OutputText(1,COMMENT_X,COMMENT_Y,"Reading files...  ");
	
	if(FAT_ENABLED){
		if (FAT_InitFiles()==false){PA_OutputText(1,COMMENT_X,COMMENT_Y,"Error. No device found  ");
		}else{
			PA_OutputText(1,COMMENT_X,COMMENT_Y,"Loading..      ");
			switch(game.slot){
				case 0:
					file=FAT_fopen("/METK1.SAV","r");
					break;
				case 1:
					file=FAT_fopen("/METK2.SAV","r");
					break;
				case 2:
					file=FAT_fopen("/METK3.SAV","r");
					break;
				default:
					break;
			}
			if(file!=0){
				FAT_fread(&data.preview, sizeof(u32), 500,file);
				FAT_fclose(file);
	
				//file read ok! decrypting..
				loadmsg = 0; //ConvertLoad(data.preview, 500); (Removed encrytion/decryption for public release)
				
				switch(loadmsg){
					case 0:
						UpdateDataLoaded();
						PA_OutputText(1,COMMENT_X,COMMENT_Y,"Load Successful!        ");
						break;
					case 1:
						PA_OutputText(1,COMMENT_X,COMMENT_Y,"Error! Saved data is broken!     ");
						game.screen = TITLE_SCREEN;
						break;
					case 2:
						PA_OutputText(1,COMMENT_X,COMMENT_Y,"Save file not compatible,     ");
						PA_OutputText(1,COMMENT_X,COMMENT_Y+1,"The version of the save you   ");
						PA_OutputText(1,COMMENT_X,COMMENT_Y+2,"are trying to read is older    ");
						PA_OutputText(1,COMMENT_X,COMMENT_Y+2,"than the current version.      ");
						game.screen = TITLE_SCREEN;
						break;
					case 3:
						PA_OutputText(1,COMMENT_X,COMMENT_Y,"Save file not compatible,     ");
						PA_OutputText(1,COMMENT_X,COMMENT_Y+1,"Please check for an updated   ");
						PA_OutputText(1,COMMENT_X,COMMENT_Y+2,"MegaETk version.               ");
						game.screen = TITLE_SCREEN;
						break;
				}
				if(loadmsg==1){
					PA_OutputText(1,COMMENT_X,COMMENT_Y,"Error! Saved data is broken!     ");
					game.screen = TITLE_SCREEN;
				}
			}
			else PA_OutputText(1,COMMENT_X,COMMENT_Y,"Can't Read file         ");
		}
	}
	else PA_OutputText(1,COMMENT_X,COMMENT_Y,"FAT disabled ");
}
void LoadGame(){
	GotoSelectSlot();
	if((game.slot>=0)&&(game.slot<3)){
		LoadData();
		//LoadMenu();
	}
	else game.screen = TITLE_SCREEN;
}
//-------
void ResetGameVars(){
	u16 b;
	ResetShopValues();
	//reset hero and data values..
	hero.speedinc=0;
	hero.jumppower=0;
	hero.doublejump=0;
	hero.dash=0;
	hero.highjump=0;
	hero.higherjump=0;
	hero.jumppressed=0;
	hero.autorun=1;
	hero.crouch=0;
	hero.manual_aim=0;
	hero.monster_aimed=0;
	hero.updatemonsterdata=0;
	
	hero.hp=0;
	hero.maxhp=0;
	hero.weapon=0;
	for(b=0;b<TOTAL_WEAPONS;b++){
		hero.numshoots[b] = 0;
		hero.maxammo[b] = 0;
		hero.ammo[b] = 0;
	}
	
	hero.lives=0;
	hero.exp=0;
	hero.totalexp=0;
	hero.incammo=0;
	game.level=0;
	game.time=0;
	game.timecounter=0;
	
	for(b=0;b<MENULVLTOTAL;b++){
		data.unlocked[b]=0;
	}
	
	for(b=0;b<TOTAL_LEVELS;b++){
		data.specialitems[b]=0;
	}
	
	for(b=0;b<TOTAL_WEAPONS;b++){
		data.numshoots[b]=0;
		data.ammo[b]=0;
		data.maxammo[b]=0;
		
		hero.numshoots[b]=0;
		hero.ammo[b]=0;
		hero.maxammo[b]=0;
	}
	
	for(b=0;b<5;b++){
		data.extras[b]=0;
	}
	
	for(b=0;b<10;b++){
		data.skills[b]=0;
	}
	
	data.exp = 0;
	data.timeplayed=0;
	data.lenght=0;
	
	for(b=0;b<500;b++){
		data.preview[b]=0;
	}
}
