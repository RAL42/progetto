#include "Chain.hpp"
#include <cassert>
#include <sstream>

auto evolve(Chain &chain, int steps_per_evolution, sf::Time delta_t){
  double const dt{delta_t.asSeconds()};
  std::cout << "in evolve : dt=" << dt << '\n';

  for (int i{0}; i != steps_per_evolution; ++i) { // fa evolvere la chain ogni dt, i volte, fino a steps_per_evolution e restituisce quest'ultima evoluzione
    chain.evolve(dt);
    std::cout << "\nFine evolve del main\n";
  }
  return chain.state();
}

std::string to_string_with_precision(const float a_value, const int n = 1) { // https://stackoverflow.com/questions/16605967/set-precision-of-stdto-string-when-converting-floating-point-values
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return std::move(out).str();
}

int main()
{
  float const mass{10000000.};
  float const k{1000.};
  int const NoPM{100};
  assert(NoPM > 0 && NoPM % 2 == 0); // Number Of PM nella catena SOLO NUMERI PARI!!!! PER LA FUNZIONE evolve DENTRO LA CLASSE CHAIN (nell'if)

  float const r{200}; // radius of the rest position of the chain
  float const theta{2 * pi / NoPM};
  float const rest_length{theta * r}; // rest length is when the chain is a circumference

  Hooke spring{k, rest_length};

  Chain chain{spring};
  chain.initial_config(theta, mass, r, NoPM);

  w = 10.; // la modifico nella libreria chain.hpp

  std::cout << "m=" << mass << " k=" << k << " NoPM=" << NoPM << " w=" << w << '\n';

  auto const delta_t{sf::milliseconds(1)};
  int const fps{60};
  int steps_per_evolution{100/ fps};

  unsigned const display_width = 0.85 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = 0.85 * sf::VideoMode::getDesktopMode().height;

  sf::Font font;
  font.loadFromFile("./font/fresco_stamp.ttf");
  sf::Text stringa1;
  sf::Text stringa2;
  sf::Text stringa3;
  stringa1.setFont(font);
  stringa1.setCharacterSize(40);
  stringa1.setFillColor(sf::Color::White);
  stringa1.setPosition(300, -300);

  stringa2.setFont(font);
  stringa2.setCharacterSize(40);
  stringa2.setFillColor(sf::Color::Magenta);
  stringa2.setPosition(300, -350);

  sf::RenderWindow window(sf::VideoMode(display_width, display_height), "Chain Evolution");
  window.setFramerateLimit(fps);
  window.setPosition(sf::Vector2i(50, 50));

  sf::Vector2f window_size(window.getSize());     // getsize prende width e height della window
  sf::View view{sf::Vector2f{0, 0}, window_size}; // view permette di cambiare l'origine, il primo vettore è l'origine, il secondo e la size della window
  window.setView(view);

  sf::Vertex x_axis[] = {sf::Vertex(sf::Vector2f(-window_size.x, 0)), sf::Vertex(sf::Vector2f(window_size.x, 0))};
  sf::Vertex y_axis[] = {sf::Vertex(sf::Vector2f(0, -window_size.y / 2)), sf::Vertex(sf::Vector2f(0, window_size.y / 2))};
   
  bool start = false;

  while (window.isOpen()) {


    sf::Event event;    
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        start = true;
        std::cout<<start<< '\n';
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        start = false;
        std::cout<<start<< '\n';
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ++w;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) --w;      
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ++steps_per_evolution ;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) --steps_per_evolution ;
    }

    if (start){
      window.clear(sf::Color::Black);
       stringa1.setString("steps_per_evolution is " + to_string_with_precision(steps_per_evolution));
       window.draw(stringa1);

       stringa2.setString("W is " + to_string_with_precision(w));
       window.draw(stringa2);

      std::cout << "\nchiamo evolve nel main\n";

      auto const state = evolve(chain, steps_per_evolution, delta_t);

      std::cout << "\nInizio for del main per disegnare \n";
      for (long unsigned int i = 0; i < chain.size(); ++i) {
        chain[i].draw(window);
        //std::cout<<"pos :"<< chain[i].get_pos() << "vel :" << chain[i].get_vel() << '\n';
      }
      std::cout << "Fuori for del main per disegnare \n";
    
      window.draw(x_axis, 2, sf::Lines);
      window.draw(y_axis, 2, sf::Lines);  
  
      window.display();
    }
  }
}

/*
NOTA: non c'è bisogno di tenere traccia del tempo. Lo scorrere del tempo è scandito dagli step che faccio nel programma,
cioè io faccio partire il programma e lui fa partire una prima iterazione chiamando la funzione evolve()
che calcola il nuovo stato della catena (e lo assegna a "state", riga 84), e stampa a schermo le posizioni
dei PM della Chain ogni tot volte, ossia ogni "steps_per_evolution" e poi ripete, richiamando la funzione evolve()
*/