#include <iostream>
#include "Integral.h"


int main()
{
	//Init App
	Integral integral;

	while (integral.running())
	{
		//Update
		integral.update();
		//Render
		integral.render();
	}

	//End of application
	return 0;
}