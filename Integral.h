#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>

#define WINDOW_X 1600
#define WINDOW_Y 900
#define CENTER_X WINDOW_X/2
#define CENTER_Y WINDOW_Y/2
#define DUPA 5 //dlugosc tych frendzlow na osiach
#define AXES_COLOR sf::Color(255, 255, 255, 255)
#define FUNCTION_COLOR sf::Color(0, 0, 255, 255)
#define DRAWING_PRECISION 1.0 //smaller - more precision
#define DEFAULT_GRAPH_SCALE 40	
#define LETTER_SPACING 4

/*
	Class that is used for everything related to integrals
	Also contains application menu
*/

class Integral
{
	private:
		//Variables
		
		int graph_scale;
		double graph_scale_multiplier;

		//Window
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event e;
		sf::View view;

		//Font
		sf::Font font;
		std::vector <sf::Text> text;

		//App objects
		sf::VertexArray axes;	//array of vertex that contains our axes

		//Structure which contains function graph and pointer to the function itself
		struct fx_struct{
			sf::VertexArray fun;	//array of vertex that contains points of graph wchich are connected by sf::Stri
			double (*fx)(double) = nullptr;
			void drawFun(double multiplier, int scale);
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
		void initFont();
		void drawGraph();
		void drawAxes();

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

