#pragma once
#include "page.h"

class PageManager
{
public:

	Page* currentPage;

	PageManager();
	
	void CreateTitlePage();
	void CreateFirstGamePage();
	void CreateSecondGamePage();
	void CreateIntroPage();
	void CreateManualPage();
	void CreateRankingPage();
	
	void DeleteCurrentPage();


	void Update();
	void Render();
};