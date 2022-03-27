#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>

#define WINDOW_X 1280
#define WINDOW_Y 720

/*
	Class that is used for everything related to integrals
	Also contains application menu
*/

class Integral
{
	private:
		//Variables
		//Window
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event e;

		//App objects
		sf::VertexArray axes;
		sf::VertexArray fun1;

		//Integral functions 
		double f4(double x);

		//Private functions
		void initVariables();
		void initWindow();
		void initGraph();
		void initAxes();
		void initFun1();

	public:
		//Constructors / Destructors
		Integral();
		virtual ~Integral();

		//Accessors
		const bool running() const;

		//Functions
		void update();
		void poolEvents();
		void render();
};

