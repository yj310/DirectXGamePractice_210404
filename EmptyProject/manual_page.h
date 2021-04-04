#pragma once
#include "page.h"

class ManualPage : public Page
{
public:

	ManualPage();
	virtual ~ManualPage();

	void Update() override;
	void Render() override;


};