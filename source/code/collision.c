u8 HCola(u8 i, s16 moved){
	s32 x = (sprites[i].x + moved)>>8;
	s32 y = sprites[i].y>>8;
	u8 w1 = sprites[i].w1;
	u8 w2 = sprites[i].w2;
	u8 h1 = sprites[i].h1;
	u8 h2 = sprites[i].h2;
	u8 size = sprites[i].size;
	u8 a;
	u8 b = 0;
	u8 c=SPRITES_PRIO;
	u8 d = 0;
	s8 counter;
	
	//si hay boss, que no deje pasaar de la <------
	if((!game.disable_outscreen)&&(boss.loaded)){
		if( (((x<<8)-hero.scrollx)>>8) < (16-w1))return 1;
	}
	
	
	
	//check if it's out of teh screen
	if((x <= 0) || ( x >= game.levelwidth - size + w2))return 1;
	if( y < 0 )y = 0;
	
	if(moved>0)a = size - w2;
	else a = w1;
	
	y += h1;
	size -= h1;
	
	if(i==0)counter = -8;
	else counter = 2;
	
	for(counter = counter;counter<(size - h2 - h1 - 1);counter+=8){
		d = game.levelmap[(((y + h1 + counter - 1)>>3)<<7) + ((x + a)>>3)];
		if(CheckTileCollision(d) == 1)b = 1;
		
		
		//mirar transparent
		if(c==SPRITES_PRIO)c = CheckTransparency(d);
		//-----------------
		
	}
	if(CheckTileCollision(game.levelmap[(((y + size - h2 - 1)>>3)<<7) + ((x + a)>>3)]) == 1)b = 1;
	
	PA_SetSpritePrio(0,i,c);
	return b;
}

u8 VCola(u8 i){
	s16 x = sprites[i].x>>8;
	s16 y = sprites[i].y>>8;
	u8 w1 = sprites[i].w1;
	u8 w2 = sprites[i].w2;
	u8 h2 = sprites[i].h2;
	u8 size = sprites[i].size;
	
	u16 a=0,b=0;

	//check if it's out of teh screen
	if( x <= 0 )return 1;
	
	a = game.levelmap[(((y + size - h2)>>3)<<7) + ((x + w1)>>3)];
	b = game.levelmap[(((y + size - h2)>>3)<<7) + ((x + size - w2)>>3)];
	
	if((i!=0)||(hero.dash==0)){
		//mirar transparent
		u8 c;
		c = CheckTransparency(a);
		if(c==SPRITES_PRIO)c = CheckTransparency(b);
		PA_SetSpritePrio(0,i,c);
		//-----------------
	}
	
	if( y > -32){
		if( (CheckTileCollision(a) == 1 )
			|| (CheckTileCollision(b) == 1 ))return 1;
		else return 0;
	}
	else{
		if(game.levelmap[((x + w1)>>3)] != 0)return 0;
	}
	return 0;
}

u8 VCola2(u8 i, s16 moved){
	s16 x = sprites[i].x>>8;
	s16 y = sprites[i].y>>8;
	u8 w1 = sprites[i].w1;
	u8 w2 = sprites[i].w2;
	u8 h1 = sprites[i].h1;
	u8 h2 = sprites[i].h2;
	u8 size = sprites[i].size;
	
	u16 a=0,b=0,c=SPRITES_PRIO;

	//check if it's out of teh screen
	if( x <= 0 )return 1;
	
	if(moved>0){//para arriba
		if( y > -32){
			a = game.levelmap[(((y + h1 - (moved>>8))>>3)<<7) + ((x + w1)>>3)];
			b = game.levelmap[(((y + h1 - (moved>>8))>>3)<<7) + ((x + size - w2)>>3)];
			
			//mirar transparent
			c = CheckTransparency(a);
			if(c==SPRITES_PRIO)c = CheckTransparency(b);
			PA_SetSpritePrio(0,i,c);
			//-----------------
			
			if((CheckTileCollision(a)==1) || (CheckTileCollision(b)==1))return 1;
		}
		else{
			if(game.levelmap[((x + w1)>>3)] != 0)return 0;
		}
	}
	else{//para abajo
		a = game.levelmap[(((y + size - h2 - (moved>>8))>>3)<<7) + ((x + w1)>>3)];
		b = game.levelmap[(((y + size - h2 - (moved>>8))>>3)<<7) + ((x + size - w2)>>3)];
		
		//mirar transparent
		c = CheckTransparency(a);
		if(c==SPRITES_PRIO)c = CheckTransparency(b);
		PA_SetSpritePrio(0,i,c);
		//-----------------
		
		if((CheckTileCollision(a)==1) || (CheckTileCollision(b)==1))return 1;
	}
	
	return 0;
}

u8 CheckTileCollision(u8 tile){
	u8 i;
	for(i=0;i<TOTAL_TRANS;i++){
		if(tile==game.levelmap_trans[i])return 0;
	}
	return 1;
}

//SPRITE collision------------------
//--------------------------------
u8 SCol(u8 s1, u8 s2){
	//CHECKING COLLISION BETWEEN SPRITES
	u16 ax = sprites[s1].x>>8;
	u16 ay = sprites[s1].y>>8;
	u16 bx = sprites[s2].x>>8;
	u16 by = sprites[s2].y>>8;
	u8 aw1, aw2, ah1, ah2, asize, bw1, bw2, bh1, bh2, bsize;

	aw1 = sprites[s1].w1;
	aw2 = sprites[s1].w2;
	ah1 = sprites[s1].h1;
	ah2 = sprites[s1].h2;
	asize = sprites[s1].size;

	bw1 = sprites[s2].w1;
	bw2 = sprites[s2].w2;
	bh1 = sprites[s2].h1;
	bh2 = sprites[s2].h2;
	bsize = sprites[s2].size;
	//-------------------------------------
	
	if((aw1==16)&&(aw2==16)&&(ah1==16)&&(ah2==16))return 0;
	if((bw1==16)&&(bw2==16)&&(bh1==16)&&(bh2==16))return 0;
	
	
	u8 a,b;

	for(b=0;b<sprites[s1].size - aw2-4;b+=4){
		for(a=0;a<sprites[s1].size - ah2;a+=4){
			if((((ax + aw1 + b) > (bx + bw1)) && ((ax + aw1 + b) < (bx + bsize - bw2)))
				 && (((ay + ah1 + a) > (by + bh1)) && ((ay + ah1 + a) < (by + bsize - bh2))))return 1;
			//if(a+4>sprites[s1].size-ah2)break;
		}
		//if(b+4>sprites[s1].size-aw2)break;
	}

	return 0;
}
