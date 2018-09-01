void Stylus_Actions(){
	u16 angle;
	//update arm angle
	if((data.skills[5])&&(Stylus.Held)){
		if(hero.flip==0)sprites[0].shoot_x = 32;
		else sprites[0].shoot_x = 16;
	
		sprites[0].shootangle = (PA_GetAngle( ((sprites[0].x-hero.scrollx)>>8)+sprites[0].shoot_x, (sprites[0].y>>8)+sprites[0].shoot_y, Stylus.X, Stylus.Y))/1.42;
		
		if((sprites[0].shootangle>100)&&(sprites[0].shootangle<260))hero.flip = 1;
		else if((sprites[0].shootangle<80)||(sprites[0].shootangle>280))hero.flip = 0;
	}
	else {
		if(hero.manual_aim==0){
			angle = sprites[0].shootangle;
			if(hero.flip==1){
				if(angle!=180){
					if(angle>185)angle-=5;
					else if(angle<175)angle+=5;
					else angle=180;
					
					if(angle<90)angle=180;
					else if(angle>270)angle=180;
				}
			}
			else {
				if(angle!=0){
					if(angle>175)angle+=5;
					else if(angle>5)angle-=5;
					else angle=0;
					
					if(angle>270)angle=0;
					else if(angle>90)angle=0;
					
					if(angle>=355)angle = 0;
				}
			}
			sprites[0].shootangle = angle;
		}
	}
}
