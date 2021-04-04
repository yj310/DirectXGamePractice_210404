#pragma once

class Page
{
public:
	virtual ~Page() {}
	virtual void Update() = 0;
	virtual void Render() = 0;
};