#pragma once
#include "transport.h"
#include "painter.h"
class breach: public painter
{
	POINT  position;
	int size;
public:
	breach(POINT  position, unsigned int size);
	~breach();
	void draw(HDC hDC) override;
	bool point_in(POINT p);
private:

};

