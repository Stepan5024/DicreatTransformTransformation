#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "DCT.h"
#include "Logger.h"
#include "Plotter.h"
#include "misc.h"
#include "Slider.h"

const int WIDTH  = 1000;
const int HEIGHT = 1000;
const sf::Vector2f window_asp = sf::Vector2f((float)WIDTH, (float)HEIGHT);

int main()
{

	std::vector<float> val;

    for (float i = 0.0f; i < 4 * DCT::PI; i += .2f)
    {
        val.push_back(
            std::max(
                4.7f * std::pow(std::sin(DCT::PI + i), 16.f), 
                0.5f * std::sqrt(fmod(DCT::PI * i, DCT::PI * DCT::PI) - (fmod(i, DCT::PI) * fmod(i, DCT::PI)))
            )
        );
    }

    std::vector<float> dct =  DCT::dct(val);
    std::vector<float> idct = DCT::idct(dct);

    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "plotter test", sf::Style::Default, settings);

    window.setFramerateLimit(60);

    sf::Text fps;

    fps.setFont(font);
    fps.setPosition(WIDTH - 150.0f, 25.0f);
    fps.setCharacterSize(25);
    fps.setFillColor(sf::Color(200, 200, 200));

    sf::Text error_percentage;

    error_percentage.setFont(font);
    error_percentage.setPosition(750, 350);
    error_percentage.setCharacterSize(25);
    error_percentage.setFillColor(sf::Color(200, 200, 200));

    sf::Text compression_percentage;

    compression_percentage.setFont(font);
    compression_percentage.setPosition(750, 250);
    compression_percentage.setCharacterSize(25);
    compression_percentage.setFillColor(sf::Color(200, 200, 200));

    sf::Text text_1;

    text_1.setString("Raw Function:");
    text_1.setFont(font);
    text_1.setPosition(100.0f, 25.0f);
    text_1.setCharacterSize(25);
    text_1.setFillColor(sf::Color(200, 200, 200));

    sf::Text text_2;

    text_2.setString("Discrete Cosine Transform(DCT):");
    text_2.setFont(font);
    text_2.setPosition(100.0f, 350.0f);
    text_2.setCharacterSize(25);
    text_2.setFillColor(sf::Color(200, 200, 200));

    sf::Text text_3;

    text_3.setString("Invert Discrete Cosine Transform(IDCT):");
    text_3.setFont(font);
    text_3.setPosition(100.0f, 675.0f);
    text_3.setCharacterSize(25);
    text_3.setFillColor(sf::Color(200, 200, 200));

    Plotter plot_1 = Plotter(
        val, 
        sf::Vector2f(100.0f, 75.0f), 
        sf::Vector2f(600, 250),
        window_asp,
        sf::Color(15, 252, 3),
        sf::Color(100, 100, 100),
        sf::Color(30, 30, 30),
        font);

    Plotter plot_2 = Plotter(
        dct,
        sf::Vector2f(100.0f, 400.0f),
        sf::Vector2f(600, 250),
        window_asp,
        sf::Color(255, 41, 66),
        sf::Color(100, 100, 100),
        sf::Color(30, 30, 30),
        font);

    Plotter plot_3 = Plotter(
        idct,
        sf::Vector2f(100.0f, 725.0f),
        sf::Vector2f(600, 250),
        window_asp,
        sf::Color(41, 219, 255),
        sf::Color(100, 100, 100),
        sf::Color(30, 30, 30),
        font);

    Slider slid = Slider(sf::Vector2f(750, 200), 200.f, sf::Color(200, 200, 200), sf::Color(100, 100, 100), window_asp);

    float a = DCT::PI * 2.0f;

    sf::Clock cl;
    size_t count = 0;

    sf::Color lsd;

    while (window.isOpen())
    {
        float fps_num = 1.0f / cl.getElapsedTime().asSeconds();
        cl.restart();

        count++;
        if (count == 20)
        {
            fps.setString("fps:\n" + to_string_with_precision(fps_num));
            count = 0;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) 
            {
                switch (event.key.code) 
                {
                case sf::Keyboard::Q:
                    plot_1.flip_col();
                    plot_2.flip_col();
                    plot_3.flip_col();
                    break;
                case sf::Keyboard::W:
                    plot_1.flip_cir();
                    plot_2.flip_cir();
                    plot_3.flip_cir();
                    break;
                case sf::Keyboard::E:
                    plot_1.flip_lin();
                    plot_2.flip_lin();
                    plot_3.flip_lin();
                    break;
                }
            }
        }

        val.clear();
        for (float i = 0.0f + a; i < 4 * DCT::PI + a; i += .2f)
        {
            val.push_back(
                std::max(
                    4.7f * std::pow(std::sin(DCT::PI + i), 16.f),
                    0.5f * std::sqrt(fmod(DCT::PI * i, DCT::PI * DCT::PI) - (fmod(i, DCT::PI) * fmod(i, DCT::PI)))
                )
            );
        }
        a += 0.01f;

        dct = DCT::dct(val);

        slid.process_input(window);
        DCT::compress(dct, slid.get_value());

        idct = DCT::idct(dct);

        float error = 0.f;

        for (size_t i = 0; i < val.size(); i++)
        {
            if (val[i] != 0) 
            {
                error += fabs((idct[i] - val[i]) / val[i]) * 100.f;
            }
        }

        error /= val.size();
        error_percentage.setString("Error:\n" + to_string_with_precision(error) + "%");

        compression_percentage.setString("Compression:\n" + to_string_with_precision(slid.get_value() * 100.f) + "%");

        plot_1.reset_values(val);
        plot_2.reset_values(dct);
        plot_3.reset_values(idct);

        window.clear(sf::Color(40, 40, 40));

        plot_1.draw(window);
        plot_2.draw(window);
        plot_3.draw(window);

        slid.draw(window);

        window.draw(text_1);
        window.draw(text_2);
        window.draw(text_3);

        window.draw(fps);
        window.draw(error_percentage);
        window.draw(compression_percentage);

        window.display();
    }

	return 0;
}