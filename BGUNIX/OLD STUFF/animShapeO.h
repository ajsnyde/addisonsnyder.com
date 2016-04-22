#pragma once
#include "shapeO.h"
class animShapeO : public shapeO {
public:
	animShapeO();
	~animShapeO();
	void set_direction(double x, double y){
		direction_x = x; direction_y = y;}
	bool collidesWith(shapeO * shape){
		double X, Y, H, W;
		(*shape).getRect(X, Y, H, W);
		if(x < X + W && x + width > X && y < Y + H && height + y > Y)
			return true;
		else return false;}
	void update(){
		x += direction_x;
		y += direction_y;}
protected:
	double direction_x, direction_y;
};
