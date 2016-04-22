#include <stdlib.h>


/* getShape data
Author: G. Zimmerman
Last Update:  10/22/2014
Purpose: generate consistent random data for shapes
input:
left, right:  range of values for x coordinates
top, bottom:  range of values for y coordinates
dmin, dmax:   range of values for rectangle dimensions

returns:
x :  x coordinant of upper left hand corner of shape:
y :  y coordinant of upper left hand corner of shape:
dx :  x component of direction vector for animated shape
dy :  y component of direction vector for animated shape
width:  rectangle width
height: rectanlge height
*/
void getShapeData(int left, int right, int bottom, int top, int dmin, int dmax,
	double &x, double &y, double &dx, double &dy, double &width, double &height) {

	x = left + rand() % (right - left);
	y = bottom + rand() % (top - bottom);
	width = dmin + rand() % (dmax - dmin);
	height = dmin + rand() % (dmax - dmin);
	 dx = -2 + rand() % 5;
	 dy = -2 + rand() % 5;

}
