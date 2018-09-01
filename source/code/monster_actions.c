void AimShotLauncher(u8 i){
	u8 ii = sprites[i].group;
	sprites[ii].rotangle = PA_GetAngle( ((sprites[i].x-hero.scrollx)>>8)+sprites[i].shoot_x, (sprites[i].y>>8)+sprites[i].shoot_y, ((hero.x-hero.scrollx)>>8)+((HERO_SIZE-12)>>1), (hero.y>>8)+((HERO_SIZE-12)>>1));
	sprites[i].shootangle = PA_GetAngle( ((sprites[i].x-hero.scrollx)>>8)+sprites[i].shoot_x, (sprites[i].y>>8)+sprites[i].shoot_y, ((hero.x-hero.scrollx)>>8)+(HERO_SIZE-12), (hero.y>>8)+((HERO_SIZE-12)))/1.42;
	PA_SetRotset(0, //screen
				sprites[ii].rot, // rotset
				sprites[ii].rotangle, // Angle...
				sprites[ii].zoom, 256);//zoom X,Y
}
