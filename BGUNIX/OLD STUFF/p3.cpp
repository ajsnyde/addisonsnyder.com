#include "iostream"
#include "animShapeO.h"
#include "Link.h"
#include "List.h"
#include <list>

using namespace std;

int main()
{
	animShapeO test, test2;
	test.setRect(3,3,3,3);
	test.set_direction(1,1);
	test2.setRect(6,6,3,3);
	test2.set_direction(-1,-1);
	bool collide = test.collidesWith(&test2);
	cout << collide;
	test.update();
	test2.update();
	collide = test.collidesWith(&test2);
	cout << collide;
	cout << "\n";	

	list<animShapeO> world;
	world.push_front(test);
	world.push_front(test2);
	list<animShapeO>::iterator pos = world.begin();

	return 0;
}

