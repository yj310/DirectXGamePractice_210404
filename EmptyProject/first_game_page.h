#pragma once
#include "page.h"
#include "global.h"
#include "player.h"

class FirstGamePage : public Page
{
public:

	FirstGamePage();
	virtual ~FirstGamePage();

	void Update() override;
	void Render() override;
	void MapUpdate();
	void PlayerMove();
	void GetLand();
	void FloodFill();
	void Bordering();

	struct Point
	{
		int x;
		int y;
		Point(int x, int y)
			: x(x), y(y)
		{}
	};



	int score;
	Player* player;
	bool isFinish;
	int visitingX;
	int visitingY;
	bool isSpace;
	bool isVisiting;

	LPD3DXSPRITE spr;
	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* floorTex;
	LPDIRECT3DTEXTURE9* maskTex;




	int map[FLOOR_WIDTH * FLOOR_HEIGHT];

	DWORD floorP[FLOOR_WIDTH * FLOOR_HEIGHT];
	DWORD maskP[FLOOR_WIDTH * FLOOR_HEIGHT];

	DWORD virtualMap[FLOOR_WIDTH * FLOOR_HEIGHT];

};