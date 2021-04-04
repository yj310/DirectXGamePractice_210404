
#include "DXUT.h"
#include "first_game_page.h"
#include "global.h"
#include <stack>
using namespace std;

FirstGamePage::FirstGamePage()
{
	score = 0;
	player = new Player();
	isFinish = false;
	visitingX = 0;
	visitingY = 0;
	isSpace = false;
	isVisiting = false;

	// texture load
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

	floorTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/floor.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, floorTex);

	maskTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/firstGameMask.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, maskTex);



	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);


	// map load
	D3DLOCKED_RECT lr;
	RECT rt = { 0, 0, FLOOR_WIDTH, FLOOR_HEIGHT };

	if (SUCCEEDED((*floorTex)->LockRect(0, &lr, &rt, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		memcpy(floorP, p, FLOOR_WIDTH * FLOOR_HEIGHT * sizeof(int));
		(*floorTex)->UnlockRect(0);
	}

	if (SUCCEEDED((*maskTex)->LockRect(0, &lr, &rt, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		memcpy(maskP, p, FLOOR_WIDTH * FLOOR_HEIGHT * sizeof(int));
		(*maskTex)->UnlockRect(0);
	}

	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		map[i] = MAP_EMPTY;
	}
	for (int x = 0; x < FLOOR_WIDTH; ++x)
	{
		map[0 * FLOOR_WIDTH + x] = MAP_EDGE;
		map[(FLOOR_HEIGHT - 1) * FLOOR_WIDTH + x] = MAP_EDGE;
	}
	for (int y = 0; y < WINDOW_HEIGHT; ++y)
	{
		map[y * FLOOR_WIDTH + 0] = MAP_EDGE;
		map[y * FLOOR_WIDTH + FLOOR_WIDTH - 1] = MAP_EDGE;
	}

	MapUpdate();













}

FirstGamePage::~FirstGamePage()
{
	(*backgroundTex)->Release();
	(*floorTex)->Release();
	(*maskTex)->Release();
	spr->Release();

	delete player;
}

void FirstGamePage::MapUpdate()
{
	D3DLOCKED_RECT lr;
	RECT rt = { 0, 0, FLOOR_WIDTH, FLOOR_HEIGHT };
	if (SUCCEEDED((*floorTex)->LockRect(0, &lr, &rt, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		for (int i = 0; i < FLOOR_PIXEL; ++i)
		{
			if (map[i] == MAP_EMPTY)
			{
				p[i] = maskP[i];
			}
			if (map[i] == MAP_EDGE)
			{
				p[i] = D3DCOLOR_ARGB(255, 255, 255, 255);
			}
			if (map[i] == MAP_VISITING)
			{
				p[i] = D3DCOLOR_ARGB(255, 255, 0, 0);
			}
			if (map[i] == MAP_VISITED)
			{
				p[i] = floorP[i];
			}
			if (map[i] == MAP_TEMP)
			{
				p[i] = D3DCOLOR_ARGB(255, 0, 0, 0);
			}
		}
		(*floorTex)->UnlockRect(0);
		
	}
}

void FirstGamePage::PlayerMove()
{
	if (!isFinish)
	{
		int speed = player->getSpeed();
		D3DXVECTOR2 dir;
		isSpace = false;

		// space
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
		{
			isSpace = true;
		}
		else
		{
			if (isVisiting)
			{
				isVisiting = false;
				isSpace = false;
				player->setPos({ (float)visitingX, (float)visitingY });
				for (int i = 0; i < FLOOR_PIXEL; ++i)
				{
					if (map[i] == MAP_VISITING)
					{
						map[i] = MAP_EMPTY;
					}
				}
			}
		}


		// move
		// left
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000 ) != 0
			&& player->getPos().x - 1 >= 0)
		{

			for (int i = 0; i < speed; ++i)
			{
				int posX = player->getPos().x;
				int posY = player->getPos().y;
				int nextX = posX - 1;
				int nextY = posY;
				dir = { -1, 0 };

				if (map[posY * FLOOR_WIDTH + posX] == MAP_EDGE
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE)
				{
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_EDGE
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY
					&& isSpace)
				{
					visitingX = posX;
					visitingY = posY;
					isVisiting = true;
					map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_VISITING
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY
					&& isSpace)
				{
					map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_VISITING
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE
					&& isSpace)
				{
					player->move(dir);
					GetLand();
					isVisiting = false;
				}




			}
		}
		// right
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0
			&& player->getPos().x + 1 < FLOOR_WIDTH)
		{
			for (int i = 0; i < speed; ++i)
			{
				int posX = player->getPos().x;
				int posY = player->getPos().y;
				int nextX = posX + 1;
				int nextY = posY;
				dir = { 1, 0 };

				if (map[posY * FLOOR_WIDTH + posX] == MAP_EDGE
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE)
				{
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_EDGE
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY
					&& isSpace)
				{
					visitingX = posX;
					visitingY = posY;
					isVisiting = true;
					map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_VISITING
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY
					&& isSpace)
				{
					map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_VISITING
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE
					&& isSpace)
				{
					player->move(dir);
					GetLand();
					isVisiting = false;
				}




			}
		}
		// up
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0
			&& player->getPos().y - 1 >= 0)
		{

			for (int i = 0; i < speed; ++i)
			{
				int posX = player->getPos().x;
				int posY = player->getPos().y;
				int nextX = posX;
				int nextY = posY - 1;
				dir = { 0, -1 };

				if (map[posY * FLOOR_WIDTH + posX] == MAP_EDGE
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE)
				{
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_EDGE
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY
					&& isSpace)
				{
					visitingX = posX;
					visitingY = posY;
					isVisiting = true;
					map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_VISITING
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY
					&& isSpace)
				{
					map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_VISITING
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE
					&& isSpace)
				{
					player->move(dir);
					GetLand();
					isVisiting = false;
				}




			}
		}
		// down
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0
			&& player->getPos().y + 1 < FLOOR_HEIGHT)
		{
			for (int i = 0; i < speed; ++i)
			{
				int posX = player->getPos().x;
				int posY = player->getPos().y;
				int nextX = posX;
				int nextY = posY + 1;
				dir = { 0, 1 };

				if (map[posY * FLOOR_WIDTH + posX] == MAP_EDGE
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE)
				{
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_EDGE
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY
					&& isSpace)
				{
					visitingX = posX;
					visitingY = posY;
					isVisiting = true;
					map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_VISITING
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EMPTY
					&& isSpace)
				{
					map[nextY * FLOOR_WIDTH + nextX] = MAP_VISITING;
					player->move(dir);
				}

				if (map[posY * FLOOR_WIDTH + posX] == MAP_VISITING
					&& map[nextY * FLOOR_WIDTH + nextX] == MAP_EDGE
					&& isSpace)
				{
					player->move(dir);
					GetLand();
					isVisiting = false;
				}




			}
		}
	}
	
}

void FirstGamePage::GetLand()
{
	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		if (map[i] == MAP_EMPTY)
			virtualMap[i] = MAP_TEMP;
		else
			virtualMap[i] = map[i];
	}

	FloodFill();

	for (int i = 0; i < FLOOR_PIXEL; ++i)
	{
		if (virtualMap[i] == MAP_TEMP)
			map[i] = MAP_VISITED;
		else if (virtualMap[i] == MAP_VISITING)
			map[i] = MAP_EDGE;
		else
			map[i] = map[i];
	}

	Bordering();

	//memcpy(map, virtualMap, FLOOR_PIXEL * sizeof(int));
}


void FirstGamePage::FloodFill()
{
	stack<Point> points;
	points.push(Point(1, 1));

	while (!points.empty())
	{
		Point point = points.top();
		points.pop();
		if (point.x < 0
			|| point.x >= FLOOR_WIDTH
			|| point.y < 0
			|| point.y >= FLOOR_HEIGHT)
			continue;

		if (virtualMap[point.y * FLOOR_WIDTH + point.x] == MAP_TEMP)
		{
			virtualMap[point.y * FLOOR_WIDTH + point.x] = MAP_EMPTY;
		}
		else
		{
			continue;
		}


		points.push(Point(point.x - 1, point.y));
		points.push(Point(point.x + 1, point.y));
		points.push(Point(point.x, point.y - 1));
		points.push(Point(point.x, point.y + 1));
	}
}

void FirstGamePage::Bordering()
{
	for (int y = 0; y < FLOOR_HEIGHT; ++y)
	{
		for(int x = 0; x < FLOOR_WIDTH; ++x)
		if (map[y * FLOOR_WIDTH + x] == MAP_EDGE)
		{
			int left_top = map[(y - 1) * FLOOR_WIDTH + x - 1];
			int top = map[(y - 1) * FLOOR_WIDTH + x];
			int right_top = map[(y - 1) * FLOOR_WIDTH + x + 1];

			int left = map[y * FLOOR_WIDTH + x - 1];
			int right = map[y * FLOOR_WIDTH + x + 1];

			int left_bottom = map[(y + 1) * FLOOR_WIDTH + x - 1];
			int bottom = map[(y + 1) * FLOOR_WIDTH + x];
			int right_bottom = map[(y + 1) * FLOOR_WIDTH + x + 1];

			if (y - 1 >= 0)
			{
				if (x - 1 >= 0)
				{
					if (left_top == MAP_EMPTY)
					{
						continue;
					}
				}
				if (top == MAP_EMPTY)
				{
					continue;
				}
				if (x + 1 < FLOOR_WIDTH)
				{
					if (right_top == MAP_EMPTY)
					{
						continue;
					}
				}
			}

			if (x - 1 >= 0)
			{
				if (left == MAP_EMPTY)
				{
					continue;
				}
			}
			if (x + 1 < FLOOR_WIDTH)
			{
				if (right == MAP_EMPTY)
				{
					continue;
				}
			}

			if (y + 1 < FLOOR_HEIGHT)
			{
				if (x - 1 >= 0)
				{
					if (left_bottom == MAP_EMPTY)
					{
						continue;
					}
				}
				if (bottom == MAP_EMPTY)
				{
					continue;
				}
				if (x + 1 < FLOOR_WIDTH)
				{
					if (right_bottom == MAP_EMPTY)
					{
						continue;
					}
				}
			}

			map[y * FLOOR_WIDTH + x] = MAP_VISITED;


		}
	}
	



}

void FirstGamePage::Update()
{
	PlayerMove();
	MapUpdate();
	player->Update();
}

void FirstGamePage::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pos = { GAME_X, GAME_Y, 0 };
	spr->Draw(*floorTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	

	spr->End();

	player->Render();
}
