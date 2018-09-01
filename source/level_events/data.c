//QUE ES CADA COSA
//STAGE: lo que seleccionas en el menu de seleccion de niveles, cada stage suele tener 3 niveles
//LEVEL: el nivel en el que juegas, van dentro de los stage
//
// STAGE-LEVEL ... ejemplo: stage 1 y level 3 seria ->>>>> 1-3

//a que niveles va cada imagen del menu 'select level'

#define MENULVLTOTAL 13
#define TOTAL_LEVELS 41

//0: level to go
//1: gfx thumbnail (0=?)
const unsigned short menulvl[(MENULVLTOTAL*2)] __attribute__ ((aligned (4))) = {
1,1, 4,2, 7,3,		//world 1
10,4, 13,5, 16,6,	//world 2
19,7, 22,8, 25,9,	//world 3
28,10, 31,11, 34,12,//world 4
37,13//Final
};


//array que tiene valors de que level desbloquea cada level (del menu de seleccion de levels). 
//si es 0, no desbloquea nada..
//ejemplo: 
//0	<- level 0, lo pongo en linea aparte para que no estorbe :P
//0,0,1,2,0,0,4 //level 3 desbloquea stage 1
const unsigned short level_unlocks_stage[TOTAL_LEVELS+1] __attribute__ ((aligned (4))) = {
0,	//level 0
0,0,1,0,0,2,0,0,3, //1-9
0,0,4,0,0,5,0,0,6, //10-18
0,0,7,0,0,8,0,0,9, //19-27
0,0,10,0,0,11,0,0,12, //28-36
0,0,0,0,0//37-41
};
