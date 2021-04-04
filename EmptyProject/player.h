#pragma once

class Player
{
public:


	int posX;
	int posY;
	int heart;
	int speed;

	LPD3DXSPRITE spr;
	LPDIRECT3DTEXTURE9* playerTex;

	Player();
	~Player();
	void Update();
	void Render();
	
	D3DXVECTOR2 getPos() { return { (float)posX, (float)posY }; }
	void setPos(D3DXVECTOR2 dir) { posX = dir.x; posY = dir.y; }
	void move(D3DXVECTOR2 dir) { posX += dir.x; posY += dir.y; }
	int getSpeed() { return speed; }
	void setSpeed(int speed) { speed = speed; }



};