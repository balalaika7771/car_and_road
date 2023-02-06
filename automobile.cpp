#include "automobile.h"

automobile::automobile()
{
	ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

automobile::automobile(point p) {
	this->position = p;
	ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
automobile::~automobile()
{

}
#define angle 0.7*time*(speed)
#define speed_up 8*time
void automobile::control(std::vector<int> input) {
	uint64_t new_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	double time = abs(double(new_ms - ms)) * 0.001;
	ms = new_ms;
	for (char cmd : input)
	{
		switch (cmd)
		{
		case VK_RIGHT:
			vector new_vector;
			new_vector.x = _vector.x * cos(angle) - _vector.y * sin(angle);
			new_vector.y = _vector.x * sin(angle) + _vector.y * cos(angle);
			_vector = new_vector;
			break;
		case VK_LEFT:
			vector new_vector2;
			new_vector2.x = _vector.x * cos(-angle) - _vector.y * sin(-angle);
			new_vector2.y = _vector.x * sin(-angle) + _vector.y * cos(-angle);
			_vector = new_vector2;
			break;
		case VK_UP:
			speed += speed_up;
			break;
		case VK_DOWN:
			speed -= speed_up;
			break;
		default:
			break;
		}
	}
	if (abs(abs(speed)-(speed_up) * 0.8 + abs(speed) * 0.03) < abs(speed)) {
		if(speed>0)
			speed -= (speed_up) * 0.8 + abs(speed) * 0.03;
		else
			speed += (speed_up) * 0.8 + abs(speed) * 0.03;
	}
	else {
		speed = 0;
	}
	
	position.x = position.x + double(speed * _vector.x);
	position.y = position.y + double(speed * _vector.y);
}

BOOL DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	POINT pt;
	MoveToEx(hdc, x1, y1, &pt);
	return LineTo(hdc, x2, y2);
}

void automobile::draw(HDC hDC) {
	SelectObject(hDC, (HGDIOBJ)pn);
	Ellipse(hDC, position.x - 10, position.y - 10, position.x + 10, position.y + 10);
	DrawLine(hDC, position.x, position.y, position.x + 10 * _vector.x, position.y + 10 * _vector.y);
}
