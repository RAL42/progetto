#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>

float const a = 20;
float const b = 5;

sf::Vector2f function(sf::Vector2f vector)
{
    //double modulus_squared {std::pow(vector.x, 2)+std::pow(vector.y, 2)};
    sf::Vector2f result{-a*vector.y, b*vector.x};
    return result;
}

int main()
{
    unsigned const display_width = .9 * sf::VideoMode::getDesktopMode().width;
    unsigned const display_height = .9 * sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(display_width, display_height), "Runge Kutta");
    window.clear(sf::Color::Black);
    sf::Vector2f window_size (window.getSize());
    sf::View view {sf::Vector2f{0,0}, window_size};
    window.setView(view);

    float dt{0.00001};
    sf::Vector2f last_state{0, 0};
    sf::Vector2f current_state(0, window_size.y / 4);

    sf::Vertex x_axis[] = {sf::Vertex(sf::Vector2f(-window_size.x, 0)), sf::Vertex(sf::Vector2f(window_size.x, 0))};
    sf::Vertex y_axis[] = {sf::Vertex(sf::Vector2f(0, -window_size.y/2)), sf::Vertex(sf::Vector2f(0, window_size.y/2))};
    sf::VertexArray vertex_array;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        for(int i=0; i<1000; ++i){
        last_state = current_state;
        current_state = last_state + function(last_state + function(last_state) * static_cast<float>(dt / 2)) * dt;
        }
        vertex_array.append(sf::Vertex(current_state));

        window.draw(vertex_array);
        window.draw(x_axis, 2, sf::Lines);
        window.draw(y_axis, 2, sf::Lines);
        window.display();
        // imposta condizione di iterazione e disegna i punti bianchi per ogni current_state
    }
}