#pragma once
#include "page_manager.h"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define FLOOR_WIDTH 1024
#define FLOOR_HEIGHT 720
#define FLOOR_PIXEL FLOOR_WIDTH * FLOOR_HEIGHT

#define GAME_X (WINDOW_WIDTH - FLOOR_WIDTH) / 2
#define GAME_Y WINDOW_HEIGHT - FLOOR_HEIGHT

#define MAP_EMPTY 0
#define MAP_EDGE 1
#define MAP_VISITED 2
#define MAP_VISITING 3
#define MAP_TEMP 4


extern PageManager pageManager;