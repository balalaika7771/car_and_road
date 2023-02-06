#include "road.h"

vector get_vector(POINT  first, POINT  second)
{
	vector direction;
	direction.x = second.x - first.x;
	direction.y = second.y - first.y;
	double s = 1 / abs(direction.x + direction.y);
	direction.x *= s;
	direction.y *= s;
	return direction;
}

road::road(POINT  first, POINT  second, unsigned int _width)
{
	width = _width;
	direction = get_vector(first, second);
	road_tuda[0] = first;
	road_tuda[1] = second;
	vector a,b;
	a.x = direction.x * cos(1.5708) - direction.y * sin(1.5708);
	a.y = direction.x * sin(1.5708) + direction.y * cos(1.5708);
	b.x = direction.x * cos(-1.5708) - direction.y * sin(-1.5708);
	b.y = direction.x * sin(-1.5708) + direction.y * cos(-1.5708);
	road_tuda[3].x = first.x + (_width * 0.5) * a.x;
	road_tuda[3].y = first.y + (_width * 0.5) * a.y;
	road_tuda[2].x = second.x + (_width * 0.5) * a.x;
	road_tuda[2].y = second.y + (_width * 0.5) * a.y;

	road_suda[0].x = first.x + (_width * 0.5) * b.x;
	road_suda[0].y = first.y + (_width * 0.5) * b.y;
	road_suda[1].x = second.x + (_width * 0.5) * b.x;
	road_suda[1].y = second.y + (_width * 0.5) * b.y;
	road_suda[3] = first;
	road_suda[2] = second;
	double lengh = abs(sqrt(pow(abs(first.x - second.x), 2) + pow(abs(first.y - second.y), 2)));
	for (int i = 200; i < lengh; i = i + 200) {
		POINT n;
		n.x = first.x + direction.x * i;
		n.y = first.y + direction.y * i;
		breach b(n,50);
		breaches.push_back(b);
	}
}

road::~road()
{
}
void road::draw(HDC hDC) {
	SelectObject(hDC, (HGDIOBJ)pn);
	Polygon(hDC, road_tuda, 4);
	Polygon(hDC, road_suda, 4);
	for (breach n : breaches) 
	{
		n.draw(hDC);
	}
}



double get_angle(vector first, vector second)
{

	double x1, y1, x2, y2;
	x1 = first.x;
	y1 = first.y;
	x2 = second.x;
	y2 = second.y;
	double t = (x1 * x2 + y1 * y2) / (sqrt((double)x1 * x1 + y1 * y1) * sqrt((double)x2 * x2 + y2 * y2));
	if (t < -1) t = -1;
	else if (t > 1) t = 1;
	return acos(t);
}

bool PointInPoly(POINT p, int n, POINT *poly)
{
	int b = 1, i;
	for (i = 0; i < n - 1; i++) {
		if ((p.y <= poly[i].y) == (p.y > poly[i + 1].y)) {
			if ((p.x - poly[i].x) <
				(p.y - poly[i].y) * (poly[i + 1].x - poly[i].x) / (poly[i + 1].y - poly[i].y)) b = !b;
		};
	};
	if ((p.y <= poly[n - 1].y) == (p.y > poly[0].y)) {
		if ((p.x - poly[n - 1].x) <
			(p.y - poly[n - 1].y) * (poly[0].x - poly[n - 1].x) / (poly[0].y - poly[n - 1].y)) b = !b;
	};
	return !b;
};

bool road::on_road_tuda(point  p)
{
	POINT pt;
	pt.x = p.x;
	pt.y = p.y;
	if (PointInPoly(pt, 4, road_tuda)) {
		return true;
	}
	return false;
	
}

bool road::on_road_suda(point  p)
{
	POINT pt;
	pt.x = p.x;
	pt.y = p.y;
	if (PointInPoly(pt, 4, road_suda)) {
		return true;
	}
	return false;

}
bool road::on_road(point  p)
{
	POINT pt;
	pt.x = p.x;
	pt.y = p.y;
	if (PointInPoly(pt, 4, road_suda)) {
		return true;
	}
	if (PointInPoly(pt, 4, road_tuda)) {
		return true;
	}
	return false;

}
bool road::in_direction(point p,vector _direction)
{
	POINT pt;
	pt.x = p.x;
	pt.y = p.y;
	if (PointInPoly(pt, 4, road_tuda)) {
		return(get_angle(_direction, direction) < 1.8708);
	}

	if (PointInPoly(pt, 4, road_suda)) {
		vector dedir;
		dedir.x = direction.x;
		dedir.y = direction.y;
		return(get_angle(_direction, dedir) > 1.2708);
	}
	return false;
	
}

bool road::in_breach(point  p)
{
	POINT pt;
	pt.x = p.x;
	pt.y = p.y;
	for (breach n : breaches) 
	{
		if (n.point_in(pt)) {
			return true;
		}
	}
	return false;
}
