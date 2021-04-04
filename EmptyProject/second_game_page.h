#pragma once
#include "page.h"

class SecondGamePage : public Page
{
public:

	SecondGamePage();
	virtual ~SecondGamePage();

	void Update() override;
	void Render() override;


};