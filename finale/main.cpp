#include <cassert>
#include <numeric>
#include <sstream>

#include "chain.hpp"
/*
  Fonte della funzione std::string to_string_with_precision:
  https://stackoverflow.com/questions/16605967/set-precision-of-stdto-string-when-converting-doubleing-point-values
*/

auto evolve(Chain& chain, int steps_per_evolution, sf::Time delta_t,
            double const w) {
  // fa evolvere la chain ogni dt, i volte, fino a steps_per_evolution e
  // restituisce quest'ultima evoluzione, che poi andrà stampata a schermo

  double const dt{delta_t.asSeconds()};

  for (int i{0}; i != steps_per_evolution; ++i) {
    chain.evolve(dt, w);
  }
  return chain.state();
}

std::string to_string_with_precision(const double a_value, const int n = 1) {
  // converte un double in string con n cifre decimali
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return std::move(out).str();
}

int main() {
  double mass{};
  // massa dei punti materiali
  double k{};
  // costante elastica della molla
  int NoPM{};
  // numero di elementi della chain
  double r{};
  // raggio della chain nella posizione iniziale
  double w{};

  // chiedo in input i parametri principali
  std::cout << "Inserisci massa dei Punti Materiali \n";
  std::cin >> mass;
  if (std::cin.fail()) {
    throw std::runtime_error{"Incorrect Input"};
  };

  std::cout << "Inserisci la costante elastica k\n";
  std::cin >> k;
  if (std::cin.fail()) {
    throw std::runtime_error{"Incorrect Input"};
  };

  std::cout << "Inserisci un numero multiplo di 4 di punti materiali\n";
  std::cin >> NoPM;
  if (std::cin.fail()) {
    throw std::runtime_error{"Incorrect Input"};
  };

  std::cout << "Inserisci il raggio della configurazione inziale\n";
  std::cin >> r;
  if (std::cin.fail()) {
    throw std::runtime_error{"Incorrect Input"};
  };

  std::cout << "Inserisci la velocità angolare \n";
  std::cin >> w;
  if (std::cin.fail()) {
    throw std::runtime_error{"Incorrect Input"};
  };

  // calcola i vari parametri per la molla "hooke" e la "chain"

  double const rest_length = sqrt(2 * r * r * (1 - cos(2 * M_PI / NoPM)));
  // la lunghezza a riposo è data dalla distanza dei punti nella condizione
  // iniziale

  Hooke spring{k, rest_length};

  Chain chain{spring, mass, r, NoPM};

  std::cout << "m=" << mass << " k=" << k << " NoPM=" << NoPM << " w=" << w
            << '\n';
  std::cout << "lunghezza a riposo : " << rest_length << '\n';

  auto const delta_t{sf::milliseconds(1)};
  int const fps{60};
  int steps_per_evolution{120 / fps};
  // parametro che permette di disegnare la chain dopo un tot di steps

  unsigned const display_width = 0.85 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = 0.85 * sf::VideoMode::getDesktopMode().height;

  // crea le varie stringhe delle variabili da stampare a schermo
  sf::Font font;
  font.loadFromFile("./font/fresco_stamp.ttf");
  sf::Text string_w;
  sf::Text string_steps;
  sf::Text string_NoPM;
  sf::Text string_k;
  sf::Text string_Kinetic_Energy;
  sf::Text string_Potential_Energy;
  sf::Text string_Total_Energy;

  string_NoPM.setFont(font);
  string_NoPM.setCharacterSize(40);
  string_NoPM.setFillColor(sf::Color::White);
  string_NoPM.setPosition(400, -250);

  string_w.setFont(font);
  string_w.setCharacterSize(40);
  string_w.setFillColor(sf::Color::White);
  string_w.setPosition(400, -300);

  string_steps.setFont(font);
  string_steps.setCharacterSize(40);
  string_steps.setFillColor(sf::Color::White);
  string_steps.setPosition(400, -350);

  string_k.setFont(font);
  string_k.setCharacterSize(40);
  string_k.setFillColor(sf::Color::White);
  string_k.setPosition(400, -400);

  string_Kinetic_Energy.setFont(font);
  string_Kinetic_Energy.setCharacterSize(40);
  string_Kinetic_Energy.setFillColor(sf::Color::White);
  string_Kinetic_Energy.setPosition(-700, -350);

  string_Potential_Energy.setFont(font);
  string_Potential_Energy.setCharacterSize(40);
  string_Potential_Energy.setFillColor(sf::Color::White);
  string_Potential_Energy.setPosition(-700, -300);

  string_Total_Energy.setFont(font);
  string_Total_Energy.setCharacterSize(40);
  string_Total_Energy.setFillColor(sf::Color::White);
  string_Total_Energy.setPosition(-700, -250);

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Chain Evolution");
  // creo la finestra di SFML
  window.setFramerateLimit(fps);
  window.setPosition(sf::Vector2i(50, 50));

  sf::Vector2f window_size(window.getSize());
  // getsize prende width e height della window

  sf::View view{sf::Vector2f{0, 0}, window_size};
  window.setView(view);
  // sf::View permette di cambiare l'origine del sistema di riferimento, il
  // primo vettore è l'origine, il secondo è la size della window

  // creo gli assi cartesiani
  sf::Vertex x_axis[] = {sf::Vertex(sf::Vector2f(-window_size.x, 0)),
                         sf::Vertex(sf::Vector2f(window_size.x, 0))};
  sf::Vertex y_axis[] = {sf::Vertex(sf::Vector2f(0, -window_size.y / 2)),
                         sf::Vertex(sf::Vector2f(0, window_size.y / 2))};

  bool start = false;
  // per far partire l'evoluzione
  bool first = true;
  // per far stampare a schermo la condizione iniziale

  while (window.isOpen()) {
    window.setKeyRepeatEnabled(true);
    // permette di "ripremere" il pulsante tenendolo premuto

    sf::Event event;
    while (window.pollEvent(event)) {
      // comandi per variare alcune grandezze in real-time

      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Enter) {
        start = true;
        first = false;
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape) {
        start = false;
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::W)
        ++w;
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::S)
        --w;
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::D)
        ++steps_per_evolution;
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::A && steps_per_evolution != 0)
        --steps_per_evolution;
    }

    if (first) {
      // disegno la condizione iniziale e le varie stringhe finche non premo
      // invio

      window.clear(sf::Color::Black);

      string_k.setString("k is " + to_string_with_precision(k));
      window.draw(string_k);

      string_NoPM.setString("NoPM is " + to_string_with_precision(NoPM));
      window.draw(string_NoPM);

      string_w.setString("steps_per_evolution is " +
                         to_string_with_precision(steps_per_evolution));
      window.draw(string_w);

      string_steps.setString("W is " + to_string_with_precision(w));
      window.draw(string_steps);

      // calcolo le varie energie, le riscalo, e poi le stampo a schermo
      double Total_Kinetic_Energy{};
      Total_Kinetic_Energy = chain.kin_energy() * .000001;
      string_Kinetic_Energy.setString(
          "Total kinetic energy is " +
          to_string_with_precision(Total_Kinetic_Energy));
      window.draw(string_Kinetic_Energy);

      double Total_Potential_Energy{};
      Total_Potential_Energy = chain.pot_energy() * .000001;
      string_Potential_Energy.setString(
          "Total potential energy is " +
          to_string_with_precision(Total_Potential_Energy));
      window.draw(string_Potential_Energy);

      auto Total_energy = Total_Kinetic_Energy + Total_Potential_Energy;
      string_Total_Energy.setString("Total energy is " +
                                    to_string_with_precision(Total_energy));
      window.draw(string_Total_Energy);

      for (size_t i = 0; i != chain.size(); ++i) {
        chain[i].draw(window);
      }

      window.draw(x_axis, 2, sf::Lines);
      window.draw(y_axis, 2, sf::Lines);

      window.display();
    }
    if (start) {
      // se premo invio parte la simulazione
      window.clear(sf::Color::Black);

      string_NoPM.setString("k is " + to_string_with_precision(k));
      window.draw(string_k);

      string_NoPM.setString("NoPM is " + to_string_with_precision(NoPM));
      window.draw(string_NoPM);

      string_w.setString("steps_per_evolution is " +
                         to_string_with_precision(steps_per_evolution));
      window.draw(string_w);

      string_steps.setString("W is " + to_string_with_precision(w));
      window.draw(string_steps);

      // calcolo le varie energie, le riscalo, e poi le stampo a schermo
      double Total_Kinetic_Energy{};
      Total_Kinetic_Energy = chain.kin_energy() * .000001;
      string_Kinetic_Energy.setString(
          "Total kinetic energy is " +
          to_string_with_precision(Total_Kinetic_Energy));
      window.draw(string_Kinetic_Energy);

      double Total_Potential_Energy{};
      Total_Potential_Energy = chain.pot_energy() * .000001;
      string_Potential_Energy.setString(
          "Total potential energy is " +
          to_string_with_precision(Total_Potential_Energy));
      window.draw(string_Potential_Energy);

      auto Total_energy = Total_Kinetic_Energy + Total_Potential_Energy;
      string_Total_Energy.setString("Total energy is " +
                                    to_string_with_precision(Total_energy));
      window.draw(string_Total_Energy);

      auto const state = evolve(chain, steps_per_evolution, delta_t, w);
      // calcola l'evoluzione della chain e restituisce la chain evoluta dopo
      // steps_per_evolution

      for (size_t i = 0; i != chain.size(); ++i) {
        chain[i].draw(window);
      }

      window.draw(x_axis, 2, sf::Lines);
      window.draw(y_axis, 2, sf::Lines);

      window.display();
    }
  }
}