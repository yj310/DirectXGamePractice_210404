#include "DXUT.h"
#include "page_manager.h"
#include "title_page.h"
#include "first_game_page.h"
#include "second_game_page.h"
#include "intro_page.h"
#include "manual_page.h"
#include "ranking_page.h"

PageManager::PageManager()
{
	currentPage = nullptr;
}

void PageManager::CreateTitlePage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	currentPage = new TitlePage();
}

void PageManager::CreateFirstGamePage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	currentPage = new FirstGamePage();
}

void PageManager::CreateSecondGamePage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	currentPage = new SecondGamePage();
}

void PageManager::CreateIntroPage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	currentPage = new IntroPage();
}

void PageManager::CreateManualPage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	currentPage = new ManualPage();
}

void PageManager::CreateRankingPage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	currentPage = new RankingPage();
}


void PageManager::Update()
{
	if (currentPage != nullptr)
	{
		currentPage->Update();
	}
}


void PageManager::Render()
{
	if (currentPage != nullptr)
	{
		currentPage->Render();
	}
}

void PageManager::DeleteCurrentPage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
}