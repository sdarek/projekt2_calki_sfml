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



void Integral::fx_struct::drawFun(double multiplier, int scale)
{
	/*	This function initializes our fx_struct
	*	-first array of graph points is cleared
	*	-set way of connecting points (linesStrip)
	*	-ok the most important part: to the array of points are adding points which are coordinates our function 
	*			-x from an i=0.0, because 0 means the left edge of our window
	*			-y from window_y/2 - .... because i want it in the middle
	*								 .... -> ((i / scale - j / scale) * scale)  because one unit is every 'value in scale' pixels. 
	*/
	this->fun.clear();
	this->fun.setPrimitiveType(sf::PrimitiveType::LinesStrip);
	for (double i = 0.0, j = CENTER_X; i < WINDOW_X; i += DRAWING_PRECISION)
	{
		this->fun.append(sf::Vertex(sf::Vector2f(i, CENTER_Y - this->fx((i - j) / scale * multiplier) * scale / multiplier), FUNCTION_COLOR));
	}
}



void Integral::initVariables()
{
	this->window = nullptr;
	this->akt_fun = &fun1;
	fun1.fx = f1;
	fun2.fx = f2;
	fun3.fx = f3;
	fun4.fx = f4;
	this->graph_scale = DEFAULT_GRAPH_SCALE;
	this->graph_scale_multiplier = 1;

	if (!this->font.loadFromFile("Fonts/times.ttf")) std::cout << "Error 195487254 couldn't load font\n";
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

void Integral::initFont()
{
	int suma = 0;
	for (int i = 0; i < WINDOW_X; i += (DEFAULT_GRAPH_SCALE / 2 + 1), suma++);
	for (int i = 0; i < WINDOW_Y; i += (DEFAULT_GRAPH_SCALE / 2 + 1), suma++);

	//sf::Text* textt = new sf::Text("", this->font, 12U)[suma];

}

void Integral::drawGraph()
{
	this->drawAxes();
	fun1.drawFun(this->graph_scale_multiplier, this->graph_scale);
	fun2.drawFun(this->graph_scale_multiplier, this->graph_scale);
	fun3.drawFun(this->graph_scale_multiplier, this->graph_scale);
	fun4.drawFun(this->graph_scale_multiplier, this->graph_scale);
}
void Integral::drawAxes()
{
	this->axes.clear();
	this->text.clear();
	this->axes.setPrimitiveType(sf::PrimitiveType::Lines);
	this->axes.append(sf::Vertex(sf::Vector2f(0, CENTER_Y), AXES_COLOR));
	this->axes.append(sf::Vertex(sf::Vector2f(WINDOW_X, CENTER_Y), AXES_COLOR));
	this->axes.append(sf::Vertex(sf::Vector2f(CENTER_X, 0), AXES_COLOR));
	this->axes.append(sf::Vertex(sf::Vector2f(CENTER_X, WINDOW_Y), AXES_COLOR));

	for (int i = CENTER_X + this->graph_scale, j = 1; i < WINDOW_X; i += this->graph_scale, j++)
	{
		//drawing lines on axis X
		this->axes.append(sf::Vertex(sf::Vector2f(i, CENTER_Y - DUPA), AXES_COLOR));
		this->axes.append(sf::Vertex(sf::Vector2f(i, CENTER_Y + DUPA), AXES_COLOR));
		this->axes.append(sf::Vertex(sf::Vector2f(WINDOW_X - i, CENTER_Y - DUPA), AXES_COLOR));
		this->axes.append(sf::Vertex(sf::Vector2f(WINDOW_X - i, CENTER_Y + DUPA), AXES_COLOR));
		//adding text above the axis X
		int one_x_point = this->graph_scale_multiplier * j;
		std::string axis_point = std::to_string(one_x_point);
		std::string axis_point2 = "." + std::to_string((int)((this->graph_scale_multiplier * j - one_x_point) * 100));
		if ((j) % LETTER_SPACING == 0 || j == 1)
		{
			this->text.push_back(sf::Text(axis_point, this->font, 12U));
			if (this->graph_scale_multiplier < 1) this->text.back().setString(this->text.back().getString() + axis_point2);
			this->text.back().setOrigin(sf::Vector2f(this->text.back().getGlobalBounds().width / 2, this->text.back().getGlobalBounds().height / 2));
			this->text.back().setPosition(sf::Vector2f(i, CENTER_Y - DUPA - 15));

			this->text.push_back(sf::Text("-" + axis_point, this->font, 12U));
			if (this->graph_scale_multiplier < 1) this->text.back().setString(this->text.back().getString() + axis_point2);
			this->text.back().setOrigin(sf::Vector2f(this->text.back().getGlobalBounds().width / 2, this->text.back().getGlobalBounds().height / 2));
			this->text.back().setPosition(sf::Vector2f(WINDOW_X - i, CENTER_Y - DUPA - 15));
		}
	}
	for (int i = CENTER_Y + this->graph_scale, j = 1; i < WINDOW_Y; i += this->graph_scale, j++)
	{
		//drawing lines on axis Y
		this->axes.append(sf::Vertex(sf::Vector2f(CENTER_X - DUPA, i), AXES_COLOR));
		this->axes.append(sf::Vertex(sf::Vector2f(CENTER_X + DUPA, i), AXES_COLOR));
		this->axes.append(sf::Vertex(sf::Vector2f(CENTER_X - DUPA, WINDOW_Y - i), AXES_COLOR));
		this->axes.append(sf::Vertex(sf::Vector2f(CENTER_X + DUPA, WINDOW_Y - i), AXES_COLOR));
		//adding text next to the axis Y
		int one_x_point = this->graph_scale_multiplier * j;
		std::string axis_point = std::to_string(one_x_point);
		std::string axis_point2 = "." + std::to_string((int)((this->graph_scale_multiplier * j - one_x_point) * 100));
		if ((j) % LETTER_SPACING == 0 || j == 1)
		{
			this->text.push_back(sf::Text("-" + axis_point, this->font, 12U));
			if (this->graph_scale_multiplier < 1) this->text.back().setString(this->text.back().getString() + axis_point2);
			this->text.back().setOrigin(sf::Vector2f(this->text.back().getGlobalBounds().width / 2, this->text.back().getGlobalBounds().height / 2));
			this->text.back().setPosition(sf::Vector2f(CENTER_X + DUPA + 10, i));

			this->text.push_back(sf::Text(axis_point, this->font, 12U));
			if (this->graph_scale_multiplier < 1) this->text.back().setString(this->text.back().getString() + axis_point2);
			this->text.back().setOrigin(sf::Vector2f(this->text.back().getGlobalBounds().width / 2, this->text.back().getGlobalBounds().height / 2));
			this->text.back().setPosition(sf::Vector2f(CENTER_X + DUPA + 10, WINDOW_Y - i));
		}
	}
}
//Constructors / Destructors

Integral::Integral()
{
	this->initVariables();
	this->initWindow();
	this->initView();
	this->initFont();
	this->drawGraph();
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
				if (this->graph_scale + 1 == DEFAULT_GRAPH_SCALE * 2 && this->graph_scale_multiplier < 0.5f) break;
				this->graph_scale++;
				if (this->graph_scale >= DEFAULT_GRAPH_SCALE * 2)
				{
					this->graph_scale_multiplier /= 2.;
					this->graph_scale -= DEFAULT_GRAPH_SCALE;
				}
				std::cout << "graph scale: " << this->graph_scale << std::endl;
				std::cout << "graph multi: " << this->graph_scale_multiplier << std::endl;
				this->drawGraph();
				this->drawAxes();
			}
			if (this->e.key.code == sf::Keyboard::Down)
			{
				this->graph_scale--;
				if (this->graph_scale < DEFAULT_GRAPH_SCALE)
				{
					this->graph_scale_multiplier *= 2;
					this->graph_scale += DEFAULT_GRAPH_SCALE;
				}
				//std::cout << this->graph_scale << std::endl;
				std::cout << this->graph_scale_multiplier << std::endl;
				this->drawGraph();
				this->drawAxes();
			}
			if (this->e.key.code == sf::Keyboard::R)
			{
				this->graph_scale = DEFAULT_GRAPH_SCALE;
				this->graph_scale_multiplier = 1;
				this->drawGraph();
				this->drawAxes();
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

	//Draw app objects
	this->window->draw(this->axes);
	for(int i = 0; i < this->text.size(); i++) this->window->draw(this->text[i]);
	this->window->draw(akt_fun->fun);

	this->window->display();
}
