#define SHOT_CHANNEL 4
#define DAMAGE_CHANNEL 5
#define ITEM_CHANNEL 6
#define OTHERS_CHANNEL 7

//sounds
#define shot1_sound 0
#define floor_sound 1
#define item_sound 2
#define dash_sound 3
#define die_sound 4
#define boss_die_sound 5
#define itemp_sound 6
#define laser_sound 7
#define huya_sound 8
#define select_sound 9
#define haha_sound 10
#define door_sound 11
#define accept_sound 12
#define back_sound 13
#define hithero_sound 14
#define hitmonster_sound 15

u8 GetSoundChannel(){
	u8 a;
	
	for(a=0;a<=7;a++){
		if(sound.id[a]==0)return a;	
	}

	return 0;
}

void NewSound(u8 name){
	u8 sfx;
	//sfx = GetSoundChannel();
	switch(name){
		case shot1_sound://shot1
			sfx = SHOT_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 2;
				sound.counter[sfx] = 1;
				PA_StopStream(SHOT_CHANNEL);
				PA_PlaySoundEx(sfx,(void*)snd_shot1_raw,2447,64,11205,1);
			}
			break;
			
		case floor_sound://hit floor
			sfx = OTHERS_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 4;
				sound.counter[sfx] = 15;
				PA_StopStream(OTHERS_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_floor_raw);
			}
			break;
			
		case item_sound://item
			sfx = ITEM_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 4;
				sound.counter[sfx] = 15;
				PA_StopStream(ITEM_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_item_raw);
			}
			break;
			
		case dash_sound://DASH
			sfx = OTHERS_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 4;
				sound.counter[sfx] = 15;
				PA_StopStream(OTHERS_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_dash_raw);
			}
			break;
			
		case die_sound://DIE
			sfx = OTHERS_CHANNEL;
			sound.id[sfx] = 4;
			sound.counter[sfx] = 15;
			PA_StopStream(OTHERS_CHANNEL);
			PA_PlaySimpleSound(sfx,(void*)snd_die_raw);
			break;
			
		case boss_die_sound://BOSS DIE
			sfx = OTHERS_CHANNEL;
			sound.id[sfx] = 4;
			sound.counter[sfx] = 15;
			PA_StopStream(OTHERS_CHANNEL);
			PA_PlaySimpleSound(sfx,(void*)snd_boss_die_raw);
			break;
		
		case itemp_sound://ITEM POWER UP SOUND
			sfx = ITEM_CHANNEL;
			sound.id[sfx] = 4;
			sound.counter[sfx] = 15;
			PA_StopStream(ITEM_CHANNEL);
			PA_PlaySimpleSound(sfx,(void*)snd_itemp_raw);
			break;
			
		case laser_sound://LASER
			sfx = SHOT_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 2;
				sound.counter[sfx] = 5;
				PA_StopStream(SHOT_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_laser_raw);
			}
			break;
		case huya_sound://HUYA
			sfx = SHOT_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 2;
				sound.counter[sfx] = 30;
				PA_StopStream(SHOT_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_huya_raw);
			}
			break;
		case select_sound://SELECT
			sfx = OTHERS_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 2;
				sound.counter[sfx] = 1;
				PA_StopStream(OTHERS_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_select_raw);
			}
			break;
		case haha_sound://HAHA
			sfx = ITEM_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 2;
				sound.counter[sfx] = 30;
				PA_StopStream(ITEM_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_haha_raw);
			}
			break;
		case door_sound://DOOR
			sfx = ITEM_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 2;
				sound.counter[sfx] = 10;
				PA_StopStream(ITEM_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_door_raw);
			}
			break;
		case accept_sound://ACCEPT
			sfx = ITEM_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 2;
				sound.counter[sfx] = 1;
				PA_StopStream(ITEM_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_accept_raw);
			}
			break;
		case back_sound://BACK
			sfx = ITEM_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 2;
				sound.counter[sfx] = 10;
				PA_StopStream(ITEM_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_back_raw);
			}
			break;
		case hithero_sound://HIT HERO
			sfx = DAMAGE_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 2;
				sound.counter[sfx] = 1;
				PA_StopStream(DAMAGE_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_hithero_raw);
			}
			break;
		case hitmonster_sound://HIT MONSTER
			sfx = DAMAGE_CHANNEL;
			if(sound.counter[sfx]==0){
				sound.id[sfx] = 2;
				sound.counter[sfx] = 1;
				PA_StopStream(DAMAGE_CHANNEL);
				PA_PlaySimpleSound(sfx,(void*)snd_hitmonster_raw);
			}
			break;
		default:
			break;
	}
}

void UpdateSoundVars(){
	u8 a;
	
	for(a=0;a<=7;a++){
		if(sound.id[a]>1){
			sound.counter[a]--;
			if(sound.counter[a]<=0){
				sound.id[a]=0;
				sound.counter[a]=0;
			}
		}
	}
}
