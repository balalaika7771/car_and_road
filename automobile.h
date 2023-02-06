#pragma once
#include "transport.h"
#include "painter.h"
#include <chrono>
#include <math.h>

class automobile :public transport, public painter
{
	uint64_t ms;
public:
	automobile();
	automobile(point p);
	~automobile();
	void control(std::vector<int> input) override;
	void draw(HDC hDC)override;
private:

};

