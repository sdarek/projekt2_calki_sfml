#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>

#define WINDOW_X 1600
#define WINDOW_Y 900
#define DRAWING_PRECISION 1.0 //smaller - more precision
#define AXES_PIXEL_PER_UNIT 10.0	

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
		sf::View view;

		//App objects
		sf::VertexArray axes;	//array of vertex that contains our axes

		//Structure which contains function graph and pointer to the function itself
		struct fx_struct{
			sf::VertexArray fun;	//array of vertex that contains points of graph wchich are connected by sf::Stri
			double (*fx)(double) = nullptr;
			void initFun();
		};

		fx_struct fun1;
		fx_struct fun2;
		fx_struct fun3;
		fx_struct fun4;
		fx_struct* akt_fun;

		//Private functions
		void initVariables();
		void initWindow();
		void initView();
		void initGraph();
		void initAxes();

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

