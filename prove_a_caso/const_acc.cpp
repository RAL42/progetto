#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "const_acc.hpp"

bool trigger{true};
void On() {
  trigger = true;
  std::cout << "trigger = " << trigger << '\n';
}
void Off() {
  trigger = false;
  std::cout << "trigger = " << trigger << '\n';
}

int main() {
  sf::RenderWindow window(sf::VideoMode(1000, 500), "finestra");
  window.setPosition(sf::Vector2i(100, 100));
  window.setVerticalSyncEnabled(false);
  window.setFramerateLimit(60);

  particle p1{};

  sf::CircleShape cerchio(20);
  cerchio.setFillColor(sf::Color::Green);
  float i{};

  while (i < t_max && trigger) {
    p1.evolve();
    cerchio.setPosition(100, p1.x_);
    i += dt;
    window.clear(sf::Color::White);
    window.draw(cerchio);
    window.display();
  };

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

          /* case sf::Event::KeyPressed:  // accende
             switch (event.key.code) {
               case sf::Keyboard::A:
                 On();
                 break;

               case sf::Keyboard::B:
                 Off();
                 break;

               default:
                 break;
             }
             break;*/
      }
    }
    

  }
}