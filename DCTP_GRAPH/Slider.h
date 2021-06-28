#pragma once

#include <SFML/Graphics.hpp>

#include "misc.h"

class Slider
{
	sf::CircleShape dragger;
	sf::RectangleShape line;
	sf::Color prim_col;
	sf::Color sec_col;
	float value;
	sf::Vector2f pos;
	float length;
	float click_area;

public:
	Slider();
	Slider(sf::Vector2f pos, float length, sf::Color p_c, sf::Color s_c, sf::Vector2f wind_asp, float init_val = 0.f);
	void process_input(sf::RenderWindow& window);
	void draw(sf::RenderWindow &window);
	float get_value();
};

