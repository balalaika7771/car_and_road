
#include <iostream>
#include "automobile.h"
#include "road.h"
#include "message.h"

enum LOCATION
{
	ROAD_TUDA,
	ROAD_SUDA,
	BREACH,
	OUTSIDE,
};

int main()
{
	point p;
	p.x = 500;
	p.y = 500;
	automobile car(p);
	HWND h = GetConsoleWindow();
	POINT  first;
	first.x = 100;
	first.y = 100;
	POINT  second;
	second.x = 1400;
	second.y = 800;
	road r(first, second, 100);
	HANDLE	hStdOut;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD homeCoords = { 0, 0 };
	SetBkColor(GetDC(h), RGB(0, 0, 0));
	std::vector<message*> msg;
	message wrong_direction("wrong direction!", 1000);
	message cross_line("crossing_a_solid_line!", 1000);
	message road_derailment("road derailment!", 1000);
	message turn_pass("the U-turn is passed !", 1000);
	msg.push_back(&wrong_direction);
	msg.push_back(&cross_line);
	msg.push_back(&road_derailment);
	msg.push_back(&turn_pass);
	LOCATION lk = OUTSIDE;
	LOCATION temp = OUTSIDE;
	while (1)
	{
		std::vector<int> cmd;
		if (GetAsyncKeyState(VK_LEFT)) {
			cmd.push_back(VK_LEFT);
		}
		if (GetAsyncKeyState(VK_UP)) {
			cmd.push_back(VK_UP);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			cmd.push_back(VK_RIGHT);
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			cmd.push_back(VK_DOWN);
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
		RECT rect;
		r.draw(GetDC(h));
		GetClientRect(h, &rect);
		car.control(cmd);
		car.draw(GetDC(h));
		
		switch (lk)
		{
		case ROAD_TUDA:
			temp = lk;
			if (!r.on_road(car.get_point()))
			{
				lk = OUTSIDE;
				temp = OUTSIDE;
				break;
			}
			if (!r.in_direction(car.get_point(),car.get_vector())) {
				wrong_direction.activate();
			}
			
			if (r.in_breach(car.get_point())) {
				lk = BREACH;
				break;
			}
			if (r.on_road_suda(car.get_point())) {
				cross_line.activate();
				lk = ROAD_SUDA;
				break;
			}
			break;
		case ROAD_SUDA:
			temp = lk;
			if (!r.on_road(car.get_point()))
			{
				lk = OUTSIDE;
				temp = OUTSIDE;
				break;
			}
			if (!r.in_direction(car.get_point(), car.get_vector())) {
				wrong_direction.activate();
			}
			
			if (r.in_breach(car.get_point())) {
				lk = BREACH;
				break;
			}
			if (r.on_road_tuda(car.get_point())) {
				cross_line.activate();
				lk = ROAD_TUDA;
				break;
			}
			break;
		case BREACH:
			if (r.on_road_tuda(car.get_point()) && temp == ROAD_SUDA && !r.in_breach(car.get_point()) && r.in_direction(car.get_point(), car.get_vector())) {
				turn_pass.activate();
				lk = ROAD_TUDA;
				break;
			}
			if (r.on_road_suda(car.get_point()) && temp == ROAD_TUDA && !r.in_breach(car.get_point()) && r.in_direction(car.get_point(), car.get_vector())) {
				turn_pass.activate();
				lk = ROAD_SUDA;
				break;
			}
			if (r.on_road_suda(car.get_point()) && !r.in_breach(car.get_point())) {
				lk = ROAD_SUDA;
				break;
			}
			if (r.on_road_tuda(car.get_point()) && !r.in_breach(car.get_point())) {
				lk = ROAD_TUDA;
				break;
			}
			break;
		case OUTSIDE:
			road_derailment.activate();
			if (r.on_road_suda(car.get_point())) {
				lk = ROAD_TUDA;
				break;
			}
			if (r.on_road_tuda(car.get_point())) {
				lk = ROAD_SUDA;
				break;
			}
			break;
		default:
			break;
		}
		for (message* n : msg) 
		{
			(*n).draw(GetDC(h));
		}
		Sleep(100);
		
		ExtTextOut(GetDC(h), 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
		SetConsoleCursorPosition(hStdOut, homeCoords);
	}
}