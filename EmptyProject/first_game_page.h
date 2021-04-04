#pragma once
#include "page.h"

class FirstGamePage : public Page
{
public:

	FirstGamePage();
	virtual ~FirstGamePage();

	void Update() override;
	void Render() override;


	LPD3DXSPRITE spr;
	LPDIRECT3DTEXTURE9* backgroundTex;


};