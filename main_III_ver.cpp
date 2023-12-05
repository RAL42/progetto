//#include <SFML/System/Time.hpp>
//#include <SFML/System/Clock.hpp>
#include <sstream>
#include "rk_III_v.hpp"

std::string to_string_with_precision(const float a_value, const int n = 2){// https://stackoverflow.com/questions/16605967/set-precision-of-stdto-string-when-converting-floating-point-values
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

int main() {
  int n_PM{20};
  float m{10};
  Chain corda{n_PM, m};

  Hooke spring(1, 2*pi/n_PM);  
  float W{100};  // velocità angolare
  
  //INIZIO DISPONENDO LA CORDA A FORMA DI CERCHIO
  corda.initial_config(spring.get_l());

  //sf::Time dt_ = sf::seconds(.1);
  //float dt{dt_.asSeconds()};
  float dt{0.01};
  float t_max{1};

  unsigned const display_width = .7 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = .7 * sf::VideoMode::getDesktopMode().height;
  sf::RenderWindow window(sf::VideoMode(display_width, display_height), "CHAIN EVOLUTION");
  window.setPosition(sf::Vector2i(100, 100));

  sf::Vector2f window_size(window.getSize());  // getsize prende width e height della window
  sf::View view{sf::Vector2f{0, 0}, window_size};  // view permette di cambiare l'origine, il primo vettore è l'origine, il secondo e la size della window
  window.setView(view);

  // sf::Vertex x_axis[] = {sf::Vertex(sf::Vector2f(-window_size.x, 0)),
  // sf::Vertex(sf::Vector2f(window_size.x, 0))}; sf::Vertex y_axis[] =
  // {sf::Vertex(sf::Vector2f(0, -window_size.y/2)), sf::Vertex(sf::Vector2f(0,
  // window_size.y/2))};

  float t {};
  bool start = false;

  while (window.isOpen()) {
    sf::Clock clock;
    sf::Time last_time{clock.getElapsedTime()};

    /*sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        start = true;
      };
    }*/


 sf::Font font;
    font.loadFromFile("./font/grasping.ttf");
    sf::Text stringa;
    stringa.setFont(font);
   // stringa.setString("caccamerda");
    stringa.setCharacterSize(40);
    stringa.setFillColor(sf::Color::White);
    stringa.setPosition(300, -300);



    sf::Event event;
    
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        /*case sf::Keyboard::Escape:
            window.close();
            break;

        case sf::Event::KeyPressed:
            start = true;*/
        }

      //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {start = true;};
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        n_PM += 1;
        std::cout<< "n_PM = " << n_PM << '\n';
        corda = Chain(n_PM, m);
        corda.initial_config(spring.get_l());
      };
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        n_PM -= 1;
        std::cout<< "n_PM = " << n_PM << '\n';
        //corda.resize(n_PM);
        corda = Chain(n_PM, m);
        //corda.initial_config(spring.get_l());
      };
    }

    // window.draw(x_axis, 2, sf::Lines);
    // window.draw(y_axis, 2, sf::Lines);
    if (start) {
        while (t <= t_max) {
        std::vector<PM> CH = rk4_II(corda, dt, t_max, W, spring.get_k(), m, spring.get_l(), t);  // creo la corda evoluta al tempo t
        std::cout << "------------ \n catena all'istante " << t << '\n';
        window.clear(sf::Color::Black);
        for (int i = 0; i < n_PM; i++) {  // disegno ogni punto della corda appena calcolata
          CH[i].draw(window);

          std::cout << "CH[i].x = " << CH[i].get_x() << "; CH[i].y = " << CH[i].get_y() << '\n'; 
        }

        stringa.setString(to_string_with_precision(t));
        window.draw(stringa);
        window.display();
        t += dt;
        };
      start = false;

      
/* sf::Time last_time1{};
if (clock.getElapsedTime() - last_time >= dt_ ){}{
  std::cout << "elapsed time = " << clock.getElapsedTime().asSeconds() << '\n';
    last_time = clock.getElapsedTime();
    }*/

      /*if (clock.getElapsedTime().asSeconds() - last_time.asSeconds() >= dt && clock.getElapsedTime().asSeconds() <= t_max) {
        std::cout << "yes " << dt << '\n';
        auto t{clock.getElapsedTime().asSeconds()};
        Chain CH = rk4_II(corda, dt, t_max, W, spring.get_k(), m, corda.l, t);  // creo la corda evoluta al tempo t
        std::cout << "------------ \n catena all'istante " << t << '\n';
        window.clear(sf::Color::Black);
        
        for (int i = 0; i < n_PM; i++) {  // disegno ogni punto della corda appena calcolata
          CH[i].draw(window);
          std::cout << "CH[i].x = " << CH[i].get_x()<< "; CH[i].y = " << CH[i].get_y() << '\n';
        }
        window.display();
        last_time = clock.getElapsedTime() ;
      }*/
    }
  }
}