#pragma once
#include "page.h"

class RankingPage : public Page
{
public:

	RankingPage();
	virtual ~RankingPage();

	void Update() override;
	void Render() override;


};