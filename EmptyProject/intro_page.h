#pragma once
#include "page.h"

class IntroPage : public Page
{
public:

	IntroPage();
	virtual ~IntroPage();

	void Update() override;
	void Render() override;


};