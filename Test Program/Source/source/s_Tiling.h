#ifndef S_TILING_H
#define S_TILING_H

#define TILEWIDTH    8
#define TILEHEIGHT   8

#define HEADERHEIGHT 3
#define GAMEHEIGHT   31
#define FOOTERHEIHT  2

#define HEADERWIDTH  28
#define GAMEWIDTH    28
#define FOOTERWIDTH  28

namespace s_Tiling
{
	enum tilingType
	{
		BLANK        = 0x00000000, //tiling for blank spaces which pacman can move around.
		WALL         = 0x00000001, //tiling for walls which block pacman.
		BORDER_WALL  = 0x00000003, //tiling for the boarder of the map. Acts like wall, just a style change.
		DEN_WALL	 = 0x00000005, //see border wall.
		DEN_GATE	 = 0x00000007, //tiling for the gate in the ghost den. Nothing can pass.
	};
	//note: one's bit represents if terrain is passible.
	//0: can be passed.
	//1: cannot be passed

	struct tileData
	{
		tilingType type;
	};

	//collision box forf tiles which have collision attached to them

	struct tileMap
	{
		tilingType map[GAMEHEIGHT][GAMEWIDTH];
	};

	//data of the maze or "game map" that pac-man and the ghost runs around in.
	//half way through writing this I realized I could just have the x dimension of the matrix
	//mirrored to save writing time but I was too lazy to change it. :(
	//I also realized i could just have a step number of unique "strips" or map and copy pasta them in
	//where needed. :(
	//I hind sight I guess these are lessons learned for how to prevent excess typing in the future.
	const struct tileMap gameMap =
	{
		{
			{BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL,
			 BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL,
			 BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL,
			 BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL}, //0, x

			{BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, WALL,
			 WALL, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL}, //1, x

			{BORDER_WALL, BLANK, WALL, WALL, WALL, WALL, BLANK,
			 WALL, WALL, WALL, WALL, WALL, BLANK, WALL,
			 WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 BLANK, WALL, WALL, WALL, WALL, BLANK, BORDER_WALL}, //2, x

			{BORDER_WALL, BLANK, WALL, WALL, WALL, WALL, BLANK,
			 WALL, WALL, WALL, WALL, WALL, BLANK, WALL,
			 WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 BLANK, WALL, WALL, WALL, WALL, BLANK, BORDER_WALL}, //3, x

			{BORDER_WALL, BLANK, WALL, WALL, WALL, WALL, BLANK,
			 WALL, WALL, WALL, WALL, WALL, BLANK, WALL,
			 WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 BLANK, WALL, WALL, WALL, WALL, BLANK, BORDER_WALL}, //4, x

			{BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL}, //5, x

			{BORDER_WALL, BLANK, WALL, WALL, WALL, WALL, BLANK,
			 WALL, WALL, BLANK, WALL, WALL, WALL, WALL,
			 WALL, WALL, WALL, WALL, BLANK, WALL, WALL,
			 BLANK, WALL, WALL, WALL, WALL, BLANK, BORDER_WALL}, //6, x

			{BORDER_WALL, BLANK, WALL, WALL, WALL, WALL, BLANK,
			 WALL, WALL, BLANK, WALL, WALL, WALL, WALL,
			 WALL, WALL, WALL, WALL, BLANK, WALL, WALL,
			 BLANK, WALL, WALL, WALL, WALL, BLANK, BORDER_WALL}, //7, x

			{BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 WALL, WALL, BLANK, BLANK, BLANK, BLANK, WALL,
			 WALL, BLANK, BLANK, BLANK, BLANK, WALL, WALL, 
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL}, //8, x

			{BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BLANK,
			 WALL, WALL, WALL, WALL, WALL, BLANK, WALL,
			 WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 BLANK, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL}, //9, x

			{BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL, BLANK, 
			 WALL, WALL, WALL, WALL, WALL, BLANK, WALL,
			 WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 BLANK, BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK}, //10, x

			{BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL, BLANK,
			 WALL, WALL, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, WALL, WALL,
			 BLANK, BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK}, //11, x

			{BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL, BLANK,
			 WALL, WALL, BLANK, DEN_WALL, DEN_WALL, DEN_WALL, DEN_GATE,
			 DEN_GATE, DEN_WALL, DEN_WALL, DEN_WALL, BLANK, WALL, WALL,
			 BLANK, BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK}, //12, x

			{BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BLANK,
			 WALL, WALL, BLANK, DEN_WALL, DEN_WALL, DEN_WALL, DEN_GATE,
			 DEN_GATE, DEN_WALL, DEN_WALL, DEN_WALL, BLANK, WALL, WALL,
			 BLANK, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL}, //13, x

			{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, DEN_WALL, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, DEN_WALL, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //14, x

			{BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BLANK,
			 WALL, WALL, BLANK, DEN_WALL, DEN_WALL, DEN_WALL, DEN_GATE,
			 DEN_GATE, DEN_WALL, DEN_WALL, DEN_WALL, BLANK, WALL, WALL,
			 BLANK, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL}, //15, x

			{BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL, BLANK,
			 WALL, WALL, BLANK, DEN_WALL, DEN_WALL, DEN_WALL, DEN_WALL,
			 DEN_WALL, DEN_WALL, DEN_WALL, DEN_WALL, BLANK, WALL, WALL,
			 BLANK, BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK}, //16, x

			{BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL, BLANK,
			 WALL, WALL, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, WALL, WALL,
			 BLANK, BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK}, //17, x

			{BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL, BLANK,
			 WALL, WALL, BLANK, WALL, WALL, WALL, WALL,
			 WALL, WALL, WALL, WALL, BLANK, WALL, WALL,
			 BLANK, BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK}, //18, x

			{BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BLANK,
			 WALL, WALL, BLANK, WALL, WALL, WALL, WALL,
			 WALL, WALL, WALL, WALL, BLANK, WALL, WALL,
			 BLANK, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL}, //19, x

			{BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, WALL,
			 WALL, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL}, //20, x

			{BORDER_WALL, BLANK, WALL, WALL, WALL, WALL, BLANK,
			 WALL, WALL, WALL, WALL, WALL, BLANK, WALL,
			 WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 BLANK, WALL, WALL, WALL, WALL, BLANK, BORDER_WALL}, //21, x

			{ BORDER_WALL, BLANK, WALL, WALL, WALL, WALL, BLANK,
			 WALL, WALL, WALL, WALL, WALL, BLANK, WALL,
			 WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 BLANK, WALL, WALL, WALL, WALL, BLANK, BORDER_WALL }, //22, x

			{BORDER_WALL, BLANK, BLANK, BLANK, WALL, WALL, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, WALL, WALL, BLANK, BLANK, BLANK, BORDER_WALL }, //23, x

			{BORDER_WALL, WALL, WALL, BLANK, WALL, WALL, BLANK,
			 WALL, WALL, BLANK, WALL, WALL, WALL, WALL,
			 WALL, WALL, WALL, WALL, BLANK, WALL, WALL,
			BLANK, WALL, WALL, BLANK, WALL, WALL, BORDER_WALL}, //24, x

			{ BORDER_WALL, WALL, WALL, BLANK, WALL, WALL, BLANK,
			 WALL, WALL, BLANK, WALL, WALL, WALL, WALL,
			 WALL, WALL, WALL, WALL, BLANK, WALL, WALL,
			BLANK, WALL, WALL, BLANK, WALL, WALL, BORDER_WALL }, //25, x

			{BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 WALL, WALL, BLANK, BLANK, BLANK, BLANK, WALL,
			 WALL, BLANK, BLANK, BLANK, BLANK, WALL, WALL,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL}, //26, x

			{BORDER_WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 WALL, WALL, WALL, WALL, WALL, BLANK, WALL,
			 WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 WALL, WALL, WALL, WALL, WALL, BLANK, BORDER_WALL}, //27, x

			{BORDER_WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 WALL, WALL, WALL, WALL, WALL, BLANK, WALL,
			 WALL, BLANK, WALL, WALL, WALL, WALL, WALL,
			 WALL, WALL, WALL, WALL, WALL, BLANK, BORDER_WALL}, //28, x

			{BORDER_WALL, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK,
			 BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BORDER_WALL}, //29, x

			{BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL,
			 BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL,
			 BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL,
			 BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL, BORDER_WALL}  //30, x
		}
	};

	void loadMap();

	void unloadMap();
}

#endif