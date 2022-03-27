#include "Integral.h"


//Private functions


double Integral::f4(double x)
{
	return (2 * sin(x) - cos(x) * x + 10);
}

void Integral::initVariables()
{
	this->window = nullptr;
}

void Integral::initWindow()
{
	this->videoMode.height = WINDOW_Y;
	this->videoMode.width = WINDOW_X;
	this->videoMode.bitsPerPixel = 32;
	this->window = new sf::RenderWindow(this->videoMode, "Integrals");
}

void Integral::initGraph()
{
	this->initAxes();
	this->initFun1();
}

void Integral::initAxes()
{
	this->axes.setPrimitiveType(sf::PrimitiveType::Lines);
	this->axes.append(sf::Vector2f(0, WINDOW_Y / 2));
	this->axes.append(sf::Vector2f(WINDOW_X, WINDOW_Y / 2));
	this->axes.append(sf::Vector2f(WINDOW_X / 2, 0));
	this->axes.append(sf::Vector2f(WINDOW_X / 2, WINDOW_Y));
	for (int i = 0; i < WINDOW_X; i += 10)
	{
		this->axes.append(sf::Vector2f(i, WINDOW_Y / 2 - 4));
		this->axes.append(sf::Vector2f(i, WINDOW_Y / 2 + 4));
	}
	for (int i = 0; i < WINDOW_Y; i += 10)
	{
		this->axes.append(sf::Vector2f(WINDOW_X / 2 - 4, i));
		this->axes.append(sf::Vector2f(WINDOW_X / 2 + 4, i));
	}
}
void Integral::initFun1()
{///////////////////////////////////////////////////////////////////////////////////////////////////////////////DOKONCZYC
	this->fun1.setPrimitiveType(sf::PrimitiveType::LinesStrip);
	for (double i = 0.0, j = WINDOW_X/2; i < WINDOW_X; i += 10.0)
	{
		this->fun1.append(sf::Vector2f(i, this->f4(i/10 - j) + WINDOW_Y/20));
	}

}
//Constructors / Destructors


Integral::Integral()
{
	this->initVariables();
	this->initWindow();
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
		}
	}
}

void Integral::render()
{
	/*
	*	-clear old frame
	*	-draw new frame
	*	-display in window
	* 
	*	Renders the new frame
	*/
	this->window->clear(sf::Color(50, 50, 50, 255));

	//Draw app objects
	this->window->draw(this->axes);
	this->window->draw(this->fun1);

	this->window->display();
}

