#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "const_acc.hpp"
//in questo caso il grafico disegnato è importato da const_acc.hpp, poichè le equazioni che disegnerò (graph_of_x & graph_of_vel) si calcolano tramite "evolve()"

int main() {
  // Genero la finestra

  int height{500};
  int width{800};
  sf::RenderWindow window(sf::VideoMode(width, height), "FINESTRA");
  window.setPosition(sf::Vector2i(100, 100));
  window.setVerticalSyncEnabled(false);
  window.setFramerateLimit(60);

  auto n{t_max / dt};  // numero di punti(vertici)
  particle p1{};
  sf::VertexArray graph_of_pos(sf::LineStrip, n);
  sf::VertexArray graph_of_vel(sf::LineStrip, n);

  auto scale_factor{width/t_max};  // in modo che il grafico occupi tutta la finestra
  float i{};
  while (i < t_max) {
    p1.evolve();
    graph_of_pos[i].position = sf::Vector2f(i * scale_factor, p1.x_); //riempio l'array del grafico della posizione con i punti x_ (la distanza è presa dal top della finestra)
    graph_of_pos[i].color = sf::Color::Red;     // "i" funge da tempo, che riscalo di un fattore "scale_factor"

    graph_of_vel[i].position = sf::Vector2f(i * scale_factor, p1.vel_);
    graph_of_vel[i].color = sf::Color::Green;
    i += dt;
    //p1.print(); //stampa i dati sul terminale (opzionale)
  };

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
      }
    }
    window.clear(sf::Color::White);
    window.draw(graph_of_pos);
    window.draw(graph_of_vel);
    window.display();
  }
}