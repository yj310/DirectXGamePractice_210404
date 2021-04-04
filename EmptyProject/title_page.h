#pragma once
#include "page.h"

class TitlePage : public Page
{
public:

	TitlePage();
	virtual ~TitlePage();

	void Update() override;
	void Render() override;

	LPD3DXSPRITE spr;
	LPDIRECT3DTEXTURE9* backgroundTex;

	LPDIRECT3DTEXTURE9* startButtonTex1;
	LPDIRECT3DTEXTURE9* startButtonTex2;
	LPDIRECT3DTEXTURE9* introButtonTex1;
	LPDIRECT3DTEXTURE9* introButtonTex2;
	LPDIRECT3DTEXTURE9* manualButtonTex1;
	LPDIRECT3DTEXTURE9* manualButtonTex2;
	LPDIRECT3DTEXTURE9* rankingButtonTex1;
	LPDIRECT3DTEXTURE9* rankingButtonTex2;
	LPDIRECT3DTEXTURE9* exitButtonTex1;
	LPDIRECT3DTEXTURE9* exitButtonTex2;

	int startState;
	int introState;
	int manualState;
	int rankingState;
	int exitState;




};