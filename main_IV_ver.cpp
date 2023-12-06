#include "libreria_x_main_IV-copia.hpp"
#include <sstream>


auto evolve(Chain& chain, int steps_per_evolution, sf::Time delta_t) {
  double const dt{delta_t.asSeconds()};

  for (int i{0}; i != steps_per_evolution; ++i) { //fa evolvere la chain ogni dt, i volte, fino a steps_per_evolution e restituisce quest'ultima evoluzione 
    chain.evolve(dt);
  }

  return chain.state();
}

std::string to_string_with_precision(const float a_value, const int n = 9){// https://stackoverflow.com/questions/16605967/set-precision-of-stdto-string-when-converting-floating-point-values
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}




int main() {
  float const mass{10};
  float const k{1000000.};
  int const NoPM{100}; //Number Of PM nella catena
  float const r{50}; //radius of the rest position of the chain
  float const rest_length{2*pi*r/ NoPM}; //rest length is when the chain is a circumference

  Hooke spring{k, rest_length};

  Chain chain{spring};
  chain.initial_config(rest_length, mass, r, NoPM);

  w=100;

  auto const delta_t{sf::milliseconds(1)};
  int const fps{60};
  int const steps_per_evolution{100 / fps};

  unsigned const display_width = sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = sf::VideoMode::getDesktopMode().height;
  

    sf::Font font;
    font.loadFromFile("./font/grasping.ttf");
    sf::Text stringa;
    stringa.setFont(font);
   // stringa.setString("caccamerda");
    stringa.setCharacterSize(40);
    stringa.setFillColor(sf::Color::White);
    stringa.setPosition(300, -300);

  sf::RenderWindow window(sf::VideoMode(display_width, display_height), "Chain Evolution");
  window.setFramerateLimit(fps);  
  window.setPosition(sf::Vector2i(0, 0));

  sf::Vector2f window_size(window.getSize());  // getsize prende width e height della window
  sf::View view{sf::Vector2f{0, 0}, window_size};  // view permette di cambiare l'origine, il primo vettore è l'origine, il secondo e la size della window
  window.setView(view);


  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
     // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) window.close();

    }

    window.clear(sf::Color::Black);
    stringa.setString(to_string_with_precision(delta_t.asSeconds()));
    window.draw(stringa); 
    auto const state = evolve(chain, steps_per_evolution, delta_t);

  //std::cout<<"istante: " << delta_t.asSeconds() << '\n';

for (int i = 0; i < chain.size(); ++i){
  chain[i].draw(window);
 // std::cout<< "PM_"<< i << " = (" << chain[i].get_pos().get_x() << ", " << chain[i].get_pos().get_y() << " ) \n"; 
}
    
    window.display();
  }
}