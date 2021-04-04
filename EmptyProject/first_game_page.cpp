
#include "DXUT.h"
#include "first_game_page.h"
#include "global.h"

FirstGamePage::FirstGamePage()
{
	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/firstGameBackground.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, backgroundTex);


	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);


}

FirstGamePage::~FirstGamePage()
{
	(*backgroundTex)->Release();
	spr->Release();
}

void FirstGamePage::Update()
{

}

void FirstGamePage::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	

	spr->End();
}
