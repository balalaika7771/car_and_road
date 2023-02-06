#pragma once
#include "painter.h"
#include "transport.h"
#include <vector>
#include "breach.h"
class road:public painter
{
	vector direction;
	std::vector<breach> breaches;
	POINT  road_tuda[4];
	POINT  road_suda[4];
	unsigned int width;
public:
	road(POINT  first, POINT  second, unsigned int _width);
	~road();
	void draw(HDC hDC) override;
	bool in_direction(point p, vector _direction);
	bool on_road (point  p);
	bool on_road_tuda(point  p);
	bool on_road_suda(point  p);
	bool in_breach(point  p);
private:

};

