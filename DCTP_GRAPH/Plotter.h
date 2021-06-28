#pragma once

#include <SFML/Graphics.hpp>

#include "misc.h"

class Plotter
{
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Vector2f window_asp;
	sf::RectangleShape area;
	std::vector<sf::RectangleShape> columns;
	std::vector<sf::CircleShape> circles;
	sf::VertexArray lines;
	sf::Color prim_color;
	sf::Color sec_color;
	sf::Color bg_color;
	std::vector<sf::Text> labels;
	std::vector<sf::RectangleShape> stripes;
	bool lines_visible;
	bool circles_visible;
	bool columns_visible;

public:
	Plotter();

	Plotter(
		std::vector<float> &values, 
		sf::Vector2f pos, 
		sf::Vector2f size, 
		sf::Vector2f window_asp);

	Plotter(
		std::vector<float> &values, 
		sf::Vector2f pos, 
		sf::Vector2f size, 
		sf::Vector2f window_asp, 
		sf::Color p_c,
		sf::Color s_c,
		sf::Color b_c,
		sf::Font &font);

	void draw(sf::RenderWindow &window);
	void reset_values(std::vector<float> &values);

	void flip_col();
	void flip_cir();
	void flip_lin();
};