//Debug
void Debug();
void BossDebug();
void CollisionDebug();
void AvailableSpriteDebug();
void GeneralInfoDebug();
void CheckEventDebug();
void MonsterDebug();
void SpriteIDDebug();
void ShootDebug();
void ItemDebug();
void ParticleDebug();
void RaiseParticleDebug();
void TeleportDebug();
void RotDebug();
void SoundDebug();

void ShowData();

void CleanText(u8 screen);
void ErrorScreen();

//LEVEL LOADING | level stuff
void LoadMonster(u8 i, u8 freesprite);
void LoadItem(u8 i, u8 freesprite);
void LoadOther(u8 i, u8 freesprite);
void Load_Level(u8 level);
void LoadMap(u8 map);
void LoadGFX(u8 level);
void LoadTeleports();
void LoadSprites();
void LoadPal();
void LoadSound();
void LevelClean();
void CleanScreen(u8 screen);

void LevelComplete();

void ResetShopValues();

//SAVE & LOAD DATA
void UpdateData();
void UpdateDataLoaded();
void SaveData();
void LoadData();
void LoadGame();

//crc
u16 CalcCrc(char *data, int length);
void EncryptDecrypt(u32 *data, u32 length);
void ConvertSave(u32 *data, u32 length);
int ConvertLoad(u32 *data, u32 length);

//MENUs
		void GotoSplash();
	//title
		void GotoTitle();
		void SetupTitle();
		void LoadTitleGfx();
		void ChangeTitleOption();
		void SelectTitleOption();
		//option selected..?
		void NewGame();
		void Continue();
		void GotoGameCredits();
	
	//select level menu
		void GotoMenu();
		void LoadMenu();
		void UpdateHPAPBar();
		void UpdateLvlThumb();
		void ScrollLevelSelect();
		void SelectLevel();
		void UpdateSelectLevel();
		void UpdateSelectedLvlGFX();
		void CheckSelectLevelButtons();
	
	//Shop
		void GotoShop();
		void LoadShop();
		void ShowShopItems();
		void ShowDescription(u8 item);
		void UpdateSelectShopItem();
		void BuyItem();
		void CheckShopButtons();
	
	
	//Status
		void SetupStatusScreen();
		void UpdateStatusScreen();
		void NewTextLine(u8 type, s32 a);
		void DrawMap();
		u8 Map_GetPixelColor(u16 tile);

	//SELECT SAVE/LOAD SLOT
		void GotoSelectSlot();
		void UpdateSelButton(u8 sel);
		void ReadSlots();
		void UpdateSlotData(u8 slot, u16 dist);
		u8 CheckSelectSlotButtons(u8 sel);
		void SelectSlot(u8 sel);
		void ResetGameVars();
		void SetSlotHidePrio(u8 slot,u8 prio);

	//EXTRAS
		void GotoExtras();
		void CheckExtrasButtons();
		void UpdateExtraSel(u8 sel);
		void SelectExtra(u8 sel);
		
		//LEVEL EDITOR
			void GotoLevelEditor();
			void MEL_CreateMEL(char filename[19], char autor[20], char levelname[20]);
			void MEL_New();//new level/map
			void MEL_SaveLevel();
			
			//level options
			void MEL_CreateNewLevel();
			
			void MEL_GotoLevelManager();
			void MEL_CheckLevelManagerButtons();
			void MEL_LM_UpdateSelected(u8 sel);
			
			void MEL_GotoOptions();
			void MEL_SetupLevelOptions();
			void MEL_Options_UpdateIMG();
			void MEL_CheckLevelOptionButtons();
			
			//level test
			void MEL_GotoTest();

	//Other
		void HideButtonEffect(u8 screen, u8 i, u16 x, u16 y);
		void HideButtonEffect2(u8 screen, u8 i, u16 x, u16 y);//pa la ->
//-------------------------

void GamePlay();

//BOSS
void LoadBoss();
void BossActions();
void BossHeroCollision();
void HitBoss(u8 dmg);
void Boss_Dies();
void Boss_Bubbleman();
void Boss_Screwman();
void Boss_Icyman();
void Boss_Ghoste();
void Boss_GhosteFINAL();

//WEAPONS
void Updateincammo();
void UseWeapon();
void NewShot(u8 type, u8 sprite);
u8 CanMultipleShot(u8 weapon);
void MultipleShot(u8 weapon, u8 sprite, u8 shoots);

//MOVING
void MoveMonster(u8 a);
void MoveFlyingMonster(u8 a);

void MoveShots(u8 i, u8 hero);//hero -> 0=shoot by monster .. 1=shoot by hero
void MoveHero();

//GENERAL
void Wait(u32 counter);
void Wait_or_skip(u32 counter);
void Pause();
void UpdateStats();
void UpdateXY();
void UpdateMapDots();
u8 GetFreeMapDot();
void OpenEvent(u8 i);
void SpriteActions();
void PauseAnim();
void UnPauseAnim();
void WaitForPressStart();
u8 CheckTransparency(u8 tile);//devuelve la prioridad del sprite que ha de tener para el tile que mira

u8 OutScreen(u8 i); //mira si el sprite queda fuera de la pantalla. si queda fuera -> return 1

void CheckEvents();
void CheckStats();
void CheckTeleport();
void UpdateScroll();

//MONSTER
void MonsterActions(u8 i);
void SummonMonster(u16 x, u16 y, u8 id);
u8 MonsterColCheck_Wall(u8 i);
u8 MonsterColCheck_Floor(u8 i);
//monstruos especificos
void AimShotLauncher(u8 i);

//HERO
void HeroCheckSkills(u8 inground);
void HeroDash();
void Hero_Die();
void UpdateHeroSprites();
void RestoreHeroSize();
void UpdateHeroVars();
u8 HeroCanDoAction();
void HeroChangeWeapon(u8 weapon);

//ITEMS
void UseItem(u8 i);
void NewCoin(u8 x, u8 y, u8 type);
void MoveCoin(u8 i);
u8 ItemisSpecial(u8 id);

//STYLUS
void Stylus_Actions();

//HIT
void HitMonster(u8 a, u8 i);
void NewHitHero(u8 m, u8 type);
void HitHero(u8 damage, u8 sprite);

//GET VALUES
u8 GetFreeRot();
u8 GetFreeSprite();
u8 GetSpriteFreeType(u8 a);
u8 PalUsed(u8 pal);

//KILL
void SetKillMonster(u8 a);
void KillSprite(u8 a);

//EFFECTS
void NewRaise(u8 i,u8 counter);//sprite nº, counter
void CheckBlink(u8 i);
void KillMonsterEffect(u8 a);

void ItemEffect(u8 i);

void SetRaise(u8 i, u8 counter);

void CreateExplosion1(u16 x, u16 y);
void CreateRaiseParticle(u16 x, u16 y);
void CreateBallRaiseParticle(u16 x, u16 y);
void CreateHumo(u16 x, u16 y, u8 face);
void CreateParticle(u8 m, u8 type);

//SOUND
u8 GetSoundChannel();
void UpdateSoundVars();
void NewSound(u8 sound);

//screen effects
void FadeIn(u8 speed);
void FadeOut(u8 speed);
void FadeInScreen(u8 speed, u8 screen);
void FadeOutScreen(u8 speed, u8 screen);
//AMO
void RefreshInfiniteAmmo(u8 i);

//COLLISION
void CheckHeroMapCollisions();
u8 HCol(int x, int y, u8 size, u8 width, u8 height, s8 moved, u8 dir);
u8 HCola(u8 sprite, s16 moved);
u8 VCola(u8 sprite);
u8 VCola2(u8 sprite, s16 moved);
u8 SCol(u8 sprite1, u8 sprite2);
u8 CheckTileCollision(u8 tile);
//--------------------------------
