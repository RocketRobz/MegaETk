//LA SHOP...

#define SHOP_ITEMS 22


//shop_price: precio de los items (dividido entre 100.. ejemplo: 15 -> 1500)
const unsigned short shop_price[SHOP_ITEMS] __attribute__ ((aligned (4))) = {
10,20,40,80,160,320,//hp up
50,//AP up
50,//mov speed
100,//jump power up
5,//map
50,//monster info
100,//laser weapon
200,//flamethrower
20,//crouch
50,//dash
50,//jump+dash
100,//aim 360º
250,//double jump
300,//rocket launcher
1500,//gold armor
1500,//gold arm
0,//???
};


//shop.unlocked: si el item esta desbloqueado o no
const unsigned short shop_unlocked[SHOP_ITEMS] __attribute__ ((aligned (4))) = {
1,0,0,0,0,0,//hp up
1,//AP up
0,//mov speed
0,//jump power up
1,//map
0,//monster info
1,//laser weapon
0,//flamethrower
0,//crouch
0,//dash
1,//jump+dash
1,//aim 360º
0,//double jump
0,//shield
0,//gold armor
0,//gold arm
0,//???
};


//que item desbloquea		(numero en que acaba)
const unsigned short shop_unlocks[SHOP_ITEMS] __attribute__ ((aligned (4))) = {
1,2,3,4,5,0,//hp up	(5)
6,//AP up	(6)
8,//mov speed  	(7) 
19,//jump power up	(8)
10,//map		(9)
7,//monster info		(10)
12,//laser weapon	(11)
18,//flamethrower	(12)
14,//crouch	(13)
15,//dash	(14)
17,//jump+dash	(15)
20,//aim 360º	(16)
0,//double jump	(17)
0,//rocket launcher	(18)
0,//gold armor	(19)
0,//gold arm	(20)
0,//???
};

//items comprados
const unsigned short shop_bought[SHOP_ITEMS] __attribute__ ((aligned (4))) = {
0,0,0,0,0,0,//hp up
0,//AP up
0,//mov speed
0,//jump power up
0,//map
0,//monster info
0,//laser weapon
0,//flamethrower
0,//crouch
0,//dash
0,//jump+dash
0,//aim 360º
0,//double jump
0,//rocket launcher
0,//gold armor
0,//gold arm
0,//???
};
