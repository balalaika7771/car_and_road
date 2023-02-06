#pragma once
#include <Windows.h>
class painter
{
protected:
	HPEN pn;
public:
	painter() {
		pn = CreatePen(PS_SOLID, 2, RGB(100, 100, 100));
	}
	virtual ~painter() {
		
	}

	virtual void draw(HDC hDC){

	}



};

