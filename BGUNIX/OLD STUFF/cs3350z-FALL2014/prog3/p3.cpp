//Addison Snyder

#include "iostream"
#include "animShapeO.h"
#include <list>
#include <stdlib.h>
#include <time.h> 

using namespace std;

void move_all(list<animShapeO> & in);
int check_all(list<animShapeO> & in);
void display_all(list<animShapeO> in);

int main()
{
	const int MAX_Y = 600; //Max 'resolution' of area
	const int MAX_X = 800;
	const int move_range = 5; // used to calculate range of speeds/directions
	animShapeO input;	// basic dummy variable for input
	int num_shapes, min, max;
	list<animShapeO> world; //	"Hello World!"

	// INPUT PHASE:

	cout << "Please enter number of shapes: ";
	cin >> num_shapes;
	cout << "Please enter min. dimensions of shapes: ";
	cin >> min;
	cout << "Please enter max. dimensions  shapes: ";
	cin >> max;
	srand (time(NULL));

	// INITIALIZE SHAPES

	for(int i = 0; i < num_shapes; i++){//sets up initial shapes with correct random properties in 'world' list container
		input.setRect(rand() % MAX_X, rand() % MAX_Y,(rand() % (max-min)) + min, rand() % (max-min) + min);
		input.set_direction((rand() % move_range) - 2, (rand() % move_range) - 2);
		world.push_front(input);}
	list<animShapeO>::iterator pos = world.begin();
	list<animShapeO>::iterator temp = world.begin();

	// PERFORM 10 ITERATIONS OF UPDATES AND COLLISION CHECKS

	int num;
	for(int i = 1; i <= 10; i++){
	cout << "Round " << i << ". . .\n";
	num = check_all(world);
	move_all(world);
	}

	// DISPLAY END RESULTS

	display_all(world);
	cout << num << " shapes left!\n";
	return 0;
}

int check_all(list<animShapeO> & in)
{
	list<animShapeO>::iterator temp = in.begin();
	list<animShapeO>::iterator temp2 = temp;
	for(temp = in.begin(); temp != in.end(); temp++){	// go through to check every single combination of shapes, flagging colliding ones for removal
		temp2 = temp;
		for(temp2++; temp2 != in.end(); temp2++){
			if((*temp).collidesWith(&(*temp2))){
				(*temp).set_destroy();
				(*temp2).set_destroy();}
		}
	}
	for(temp = in.begin(); temp != in.end(); temp++)	// remove flagged shapes
	{
		if((*temp).get_destroy()){
			in.erase(temp);
			temp = in.begin();
			cout << "Shape deleted!\n";
		}
	}
	return in.size();					// returns number of shapes left
}

void move_all(list<animShapeO> & in)
{
	list<animShapeO>::iterator temp = in.begin();		// applies movement to shapes, simulating one 'tick' of the world
	for(temp = in.begin(); temp != in.end(); temp++){
		(*temp).update();
	}
}

void display_all(list<animShapeO> in)				// displays all properties of shapes in world
{
	list<animShapeO>::iterator temp = in.begin();
	int i = 0;
	double x,y,l,h,dx,dy;
	char tab = 9;
	cout << "#" << tab << "x" << tab << "y" << tab << "l" << tab << "h" << tab << "dx" << tab << "dy" << "\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	for(temp = in.begin(); temp != in.end(); temp++)
	{
		(*temp).getRect(x,y,l,h);
		(*temp).get_direction(dx,dy);
		cout << i << tab << x << tab << y << tab << l << tab << h << tab << dx << tab << dy << "\n";
		i++;
	}
}
