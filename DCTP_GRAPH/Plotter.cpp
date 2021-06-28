#include "Plotter.h"

Plotter::Plotter()
{
}

Plotter::Plotter(
	std::vector<float> &values, 
	sf::Vector2f pos, 
	sf::Vector2f size, 
	sf::Vector2f window_asp)
{
	//TODO: Text, Circles, Hover
}

Plotter::Plotter(
	std::vector<float> &values, 
	sf::Vector2f pos, 
	sf::Vector2f size, 
	sf::Vector2f window_asp, 
	sf::Color p_c, 
	sf::Color s_c, 
	sf::Color b_c,
	sf::Font& font)
{
	columns_visible = false;
	lines_visible = true;
	circles_visible = false;

	prim_color = p_c;
	sec_color  = s_c;
	bg_color   = b_c;

	this->window_asp = window_asp;
	this->pos = pos;
	this->size = size;

	float off = (size.x * (0.5f / (float)values.size()));

	area.setFillColor(bg_color);
	area.setOutlineColor(sec_color);
	area.setOutlineThickness(size.x * 0.005);
	area.setPosition(sf::Vector2f(pos.x, pos.y - off/2.0f));
	area.setSize(sf::Vector2f(size.x, size.y + off));

	float min = values[0];
	float max = values[0];
	for (size_t i = 1; i < values.size(); i++)
	{
		min = std::min(values[i], min);
		max = std::max(values[i], max);
	}

	lines = sf::VertexArray(sf::LineStrip, values.size());

	for (size_t i = 0; i < values.size(); i++)
	{
		sf::Vector2f loc_pos(off + pos.x + size.x * ((float)i / (float)values.size()), pos.y + ((max - values[i]) / (max - min)) * size.y);

		sf::RectangleShape column;
		column.setFillColor(prim_color);
		column.setPosition(loc_pos.x - size.x * 0.0025, loc_pos.y);
		column.setSize(sf::Vector2f(size.x * 0.005, ((values[i] - min) / (max - min)) * size.y));
		columns.push_back(column);

		lines[i].color = prim_color;
		lines[i].position = sf::Vector2f(loc_pos);

		sf::CircleShape circle;
		circle.setFillColor(prim_color);
		circle.setPosition(loc_pos.x - size.y * 0.02, loc_pos.y - size.y * 0.02);
		circle.setRadius(size.y * 0.02);
		circles.push_back(circle);
	}

	for (size_t i = 0; i <= 10; i++)
	{
		sf::Text label;

		label.setString(to_string_with_precision((((float)i / 10.0f) * (max - min)) + min));
		label.setFont(font);
		label.setPosition(pos.x - size.y * 0.18f, (((10.0f - (float)i) / 10.0f) * size.y) + pos.y - size.y * 0.026f);
		label.setCharacterSize(size.y * 0.05f);
		label.setFillColor(sec_color);

		labels.push_back(label);

		sf::RectangleShape stripe;
		stripe.setPosition(pos.x, (((10.0f - (float)i) / 10.0f) * size.y) + pos.y);
		stripe.setSize(sf::Vector2f(size.x, size.x * 0.001));
		stripe.setFillColor(sec_color);
		stripes.push_back(stripe);
	}
}

void Plotter::draw(sf::RenderWindow& window)
{
	window.draw(area);
	for (auto &stripe : stripes)
	{
		window.draw(stripe);
	}
	if (columns_visible) 
	{
		for (auto& column : columns)
		{
			window.draw(column);
		}
	}
	if (circles_visible) 
	{
		for (auto& circle : circles)
		{
			window.draw(circle);
		}
	}
	if (lines_visible) 
	{
		window.draw(lines);
	}
	for (auto &label : labels)
	{
		window.draw(label);
	}
}

void Plotter::reset_values(std::vector<float> &values)
{
	columns.clear();
	circles.clear();
	float off = (size.x * (0.5f / (float)values.size()));

	float min = values[0];
	float max = values[0];
	for (size_t i = 1; i < values.size(); i++)
	{
		min = std::min(values[i], min);
		max = std::max(values[i], max);
	}

	lines = sf::VertexArray(sf::LineStrip, values.size());

	for (size_t i = 0; i < values.size(); i++)
	{
		sf::Vector2f loc_pos(off + pos.x + size.x * ((float)i / (float)values.size()), pos.y + ((max - values[i]) / (max - min)) * size.y);

		sf::RectangleShape column;
		column.setFillColor(prim_color);
		column.setPosition(loc_pos.x - size.x * 0.0025, loc_pos.y);
		column.setSize(sf::Vector2f(size.x * 0.005, ((values[i] - min) / (max - min)) * size.y));
		columns.push_back(column);

		lines[i].color = prim_color;
		lines[i].position = sf::Vector2f(loc_pos);

		sf::CircleShape circle;
		circle.setFillColor(prim_color);
		circle.setPosition(loc_pos.x - size.y * 0.02, loc_pos.y - size.y * 0.02);
		circle.setRadius(size.y * 0.02);
		circles.push_back(circle);
	}

	for (size_t i = 0; i < labels.size(); i++)
	{
		labels[i].setString(to_string_with_precision((((float)i / 10.0f) * (max - min)) + min));
	}
}

void Plotter::flip_col()
{
	columns_visible = !columns_visible;
}

void Plotter::flip_cir()
{
	circles_visible = !circles_visible;
}

void Plotter::flip_lin()
{
	lines_visible = !lines_visible;
}
