#pragma once
#include "shapeO.h"
class animShapeO : public shapeO {
public:
	animShapeO();
	~animShapeO();
	void set_direction(double x, double y){		//getters/setters for direction - dimensions availble via ShapeO inheritance
		direction_x = x; direction_y = y;}
	void get_direction(double & x, double & y){
	x = direction_x; y = direction_y;}
	bool collidesWith(animShapeO * shape){		// Collision function, returns true for overlaps
		double X, Y, H, W;
		(*shape).getRect(X, Y, H, W);
		if(x < X + W && x + width > X && y < Y + H && height + y > Y)
			return true;
		else return false;}
	void update(){					// Moves shape's position and reverses directions accordingly when hitting a boundary
		x += direction_x;
		y += direction_y;
			if(x < 0 && direction_x < 0)
			direction_x = -direction_x;
		if(y < 0 && direction_y < 0)
			direction_y = -direction_y;
		if(x > 800 && direction_x > 0)
			direction_x = -direction_x;
		if(y > 600 && direction_y > 0)
			direction_y = -direction_y;}
	bool get_destroy(){return destroy;}		//more basic getters and setters
	void set_destroy(){destroy = true;}
protected:
	double direction_x, direction_y;
	bool destroy;					// allows for easy flagging for removal and/or other purposes (potential explosion implentation??)
};
