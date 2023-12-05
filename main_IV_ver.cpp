#include "libreria_x_main_IV-copia.hpp"



auto evolve(Chain& chain, int steps_per_evolution, sf::Time delta_t) {
  double const dt{delta_t.asSeconds()};

  for (int i{0}; i != steps_per_evolution; ++i) { //fa evolvere la chain ogni dt, i volte, fino a steps_per_evolution e restituisce quest'ultima evoluzione 
    chain.evolve(dt);
  }

  return chain.state();
}



int main() {
  float const mass{1};
  float const k{50};
  int const NoPM{100}; //Number Of PM nella catena
  float const r{100}; //radius of the rest position of the chain
  float const rest_length{2*pi*r/ NoPM}; //rest length is when the chain is a circumference

  Hooke const spring{k, rest_length};

  Chain chain{spring};
  chain.initial_config(rest_length, mass, r, NoPM);

  w=100;

  auto const delta_t{sf::microseconds(10)};
  int const fps{60};
  int const steps_per_evolution{500 / fps};

  unsigned const display_width = .9 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = .9 * sf::VideoMode::getDesktopMode().height;
  

  sf::RenderWindow window(sf::VideoMode(display_width, display_height), "Chain Evolution");
  window.setFramerateLimit(fps);  
  window.setPosition(sf::Vector2i(100, 100));

  sf::Vector2f window_size(window.getSize());  // getsize prende width e height della window
  sf::View view{sf::Vector2f{0, 0}, window_size};  // view permette di cambiare l'origine, il primo vettore è l'origine, il secondo e la size della window
  window.setView(view);


  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Black);

    auto const state = evolve(chain, steps_per_evolution, delta_t);

  std::cout<<"istante: " << delta_t.asSeconds() << '\n';

for (int i = 0; i < chain.size(); ++i){
  chain[i].draw(window);
  std::cout<< "PM_"<< i << " = (" << chain[i].get_pos().get_x() << ", " << chain[i].get_pos().get_y() << " ) \n"; 
}


/*
    for (auto& particle : state) {
      circ.setPosition((particle.x - min_x) * scale_x, display_height * 0.5);
      window.draw(circ);
    }
*/
    window.display();


  }










}