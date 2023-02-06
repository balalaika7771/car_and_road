#pragma once
#include <vector>
struct vector {
	double x;
	double y;
};
struct point {
	double x;
	double y;
};
class transport 
{
protected:
	point position;
	vector _vector;
	double speed;
public:
	transport() {
		_vector.x = 0; 
		_vector.y = 1;
		position.x = 0;
		position.y = 0;
		speed = 0;
	}
	virtual ~transport() {

	}
	virtual void control(std::vector<int> input) {

	}
	vector get_vector() {
		return _vector;
	}
	point get_point() {
		return position;
	}

};
