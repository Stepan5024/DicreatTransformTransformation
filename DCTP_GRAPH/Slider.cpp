#include "Slider.h"

Slider::Slider()
{
}

Slider::Slider(sf::Vector2f pos, float length, sf::Color p_c, sf::Color s_c, sf::Vector2f wind_asp, float init_val)
{
	this->pos = pos;
	this->length = length;
	
	prim_col = p_c;
	sec_col = s_c;
	value = init_val;
	click_area = wind_asp.y * 0.02f;

	dragger.setFillColor(prim_col);
	dragger.setRadius(click_area / 2.f);
	dragger.setPosition(sf::Vector2f(pos.x + (value * length) - (click_area / 2.f), pos.y - (click_area / 2.f)));

	line.setFillColor(sec_col);
	line.setPosition(sf::Vector2f(pos.x, pos.y - wind_asp.y * 0.0025f));
	line.setSize(sf::Vector2f(length, wind_asp.y * 0.005f));
}

void Slider::process_input(sf::RenderWindow &window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		if (
			mouse_pos.x >= pos.x - (click_area / 2.f) &&
			mouse_pos.x <= pos.x + length + (click_area / 2.f) &&
			mouse_pos.y >= pos.y - click_area &&
			mouse_pos.y <= pos.y + click_area)
		{
			dragger.setPosition(sf::Vector2f(clamp(mouse_pos.x, pos.x, pos.x + length) - (click_area / 2.f), dragger.getPosition().y));
			value = ((dragger.getPosition().x + (click_area / 2.f)) - pos.x) / length;
		}
	}
}

void Slider::draw(sf::RenderWindow& window)
{
	window.draw(line);
	window.draw(dragger);
}

float Slider::get_value()
{
	return value;
}
