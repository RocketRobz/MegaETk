//splash
void GotoSplash(){
	PA_LoadTiledBg(0,0,etk);
	FadeOutScreen(1,0);
	Wait(40);
	PA_LoadTiledBg(1,0,neoflash);
	FadeOutScreen(1,1);
	Wait(75);
	FadeIn(1);
}


//---------------------------------GAME TITLE
//------------------------------------------
#define ball_start 16
void GotoTitle(){
	s8 alpha=31;
	s16 alpha2=10;
	u8 counter=0;
	u8 a=0;
	s8 b=0;
	u8 c=0;
	u8 i=0;
	s8 d=-31;//fade in effectt
	
	SetupTitle();
	//top screen
	//SET OTHER SCREEN WITH COMMENT
	CleanScreen(1);
	PA_InitCustomText(1,1,font);
	PA_EnableSpecialFx(1,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(1,16,16);
	
	PA_LoadTiledBg(1,3,menu_bg);
	PA_OutputText(1,0,10,"                                ");
	PA_OutputText(1,0,10,"                                ");
	//-----------
	
	ResetGameVars();
	
	PA_SetSFXAlpha(0,31,0);
	while(game.screen==TITLE_SCREEN){
		//fade in till done
		if((d>>2)<0){
			PA_SetBrightness(0,d>>2);
			PA_SetBrightness(1,d>>2);
			d+=1;
		}
		//BG EFFECT------------------
			counter++;
			if(counter==2){
				a++;
				if(a<20)b=70;
				else if(a<30)b=40;
				else if(a<45)b=20;
				else{
					a = 0;
					if(c==0)c = 1;
					else c=0;
				}
				
				if(c==0)alpha2+=b;
				else alpha2-=b;
				
				if((alpha2>>7)<2)alpha2=2<<7;
				if((alpha2>>7)>16)alpha2=16<<7;
				PA_SetSFXAlpha(0,alpha,alpha2>>7);
				
				/*PA_OutputText(1,0,0,"%c2alpha:%c0 %d       ", alpha);
				PA_OutputText(1,0,1,"%c2alpha2:%c0 %d      ", alpha2);
				PA_OutputText(1,0,2,"%c2alpha2:%c0 %d      ", alpha2>>7);
				*/
				counter=0;
			//ball raise effect
					for(i=ball_start;i<(ball_start+7);i++){
						if(sprites[i].ballraise<5)sprites[i].ballraise=200;
					}
				SpriteActions();
				//UpdateXY();
				UpdateSoundVars();
			//-----------------
			}
		//--------------------------
		if((Pad.Newpress.Down)||(Pad.Newpress.Up))ChangeTitleOption();
		if((Pad.Newpress.A)||(Pad.Newpress.Start))SelectTitleOption();
		PA_WaitForVBL();
	}
}

void SelectTitleOption(){
	switch(game.option_selected){
		case 1:
			PA_StopMod();
			NewSound(huya_sound);
			game.slot = 0;	//set data slot
			FadeIn(8);
			game.screen=GAME_NEWFILE;
			break;
		case 2:
			PA_StopMod();
			NewSound(huya_sound);
			FadeIn(4);
			game.screen = GAME_LOAD;
			break;
		case 3:
			GotoGameCredits();
			break;
		case 4:
			PA_StopMod();
			NewSound(huya_sound);
			game.screen = GAME_EXTRAS;
			FadeIn(4);
			break;
		default:
			break;
	}
}
void ChangeTitleOption(){
	u8 pal[5];
	
	pal[1]=0;
	pal[2]=0;
	pal[3]=0;
	pal[4]=0;
	
	//checking option changed
	if(Pad.Newpress.Down){
		game.option_selected++;
		NewSound(select_sound);
		if(game.option_selected>4)game.option_selected = 1;
	}
	else if(Pad.Newpress.Up){
		game.option_selected--;
		NewSound(select_sound);
		if(game.option_selected<1)game.option_selected = 4;
	}
	//option changed DONE
	pal[game.option_selected] = 1;
	
//changing sprite pal
	//"New Game"
		PA_SetSpritePal(0,0,pal[1]);
		PA_SetSpritePal(0,1,pal[1]);
		PA_SetSpritePal(0,2,pal[1]);
		PA_SetSpritePal(0,3,pal[1]);
		PA_SetSpritePal(0,4,pal[1]);
	//"Continue"
		PA_SetSpritePal(0,5,pal[2]);
		PA_SetSpritePal(0,6,pal[2]);
		PA_SetSpritePal(0,7,pal[2]);
		PA_SetSpritePal(0,8,pal[2]);
	//"Options"
		PA_SetSpritePal(0,9,pal[3]);
		PA_SetSpritePal(0,10,pal[3]);
		PA_SetSpritePal(0,11,pal[3]);
	//"Options"
		PA_SetSpritePal(0,12,pal[4]);
		PA_SetSpritePal(0,13,pal[4]);
		PA_SetSpritePal(0,14,pal[4]);
}
void SetupTitle(){
	u8 i;
	LevelClean();
	
	PA_PlayMod(music_title_mod);
	
	//Wait(5);
	LoadTitleGfx();
	PA_InitText(1,0);
	
	//create 7 sprites.. for ball raise effect
		PA_LoadSpritePal(0,0,(void*)player_Pal);	//effect sprites
		PA_LoadSpritePal(0,EFFECTS_PAL,(void*)effects_Pal);	//effect sprites
		gfx.ballraiseparticle[0] = PA_CreateGfx(0,(void*)effect_ballraise_Sprite,OBJ_SIZE_8X8,1);
		gfx.ballraiseparticle[1] = PA_CreateGfx(0,(void*)effect_ballraise_Sprite+64,OBJ_SIZE_8X8,1);
		gfx.ballraiseparticle[2] = PA_CreateGfx(0,(void*)effect_ballraise_Sprite+128,OBJ_SIZE_8X8,1);
		gfx.ballraiseparticle[3] = PA_CreateGfx(0,(void*)effect_ballraise_Sprite+192,OBJ_SIZE_8X8,1);
		gfx.ballraiseparticle[4] = PA_CreateGfx(0,(void*)effect_ballraise_Sprite+256,OBJ_SIZE_8X8,1);
	
	for(i=ball_start;i<(ball_start+7);i++){
		sprites[i].free = 10;
		sprites[i].x = ((i-ball_start)*40 - 20)<<8;
		sprites[i].y = 150<<8;
		sprites[i].ballraise=200;
		sprites[i].size = 100;
	}
	game.ballraiseprio=2;
	//------------
	
	game.option_selected = 1;
	ChangeTitleOption();
	PA_EnableSpecialFx(0,SFX_ALPHA,SFX_BG2,SFX_BG3);
}
void LoadTitleGfx(){
	u8 i;
	s8 a;//para mover texto un poco (x)
	s8 b;//para mover el texto un poc (y)
	//Load BG 1
	PA_LoadTiledBg(0,1,title_bg1);
	//Load BG 2
	PA_LoadTiledBg(0,2,title_bg2);
	//Load BG 3
	PA_LoadTiledBg(0,3,title_bg3);
	
	//text
	PA_LoadSpritePal(0, 1,(void*)title_text_Pal);	//effect sprites
	
	for(i=0;i<15;i++){
		sprites[i].free = 10;
	}
	i=0;
	
	b=16;//y+b
	
	a=5;
	PA_CreateSprite(0, 0,(void*)title_text_Sprite, OBJ_SIZE_16X16,1,1,88+a,80+b);//Ne
	i++;
	PA_CreateSprite(0, 1,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,104+a,80+b);//ew
	i++;
	PA_CreateSprite(0, 2,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,120+a,80+1+b);//ga
	i++;
	PA_CreateSprite(0, 3,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,136+a,80+b);//m
	i++;
	PA_CreateSprite(0, 4,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,152+a,80+b);//e
	i++;
	
	a=7;
	PA_CreateSprite(0, 5,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,88+a,96+b);//C
	i++;
	PA_CreateSprite(0, 6,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,104+a,96+b);//on
	i++;
	PA_CreateSprite(0, 7,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,120+a,96+b);//tin
	i++;
	PA_CreateSprite(0, 8,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,136+a,96+b);//ue
	i++;
	
	a=16;
	PA_CreateSprite(0, 9,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,88+a,112+b);//Cr
	i++;
	PA_CreateSprite(0, 10,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,104+a,112+b);//ed
	i++;
	PA_CreateSprite(0, 11,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,120+a,112+b);//its
	i++;
	
	a=19;
	PA_CreateSprite(0, 12,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,88+a,128+b);//Ex
	i++;
	PA_CreateSprite(0, 13,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,104+a,128+b);//tra
	i++;
	PA_CreateSprite(0, 14,(void*)title_text_Sprite+256*i, OBJ_SIZE_16X16,1,1,120+a,128+b);//as
}






#define CREDITS_BACK_X 195
#define CREDITS_BACK_Y 166
//credits:
void GotoGameCredits(){
	FadeInScreen(8,1);
	PA_LoadSpritePal(1,1,(void*)buttons_Pal);
	PA_CreateSprite(1,0,(void*)backbutton_Sprite,OBJ_SIZE_64X32,1,1,CREDITS_BACK_X,CREDITS_BACK_Y);
	
	PA_OutputText(1,2,4," Code: ETk                  ");
	PA_OutputText(1,2,6,"  Gfx: ETk                  ");
	PA_OutputText(1,2,8,"Sound: HtheB                ");
	PA_OutputText(1,2,12,"    Special Thanks to:      ");
	PA_OutputText(1,2,14,"Kagisa, Huuf, Carl, dRM    ");
	PA_OutputText(1,2,16,"and other people I may forget ");
	
	FadeOutScreen(6,1);
	u8 a=0;
	while(a==0){
		if(Pad.Newpress.B){
			a=1;
			NewSound(back_sound);
			HideButtonEffect(1,0,CREDITS_BACK_X,CREDITS_BACK_Y);
		}
		SpriteActions();
		UpdateSoundVars();
		PA_WaitForVBL();
	}
	FadeInScreen(8,1);
	CleanText(1);
	FadeOutScreen(8,1);
}

//---------------------------------GAME MENU
//------------------------------------------
#define BAR_SPRITES 19
#define ARROW_X 167
#define ARROW_Y1 50
#define ARROW_Y2 142
#define SLT_X 12
#define SLT_Y 76
#define SLT_W 12
#define SLT_SEPX 48 //separacion X
#define SLT_SEPY 38 //separacion Y

#define SAVEBUTTON_X 190
#define SAVEBUTTON_Y 165

#define EXITBUTTON_X 0
#define EXITBUTTON_Y 165

#define SHOPBUTTON_X 122
#define SHOPBUTTON_Y 165

#define SELECTLEVELBUTTON_X 54
#define SELECTLEVELBUTTON_Y 165


#define SB_width 60
#define SB_height 25

#define COMMENT_X 6
#define COMMENT_Y 10


//scroll counter values---------------
#define SCRC1 30 //1st time to wait  |
#define SCRC2 20 //up down counter   |
#define SCRC3 26 //right left counter|
//------------------------------------

//paletas
//2: FLECHAS
//3: lvl thumbs
//4: BOTONES

//sprites usados en el menu:
//0-19: HP y AMMO
//20-21: Select Level Arrows
//22-27: Level gfx thumbnails
//28: level sel gfx
//29: SAVE BUTTON
//30: SHOP BUTTON
//31: SELECT LEVEL BUTTON
//32: EXIT BUTTON

void GotoMenu(){
//	u8 a=16,b=16;
	u8 c=0;
	u8 changed=0;
	
	//keys counter
	u16 right=0;
	u16 left=0;
	u16 up=0;
	u16 down=0;
	//-----------
	
	//Wait(10);
	PA_WaitForVBL();
	LoadMenu();
	game.stopcheck=0;
	
	FadeOut(8);
	while(game.screen==GAME_MENU){
		game.stopcheck=0;
		changed=0;
		ScrollLevelSelect();
		CheckSelectLevelButtons();
		UpdateSelectLevel();
		
		//acciones de teclas
			//cambia weapon :?
			if(Pad.Newpress.R==1){
				while(c==0){
					hero.weapon++;
					if(hero.weapon == TOTAL_WEAPONS)hero.weapon = 0;
					if(hero.maxammo[hero.weapon] > 0)c=1;
				}
				//cambiada.. actualizando barras
				UpdateHPAPBar();
				c = 0;
			}
			
			//seleccionar nivel sin stylus
			if((Pad.Newpress.Left)||left>SCRC1){
				if(left>SCRC3)left=SCRC3;
				if(game.sl>0){
					game.sl--;
					changed=1;
				}
			}
			if((Pad.Newpress.Right)||right>SCRC1){
				if(right>SCRC3)right=SCRC3;
				if(game.sl<MENULVLTOTAL-1){
					game.sl++;
					changed=1;
				}
			}
			if((Pad.Newpress.Up)||up>SCRC1){
				if(up>SCRC2)up=SCRC2;
				if(game.sl>2){
					game.sl-=3;
					changed=1;
				}
			}
			if((Pad.Newpress.Down)||down>SCRC1){
				if(down>SCRC2)down=SCRC2;
				game.sl+=3;
				if(game.sl>MENULVLTOTAL-1)game.sl=MENULVLTOTAL-1;
				changed=1;
			}
			
			
			if(Pad.Held.Right)right++;
			else right=0;
			if(Pad.Held.Left)left++;
			else left=0;
			if(Pad.Held.Up)up++;
			else up=0;
			if(Pad.Held.Down)down++;
			else down=0;
			
		//---------
		
		if(changed){
			NewSound(select_sound);
			while((game.sl - game.sl_row*3)<0){
					game.sl_row--;
				}
				while((game.sl - game.sl_row*3)>5){
					game.sl_row++;
				}				
				UpdateLvlThumb();
				UpdateSelectedLvlGFX();		
		}
		
		
		//debugging
			/*alpha debuggzzz
			if((Pad.Held.Up)&&b<31)b++;
			if((Pad.Held.Down)&&b>0)b--;
			if((Pad.Held.Right)&&a<31)a++;
			if((Pad.Held.Left)&&a>0)a--;
			PA_SetSFXAlpha(0,a,b);
			//Debug();
			PA_OutputText(1,0,0,"%c2row%c0 %d %c2sl%c0 %d ", game.sl_row, game.sl);
			PA_OutputText(1,0,1,"%c2held%c0 %d %c2cnt%c0 %d  ", game.arrow_held, game.arrow_held_counter);
			
			PA_OutputText(1,0,3,"%c2up%c0 %d  ", up);
			PA_OutputText(1,0,4,"%c2down%c0 %d  ", down);
			PA_OutputText(1,0,5,"%c2left%c0 %d  ", left);
			PA_OutputText(1,0,6,"%c2right%c0 %d  ", right);*/
		//---------------
		if((Pad.Newpress.A)&&(!game.stopcheck))SelectLevel();
		
		//if(Pad.Newpress.X)game.screen = GAME_SHOP;//TEMPPPPPPPPP <<<<<<<<<<<<<<<<<<<<<<<<<<<<
		
		UpdateSoundVars();
		PA_WaitForVBL();
	}
}

void LoadMenu(){
	LevelClean();
	
	PA_ResetBgSys();
	PA_ResetSpriteSys();
		
	//top screen
	//SET OTHER SCREEN WITH COMMENT
	CleanScreen(1);
	PA_InitCustomText(1,1,font);
	PA_EnableSpecialFx(1,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(1,16,16);
	
	PA_LoadTiledBg(1,3,menu_bg);
	PA_OutputText(1,0,10,"                                ");
	//-----------
	
	
	
	PA_PlayMod(music_selectlevel_mod);
	
	PA_LoadTiledBg(0,3,menu_bg);
	PA_LoadTiledBg(0,2,menu_bgd);
	PA_InitCustomText(0,1,font);
	
	//game.sl = game.level-1;
	
//TEXTO----
	//equipo y tal
	if(data.skills[8])PA_OutputText(0,25,9,"M-BODY");
	else PA_OutputText(0,25,9,"BODY ");
	
	if(data.skills[9])PA_OutputText(0,25,11,"M-ARM  ");
	else PA_OutputText(0,25,11,"ARM ");
	
	PA_OutputText(0,25,13,"HP %d",data.shop[0]+data.shop[1]+data.shop[2]+data.shop[3]+data.shop[4]+data.shop[5]);
	
	if(data.skills[16])PA_OutputText(0,25,15,"AIMER");
	else PA_OutputText(0,25,15,"----");
	
	if(data.skills[17])PA_OutputText(0,25,17,"D-JUMP");
	else PA_OutputText(0,25,17,"----");
	//-----------
	
	//EP
	PA_OutputText(0,5,2,"%d      ", hero.totalexp);
	
	
	//Select Level txt..
	PA_OutputText(0,3,7,"Select Level...");
//-------------
	PA_EnableSpecialFx(0,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(0,16,16);
	
//SPRITES
	UpdateHPAPBar();
	
	//creando lvlthumbs
	u16 x=0;
	u16 y=0;
	u8 i;
	
	PA_LoadSpritePal(0,3,(void*)lvl_Pal);
	for(i=22;i<=27;i++){
		PA_CreateSprite(0,i,(void*)lvlthumb_Sprite,OBJ_SIZE_64X32,1,3,SLT_X + x,SLT_Y + y);
		PA_SetSpritePrio(0,i,1);
		if(x==SLT_SEPX<<1){
			y+=SLT_SEPY;
			x=0;
		}
		else x+=SLT_SEPX;
	}
	//sprite de seleccionado
	PA_CreateSprite(0,28,(void*)lvlsel_Sprite,OBJ_SIZE_64X32,1,3,SLT_X,SLT_Y);
	PA_SetSpritePrio(0,28,0);
	
	UpdateLvlThumb();
	
	
	//flechas
	PA_LoadSpritePal(0,2,(void*)arrow_Pal);
	PA_CreateSprite(0,20,(void*)arrow_Sprite,OBJ_SIZE_16X16,1,2,ARROW_X,ARROW_Y1);//flecha de arriba
	PA_CreateSprite(0,21,(void*)arrow_Sprite,OBJ_SIZE_16X16,1,2,ARROW_X,ARROW_Y2);//flecha de abajo
	PA_SetSpriteVflip(0, 21, 1);
	//-----
	
	//BOTONES
	PA_LoadSpritePal(0,4,(void*)buttons_Pal);
		PA_CreateSprite(0,29,(void*)savebutton_Sprite,OBJ_SIZE_64X32,1,4,SAVEBUTTON_X,SAVEBUTTON_Y);
		PA_CreateSprite(0,30,(void*)shopbutton_Sprite,OBJ_SIZE_64X32,1,4,SHOPBUTTON_X,SHOPBUTTON_Y);
		PA_CreateSprite(0,31,(void*)selectlevelbutton_Sprite,OBJ_SIZE_64X32,1,4,SELECTLEVELBUTTON_X,SELECTLEVELBUTTON_Y);
		PA_CreateSprite(0,32,(void*)exitbutton_Sprite,OBJ_SIZE_64X32,1,4,EXITBUTTON_X,EXITBUTTON_Y);
		//-----
	
	//poner sprites del 0 a 28 que estan usados
	for(i=0;i<=28;i++){
		sprites[i].free=10;
	}
	
	
	//actualiza scroll y todo mierdas
		while((game.sl - game.sl_row*3)<0){
			game.sl_row--;
		}
		while((game.sl - game.sl_row*3)>5){
			game.sl_row++;
		}				
		UpdateLvlThumb();
		UpdateSelectedLvlGFX();
	//----------------------
}

void UpdateLvlThumb(){
	u8 i;
	u16 a=(game.sl_row*6) + 1;
	
	for(i=22;i<=27;i++){
		if(a>(MENULVLTOTAL*2))PA_SetSpriteAnim(0,i,0);
		else if(data.unlocked[((a-1)>>1)] == 0)PA_SetSpriteAnim(0,i,1);
		else PA_SetSpriteAnim(0,i,menulvl[a]+1);
		a+=2;
	}
}
void UpdateHPAPBar(){
	u8 i=0;
	u16 b=0;
	s16 a=hero.hp;
	u16 max=hero.maxhp;
	u16 x=180,y=12;
	u16 xc=0;
	
	//borrando sprites..
	for(i=0;i<=BAR_SPRITES;i++){
		sprites[i].free=0;
		PA_DeleteSprite(0,i);
	}
	i=0;
	
	//load menu hp bar
	u8 pal=0;
	PA_LoadSpritePal(0,pal,(void*)hp_bar_Pal);
	//-------------------
	
	if(hero.hp==0)hero.hp=1;
	a = hero.hp;

	if(hero.maxhp>64)max=64;
	//HP BAR
		sprites[i].free=10;
		PA_CreateSprite(0,i,(void*)hp_bar_Sprite,OBJ_SIZE_8X8,1,pal,x-8,y);
		PA_SetSpriteAnim(0,i,0);
		i++;
		
		for(b=0;b<(max>>3);b++){
			if(a>8){
				sprites[i].free=10;
				PA_CreateSprite(0,i,(void*)hp_bar_Sprite,OBJ_SIZE_8X8,1,pal,x+xc,y);
				PA_SetSpriteAnim(0,i,2);
				i++;
				a-=8;
				}
			else if((a>0)&&(a<=8)){
				sprites[i].free=10;
				PA_CreateSprite(0,i,(void*)hp_bar_Sprite,OBJ_SIZE_8X8,1,pal,x+xc,y);
				PA_SetSpriteAnim(0,i,10-a);
				i++;
				a=0;
			}
			else if(a==0){
				sprites[i].free=10;
				PA_CreateSprite(0,i,(void*)hp_bar_Sprite,OBJ_SIZE_8X8,1,pal,x+xc,y);
				PA_SetSpriteAnim(0,i,10);
				i++;
			}
			xc+=8;
		}
		sprites[i].free=10;
		PA_CreateSprite(0,i,(void*)hp_bar_Sprite,OBJ_SIZE_8X8,1,pal,x+xc,y);
		PA_SetSpriteAnim(0,i,1);
		i++;
	
	//AMMO BAR
	b=0;
	a=hero.ammo[hero.weapon];
	x=180,y=24;
	xc=0;
	
	pal=1;
	PA_LoadSpritePal(0,pal,(void*)ammo_bar_Pal);
	
	if(hero.maxammo[hero.weapon]>128)max=128;
	
	max>>=1;
	hero.ammo[hero.weapon]>>=1;
	
		sprites[i].free=10;
		PA_CreateSprite(0,i,(void*)ammo_bar_Sprite,OBJ_SIZE_8X8,1,pal,x-8,y);
		PA_SetSpriteAnim(0,i,0);
		i++;
		
		for(b=0;b<(max>>3);b++){
			if(a>8){
				sprites[i].free=10;
				PA_CreateSprite(0,i,(void*)ammo_bar_Sprite,OBJ_SIZE_8X8,1,pal,x+xc,y);
				PA_SetSpriteAnim(0,i,2);
				i++;
				a-=8;
				}
			else if((a>0)&&(a<=8)){
				sprites[i].free=10;
				PA_CreateSprite(0,i,(void*)ammo_bar_Sprite,OBJ_SIZE_8X8,1,pal,x+xc,y);
				PA_SetSpriteAnim(0,i,10-a);
				i++;
				a=0;
			}
			else if(a==0){
				sprites[i].free=10;
				PA_CreateSprite(0,i,(void*)ammo_bar_Sprite,OBJ_SIZE_8X8,1,pal,x+xc,y);
				PA_SetSpriteAnim(0,i,10);
				i++;
			}
			xc+=8;
		}
		sprites[i].free=10;
		PA_CreateSprite(0,i,(void*)ammo_bar_Sprite,OBJ_SIZE_8X8,1,pal,x+xc,y);
		PA_SetSpriteAnim(0,i,1);
		i++;
		
	hero.ammo[hero.weapon]<<=1;
}

void ScrollLevelSelect(){
	//mirar si toca a flecha
	if(Stylus.Held){
		if((Stylus.X>ARROW_X)&&(Stylus.X<ARROW_X+16)){
			//mirar flecha de ARRIBA
			if((Stylus.Y>ARROW_Y1)&&(Stylus.Y<ARROW_Y1+16)&&(game.arrow_held!=2)){
				game.arrow_held = 1;
				game.arrow_held_counter++;
				PA_SetSpriteAnim(0, 20, 1);
			}
			//mirar flecha de ABAJO
			else if((Stylus.Y>ARROW_Y2)&&(Stylus.Y<ARROW_Y2+16)&&(game.arrow_held!=1)){
				game.arrow_held = 2;
				game.arrow_held_counter++;
				PA_SetSpriteAnim(0, 21, 1);
			}
			else{
				game.arrow_held_counter = 0;
				PA_SetSpriteAnim(0, 20, 0);
				PA_SetSpriteAnim(0, 21, 0);	
			}
		}
		else {
			game.arrow_held_counter = 0;
			PA_SetSpriteAnim(0, 20, 0);
			PA_SetSpriteAnim(0, 21, 0);
		}
	}
	else {
		game.arrow_held_counter = 0;
		game.arrow_held = 0;
		PA_SetSpriteAnim(0, 20, 0);
		PA_SetSpriteAnim(0, 21, 0);
	}
	
	//moviendo!
	if((Stylus.Released)||(game.arrow_held_counter>50)||(game.arrow_held_counter==1)){
		game.arrow_held_counter = 30;
		if((game.arrow_held==1)&&(game.sl_row>0)){
			game.sl_row--;
		}
		else if((game.arrow_held==2)&&(game.sl_row<((MENULVLTOTAL/3)-1))){
			game.sl_row++;
		}
		UpdateLvlThumb();
		UpdateSelectedLvlGFX();
	}
}
void SelectLevel(){
	if(data.unlocked[game.sl]==1){
		PA_StopMod();
		NewSound(accept_sound);
		
		HideButtonEffect(0,31,SELECTLEVELBUTTON_X,SELECTLEVELBUTTON_Y);
		
		//recover hp and ammo, and lives
		hero.hp = hero.maxhp;
		if(data.mode==0)hero.lives=5;//easy
		else if(data.mode==1)hero.lives=2;//normal
		else if(data.mode==2)hero.lives=0;//hard
		
		u8 a;
		
		for(a=0;a<TOTAL_WEAPONS;a++){RefreshInfiniteAmmo(a);}
		
		game.level = menulvl[game.sl<<1];
		game.screen = GAME_PLAY;
		sound.startmod=1;
		
		//quitar las imagenes de los otros levels
		for(a=0;a<=5;a++){
			if((PA_GetSpriteX(0,22+a)!=PA_GetSpriteX(0,28))||(PA_GetSpriteY(0,22+a)!=PA_GetSpriteY(0,28))){
				PA_SetSpriteXY(0,22+a,256, 0);
			}
		}
		Wait(10);
		
		FadeIn(4);
		//----------------
	}
}
void UpdateSelectLevel(){
	//select level
	u8 s;
	u16 a=0;
	u8 a1=0;
	u16 b=0;
	u8 b1=0;
	u16 lastsel;
	
	if(Stylus.Newpress){
		for(s=0;s<6;s++){
			if((Stylus.X > (SLT_X + SLT_W + a)) && (Stylus.X < (SLT_X + 64 - SLT_W + a)) && (Stylus.Y > (SLT_Y + b)) && (Stylus.Y < (SLT_Y + 32 + b))){
				lastsel = game.sl;
				game.sl =  game.sl_row*3 + b1*3 + a1;
				
				if(game.sl > MENULVLTOTAL - 1)game.sl = -1;
				if((lastsel==game.sl)&&(game.sl>=0))SelectLevel();//level selected!
				else UpdateSelectedLvlGFX(); //updtae selected lvl gfx
				break;
			}
			a+=SLT_SEPX;
			a1++;
			if(a1==3){a=0;a1=0;b+=SLT_SEPY;b1++;}
		}
	}
	//---
}

void UpdateSelectedLvlGFX(){
	s16 x=0;
	s16 y=0;
	s16 c=0;
	
	c = game.sl - game.sl_row*3;	
	if((c>=0)&&(c<=5)){
		if(c>2){y+=SLT_SEPY;c-=3;}
		x = c * SLT_SEPX;
		PA_SetSpriteXY(0,28,SLT_X + x, SLT_Y + y);
	}
	else PA_SetSpriteXY(0,28,256, 0);	
}



void CheckSelectLevelButtons(){
	if(Stylus.Newpress){
		u16 x;
		u16 y;

		x = SAVEBUTTON_X;
		y = SAVEBUTTON_Y;
		//mirar boton de savelol
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			NewSound(accept_sound);
			//lo a apretao, a salvarr
			PA_SetSpriteAnim(0,29,1);//cambia grafico a apretado
			PA_OutputText(1,COMMENT_X,COMMENT_Y,"Saving...           ");
			Wait(5);
			PA_SetSpriteAnim(0,29,0);
			Wait(3);
			PA_SetSpriteAnim(0,29,1);
			Wait(1);
			PA_SetSpriteAnim(0,29,0);
			
			UpdateData();
			PA_OutputText(1,COMMENT_X,COMMENT_Y,"Writing file...  ");
			SaveData();
			game.stopcheck=1;
		}
		
		//mirar boton de shoplol
		x = SHOPBUTTON_X;
		y = SHOPBUTTON_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			NewSound(accept_sound);
			HideButtonEffect(0,30,x,y);
			
			PA_StopMod();
			game.screen = GAME_SHOP;
			FadeIn(8);
			game.stopcheck=1;
		}
		
		x = SELECTLEVELBUTTON_X;
		y = SELECTLEVELBUTTON_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			SelectLevel();
			game.stopcheck=1;
		}
		
		x = EXITBUTTON_X;
		y = EXITBUTTON_Y;
		if((Stylus.X>x)&&(Stylus.X<x+44)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(back_sound);
			HideButtonEffect(0,32,x,y);
			game.screen = TITLE_SCREEN;
		}
	}
}
//---------------------------------IN-GAME STATUS SCREEN
//------------------------------------------
#define STATUS_HP_X 3
#define STATUS_HP_Y 1
#define STATUS_AP_X 5
#define STATUS_AP_Y 3
#define STATUS_WEAPON_IMG_X 58
#define STATUS_WEAPON_IMG_Y 43


#define STATUS_MONSTER_ID_X 25
#define STATUS_MONSTER_ID_Y 12
#define STATUS_MONSTER_HP_X 25
#define STATUS_MONSTER_HP_Y 14
#define STATUS_MONSTER_SPEED_X 27
#define STATUS_MONSTER_SPEED_Y 16
#define STATUS_MONSTER_EP_X 25
#define STATUS_MONSTER_EP_Y 18
#define STATUS_MONSTER_IMG_X 200
#define STATUS_MONSTER_IMG_Y 156

#define STATUS_TEXT_X 1
#define STATUS_TEXT_Y 22
#define STATUS_TEXT_LINES 10
#define STATUS_TEXT_SEPARACION 2

#define MAP_X 120
#define MAP_Y 16

#define MAPDOTF 50

#define recoverhp 0
#define recoverap 1
#define powerupwsx2 2
#define getdmg 3
#define getep 4
//sprites usados en el menu:
//0-1: map sprites
//2: monster image
//3: monster part image
//4: weapon image
//50-100: map dots

void SetupStatusScreen(){
	CleanScreen(1);
	
	PA_LoadTiledBg(1,3,menu_bggame);
	
	PA_InitCustomText(1,1,font);
	PA_EnableSpecialFx(1,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(1,16,16);
	
	UpdateStatusScreen();
	
	//MAP------------------------
	if(data.extras[0]){
		//crear 3 sprites pa map
		PA_CreateSprite(1,0,(void*)map_Sprite,OBJ_SIZE_64X32,1,0,MAP_X,MAP_Y);
		PA_CreateSprite(1,1,(void*)map_Sprite,OBJ_SIZE_64X32,1,0,MAP_X+64,MAP_Y);
		PA_InitSpriteDraw(1,0);
		PA_InitSpriteDraw(1,1);
		DrawMap();
		
		PA_SetSpritePrio(1,0,1);
		PA_SetSpritePrio(1,1,1);
		
		gfx.mapdot[0] = PA_CreateGfx(1,(void*)map_pointer_Sprite,OBJ_SIZE_8X8,1);
		gfx.mapdot[1] = PA_CreateGfx(1,(void*)map_pointer_Sprite+64,OBJ_SIZE_8X8,1);
		gfx.mapdot[2] = PA_CreateGfx(1,(void*)map_pointer_Sprite+128,OBJ_SIZE_8X8,1);
		gfx.mapdot[3] = PA_CreateGfx(1,(void*)map_pointer_Sprite+192,OBJ_SIZE_8X8,1);
	}
	//-----------------------
	
	//PAL
	PA_LoadSpritePal(1,0,(void*)map_Pal);
	PA_LoadSpritePal(1,1,(void*)monster_Pal);
	PA_LoadSpritePal(1,2,(void*)weaponstatus_Pal);
	PA_LoadSpritePal(1,3,(void*)map_pointer_Pal);
	
	//monster pre
	game.monsterimgloaded = 0;	
	PA_CreateSprite(1,2, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
	PA_CreateSprite(1,3, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
	
	//weapon img
	PA_CreateSprite(1,4, (void*)status_weapon_1_Sprite, OBJ_SIZE_16X8,1,2,STATUS_WEAPON_IMG_X,STATUS_WEAPON_IMG_Y);
}

void UpdateStatusScreen(){
	//HP
	PA_OutputText(1,STATUS_HP_X,STATUS_HP_Y,"%d/%d  ", hero.hp, hero.maxhp);
	//AP
	if(hero.maxammo[hero.weapon]==UNLIMITED_AMMO)PA_OutputText(1,STATUS_AP_X,STATUS_AP_Y,"INFIN.  ");
	else PA_OutputText(1,STATUS_AP_X,STATUS_AP_Y,"%d/%d  ", hero.ammo[hero.weapon], hero.maxammo[hero.weapon]);
	//weapon
	PA_SetSpriteAnim(1,4,hero.weapon);
	
	
	if(data.extras[1]){
		//MONSTER INFO
		if((hero.updatemonsterdata)&&(boss.id!=4)){
			if((hero.updatemonsterdata==1)&&(hero.monster_aimed!=0)&&((sprites[hero.monster_aimed].free==3)||(sprites[hero.monster_aimed].free==4))){
			//MONSUTAH
				//ID
				PA_OutputText(1,STATUS_MONSTER_ID_X,STATUS_MONSTER_ID_Y,"%d     ", sprites[hero.monster_aimed].id);
				
				//HP
				PA_OutputText(1,STATUS_MONSTER_HP_X,STATUS_MONSTER_HP_Y,"%d/%d     ", sprites[hero.monster_aimed].hp, monsterdata[MONSTERDATA_HP + 8 + sprites[hero.monster_aimed].id * MONSTERDATA_TOTAL]);
				
				//SPEED
				PA_OutputText(1,STATUS_MONSTER_SPEED_X,STATUS_MONSTER_SPEED_Y,"%d     ", sprites[hero.monster_aimed].speed>>4);
				
				//EP
				PA_OutputText(1,STATUS_MONSTER_EP_X,STATUS_MONSTER_EP_Y,"%d     ", sprites[hero.monster_aimed].exp);
				
				
				
				if(hero.last_monster_aimed != hero.monster_aimed){
					//SET MONSTER IMG
					if(game.monsterimgloaded==1){
						//PA_StopSpriteAnim(1,2);
						//PA_StopSpriteAnim(1,3);
						PA_SetSpriteXY(1,2,256,0);
						PA_SetSpriteXY(1,3,256,0);
						//PA_DeleteSprite(1,2);
						//PA_DeleteSprite(1,3);
					}
					else game.monsterimgloaded = 1;
					
					switch(sprites[hero.monster_aimed].id){
						case 0:
							PA_CreateSprite(1,2, (void*)monster_0_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							PA_CreateSprite(1,3, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							//PA_StartSpriteAnim(1, 2, 1, 4, 3);
							break;
						case 1:
							PA_CreateSprite(1,2, (void*)monster_1_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							PA_CreateSprite(1,3, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							//PA_StartSpriteAnim(1, 2, 0, 3, 20);
							break;
						case 2:
							PA_CreateSprite(1,2, (void*)monster_2_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							PA_CreateSprite(1,3, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							//PA_StartSpriteAnim(1, 2, 0, 3, 14);
							break;
						case 3:
							PA_CreateSprite(1,2, (void*)monster_3_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							PA_CreateSprite(1,3, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							//PA_StartSpriteAnim(1, 2, 1, 3, 8);
							break;
						case 4:
							PA_CreateSprite(1,2, (void*)monster_4_Sprite, OBJ_SIZE_64X64,1,1,STATUS_MONSTER_IMG_X-16,STATUS_MONSTER_IMG_Y-16);
							PA_CreateSprite(1,3, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							//PA_StartSpriteAnim(1, 2, 0, 4, 7);
							break;
						case 5:
							PA_CreateSprite(1,2, (void*)monster_5_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							PA_CreateSprite(1,3, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							//PA_StartSpriteAnim(1, 2, 0, 3, 20);
							break;
						case 6:
							PA_CreateSprite(1,2, (void*)monster_6_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							PA_SetSpriteAnim(1,2,0);
							PA_CreateSprite(1,3, (void*)monster_6_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X-4,STATUS_MONSTER_IMG_Y-4);
							PA_SetSpriteAnim(1,3,1);
							break;
						case 7:
							PA_CreateSprite(1,2, (void*)monster_7_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							PA_CreateSprite(1,3, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							//PA_StartSpriteAnim(1, 2, 0, 3, 20);
							break;
						case 8:
							PA_CreateSprite(1,2, (void*)monster_8_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							PA_CreateSprite(1,3, (void*)blank_Sprite, OBJ_SIZE_8X8,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
							//PA_StartSpriteAnim(1, 2, 0, 3, 20);
							break;
						default:
							break;
					}
				}
				hero.last_monster_aimed = hero.monster_aimed;
			}
			else{
				hero.monster_aimed = 0;
				//ID
				PA_OutputText(1,STATUS_MONSTER_ID_X,STATUS_MONSTER_ID_Y," --- ");
				
				//HP
				PA_OutputText(1,STATUS_MONSTER_HP_X,STATUS_MONSTER_HP_Y," --- ");
				
				//SPEED
				PA_OutputText(1,STATUS_MONSTER_SPEED_X,STATUS_MONSTER_SPEED_Y," --- ");
				
				//EP
				PA_OutputText(1,STATUS_MONSTER_EP_X,STATUS_MONSTER_EP_Y," ---  ");
			}
			hero.updatemonsterdata = 0;
		}
		else if(hero.updatebossdata){
			//BOSS
			//ID
			PA_OutputText(1,STATUS_MONSTER_ID_X,STATUS_MONSTER_ID_Y,"%d     ", boss.id);
			
			//HP
			PA_OutputText(1,STATUS_MONSTER_HP_X,STATUS_MONSTER_HP_Y,"%d      ", boss.hp);
			
			//SPEED
			PA_OutputText(1,STATUS_MONSTER_SPEED_X,STATUS_MONSTER_SPEED_Y,"%d     ",sprites[boss.sprite].speed);
			
			//EP
			PA_OutputText(1,STATUS_MONSTER_EP_X,STATUS_MONSTER_EP_Y,"%d     ", sprites[boss.sprite].exp);

			if(game.monsterimgloaded==0){
				switch(boss.id){
					case 0:
						PA_CreateSprite(1,2, (void*)boss_0_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
						PA_StartSpriteAnimEx(1, 2, 0, 6, 8, ANIM_UPDOWN,0);
						break;
					case 1:
						PA_CreateSprite(1,2, (void*)boss_1_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
						PA_StartSpriteAnimEx(1,2,2,4,5,ANIM_UPDOWN,0);
						break;
					case 2:
						PA_CreateSprite(1,2, (void*)boss_2_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
						PA_StartSpriteAnimEx(1,2,5,7,5,ANIM_UPDOWN,0);
						break;
					case 3:
						PA_CreateSprite(1,2, (void*)boss_3_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
						PA_StartSpriteAnim(1, 2, 0, 3, 8);
						break;
					case 4:
						PA_CreateSprite(1,2, (void*)boss_3_Sprite, OBJ_SIZE_32X32,1,1,STATUS_MONSTER_IMG_X,STATUS_MONSTER_IMG_Y);
						PA_StartSpriteAnim(1, 2, 0, 3, 8);
						break;
				}
				game.monsterimgloaded = 1;
			}
			hero.updatebossdata = 0;
		}
	}
	else{
		hero.monster_aimed = 0;
		//ID
		PA_OutputText(1,STATUS_MONSTER_ID_X,STATUS_MONSTER_ID_Y," ??? ");
		
		//HP
		PA_OutputText(1,STATUS_MONSTER_HP_X,STATUS_MONSTER_HP_Y," ??? ");
		
		//SPEED
		PA_OutputText(1,STATUS_MONSTER_SPEED_X,STATUS_MONSTER_SPEED_Y," ??? ");
	
		//EP
		PA_OutputText(1,STATUS_MONSTER_EP_X,STATUS_MONSTER_EP_Y," ???  ");
	}
}
void DrawMap(){
	u8 x=0;
	u8 y=0;
	//copiando mapa (sprite 1)
	for(y=0;y<24;y++){
		for(x=0;x<64;x++){
			PA_SetSpritePixel(1,0,x,y,Map_GetPixelColor(game.levelmap[(y<<7) + x]));
		}
	}
	//copiando mapa (sprite 2)
	for(y=0;y<24;y++){
		for(x=0;x<64;x++){
			PA_SetSpritePixel(1,1,x,y,Map_GetPixelColor(game.levelmap[(y<<7) + x + 64]));
		}
	}
}
u8 Map_GetPixelColor(u16 tile){
	if(tile==0)return 0;//transparente
	else{
		u8 a;
		
		//colores:
		//0: transparente
		//1: blanco
		//2: rojo
		//3: verde
		//4: marron
		//5: azul
		//6: amarillo
		//7: negro
		
		//agua,lava?
		for(a=0;a<8;a++){
			if(tile==game.tiletransp[a]){
				switch(game.levelevent[LEVELDATA_TILES]){//que level
					case 1://lava tiles
						return 2;//rojo
						break;
						
					case 2://hierba tiles
						return 5;//azul
						break;
						
					case 3://nieve
						return 5;//azul
						break;
						
					case 4://fantasm
						return 7;//negor
						break;
						
					default:
						return 5;//azul
						break;
				}
			}
		}
		
		switch(game.levelevent[LEVELDATA_TILES]){
			case 1://lava tiles
				return 4;//marron
				break;
				
			case 2://hierba tiles
				return 3;//verde
				break;
				
			case 3://nieve
				return 1;//blanco
				break;
				
			case 4://fantasm
				return 4;//marron
				break;
			default:
				return 3;//verde
				break;
		}
	}
	return 7;//negro
}

void NewTextLine(u8 type, s32 a){
//type text
//	0: Recovered X HP
//	1: Recovered X AP
//	2: Power Up! Weapon X shot x2
//	3: Received X dmg
//	4: Obtained X EP

//scroll text
	u8 counter;
	u16 x = STATUS_TEXT_X;
	u16 y = STATUS_TEXT_Y;
	s8 yc;

	//borrar la linea k keda arriba
	PA_OutputText(1,STATUS_TEXT_X,STATUS_TEXT_Y-STATUS_TEXT_LINES,"                    ",a);
	//scroll
	for(yc=STATUS_TEXT_LINES;yc>=0;yc--){
		for(counter=0;counter<20;counter++){
			*(u16*)(PA_bgmap[1][1] + ((x+counter) << 1) + ((y-STATUS_TEXT_SEPARACION-yc) << 6)) = *(u16*)(PA_bgmap[1][1] + ((x+counter) << 1) + ((y-yc) << 6));
		}
	}
	//---------------------


//new line
	switch(type){
		case recoverhp:
			PA_OutputText(1,STATUS_TEXT_X,STATUS_TEXT_Y,"%d HP recovered     ",a);
			break;
		case recoverap:
			PA_OutputText(1,STATUS_TEXT_X,STATUS_TEXT_Y,"%d AP recovered     ",a);
			break;
		case powerupwsx2:
			PA_OutputText(1,STATUS_TEXT_X,STATUS_TEXT_Y,"Weapon %d Shots x2  ",a);
			break;
		case getdmg:
			PA_OutputText(1,STATUS_TEXT_X,STATUS_TEXT_Y,"Received %d damage  ",a);
			break;
		case getep:
			PA_OutputText(1,STATUS_TEXT_X,STATUS_TEXT_Y,"+%d EP              ",a);
			break;
	}
}






//---------------------------------IN-GAME STATUS SCREEN
//------------------------------------------
#define SHOPCOMMENT_X 10
#define SHOPCOMMENT_Y 2


#define DESCRIPTION_X 2
#define DESCRIPTION_Y 6

#define SHOPITEM_X 2
#define SHOPITEM_Y 6

#define EP_X 5
#define EP_Y 21

#define SHOPSELECT_X 14
#define SHOPSELECT_Y 45

#define SHOP_BUY_X 134
#define SHOP_BUY_Y 166

#define SHOP_BACK_X 195
#define SHOP_BACK_Y 166

//sprites usados en el menu

//top screen:
//0-7: select y eso
//8: Buy Button
//9: back button



void GotoShop(){
	u8 updateselect=0;
	game.numlist=0;
	
	LoadShop();
	game.shop_sel=0;
	UpdateSelectShopItem();
	PA_PlayMod(music_shop_mod);
	
	FadeOut(4);
	
	//FadeOut(8);
	while(game.screen==GAME_SHOP){
		updateselect=0;
		if(game.listed[game.shop_sel]<SHOP_ITEMS-1){
			if(Pad.Newpress.Down){game.shop_sel++;updateselect=1;}
			if(Pad.Newpress.Up){game.shop_sel--;updateselect=1;}
			
			if(game.shop_sel<0)game.shop_sel=game.numlist-1;
			if(game.shop_sel>game.numlist-1)game.shop_sel=0;
		}
		
		CheckShopButtons();
		if(updateselect){
			NewSound(select_sound);
			UpdateSelectShopItem();
		}
		
		if(Pad.Newpress.A){
			if(game.listed[game.shop_sel]<SHOP_ITEMS-1)BuyItem();
		}
		if(Pad.Newpress.B){
			NewSound(back_sound);
			HideButtonEffect(0,9,SHOP_BACK_X,SHOP_BACK_Y);
			game.screen = GAME_MENU;
			FadeIn(8);
		}
		
		UpdateSoundVars();
		PA_WaitForVBL();
	}
}

void LoadShop(){
	CleanScreen(1);
	PA_ResetBgSys();
	PA_ResetSpriteSys();
	
	
	//SET OTHER SCREEN WITH description
	CleanScreen(1);
	PA_InitCustomText(1,1,font);
	PA_EnableSpecialFx(1,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(1,16,16);
	
	PA_LoadTiledBg(1,3,menu_bg);
	PA_OutputText(1,0,0,"                                ");
	PA_OutputText(1,0,1,"                                ");
	//-----------
	
	PA_LoadTiledBg(1,2,game_shop_bottom);
	
	
	
	game.listed[0]=0;
	game.listed[1]=0;
	game.listed[2]=0;
	game.listed[3]=0;
	game.listed[4]=0;
	game.listed[5]=0;
	
	PA_LoadTiledBg(0,3,game_shop);
	
	PA_InitCustomText(0,1,font);
	PA_EnableSpecialFx(0,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(0,16,16);
	
	//PAL
	PA_LoadSpritePal(0,0,(void*)shop_select_Pal);
	PA_LoadSpritePal(0,1,(void*)buttons_Pal);
	PA_LoadSpritePal(1,1,(void*)buttons_Pal);
	
	
	//SHOP SELECT SPRITES
	PA_CreateSprite(0,0,(void*)shop_select_Sprite,OBJ_SIZE_32X16,1,0,SHOPSELECT_X,SHOPSELECT_Y);
	PA_SetSpriteAnim(0,0,0);
	
	PA_CreateSprite(0,1,(void*)shop_select_Sprite,OBJ_SIZE_32X16,1,0,SHOPSELECT_X+32*1,SHOPSELECT_Y);
	PA_SetSpriteAnim(0,1,1);
	
	PA_CreateSprite(0,2,(void*)shop_select_Sprite,OBJ_SIZE_32X16,1,0,SHOPSELECT_X+32*2,SHOPSELECT_Y);
	PA_SetSpriteAnim(0,2,1);
	
	PA_CreateSprite(0,3,(void*)shop_select_Sprite,OBJ_SIZE_32X16,1,0,SHOPSELECT_X+32*3,SHOPSELECT_Y);
	PA_SetSpriteAnim(0,3,1);
	
	PA_CreateSprite(0,4,(void*)shop_select_Sprite,OBJ_SIZE_32X16,1,0,SHOPSELECT_X+32*4,SHOPSELECT_Y);
	PA_SetSpriteAnim(0,4,1);
	
	PA_CreateSprite(0,5,(void*)shop_select_Sprite,OBJ_SIZE_32X16,1,0,SHOPSELECT_X+32*5,SHOPSELECT_Y);
	PA_SetSpriteAnim(0,5,2);
	
	PA_CreateSprite(0,6,(void*)shop_select_Sprite,OBJ_SIZE_32X16,1,0,SHOPSELECT_X+32*6,SHOPSELECT_Y);
	PA_SetSpriteAnim(0,6,3);
	
	PA_CreateSprite(0,7,(void*)shop_select_Sprite,OBJ_SIZE_32X16,1,0,SHOPSELECT_X+32*7,SHOPSELECT_Y);
	PA_SetSpriteAnim(0,7,4);
	//--------------------------------
	
	//BUTTONS
	PA_CreateSprite(0,8,(void*)buybutton_Sprite,OBJ_SIZE_64X32,1,1,SHOP_BUY_X,SHOP_BUY_Y);
	PA_CreateSprite(0,9,(void*)backbutton_Sprite,OBJ_SIZE_64X32,1,1,SHOP_BACK_X,SHOP_BACK_Y);
	
	ShowShopItems();
	
	PA_OutputText(0,EP_X,EP_Y,"%d", hero.totalexp);
}

void ShowShopItems(){
	u8 a=6;//shown shop items counter
	u8 b=0;
	u8 item;
	u8 x=SHOPITEM_X;
	u8 y=SHOPITEM_Y;
	PA_OutputText(0,x,y,"                              ");
	PA_OutputText(0,x,y+2,"                             ");
	PA_OutputText(0,x,y+4,"                             ");
	PA_OutputText(0,x,y+6,"                             ");
	PA_OutputText(0,x,y+8,"                             ");
	PA_OutputText(0,x,y+10,"                             ");
	
	game.numlist = 0;
	for(item=0;item<SHOP_ITEMS;item++){
		if(a>0){//there's space to show item :)
			if((data.shop_unlocked[item]==1)&&(data.shop[item]==0)){//if item is unlocked, write text, description etc
				game.listed[b]=item;
				b++;
				game.numlist++;
				switch(item){
					case 0://HP up 1
						PA_OutputText(0,x,y,"HP UP - LVL 1         ");
						break;
					case 1://HP up 2
						PA_OutputText(0,x,y,"HP UP - LVL 2         ");
						break;
					case 2://HP up 3
						PA_OutputText(0,x,y,"HP UP - LVL 3         ");
						break;
					case 3://HP up 4
						PA_OutputText(0,x,y,"HP UP - LVL 4         ");
						break;
					case 4://HP up 5
						PA_OutputText(0,x,y,"HP UP - LVL 5         ");
						break;
					case 5://HP up 6
						PA_OutputText(0,x,y,"HP UP - LVL 6         ");
						break;
					case 6://AP up
						PA_OutputText(0,x,y,"Ammo UP               ");
						break;
					case 7://speed up
						PA_OutputText(0,x,y,"Speed UP              ");
						break;
					case 8://jump power up
						PA_OutputText(0,x,y,"Jump Power UP         ");
						break;
					case 9://map
						PA_OutputText(0,x,y,"Map                   ");
						break;
					case 10://monster info
						PA_OutputText(0,x,y,"Monster Data          ");
						break;
					case 11://laser
						PA_OutputText(0,x,y,"Weapon: Laser         ");
						break;
					case 12://flamethrower
						PA_OutputText(0,x,y,"Weapon: Flamethrower  ");
						break;
					case 13://crouch
						PA_OutputText(0,x,y,"Skill: Crouch         ");
						break;
					case 14://dash
						PA_OutputText(0,x,y,"Skill: Dash           ");
						break;
					case 15://jump+dash
						PA_OutputText(0,x,y,"Skill: Jump+Dash      ");
						break;
					case 16://aim 360º
						PA_OutputText(0,x,y,"Skill: Aim 360º       ");
						break;
					case 17://double jump
						PA_OutputText(0,x,y,"Skill: Double Jump    ");
						break;
					case 18://shield
						PA_OutputText(0,x,y,"Weapon: Bouncin' Ball ");
						break;
					case 19://golden armour
						PA_OutputText(0,x,y,"Equip: Black Armor    ");
						break;
					case 20://gold arm
						PA_OutputText(0,x,y,"Equip: Mega Arm       ");
						break;
					default:
						PA_OutputText(0,x,y,"---                   ");
						break;
				}
				if(item<21)PA_OutputText(0,x+22,y,"%d  ",shop_price[item]*100);
				y+=2;
			}
		}
	}
}

void ShowDescription(u8 item){
	u8 dx=DESCRIPTION_X;
	u8 dy=DESCRIPTION_Y;
	u8 s=2;
	
	    PA_OutputText(1,dx,dy,"                            ");
	  PA_OutputText(1,dx,dy+s,"                            ");
	PA_OutputText(1,dx,dy+s*2,"                            ");
	PA_OutputText(1,dx,dy+s*3,"                            ");
	switch(item){
		case 0://HP up 1
			    PA_OutputText(1,dx,dy,"Increases MegaETk maximum HP");
			  PA_OutputText(1,dx,dy+s,"                           ");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"Hero MAX HP: %d -> %d       ", hero.maxhp, hero.maxhp+8);
			break;
		case 1://HP up 2
			    PA_OutputText(1,dx,dy,"Increases MegaETk maximum HP");
			  PA_OutputText(1,dx,dy+s,"                            ");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"Hero MAX HP: %d -> %d       ", hero.maxhp, hero.maxhp+16);
			break;
		case 2://HP up 2
			    PA_OutputText(1,dx,dy,"Increases MegaETk maximum HP");
			  PA_OutputText(1,dx,dy+s,"                            ");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"Hero MAX HP: %d -> %d       ", hero.maxhp, hero.maxhp+24);
			break;
		case 3://HP up 3
			    PA_OutputText(1,dx,dy,"Increases MegaETk maximum HP");
			  PA_OutputText(1,dx,dy+s,"                            ");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"Hero MAX HP: %d -> %d       ", hero.maxhp, hero.maxhp+32);
			break;
		case 4://HP up 4
			    PA_OutputText(1,dx,dy,"Increases MegaETk maximum HP");
			  PA_OutputText(1,dx,dy+s,"                            ");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"Hero MAX HP: %d -> %d       ", hero.maxhp, hero.maxhp+32);
			break;
		case 5://HP up 5
			    PA_OutputText(1,dx,dy,"Increases MegaETk maximum HP");
			  PA_OutputText(1,dx,dy+s,"                            ");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"Hero MAX HP: %d -> %d       ", hero.maxhp, hero.maxhp+32);
			break;
		case 6://AP up
			    PA_OutputText(1,dx,dy,"Increases maximum Ammo for  ");
			  PA_OutputText(1,dx,dy+s,"all weapons by 50.          ");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"Max Ammo: %d -> %d          ", defaultAMMO+hero.incammo,defaultAMMO+hero.incammo+50);
			break;
		case 7://speed up
			    PA_OutputText(1,dx,dy,"Increases MegaETk movement  ");
			  PA_OutputText(1,dx,dy+s,"speed, which makes run 1.5x ");
			PA_OutputText(1,dx,dy+s*2,"times faster.               ");
			PA_OutputText(1,dx,dy+s*3,"                            ");
			break;
		case 8://jump power up
				PA_OutputText(1,dx,dy,"Increases hero jump power.  ");
			  PA_OutputText(1,dx,dy+s,"                            ");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"Jump power x1.2             ");
			break;
		case 9://map
				PA_OutputText(1,dx,dy,"A Map to see the level in a ");
			  PA_OutputText(1,dx,dy+s,"small window in the status  ");
			PA_OutputText(1,dx,dy+s*2,"screen. Includes a radar to ");
			PA_OutputText(1,dx,dy+s*3,"know where MegaETk is       ");
			break;
		case 10://monster info
			    PA_OutputText(1,dx,dy,"See all monster information ");
			  PA_OutputText(1,dx,dy+s,"in the status screen:       ");
			PA_OutputText(1,dx,dy+s*2,"HP, Speed, ID and EP        ");
			PA_OutputText(1,dx,dy+s*3,"                            ");
			break;
		case 11://laser
			    PA_OutputText(1,dx,dy,"A fast laser that bounces at");
			  PA_OutputText(1,dx,dy+s,"all walls.                  ");
			PA_OutputText(1,dx,dy+s*2,"Attack power: 5             ");
			PA_OutputText(1,dx,dy+s*3,"Shoot Speed: x2             ");
			break;
		case 12://flamethrower
			    PA_OutputText(1,dx,dy,"Throws a large flame which  ");
			  PA_OutputText(1,dx,dy+s,"can kill an enemy in a short");
			PA_OutputText(1,dx,dy+s*2,"time.                       ");
			PA_OutputText(1,dx,dy+s*3,"Attack power: 25            ");
			break;
		case 13://crouch
			    PA_OutputText(1,dx,dy,"Skill:                      ");
			  PA_OutputText(1,dx,dy+s,"Use Down Button to crouch!  ");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"                            ");
			break;
		case 14://dash
			    PA_OutputText(1,dx,dy,"Skill:                      ");
			  PA_OutputText(1,dx,dy+s,"Down+A Button to dash and go");
			PA_OutputText(1,dx,dy+s*2,"through small tunnels that  ");
			PA_OutputText(1,dx,dy+s*3,"you couldn't go before.     ");
			break;
		case 15://jump+dash
			    PA_OutputText(1,dx,dy,"Skill:                      ");
			  PA_OutputText(1,dx,dy+s,"Now you will be able to jump");
			PA_OutputText(1,dx,dy+s*2,"while you dash to go to far ");
			PA_OutputText(1,dx,dy+s*3,"distances.                  ");
			break;
		case 16://aim 360º
			    PA_OutputText(1,dx,dy,"Skill:                      ");
			  PA_OutputText(1,dx,dy+s,"Hold Button Y or use your   ");
			PA_OutputText(1,dx,dy+s*2,"Stylus to aim in all ways.  ");
			PA_OutputText(1,dx,dy+s*3,"Aim at all 360º             ");
			break;
		case 17://double jump
			    PA_OutputText(1,dx,dy,"Skill:                      ");
			  PA_OutputText(1,dx,dy+s,"Ability to make a double    ");
			PA_OutputText(1,dx,dy+s*2,"jump to get higher distances");
			PA_OutputText(1,dx,dy+s*3,"                            ");
			break;
		case 18://rocket launcher
			    PA_OutputText(1,dx,dy,"A ball that will bounce     ");
			  PA_OutputText(1,dx,dy+s,"through all the level.      ");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"Attack power: 50            ");
			break;
		case 19://golden armour
			    PA_OutputText(1,dx,dy,"Equip:                      ");
			  PA_OutputText(1,dx,dy+s,"Increases MegaETk defense x2");
			PA_OutputText(1,dx,dy+s*2,"                            ");
			PA_OutputText(1,dx,dy+s*3,"                            ");
			break;
		case 20://gold arm
			    PA_OutputText(1,dx,dy,"Equip:                      ");
			  PA_OutputText(1,dx,dy+s,"Increases MegaETk attack    ");
			PA_OutputText(1,dx,dy+s*2,"power when shooting x1.5    ");
			PA_OutputText(1,dx,dy+s*3,"                            ");
			break;
		default:
			PA_OutputText(1,dx,dy,"There are no more items to  ", item);
			PA_OutputText(1,dx,dy+s,"buy. The Shop list is empty  ", item);
			break;
	}
}
void UpdateSelectShopItem(){
	u16 y = SHOPSELECT_Y + game.shop_sel*16;
	u16 x = SHOPSELECT_X;
	u8 i;
	for(i=0;i<8;i++){
		PA_SetSpriteXY(0,i,x+32*i,y);
	}
	ShowDescription(game.listed[game.shop_sel]);
}
void BuyItem(){
	u8 item = game.listed[game.shop_sel];
	u8 nosound=0;
	PA_OutputText(0,SHOPCOMMENT_X,SHOPCOMMENT_Y,"                      ");
	if(hero.totalexp>=shop_price[item]*100){
		PA_SetSpriteAnim(0,8,1);
		u32 newexp;
		u8 x,y;
		x=0;
		y=0;
		
		switch(item){
			case 0://HP up 1
				hero.maxhp += 8;
				hero.hp = hero.maxhp;
				break;
			case 1://HP up 2
				hero.maxhp += 16;
				hero.hp = hero.maxhp;
				break;
			case 2://HP up 3
				hero.maxhp += 24;
				hero.hp = hero.maxhp;
				break;
			case 3://HP up 4
				hero.maxhp += 32;
				hero.hp = hero.maxhp;
				break;
			case 4://HP up 5
				hero.maxhp += 32;
				hero.hp = hero.maxhp;
				break;
			case 5://HP up 6
				hero.maxhp += 32;
				hero.hp = hero.maxhp;
				break;
			case 6://AP up
				hero.incammo += 50;
				Updateincammo();
				break;
			case 7://speed up
				hero.speedinc = SKILL_SPEED_INC;
				data.skills[0]=1;
				break;
			case 8://jump power up
				hero.jumppower = defaultJUMPPOWER + SKILL_JUMP_INC;
				data.skills[1]=1;
				break;
			case 9://map
				data.extras[0]=1;
				break;
			case 10://monster info
				data.extras[1]=1;
				break;
			case 11://laser
				hero.numshoots[2] = 1;
				hero.maxammo[2] = defaultAMMO + hero.incammo;
				hero.ammo[2] = defaultAMMO + hero.incammo;
				break;
			case 12://flamethrower
				hero.numshoots[6] = 1;
				hero.maxammo[6] = defaultAMMO + hero.incammo;
				hero.ammo[6] = defaultAMMO + hero.incammo;
				break;
			case 13://crouch
				data.skills[2]=1;
				break;
			case 14://dash
				data.skills[3]=1;
				break;
			case 15://jump+dash
				data.skills[4]=1;
				break;
			case 16://aim 360º
				data.skills[5]=1;
				break;
			case 17://double jump
				data.skills[6]=1;
				break;
			case 18://bouncin' ball
				hero.numshoots[7] = 1;
				hero.maxammo[7] = defaultAMMO + hero.incammo;
				hero.ammo[7] = defaultAMMO + hero.incammo;
				break;
			case 19://golden armour
				data.skills[8]=1;
				break;
			case 20://gold arm
				data.skills[9]=1;
				break;
			default:
				nosound=1;
				break;
		}
		
		if(nosound==0)NewSound(accept_sound);
		
		for(newexp = hero.totalexp - shop_price[item]*100; hero.totalexp > newexp; hero.totalexp-=shop_price[item]<<2){
			PA_OutputText(0,EP_X,EP_Y,"               ");
			PA_OutputText(0,EP_X,EP_Y,"%d", hero.totalexp);
			PA_WaitForVBL();
		}
		hero.totalexp = newexp;
		
		PA_OutputText(0,EP_X,EP_Y,"               ");
		PA_OutputText(0,EP_X,EP_Y,"%d", hero.totalexp);
		PA_OutputText(0,SHOPCOMMENT_X,SHOPCOMMENT_Y,"Item bought!");
		data.shop_unlocked[item] = 0;
		data.shop[item] = 1;
		if(shop_unlocks[item]!=0)data.shop_unlocked[shop_unlocks[item]] = 1;
		ShowShopItems();
		
		if(game.numlist==0){
			data.shop_unlocked[SHOP_ITEMS-1]=1;
			ShowShopItems();
		}
		else if(game.shop_sel>game.numlist-1){
			game.shop_sel--;
			UpdateSelectShopItem();
		}
		
		ShowDescription(game.listed[game.shop_sel]);
		
		PA_SetSpriteAnim(0,8,0);
	}
	else{
		PA_OutputText(0,SHOPCOMMENT_X,SHOPCOMMENT_Y,"Not enough EP!");
	}
}
void CheckShopButtons(){
	if(Stylus.Newpress){
		u16 x;
		u16 y;

		x = SHOP_BACK_X;
		y = SHOP_BACK_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)){
			PA_StopMod();
			NewSound(back_sound);
			HideButtonEffect(0,9,x,y);
	
			game.screen = GAME_MENU;
			FadeIn(8);
		}
		
		x = SHOP_BUY_X;
		y = SHOP_BUY_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)){
			if(Pad.Newpress.A){
				if(game.listed[game.shop_sel]<SHOP_ITEMS-1)BuyItem();
			}
		}
	}
}


//---------------------------------IN-GAME STATUS SCREEN
//------------------------------------------
#define LOAD_BACK_X 195
#define LOAD_BACK_Y 166

#define LOAD_SELECTB_X 192
#define LOAD_SELECTB_Y 8

#define SLOT_NOTE_X 8
#define SLOT_NOTE_Y 4

#define SLOT_HP_X 4
#define SLOT_HP_Y 2

#define SLOT_EP_X 4
#define SLOT_EP_Y 4

#define SLOT_MODE_X 3
#define SLOT_MODE_Y 6

#define SLOT_LEVELCOMPLETE_X 18
#define SLOT_LEVELCOMPLETE_Y 2

#define SLOT_COMPLETE_X 18
#define SLOT_COMPLETE_Y 4

#define SLOT_TTIME_X 18
#define SLOT_TTIME_Y 6

#define SLOT_DIST 64
#define SLOT_DISTT 8

#define SLOTBOX_X 9
#define SLOTBOX_Y 9

#define SLOTBOX_WIDTH 183
#define SLOTBOX_HEIGHT 55

#define SLOT_HIDE_X1 11
#define SLOT_HIDE_X2 72
#define SLOT_HIDE_X3 104
#define SLOT_HIDE_X4 136
#define SLOT_HIDE_Y 13

#define SLOT_HIDE_PRIO 2
#define SLOT_NOHIDE_PRIO 3

#define MODE_EASY_X 20
#define MODE_EASY_Y 80
#define MODE_NORMAL_X 94
#define MODE_NORMAL_Y 80
#define MODE_HARD_X 168
#define MODE_HARD_Y 80

//sprites usados en el menu

//bottom screen:
//0: back button
//1: select button
//3-6: slot 1 hide text
//7-10: slot 2 hide text
//11-14: slot 3 hide text
//15: easy button
//16: normal button
//17: hard button

void GotoSelectSlot(){//mode 0: load data ... mode 1: new game, select slot
	LevelClean();
	CleanScreen(0);
	PA_ResetBgSys();
	PA_ResetSpriteSys();
	ResetGameVars();
	PA_WaitForVBL();
	
	//SET OTHER SCREEN WITH description
	CleanScreen(1);
	PA_InitCustomText(1,1,font);
	PA_EnableSpecialFx(1,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(1,16,16);
	
	PA_LoadTiledBg(1,3,menu_bg);
	
	if(game.slotmode==0){
		PA_OutputText(1,0,0,"    Select a slot to load      ");
		PA_OutputText(1,0,1,"        a saved game           ");
	}
	else{
		PA_OutputText(1,0,0,"    Select a slot to create     ");
		PA_OutputText(1,0,1,"          a new game            ");
	}
	//-----------
	u16 hidetextgfx = PA_CreateGfx(0,(void*)slotempty_Sprite,OBJ_SIZE_32X64,1);
	u8 hidepal=1;
	PA_LoadSpritePal(0,hidepal,(void*)slotempty_Pal);
	
	//hide slot text sprites
	//slot 1:
		PA_CreateSpriteFromGfx(0,3,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X1,SLOT_HIDE_Y);
		PA_CreateSpriteFromGfx(0,4,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X2,SLOT_HIDE_Y);
		PA_CreateSpriteFromGfx(0,5,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X3,SLOT_HIDE_Y);
		PA_CreateSpriteFromGfx(0,6,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X4,SLOT_HIDE_Y);
		SetSlotHidePrio(1,SLOT_HIDE_PRIO);
	//slot 2:
		PA_CreateSpriteFromGfx(0,7,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X1,SLOT_HIDE_Y+SLOT_DIST);
		PA_CreateSpriteFromGfx(0,8,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X2,SLOT_HIDE_Y+SLOT_DIST);
		PA_CreateSpriteFromGfx(0,9,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X3,SLOT_HIDE_Y+SLOT_DIST);
		PA_CreateSpriteFromGfx(0,10,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X4,SLOT_HIDE_Y+SLOT_DIST);
		SetSlotHidePrio(2,SLOT_HIDE_PRIO);
	//slot 3:
		PA_CreateSpriteFromGfx(0,11,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X1,SLOT_HIDE_Y+(SLOT_DIST<<1));
		PA_CreateSpriteFromGfx(0,12,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X2,SLOT_HIDE_Y+(SLOT_DIST<<1));
		PA_CreateSpriteFromGfx(0,13,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X3,SLOT_HIDE_Y+(SLOT_DIST<<1));
		PA_CreateSpriteFromGfx(0,14,hidetextgfx,OBJ_SIZE_32X64,1,hidepal,SLOT_HIDE_X4,SLOT_HIDE_Y+(SLOT_DIST<<1));
		SetSlotHidePrio(3,SLOT_HIDE_PRIO);
	//--------------

	
	PA_LoadTiledBg(0,2,game_selectsave);
	PA_InitCustomText(0,1,font);
	PA_EnableSpecialFx(0,SFX_ALPHA,SFX_BG1,SFX_OBJ|SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(0,16,16);
	
	PA_LoadSpritePal(0,0,(void*)buttons_Pal);
	
	//ReadSlots();
	
	PA_CreateSprite(0,0,(void*)backbutton_Sprite,OBJ_SIZE_64X32,1,0,LOAD_BACK_X,LOAD_BACK_Y);
	PA_CreateSprite(0,1,(void*)selectsavebutton_Sprite,OBJ_SIZE_64X32,1,0,LOAD_SELECTB_X,LOAD_SELECTB_Y);
	PA_SetSpriteAnim(0,1,0);

	game.slot=-1;
	s8 sel=0;
	u8 a=0;
	
	PA_PlayMod(music_selectlevel_mod);
	FadeOut(8);
	
	PA_OutputText(1,LOADCOMMENT_X,LOADCOMMENT_Y-1,"Read slots...");
	ReadSlots();
	while((game.screen==GAME_LOAD)||(game.screen==GAME_NEWFILE)){
		if(Pad.Newpress.Down){
			sel++;
			if(sel>2)sel=0;
			UpdateSelButton(sel);
		}
		if(Pad.Newpress.Up){
			sel--;
			if(sel<0)sel=2;
			UpdateSelButton(sel);
		}
		
		
		sel = CheckSelectSlotButtons(sel);
		
		if(Pad.Newpress.A){
			if(game.slotmode==0){
				if(game.slotread[sel]==1){
					PA_StopMod();
					NewSound(accept_sound);
					
					SelectSlot(sel);
					LoadData();
					
					HideButtonEffect2(0,1,LOAD_SELECTB_X,LOAD_SELECTB_Y + SLOT_DIST*sel);
					FadeIn(12);
				}
			}
			else{
				PA_SetSpriteAnim(0,1,1);
				if(game.slotread[sel]==1){
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-2,"                                ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-1,"                                ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-0,"                                ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-2,"This slot already contains a    ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-1,"saved file. Do you want to      ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-0,"Overwrite it?  A: Yes - B: No   ");
					
					a=0;
					PA_WaitForVBL();
					while(a==0){
						if(Pad.Newpress.B){
							a=1;
							NewSound(back_sound);
						}
						if(Pad.Newpress.A){
							a=1;
							NewSound(accept_sound);
							SelectSlot(sel);
						}
						PA_WaitForVBL();
					}
					PA_SetSpriteAnim(0,1,0);
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-2,"                                ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-1,"                                ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-0,"                                ");
				}
				else SelectSlot(sel);
			}
		}

		else if(Pad.Newpress.B){
			PA_StopMod();
			NewSound(back_sound);
			
			HideButtonEffect(0,0,LOAD_BACK_X,LOAD_BACK_Y);
			
			game.screen = TITLE_SCREEN;
			FadeIn(8);
		}
		
		UpdateSoundVars();
		PA_WaitForVBL();
	}
}
void SetSlotHidePrio(u8 slot,u8 prio){
	u16 a=3 + 4*(slot-1);
	u16 b=a+4;
	for(a=a;a<b;a++){
		PA_SetSpritePrio(0,a,prio);
	}
}
u8 CheckSelectSlotButtons(u8 sel){
	if(Stylus.Newpress){
		u16 x;
		u16 y;
		u8 a;

		x = LOAD_SELECTB_X;
		y = LOAD_SELECTB_Y + SLOT_DIST*sel;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)){
			if(game.slotmode==0){
				if(game.slotread[sel]==1){
					PA_StopMod();
					NewSound(accept_sound);
					
					SelectSlot(sel);
					LoadData();
					
					HideButtonEffect2(0,1,LOAD_SELECTB_X,LOAD_SELECTB_Y + SLOT_DIST*sel);
					FadeIn(12);
				}
			}
			else{
				PA_SetSpriteAnim(0,1,1);
				if(game.slotread[sel]==1){
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-2,"                                ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-1,"                                ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-0,"                                ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-2,"This slot already contains a    ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-1,"saved file. Do you want to      ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-0,"Overwrite it?  A: Yes - B: No   ");
					
					a=0;
					PA_WaitForVBL();
					while(a==0){
						if(Pad.Newpress.B){
							a=1;
							NewSound(back_sound);
						}
						if(Pad.Newpress.A){
							a=1;
							NewSound(accept_sound);
							SelectSlot(sel);
						}
						PA_WaitForVBL();
					}
					PA_SetSpriteAnim(0,1,0);
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-2,"                                ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-1,"                                ");
					PA_OutputText(1,LOADCOMMENT_X-1,LOADCOMMENT_Y-0,"                                ");
				}
				else SelectSlot(sel);
			}
		}
		
		x = LOAD_BACK_X;
		y = LOAD_BACK_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)){
			PA_StopMod();
			NewSound(back_sound);
			
			HideButtonEffect(0,0,x,y);
			game.screen = TITLE_SCREEN;
			FadeIn(8);
		}
		
		x = SLOTBOX_X;
		y = SLOTBOX_Y;
		a=0;
		for(a=0;a<3;a++){
			if((Stylus.X>x)&&(Stylus.X<x+SLOTBOX_WIDTH)&&(Stylus.Y>y+SLOT_DIST*a)&&(Stylus.Y<y+SLOTBOX_HEIGHT+SLOT_DIST*a)){
				sel = a;
				UpdateSelButton(sel);
				break;
			}
		}
		//change slottt
		
	}
	
	return sel;
}

void ReadSlots(){
	if(FAT_ENABLED){
		PA_OutputText(1,LOADCOMMENT_X,LOADCOMMENT_Y,"Searching devices..");
		if (FAT_InitFiles()==false){
			PA_OutputText(1,LOADCOMMENT_X,LOADCOMMENT_Y,"Error. No device found");
		}
		else{
			//SLOT 1
			file=FAT_fopen("/METK1.SAV","r");
			UpdateSlotData(1, 0);
			//SLOT 2
			file=FAT_fopen("/METK2.SAV","r");
			UpdateSlotData(2, SLOT_DISTT);
			//SLOT 3
			file=FAT_fopen("/METK3.SAV","r");
			UpdateSlotData(3, SLOT_DISTT<<1);
			
			PA_OutputText(1,LOADCOMMENT_X,LOADCOMMENT_Y-4,"                    ");
		}
	}
	else PA_OutputText(1,LOADCOMMENT_X,LOADCOMMENT_Y,"FAT disabled          ");
}
void UpdateSlotData(u8 slot, u16 dist){
	u8 loadmsg;
	u32 time=0;
	u32 hour=0;
	u32 min=0;
	u16 levels=0;
	u8 a;
	if(file!=0){
		game.slotread[slot-1]=1;
		FAT_fread(&data.preview, sizeof(u32), 500,file);
		FAT_fclose(file);
		loadmsg = ConvertLoad(data.preview, 500);
		switch(loadmsg){
			case 0:
				UpdateDataLoaded();
				SetSlotHidePrio(slot,SLOT_NOHIDE_PRIO);
				
				PA_OutputText(0,SLOT_HP_X,SLOT_HP_Y+dist,"%d",hero.maxhp);
				PA_OutputText(0,SLOT_EP_X,SLOT_EP_Y+dist,"%d",hero.totalexp);
				if(data.mode==0)PA_OutputText(0,SLOT_MODE_X,SLOT_MODE_Y+dist,"EASY");
				else if(data.mode==1)PA_OutputText(0,SLOT_MODE_X,SLOT_MODE_Y+dist,"NORMAL");
				else if(data.mode==2)PA_OutputText(0,SLOT_MODE_X,SLOT_MODE_Y+dist,"HARD");
				
				//get how many levels completed
				for(a=0;a<MENULVLTOTAL;a++){
					levels+=data.unlocked[a];
				}
				u16 levelss = levels;
				
				if(levels<MENULVLTOTAL)levels=levels*3;
				
				PA_OutputText(0,SLOT_LEVELCOMPLETE_X,SLOT_LEVELCOMPLETE_Y+dist," %d ",levels);
				PA_OutputText(0,SLOT_COMPLETE_X,SLOT_COMPLETE_Y+dist," %d\% ",(levelss*100)/MENULVLTOTAL);
				//--------------------
				
				time = game.totaltime;
				hour = time/3600;
				min = time/60 - hour*60;
				
				if(hour<10)PA_OutputText(0,SLOT_TTIME_X,SLOT_TTIME_Y+dist,"0%d:",hour);
				else PA_OutputText(0,SLOT_TTIME_X,SLOT_TTIME_Y+dist,"%d:",hour);
				
				if(min<10)PA_OutputText(0,SLOT_TTIME_X+3,SLOT_TTIME_Y+dist,"0%d ",min);
				else PA_OutputText(0,SLOT_TTIME_X+3,SLOT_TTIME_Y+dist,"%d ",min);
				break;
			case 1:
				SetSlotHidePrio(slot,SLOT_HIDE_PRIO);
				PA_OutputText(0,SLOT_NOTE_X-5,SLOT_NOTE_Y+dist,"Save file is broken");
				game.slotread[slot-1]=2;
				break;
			case 2:
				SetSlotHidePrio(slot,SLOT_HIDE_PRIO);
				PA_OutputText(0,SLOT_NOTE_X-5,SLOT_NOTE_Y+dist,"Error: old data version ");
				PA_OutputText(0,SLOT_NOTE_X-5,SLOT_NOTE_Y+dist+1,"(older version)  ");
				game.slotread[slot-1]=2;
				break;
			case 3:
				SetSlotHidePrio(slot,SLOT_HIDE_PRIO);
				PA_OutputText(0,SLOT_NOTE_X-5,SLOT_NOTE_Y+dist,"Save Not compatible ");
				PA_OutputText(0,SLOT_NOTE_X-5,SLOT_NOTE_Y+dist+1,"(newer version)  ");
				game.slotread[slot-1]=2;
				break;
		}
	}
	else{
		SetSlotHidePrio(slot,SLOT_HIDE_PRIO);
		PA_OutputText(0,SLOT_NOTE_X,SLOT_NOTE_Y+dist,"  EMPTY");
		game.slotread[slot-1]=0;
	}
}
void UpdateSelButton(u8 sel){
	PA_SetSpriteXY(0,1,LOAD_SELECTB_X,LOAD_SELECTB_Y + SLOT_DIST*sel);
	NewSound(select_sound);
}

void SelectSlot(u8 sel){
	game.slot=sel;
	if(game.slotmode==1){
		HideButtonEffect2(0,1,LOAD_SELECTB_X,LOAD_SELECTB_Y + SLOT_DIST*sel);
		
		//select easy/normal/hard
			//setup game mode
			PA_CreateSprite(0,15,(void*)mode_easy_Sprite,OBJ_SIZE_64X32,1,0,MODE_EASY_X,MODE_EASY_Y);
			PA_CreateSprite(0,16,(void*)mode_normal_Sprite,OBJ_SIZE_64X32,1,0,MODE_NORMAL_X,MODE_NORMAL_Y);
			PA_SetSpriteAnim(0,16,1);
			PA_CreateSprite(0,17,(void*)mode_hard_Sprite,OBJ_SIZE_64X32,1,0,MODE_HARD_X,MODE_HARD_Y);
			//---------------
		
		
		//loop till select
		u8 mode=1;
		u8 accept=0;
		u16 x;
		u16 y;
		
		//SELECCIONANDO MODO
		while(accept==0){
			if(Pad.Newpress.Right){
				if(mode<2)mode++;
				
				if(mode==0){
					PA_SetSpriteAnim(0,15,1);
					PA_SetSpriteAnim(0,16,0);
					PA_SetSpriteAnim(0,17,0);
				}
				else if(mode==1){
					PA_SetSpriteAnim(0,15,0);
					PA_SetSpriteAnim(0,16,1);
					PA_SetSpriteAnim(0,17,0);
				}
				else if(mode==2){
					PA_SetSpriteAnim(0,15,0);
					PA_SetSpriteAnim(0,16,0);
					PA_SetSpriteAnim(0,17,1);
				}
			}
			else if(Pad.Newpress.Left){
				if(mode>0)mode--;
				
				if(mode==0){
					PA_SetSpriteAnim(0,15,1);
					PA_SetSpriteAnim(0,16,0);
					PA_SetSpriteAnim(0,17,0);
				}
				else if(mode==1){
					PA_SetSpriteAnim(0,15,0);
					PA_SetSpriteAnim(0,16,1);
					PA_SetSpriteAnim(0,17,0);
				}
				else if(mode==2){
					PA_SetSpriteAnim(0,15,0);
					PA_SetSpriteAnim(0,16,0);
					PA_SetSpriteAnim(0,17,1);
				}
			}
			
			if((Pad.Newpress.A)||(Pad.Newpress.Start)){
				if(mode==0){
					accept=1;
					HideButtonEffect(0,15,MODE_EASY_X,MODE_EASY_Y);
				}
				else if(mode==1){
					accept=1;
					HideButtonEffect(0,16,MODE_NORMAL_X,MODE_NORMAL_Y);
				}
				else if(mode==2){
					accept=1;
					HideButtonEffect(0,17,MODE_HARD_X,MODE_HARD_Y);
				}
			}
			
			//stylus?
			if(Stylus.Newpress){
				//EASY?
					x = MODE_EASY_X;
					y = MODE_EASY_Y;
					if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(accept==0)){
						if(mode!=0){
							mode=0;
							PA_SetSpriteAnim(0,15,1);
							PA_SetSpriteAnim(0,16,0);
							PA_SetSpriteAnim(0,17,0);
						}
						else{//si se apreta ortra vez:
							accept=1;
							HideButtonEffect(0,15,x,y);
						}
					}
				//NORMAL?
					x = MODE_NORMAL_X;
					y = MODE_NORMAL_Y;
					if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(accept==0)){
						if(mode!=1){
							mode=1;
							PA_SetSpriteAnim(0,15,0);
							PA_SetSpriteAnim(0,16,1);
							PA_SetSpriteAnim(0,17,0);
						}
						else{//si se apreta ortra vez:
							accept=1;
							HideButtonEffect(0,16,x,y);
						}
					}
				//HARD?
					x = MODE_HARD_X;
					y = MODE_HARD_Y;
					if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(accept==0)){
						if(mode!=2){
							mode=2;
							PA_SetSpriteAnim(0,15,0);
							PA_SetSpriteAnim(0,16,0);
							PA_SetSpriteAnim(0,17,1);
						}
						else{//si se apreta ortra vez:
							accept=1;
							HideButtonEffect(0,17,x,y);
						}
					}
			}//end stylus check
			UpdateSoundVars();
			PA_WaitForVBL();
		}
		
		NewSound(accept_sound);
		
		PA_StopMod();
		data.mode = mode;
		NewGame();
		FadeIn(4);
	}
	game.screen = GAME_MENU;
}


//---------------------------------EXTRAS
//------------------------------------------
#define ARROW_SEL_X1_1 80
#define ARROW_SEL_X1_2 162
#define ARROW_SEL_Y1 42

#define ARROW_SEL_X2_1 79
#define ARROW_SEL_X2_2 164
#define ARROW_SEL_Y2 122

//bottom screen:
//0: back button
//1: arrow select
//2: arrow select 2
void GotoExtras(){
	LevelClean();
	CleanScreen(0);
	PA_ResetBgSys();
	PA_ResetSpriteSys();
	ResetGameVars();
	PA_WaitForVBL();
	
	//SET OTHER SCREEN WITH description
	CleanScreen(1);
	PA_InitCustomText(1,1,font);
	PA_EnableSpecialFx(1,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(1,16,16);
	
	PA_LoadTiledBg(1,3,menu_bg);
	
	PA_OutputText(1,0,12,"         Select option         ");
	//-----------
	
	//load pal
	PA_LoadSpritePal(0,0,(void*)buttons_Pal);
	PA_LoadSpritePal(0,1,(void*)effects_Pal);
	
	
	PA_LoadTiledBg(0,3,menu_bg);
	PA_LoadTiledBg(0,2,menu_extras);
	
	PA_CreateSprite(0,0,(void*)backbutton_Sprite,OBJ_SIZE_64X32,1,0,LOAD_BACK_X,LOAD_BACK_Y);
	PA_CreateSprite(0,1,(void*)pause_select_Sprite, OBJ_SIZE_8X8,1,1,ARROW_SEL_X1_1, ARROW_SEL_Y1);
	PA_CreateSprite(0,2,(void*)pause_select_Sprite, OBJ_SIZE_8X8,1,1,ARROW_SEL_X1_2, ARROW_SEL_Y1);
	PA_SetSpriteHflip(0,2,1);
	
	FadeOut(4);
	u8 sel=0;//extra option selected
	while(game.screen == GAME_EXTRAS){
		game.stopcheck=0;
		
		CheckExtrasButtons();
		if((Pad.Newpress.B)&&(!game.stopcheck)){
			game.stopcheck=1;
			PA_StopMod();
			NewSound(back_sound);
			
			HideButtonEffect(0,0,LOAD_BACK_X,LOAD_BACK_Y);
			game.screen = TITLE_SCREEN;
			FadeIn(8);
		}
		
		if((Pad.Newpress.Down)&&(!game.stopcheck)){
			NewSound(select_sound);
			game.stopcheck=1;
			sel++;
			if(sel>1)sel=0;
			UpdateExtraSel(sel);
		}
		if((Pad.Newpress.Up)&&(!game.stopcheck)){
			NewSound(select_sound);
			game.stopcheck=1;
			sel--;
			if(sel==255)sel=1;
			UpdateExtraSel(sel);
		}
		
		
		if(Pad.Newpress.A)SelectExtra(sel);
		
		UpdateSoundVars();
		PA_WaitForVBL();
	}
}

void UpdateExtraSel(u8 sel){
	switch(sel){
		case 0:
			PA_SetSpriteXY(0,1,ARROW_SEL_X1_1, ARROW_SEL_Y1);
			PA_SetSpriteXY(0,2,ARROW_SEL_X1_2, ARROW_SEL_Y1);
			break;
		case 1:
			PA_SetSpriteXY(0,1,ARROW_SEL_X2_1, ARROW_SEL_Y2);
			PA_SetSpriteXY(0,2,ARROW_SEL_X2_2, ARROW_SEL_Y2);
			break;
	}
}

void CheckExtrasButtons(){
	if(Stylus.Newpress){
		u16 x;
		u16 y;
		x = LOAD_BACK_X;
		y = LOAD_BACK_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			PA_StopMod();
			NewSound(back_sound);
			
			HideButtonEffect(0,0,x,y);
			game.screen = TITLE_SCREEN;
			FadeIn(8);
		}
	}
}
void SelectExtra(u8 sel){
	switch(sel){
		case 0:
			game.screen = GAME_OPENMEL;
			NewSound(accept_sound);
			FadeIn(4);
			break;
		case 1:
			game.screen = GAME_LEVELEDITOR;
			NewSound(accept_sound);
			FadeIn(4);
			break;
		default:
			break;
	}
}
