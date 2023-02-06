#pragma once
#include <string>
#include "painter.h"
#include <chrono>
class message: painter
{
	std::string msg;
	uint64_t ms_live;
	uint64_t ms_tick;
public:
	message(std::string _msg, uint64_t _ms);
	~message();
	void draw(HDC hDC) override;
	void activate();
};

