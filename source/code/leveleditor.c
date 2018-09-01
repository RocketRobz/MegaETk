#define strcasestr(x, y) (strcasecmp(&(x)[strlen(x) - strlen(y)], (y)))

//estructura .mel:
//0:number of levels on the file (MAX 6)
//1-20:autor
//21-40: Level name
//41+a: level events
//41+a+512: level map (4096 length)... 4096/8 -> 512 (tiles de 16 mejor)
//next level data (a+2048+208)
//
//si hay 5 niveles, calculamos espacio total:
//40 + 2048+208 = 2296
#define MEL_FILESIZE 2296
#define MEL_DATA_NUMLEVELS 0
#define MEL_DATA_AUTOR 1
#define MEL_DATA_LEVELNAME 21
#define MEL_DATA_START 41
#define MEL_DATA_LEVELSIZE 2256
#define MEL_DATA_MAPLEVELSIZE 2048
void MEL_CreateMEL(char filename[19], char autor[20], char levelname[20]){
	strncpy (mel_file, filename, MAX_FILENAME_LENGTH - 1);
	if (FAT_InitFiles()==false)PA_OutputText(1,COMMENT_X,COMMENT_Y,"Error. No device found  ");
	else{
		file=FAT_fopen(mel_file,"w");
		u16 buff[MEL_FILESIZE];
		FAT_fwrite(&buff, sizeof(u16), MEL_FILESIZE, file);//writting 0's...

		//set nº of levels, autor y level name (seek)
		u16 buf[1]={1};
		FAT_fseek(file,MEL_DATA_NUMLEVELS,SEEK_SET);
		FAT_fwrite(&buf, sizeof(u16), 1, file);
		
		//              X--------------------X
		//char autor[20]="ETk                 ";
		FAT_fseek(file,MEL_DATA_AUTOR,SEEK_SET);
		FAT_fwrite(&autor, sizeof(char), 20, file);
		
		//                  X--------------------X
		//char levelname[20]="Superdungeon Test   ";
		FAT_fseek(file,MEL_DATA_LEVELNAME,SEEK_SET);
		FAT_fwrite(&levelname, sizeof(char), 20, file);
		FAT_fclose(file);
	}
}
void GotoLevelEditor(){
	CleanScreen(0);
	CleanScreen(1);
	game.option_selected=0;//0: Level Options
	
	//create new level
	MEL_New();//init new level vars
	
	while(game.screen == GAME_LEVELEDITOR){
		switch(game.option_selected){
			case 0://level manager (editor)
				MEL_GotoLevelManager();
				break;
			case 1://Level Options
				MEL_GotoOptions();
				break;
			case 2://Map Editor
				break;
			case 3://Event Editor
				break;
			case 4://Test
				FadeIn(4);
				MEL_GotoTest();
				break;
			case 5://Exit
				game.screen = GAME_EXTRAS;
				FadeIn(4);
				break;
			case 6://Create
				FadeIn(4);
				MEL_CreateNewLevel();
				break;
		}
		PA_WaitForVBL();
	}
}


//define de posicions 
#define FILENAME_X 10
#define FILENAME_Y 3// las otras cosas es solo +2, +2 +2 ...
//sprites:
//0:select letter
//1:"_" blinking
void MEL_CreateNewLevel(){
	LevelClean();
	//init keyboard vars etc
		u16 keyboard_x = 33;//indica posicion de tecla "1"
		u16 keyboard_y = 83;//para calcular posicion de teclas etc
		
		u16 kb_x[36];
		u16 kb_y[36];
		char kb[36]="1234567890QWERTYUIOPASDFGHJKLZXCVBNM";
		
		//calcular posicion de teclas
		u8 a;//contador de teclas
		u8 b=0;//contador x de teclas
		u16 xc=keyboard_x;//posicion X de la fila
		u16 yc=keyboard_y;//posicion Y de la fila
		for(a=0;a<36;a++){
			if((a==10)||(a==20)||(a==29)){yc+=15;xc+=5;b=0;}
			kb_x[a] = xc + (b<<4);//a<<4 = a*16 ... hay 16 pixeles entre el principio de cada tecla
			kb_y[a] = yc;
			b++;
		}
		//--------------
		
		//calcular posicion de BACKSPACE, ENTER y SPACE
		/*no lo pongo, ya se calculara cuando calcule a que apreta*/
		//backspace_x = keyboard_x + 160;
		//backspace_y = keyboard_y;
		//enter_x = keyboard_x + 167;
		//enter_y = keyboard_y + 10;
		//space_x = keyboard_x + 45;
		//space_y = keyboard_y + 60;
	//--------------
	
	//load bg etc
	PA_LoadTiledBg(1,3,menu_bg);
	PA_LoadTiledBg(0,3,menu_bg);
	PA_LoadTiledBg(0,2,editor_new);
	PA_InitCustomText(0,1,font);
	PA_EnableSpecialFx(0,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(0,16,16);
	
	PA_LoadSpritePal(0,1,(void*)editor_extra_Pal);
	PA_CreateSprite(0,0,(void*)editor_extra_Sprite,OBJ_SIZE_16X16,1,1,256,0);//letter selector
	PA_CreateSprite(0,1,(void*)editor_extra_Sprite+256,OBJ_SIZE_8X8,1,1,FILENAME_X<<3,FILENAME_Y<<3);//text "_" blinking
	PA_StartSpriteAnim(0, 1, 0, 1, 2);
	
	char filename[256]="";
	char authorname[20]="";
	char levelname[20]="";
	u8 textlenght[3]={0,0,0};
	u8 sel=0;
	
	char* text;
	text = filename;//apuntar al texto
	
	s8 key=-1;
	FadeOut(4);
	while(game.option_selected==6){
		game.stopcheck=0;
		key = -1;
		//check key presse
		if(Stylus.Newpress){
			for(a=0;a<36;a++){
				if((Stylus.X>=kb_x[a])&&(Stylus.X<=kb_x[a]+14)&&(Stylus.Y>=kb_y[a])&&(Stylus.Y<=kb_y[a]+14)&&(!game.stopcheck))
				{
					key = a;
					game.stopcheck=1;
					a=37;
				}
			}
			
			//mirar especiales
				//espacio
				if((Stylus.X>=keyboard_x + 45)&&(Stylus.X<=keyboard_x + 45 + 81)&&(Stylus.Y>=keyboard_y + 60)&&(Stylus.Y<=keyboard_y + 60 + 14)&&(!game.stopcheck)){
					key=36;
					game.stopcheck=1;
				}
				//backspace
				if((Stylus.X>=keyboard_x + 160)&&(Stylus.X<=keyboard_x + 160 + 32)&&(Stylus.Y>=keyboard_y)&&(Stylus.Y<=keyboard_y + 14)&&(!game.stopcheck)){
					if(textlenght[sel]>0){
						key=37;
						game.stopcheck=1;
					}
				}
				//enter (next text)
				if((Stylus.X>=keyboard_x + 167)&&(Stylus.X<=keyboard_x + 167 + 22)&&(Stylus.Y>=keyboard_y+10)&&(Stylus.Y<=keyboard_y+10 + 29)&&(!game.stopcheck)){
					key=38;
					game.stopcheck=1;
				}
		}
		
		//si se ha apretado una tecla, pos a ponerla donde toca
		if((key>=0)&&(key<38)){
			if(key<36)PA_SetSpriteXY(0,0,kb_x[key]-1,kb_y[key]-1);//select letter gfx
			
			
			if((key==37)||(textlenght[sel]<15)||((sel>0)&&(textlenght[sel]<19))){
				if(key==36)text[textlenght[sel]]=' ';//white space
				else if(key==37){//backspace
					textlenght[sel]--;
					text[textlenght[sel]]=' ';
					textlenght[sel]--;
				}
				else text[textlenght[sel]]=kb[key];
				
				PA_OutputText(0,FILENAME_X,FILENAME_Y+(sel<<1),"%s",text);//actualiza texto
				PA_SetSpriteXY(0,1,(FILENAME_X+textlenght[sel]+1)<<3,(FILENAME_Y<<3) + (sel<<4));//move _ blinking
				textlenght[sel]++;
			}
		}
		else if(key==38){//next text
			switch(sel){
				case 0://current: filename .. next: author
					text = authorname;
					sel++;
					PA_SetSpriteXY(0,1,(FILENAME_X+textlenght[sel]+1)<<3,(FILENAME_Y<<3) + (sel<<4));//move _ blinking
					break;
				case 1://current: author .. next: levelname
					text = levelname;
					sel++;
					PA_SetSpriteXY(0,1,(FILENAME_X+textlenght[sel]+1)<<3,(FILENAME_Y<<3) + (sel<<4));//move _ blinking
					break;
				case 2://current: levelname .. next: CREATE FILE
					sel++;
					filename[textlenght[0]]='.';
					filename[textlenght[0]+1]='m';
					filename[textlenght[0]+2]='e';
					filename[textlenght[0]+3]='l';
					textlenght[0]+=4;
					//creating file...
						strncpy (mel_file, filename, MAX_FILENAME_LENGTH - 1);
						if (FAT_InitFiles()==false)PA_OutputText(1,COMMENT_X,COMMENT_Y,"Error. No device found  ");
						else{
							file=FAT_fopen(mel_file,"w");
							u16 buff[MEL_FILESIZE];
							FAT_fwrite(&buff, sizeof(u16), MEL_FILESIZE, file);//writting 0's...
					
							//set nº of levels, autor y level name (seek)
							u16 buf[1]={1};
							FAT_fseek(file,MEL_DATA_NUMLEVELS,SEEK_SET);
							FAT_fwrite(&buf, sizeof(u16), 1, file);
							
							//              X--------------------X
							//char autor[20]="ETk                 ";
							FAT_fseek(file,MEL_DATA_AUTOR,SEEK_SET);
							FAT_fwrite(&authorname, sizeof(char), 20, file);
							
							//                  X--------------------X
							//char levelname[20]="Superdungeon Test   ";
							FAT_fseek(file,MEL_DATA_LEVELNAME,SEEK_SET);
							FAT_fwrite(&levelname, sizeof(char), 20, file);
							FAT_fclose(file);
						}
					//--------
					break;
			}
		}
		
		PA_WaitForVBL();
	}
}



#define BUTTON1_X 0
#define BUTTON2_X 65
#define BUTTON3_X 129
#define BUTTON4_X 195
#define BUTTONA_Y 166

#define LM_SEL_X 128
#define LM_SEL_Y 166
#define LM_SELBAR_X 73
#define LM_SELBAR_Y 21
//sprites:
//1:new
//2:load
//3:select
//4:back
//5-7:level select
void MEL_GotoLevelManager(){
	LevelClean();
	u8 sel=0;//limit 5
	u8 maxsel=5;
	//backgrounds:
	PA_LoadTiledBg(1,3,menu_bg);
	PA_LoadTiledBg(0,3,menu_bg);
	PA_LoadTiledBg(0,2,editor_levelmanager);
	//set text
	PA_InitCustomText(0,1,font);
	PA_EnableSpecialFx(0,SFX_ALPHA,SFX_BG1,SFX_BG2|SFX_BG3);
	PA_SetSFXAlpha(0,16,16);
	//------------
	
	//sprites
	PA_LoadSpritePal(0,0,(void*)buttons_Pal);
	PA_LoadSpritePal(0,1,(void*)ed_buttons_Pal);
	PA_LoadSpritePal(0,2,(void*)lm_selbar_Pal);
	
	
	PA_CreateSprite(0,1,(void*)editor_newbutton_Sprite,OBJ_SIZE_64X32,1,1,BUTTON1_X,BUTTONA_Y);
	PA_CreateSprite(0,2,(void*)editor_loadbutton_Sprite,OBJ_SIZE_64X32,1,1,BUTTON2_X,BUTTONA_Y);
	PA_CreateSprite(0,3,(void*)selectbutton_Sprite,OBJ_SIZE_64X32,1,0,BUTTON3_X,BUTTONA_Y);
	PA_CreateSprite(0,4,(void*)backbutton_Sprite,OBJ_SIZE_64X32,1,0,BUTTON4_X,BUTTONA_Y);
	
	PA_CreateSprite(0,5,(void*)editor_levelmanager_selbar_Sprite,OBJ_SIZE_64X32,1,2,LM_SELBAR_X,LM_SELBAR_Y);
	PA_CreateSprite(0,6,(void*)editor_levelmanager_selbar_Sprite,OBJ_SIZE_64X32,1,2,LM_SELBAR_X+64,LM_SELBAR_Y);
	PA_CreateSprite(0,7,(void*)editor_levelmanager_selbar_Sprite,OBJ_SIZE_64X32,1,2,LM_SELBAR_X+64+64-26,LM_SELBAR_Y);
	PA_SetSpritePrio(0,5,2);
	PA_SetSpritePrio(0,6,2);
	PA_SetSpritePrio(0,7,2);
	
	//writing levelsssss text (reading to check which are created..)
	file=FAT_fopen(mel_file,"r");
	u16 buff[MEL_FILESIZE];
	FAT_fread(&buff, sizeof(u16), MEL_FILESIZE,file);
	FAT_fclose(file);
		
	if (FAT_InitFiles()==false)PA_OutputText(1,COMMENT_X,COMMENT_Y,"Error. No device found  ");
	else{
		//read list
		u16 curFile=0;
		u8 a=0;
		FileList[curFile].fType = FAT_FindFirstFileLFN(FileList[curFile].fName);
		while(FileList[curFile].fType != FT_NONE){//mientras no encuentre un archivo que no exista..
			curFile++;
			FileList[curFile].fType  = FAT_FindNextFileLFN(FileList[curFile].fName);
			FileList[curFile].mel = !strcasestr(FileList[curFile].fName, ".mel");
			if(FileList[curFile].mel){
				PA_OutputText(0,10,3+(a<<1),"%s",FileList[curFile].fName);
				a++;
			}
		}
		maxsel=a-1;
	}
	
	MEL_LM_UpdateSelected(sel);
	FadeOut(2);
	while(game.option_selected==0){
		game.stopcheck=0;
		
		//----SELECT LEVEL
			if(Pad.Newpress.Up){
				if(sel>0)sel--;
				else sel=maxsel;
				MEL_LM_UpdateSelected(sel);
			}
			if(Pad.Newpress.Down){
				if(sel<maxsel)sel++;
				else sel=0;
				MEL_LM_UpdateSelected(sel);
			}
		//------------------
		MEL_CheckLevelManagerButtons();
		mel_slot = sel;
		
		PA_WaitForVBL();
	}
}
void MEL_LM_UpdateSelected(u8 sel){
	u16 y = LM_SELBAR_Y+(sel<<4);
	PA_SetSpriteY(0,5,y);//sel<<3 = sel*8
	PA_SetSpriteY(0,6,y);//sel<<3 = sel*8
	PA_SetSpriteY(0,7,y);//sel<<3 = sel*8
}
void MEL_CheckLevelManagerButtons(){
	if(Stylus.Newpress){
		u16 x;
		u16 y;
		//bottom buttons------------------------------------------------
		
		//NEW level button
		x = BUTTON1_X;
		y = BUTTONA_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(accept_sound);
			
			HideButtonEffect(0,1,x,y);
			game.option_selected = 6;//go to level manager
		}
		
		//LOAD level button
		x = BUTTON2_X;
		y = BUTTONA_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(accept_sound);
			
			HideButtonEffect(0,2,x,y);
			game.option_selected = 1;//go to level manager
		}
		
		//BACK BUTTON
		x = BUTTON4_X;
		y = BUTTONA_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(back_sound);
			
			HideButtonEffect(0,4,x,y);
			game.option_selected = 5;//go to level manager
		}
		//---------------
	}
}

//---------MEL: LEVEL OPTIONS------------------
//LE=LevelEditor
//BG=Background
//TG=TileGFX
//SB=SelectButton

#define LE_BG_X 83
#define LE_BG_Y 22

#define LE_BG_SB_X1 68
#define LE_BG_SB_X2 146
#define LE_BG_SB_Y 34

#define LE_TG_X 83
#define LE_TG_Y 71

#define LE_TG_SB_X1 68
#define LE_TG_SB_X2 210
#define LE_TG_SB_Y 75

#define SelArrow_width 16
#define SelArrow_height 23

#define TESTBUTTON_X 0
#define TESTBUTTON_Y 166

#define EDITMAPBUTTON_X 64
#define EDITMAPBUTTON_Y 166

#define EVENTSBUTTON_X 128
#define EVENTSBUTTON_Y 166
//sprites:
//0: back button
//1: test button
//2: edit map button
//3: event button
//4-7: ???

//8: bg preview
//9-10: bg select arrows
//11-12: tilegfx preview
//13-14: tilegfx select arrows


#define TOTAL_BG 3
#define TOTAL_TILEGFX 4
void MEL_GotoOptions(){
	LevelClean();
	CleanScreen(0);
	CleanScreen(1);	
	
	MEL_SetupLevelOptions();
	FadeOut(4);
	
	while(game.option_selected==1){
		game.stopcheck=0;
		MEL_CheckLevelOptionButtons();
		
		UpdateSoundVars();
		PA_WaitForVBL();
	}
	MEL_SaveLevel();//save level data
}
void MEL_SetupLevelOptions(){
	//backgrounds:
	PA_LoadTiledBg(1,3,menu_bg);
	
	PA_LoadTiledBg(0,3,menu_bg);
	PA_LoadTiledBg(0,2,editor_leveloptions);
	
	//sprites
	PA_LoadSpritePal(0,0,(void*)buttons_Pal);
	PA_LoadSpritePal(0,1,(void*)ed_buttons_Pal);
	PA_LoadSpritePal(0,2,(void*)ed_bg_Pal);
	PA_LoadSpritePal(0,3,(void*)ed_tg_Pal);
	PA_LoadSpritePal(0,4,(void*)editor_arrow_Pal);
	
	PA_CreateSprite(0,0,(void*)backbutton_Sprite,OBJ_SIZE_64X32,1,0,LOAD_BACK_X,LOAD_BACK_Y);
	PA_CreateSprite(0,1,(void*)editor_testbutton_Sprite, OBJ_SIZE_64X32,1,1,TESTBUTTON_X, TESTBUTTON_Y);
	PA_CreateSprite(0,2,(void*)editor_editmapbutton_Sprite, OBJ_SIZE_64X32,1,1,EDITMAPBUTTON_X, EDITMAPBUTTON_Y);
	PA_CreateSprite(0,3,(void*)editor_eventsbutton_Sprite, OBJ_SIZE_64X32,1,1,EVENTSBUTTON_X, EVENTSBUTTON_Y);
	
//level options..
	//init option sprites...
	gfx.editor_bg = PA_CreateGfx(0,(void*)editor_bg0_Sprite,OBJ_SIZE_64X64,1);
	gfx.editor_tg[0] = PA_CreateGfx(0,(void*)editor_tilegfx1_Sprite,OBJ_SIZE_64X32,1);
	gfx.editor_tg[1] = PA_CreateGfx(0,(void*)editor_tilegfx1_Sprite+2048,OBJ_SIZE_64X32,1);
	
	PA_CreateSpriteFromGfx(0,8,gfx.editor_bg,OBJ_SIZE_64X64,1,2,LE_BG_X,LE_BG_Y);
	PA_CreateSpriteFromGfx(0,11,gfx.editor_tg[0],OBJ_SIZE_64X32,1,3,LE_TG_X,LE_TG_Y);
	PA_CreateSpriteFromGfx(0,12,gfx.editor_tg[1],OBJ_SIZE_64X32,1,3,LE_TG_X+64,LE_TG_Y);

	//selectarrows
	PA_CreateSprite(0,9,(void*)editor_arrow_Sprite,OBJ_SIZE_16X32,1,4,LE_BG_SB_X1,LE_BG_SB_Y);
	PA_CreateSprite(0,10,(void*)editor_arrow_Sprite,OBJ_SIZE_16X32,1,4,LE_BG_SB_X2,LE_BG_SB_Y);
	PA_SetSpriteHflip(0,10,1);
	
	PA_CreateSprite(0,13,(void*)editor_arrow_Sprite,OBJ_SIZE_16X32,1,4,LE_TG_SB_X1,LE_TG_SB_Y);
	PA_CreateSprite(0,14,(void*)editor_arrow_Sprite,OBJ_SIZE_16X32,1,4,LE_TG_SB_X2,LE_TG_SB_Y);
	PA_SetSpriteHflip(0,14,1);
	
	MEL_Options_UpdateIMG();//update bg,tilegfx,.. selected
}
void MEL_Options_UpdateIMG(){
	//bg:
		switch(mel_events[LEVELDATA_BG]){
			case 0:
				PA_UpdateGfx(0,gfx.editor_bg,(void*)editor_bg0_Sprite);
				break;
			case 1:
				PA_UpdateGfx(0,gfx.editor_bg,(void*)editor_bg1_Sprite);
				break;
			case 2:
				PA_UpdateGfx(0,gfx.editor_bg,(void*)editor_bg2_Sprite);
				break;
			case 3:
				PA_UpdateGfx(0,gfx.editor_bg,(void*)editor_bg3_Sprite);
				break;
		}
	//tilegfx:
		switch(mel_events[LEVELDATA_TILES]){
			case 1:
				PA_UpdateGfx(0,gfx.editor_tg[0],(void*)editor_tilegfx1_Sprite);
				PA_UpdateGfx(0,gfx.editor_tg[1],(void*)editor_tilegfx1_Sprite+2048);
				break;
			case 2:
				PA_UpdateGfx(0,gfx.editor_tg[0],(void*)editor_tilegfx2_Sprite);
				PA_UpdateGfx(0,gfx.editor_tg[1],(void*)editor_tilegfx2_Sprite+2048);
				break;
			case 3:
				PA_UpdateGfx(0,gfx.editor_tg[0],(void*)editor_tilegfx3_Sprite);
				PA_UpdateGfx(0,gfx.editor_tg[1],(void*)editor_tilegfx3_Sprite+2048);
				break;
			case 4:
				PA_UpdateGfx(0,gfx.editor_tg[0],(void*)editor_tilegfx4_Sprite);
				PA_UpdateGfx(0,gfx.editor_tg[1],(void*)editor_tilegfx4_Sprite+2048);
				break;
		}
}

void MEL_CheckLevelOptionButtons(){
	if(Stylus.Newpress){
		u16 x;
		u16 y;
		
	//option buttons (select bg, tilegfx, music, etc..)-----------
		//BG SELECT LEFT
		x = LE_BG_SB_X1;
		y = LE_BG_SB_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SelArrow_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SelArrow_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(select_sound);
			
			if(mel_events[LEVELDATA_BG]==0)mel_events[LEVELDATA_BG]=TOTAL_BG;
			else mel_events[LEVELDATA_BG]--;
			MEL_Options_UpdateIMG();
			
			PA_SetSpriteAnim(0,9,1);
			Wait(3);
			PA_SetSpriteAnim(0,9,0);
		}
		
		//BG SELECT RIGHT
		x = LE_BG_SB_X2;
		y = LE_BG_SB_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SelArrow_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SelArrow_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(select_sound);
			
			if(mel_events[LEVELDATA_BG]==TOTAL_BG)mel_events[LEVELDATA_BG]=0;
			else mel_events[LEVELDATA_BG]++;
			MEL_Options_UpdateIMG();
			
			PA_SetSpriteAnim(0,10,1);
			Wait(3);
			PA_SetSpriteAnim(0,10,0);
		}
		
		//TileGFX SELECT LEFT
		x = LE_TG_SB_X1;
		y = LE_TG_SB_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SelArrow_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SelArrow_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(select_sound);
			
			if(mel_events[LEVELDATA_TILES]==1)mel_events[LEVELDATA_TILES]=TOTAL_TILEGFX;
			else mel_events[LEVELDATA_TILES]--;
			MEL_Options_UpdateIMG();
			
			PA_SetSpriteAnim(0,13,1);
			Wait(3);
			PA_SetSpriteAnim(0,13,0);
		}
		
		//TileGFX SELECT RIGHT
		x = LE_TG_SB_X2;
		y = LE_TG_SB_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SelArrow_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SelArrow_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(select_sound);
			
			if(mel_events[LEVELDATA_TILES]==TOTAL_TILEGFX)mel_events[LEVELDATA_TILES]=1;
			else mel_events[LEVELDATA_TILES]++;
			MEL_Options_UpdateIMG();
			
			PA_SetSpriteAnim(0,14,1);
			Wait(3);
			PA_SetSpriteAnim(0,14,0);
		}
	//--------------------------------------------------------------
	
	
	//bottom buttons------------------------------------------------
		x = LOAD_BACK_X;
		y = LOAD_BACK_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(back_sound);
			
			HideButtonEffect(0,0,x,y);
			game.option_selected = 0;//go to level manager
		}
		
		x = TESTBUTTON_X;
		y = TESTBUTTON_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(accept_sound);
			HideButtonEffect(0,1,x,y);
			game.option_selected = 4;//go to test level
		}
		
		x = EDITMAPBUTTON_X;
		y = EDITMAPBUTTON_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(accept_sound);
			HideButtonEffect(0,2,x,y);
		}
		
		x = EVENTSBUTTON_X;
		y = EVENTSBUTTON_Y;
		if((Stylus.X>x)&&(Stylus.X<x+SB_width)&&(Stylus.Y>y)&&(Stylus.Y<y+SB_height)&&(!game.stopcheck)){
			game.stopcheck=1;
			NewSound(accept_sound);
			HideButtonEffect(0,3,x,y);
		}
		//---------------
	}
}

//MEL: TEST
void MEL_GotoTest(){
	CleanScreen(0);
	CleanScreen(1);
	LevelClean();
	
	//test vars for hero
		//all weaponsz
		u8 b;
		for(b=1;b<9;b++){
			hero.numshoots[b] = 3;
			hero.maxammo[b] = UNLIMITED_AMMO;
			hero.ammo[b] = hero.maxammo[b];
		}
		hero.weapon = 1;
		//skills
		for(b=0;b<10;b++){
			data.skills[b] = 1;
		}
		hero.speedinc = 0;
		hero.jumppower = defaultJUMPPOWER;
		
		hero.hp = 200;
		hero.maxhp = hero.hp;
		if(data.skills[0]==1)hero.speedinc = SKILL_SPEED_INC;
		if(data.skills[1]==1)hero.jumppower = defaultJUMPPOWER + SKILL_JUMP_INC;
	//----------
	
	//load map
		//LoadMap(0);
		sprites[0].free = 1;	//sprite number 0 is allways used! (the hero)
		sprites[1].free = 10;	//sprite number 0 is allways used! (the hero)
		sprites[2].free = 10;	//sprite number 0 is allways used! (the hero)
		LoadGFX(0);
		LoadTeleports();
		
		hero.status_changed = 1;
		hero.x = game.levelevent[LEVELDATA_HEROX]<<11;
		hero.y = game.levelevent[LEVELDATA_HEROY]<<11;
		hero.scrollx = 0;
		hero.flip = 0;	//0=right ... 1=left
		hero.vy = 0;
		sprites[1].size = 32;//set arm size
		game.mapdot[0]=1;//set hero map dot
		
		UpdateStats();
		UpdateXY();
		
		HeroChangeWeapon(hero.weapon);
		game.ballraiseprio=1;
		game.levelwidth = 1024;
		boss.loaded=0;
	//-------------
	FadeOut(4);
	while(game.option_selected==4){
		MoveHero();
		UseWeapon();
		
		UpdateHeroSprites();
		Stylus_Actions();//stylus aiming and fix arm!
		SpriteActions();
		
		CheckEvents();//check if there's any monster or item to be shown
		CheckStats();//check hero status, options changes etc..
		
		UpdateScroll();
		UpdateSoundVars();
		UpdateStats();
		
		if(Pad.Newpress.Start)game.option_selected = 1;//go back to level options
		PA_WaitForVBL();
	}
	FadeIn(4);
}


//MEL: OTHERS
void MEL_New(){
//copiar un mapa para test hasta k no haya map editor
	u16 a;
	
	for(a=0; a<4096; a++){
		mel_map[a] = level_31_Map[a];
	}
	
	for(a=0; a<84; a++){
		mel_events[a] = level31_events[a];
	}
/*
	mel_events[LEVELDATA_TOTALEVENTS] = 0;
	mel_events[LEVELDATA_HEROX] = 2;
	mel_events[LEVELDATA_HEROY] = 16;
	mel_events[LEVELDATA_BG] = 0;
	mel_events[LEVELDATA_MAPWIDTH] = 0;
	mel_events[LEVELDATA_TILES] = 1;
	mel_events[LEVELDATA_TYPE] = 0;*/
}

void MEL_SaveLevel(){//Save level on .mel file..slot= slot on level file (0-10 slots)
	//copiar buff de archivo
	u16 buff[MEL_FILESIZE];
	u16 a;
	
	//READ
		file=FAT_fopen(mel_file,"r");
		FAT_fread(&buff, sizeof(u16), MEL_FILESIZE,file);
		FAT_fclose(file);
	//-----
	
	//EDIT
		//grabar mel_events
		for(a=0;a<208;a++){
			buff[MEL_DATA_START + (mel_slot*MEL_DATA_LEVELSIZE) + a] = mel_events[a];
		}
//16x16 tiles:


		//grabar mel_map
		u16 x=0;//tile x counter
		u16 y=0;//tile y counter
		
		//check which tilegfx is used
			u16 const* tilegfx=0;
			switch(mel_events[LEVELDATA_TILES]){
				case 0:
					tilegfx = tilegfx0_Map;
					break;
				case 1:
					tilegfx = tilegfx1_Map;
					break;
				case 2:
					tilegfx = tilegfx2_Map;
					break;
				case 3:
					tilegfx = tilegfx3_Map;
					break;
				case 4:
					tilegfx = tilegfx4_Map;
					break;
			}
		//-
		
		//1 tile: +1
		//1 row: +128
		u16 xm=0;//contador X mel_map
		u16 ym=0;//Y
		
		u32 t1=0;//temp x and y
		u32 t2=0;
		for(a=0;a<MEL_DATA_MAPLEVELSIZE;a++){
			xm+=2;
			if(xm==64){ym+=2;xm=0;}
			for(y=0;y<2;y++){
				for(x=0;x<64;x++){
					t1 = 512+xm+(ym<<8);
					t2 = (y<<9)+(x<<1);
					if(   (mel_map[    t1]==tilegfx[t2])//y<<9 -> y*128(tiles largo)*2(filas)
						&&(mel_map[  t1+1]==tilegfx[t2 + 1])
						&&(mel_map[t1+128]==tilegfx[t2 + 128])
						&&(mel_map[t1+129]==tilegfx[t2 + 129]))
					{
						buff[MEL_DATA_START + 208 + a] = x;
						x=64;y=2;//force STOP and go to check next tile..
					}
				}
			}
		}
	//----------------
	
	//SAVE
		file=FAT_fopen(mel_file,"w");
		FAT_fwrite(&buff, sizeof(u16), MEL_FILESIZE,file);
		FAT_fclose(file);
	//--------
}
