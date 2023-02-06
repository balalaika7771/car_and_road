#include "breach.h"
breach::breach(POINT  _position, unsigned int _size)
{
	pn = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	position = _position;
	size = _size;
}

breach::~breach()
{
}

void breach::draw(HDC hDC)
{
	SelectObject(hDC, (HGDIOBJ)pn);
	Ellipse(hDC, position.x - size/2, position.y - size/2, position.x + size/2, position.y + size/2);
}

bool breach::point_in(POINT p)
{
	double lengh = abs(sqrt(pow(abs(p.x - position.x), 2) + pow(abs(p.y - position.y), 2)));

	return lengh < double(size / 2);
}
