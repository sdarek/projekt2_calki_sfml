#include "Integral.h"

//Function definitions that we want in the program 

double f1(double x)
{
	return (x * x * x - x * x - 2 * x + 15);
}
double f2(double x)
{
	return (2 * sin(x) - cos(x) * x + 10);
}
double f3(double x)
{
	return 0.23 * x * x * x + 2 * x - 99;
}
double f4(double x)
{
	double y;
	y = sin(2 * x) + cos(3 * x) - 1;
	return y;
}

//Private functions



void Integral::fx_struct::initFun()
{
	/*	This function initializes our fx_struct
	*	-first array of graph points is cleared
	*	-set way of connecting points (linesStrip)
	*	-ok the most important part: to the array of points are adding points which are coordinates our function 
	*			-x from an i=0.0, because 0 means the left edge of our window
	*			-y from window_y/2 - .... because i want it in the middle
	*								 .... -> ((i / axes_pixel_per_unit - j / axes_..) * axes_..)  because one unit is every 10 (defined by axes...) pixels. 
	*/
	this->fun.clear();
	this->fun.setPrimitiveType(sf::PrimitiveType::LinesStrip);
	for (double i = 0.0, j = WINDOW_X / 2; i < WINDOW_X; i += DRAWING_PRECISION)
	{
		this->fun.append(sf::Vector2f(i, WINDOW_Y / 2 - this->fx(i / AXES_PIXEL_PER_UNIT - j / AXES_PIXEL_PER_UNIT) * AXES_PIXEL_PER_UNIT));
	}
}



void Integral::initVariables()
{
	this->window = nullptr;
	this->akt_fun = &fun1;
}

void Integral::initWindow()
{
	this->videoMode.height = WINDOW_Y;
	this->videoMode.width = WINDOW_X;
	this->videoMode.bitsPerPixel = 32;
	this->window = new sf::RenderWindow(this->videoMode, "Integrals");
	this->window->setFramerateLimit(30);
}

void Integral::initView()
{
	this->view.setSize(sf::Vector2f(WINDOW_X, WINDOW_Y));
	this->view.setCenter(sf::Vector2f(WINDOW_X / 2, WINDOW_Y / 2));
}

void Integral::initGraph()
{
	this->initAxes();
	fun1.fx = f1;
	fun1.initFun();
	fun2.fx = f2;
	fun2.initFun();
	fun3.fx = f3;
	fun3.initFun();
	fun4.fx = f4;
	fun4.initFun();
}

void Integral::initAxes()
{
	this->axes.clear();
	this->axes.setPrimitiveType(sf::PrimitiveType::Lines);
	this->axes.append(sf::Vector2f(0, WINDOW_Y / 2));
	this->axes.append(sf::Vector2f(WINDOW_X, WINDOW_Y / 2));
	this->axes.append(sf::Vector2f(WINDOW_X / 2, 0));
	this->axes.append(sf::Vector2f(WINDOW_X / 2, WINDOW_Y));
	for (int i = 0; i < WINDOW_X; i += AXES_PIXEL_PER_UNIT)
	{
		this->axes.append(sf::Vector2f(i, WINDOW_Y / 2 - 4));
		this->axes.append(sf::Vector2f(i, WINDOW_Y / 2 + 4));
	}
	for (int i = 0; i < WINDOW_Y; i += AXES_PIXEL_PER_UNIT)
	{
		this->axes.append(sf::Vector2f(WINDOW_X / 2 - 4, i));
		this->axes.append(sf::Vector2f(WINDOW_X / 2 + 4, i));
	}
}

//Constructors / Destructors

Integral::Integral()
{
	this->initVariables();
	this->initWindow();
	this->initView();
	this->initGraph();
}

Integral::~Integral()
{
	delete this->window;

}

//Accessors

const bool Integral::running() const
{
	return this->window->isOpen();
}


//Functions


void Integral::update()
{
	this->poolEvents();
}

void Integral::poolEvents()
{
	while (this->window->pollEvent(this->e))
	{
		if (this->e.type == sf::Event::Closed) this->window->close();
		else if (this->e.type == sf::Event::KeyPressed)
		{
			if (this->e.key.code == sf::Keyboard::Escape) this->window->close();
			if (this->e.key.code == sf::Keyboard::Up)
			{
				this->view.zoom(0.99);
			}
			if (this->e.key.code == sf::Keyboard::Down)
			{
				if(this->view.getSize().x < WINDOW_X) this->view.zoom(1.01);
			}
			if (this->e.key.code == sf::Keyboard::Left)
			{
				if(akt_fun != &fun1) akt_fun--;	//by default fun1 is always first function and pointer to actual function cant be out of range
			}
			if (this->e.key.code == sf::Keyboard::Right)
			{
				if (akt_fun != &fun4) akt_fun++;	//here akt_fun points to the last function (so we have to change it every time when we add the function
			}
		}
	}
}

void Integral::render()
{
	/*
	*	-clear old frame
	*	-set view
	*	-draw new frame
	*	-display in window
	* 
	*	Renders the new frame
	*/
	this->window->clear(sf::Color(50, 50, 50, 255));


	this->window->setView(this->view);

	//Draw app objects
	this->window->draw(this->axes);
	this->window->draw(akt_fun->fun);

	this->window->display();
}
