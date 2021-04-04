
#include "DXUT.h"
#include "title_page.h"
#include "global.h"

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 60

TitlePage::TitlePage()
{
	startState = 0;
	introState = 0;
	manualState = 0;
	rankingState = 0;
	exitState = 0;

	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/titlePageBackground.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, backgroundTex);


	startButtonTex1 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/startButton1.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, startButtonTex1);


	startButtonTex2 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/startButton2.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, startButtonTex2);


	introButtonTex1 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/introButton1.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, introButtonTex1);


	introButtonTex2 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/introButton2.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, introButtonTex2);


	manualButtonTex1 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/manualButton1.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, manualButtonTex1);


	manualButtonTex2 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/manualButton2.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, manualButtonTex2);


	rankingButtonTex1 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/rankingButton1.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, rankingButtonTex1);


	rankingButtonTex2 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/rankingButton2.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, rankingButtonTex2);


	exitButtonTex1 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/exitButton1.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, exitButtonTex1);


	exitButtonTex2 = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/exitButton2.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, exitButtonTex2);


	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);

}

TitlePage::~TitlePage()
{
	(*backgroundTex)->Release();
	(*startButtonTex1)->Release();
	(*startButtonTex2)->Release();
	(*introButtonTex1)->Release();
	(*introButtonTex2)->Release();
	(*manualButtonTex1)->Release();
	(*manualButtonTex2)->Release();
	(*rankingButtonTex1)->Release();
	(*rankingButtonTex2)->Release();
	(*exitButtonTex1)->Release();
	(*exitButtonTex2)->Release();
	spr->Release();
}

void TitlePage::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);


	// button state
	if (pt.x > (WINDOW_WIDTH / 2) - (BUTTON_WIDTH / 2)
		&& pt.x < (WINDOW_WIDTH / 2) + (BUTTON_WIDTH / 2))
	{
		if (pt.y > 350 - 35
			&& pt.y < 350 + 35)
		{
			startState = 1;
		}
		else
		{
			startState = 0;
		}

		if (pt.y > 350 + (70 * 1) - 30
			&& pt.y < 350 + (70 * 1) + 30)
		{
			introState = 1;
		}
		else
		{
			introState = 0;
		}

		if (pt.y > 350 + (70 * 2) - 30
			&& pt.y < 350 + (70 * 2) + 30)
		{
			manualState = 1;
		}
		else
		{
			manualState = 0;
		}

		if (pt.y > 350 + (70 * 3) - 30
			&& pt.y < 350 + (70 * 3) + 30)
		{
			rankingState = 1;
		}
		else
		{
			rankingState = 0;
		}

		if (pt.y > 350 + (70 * 4) - 30
			&& pt.y < 350 + (70 * 4) + 30)
		{
			exitState = 1;
		}
		else
		{
			exitState = 0;
		}

	}

	// button click
	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
	{
		if (startState == 1)
		{
			pageManager.CreateFirstGamePage();
		}
		else if (introState == 1)
		{
			pageManager.CreateIntroPage();
		}
		else if (manualState == 1)
		{
			pageManager.CreateManualPage();
		}
		else if (rankingState == 1)
		{
			pageManager.CreateRankingPage();
		}
		else if (exitState == 1)
		{
			PostQuitMessage(0);
		}
	}
	
}

void TitlePage::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pos = { WINDOW_WIDTH / 2, 350, 0 };
	cen = { BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2, 0 };
	if (startState == 0)
	{
		spr->Draw(*startButtonTex1, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		spr->Draw(*startButtonTex2, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	pos = { WINDOW_WIDTH / 2, 350 + 70 * 1, 0 };
	if (introState == 0)
	{
		spr->Draw(*introButtonTex1, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		spr->Draw(*introButtonTex2, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	pos = { WINDOW_WIDTH / 2, 350 + 70 * 2, 0 };
	if (manualState == 0)
	{
		spr->Draw(*manualButtonTex1, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		spr->Draw(*manualButtonTex2, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	pos = { WINDOW_WIDTH / 2, 350 + 70 * 3, 0 };
	if (rankingState == 0)
	{
		spr->Draw(*rankingButtonTex1, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		spr->Draw(*rankingButtonTex2, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	pos = { WINDOW_WIDTH / 2, 350 + 70 * 4, 0 };
	if (exitState == 0)
	{
		spr->Draw(*exitButtonTex1, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		spr->Draw(*exitButtonTex2, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	



	spr->End();
}
