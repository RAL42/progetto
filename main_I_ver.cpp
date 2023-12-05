#include <SFML/Graphics.hpp>
#include <iostream>
#include<math.h>

#include"rk4_II_prima_verione.hpp" //suppongo sia questo, non ricordo

class point {
 private:
  sf::Vector2f pos;
  sf::CircleShape s;

 public:
  point(float T_, float X_) {
    pos.x = T_;
    pos.y = X_;

    s.setPosition(pos);
    s.setFillColor(sf::Color::White);
    s.setRadius(5);
  }

  void render(sf::RenderWindow& wind) {
    s.setPosition(pos);
    wind.draw(s);
  }

  auto get_x() {
    auto _x = pos.x;
    return _x;
  }

  auto get_y() {
    auto _y = pos.y;
    return _y;
  }
};

/*
non funziona un cazzo, se printo gli elementi di x sono sballati, cioè se ESEGUO due volte il programma ottengo numeri diversi. 
Sarà colpa dell'integratore?
Il fatto è che ESEGUO, non è che compilo, due volte, quindi non penso sia l'integratore (?). 
*/

int main() {
  unsigned const width = .7 * sf::VideoMode::getDesktopMode().width;
  unsigned const height = .7 * sf::VideoMode::getDesktopMode().height;
  sf::RenderWindow window(sf::VideoMode(width, height), "Display RK4_II");
  window.setPosition(sf::Vector2i(100, 100));
  // window.setFramerateLimit(60);

  rk4_II();

  bool first_time = true;
  auto scale_factor_width{width / t_max};
  //auto scale_factor_height{height / x[x.size()-1]};

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
    };

    window.clear();

    if (first_time) {
      float j{};
      while (j <= t_max) {
        point p(j * scale_factor_width, x[2 * j]);
        p.render(window);

        //std::cout << "(" << j * scale_factor_width << ", " << x[j] << ") \n";
        j += dt;
      };
      first_time = false;
    }

    //window.display();
  }

for (int i = 0; i < x.size(); i++){
  std::cout<< "x_" << i << " = " << x[i] << "\n";
}

  // std::cout << "t[t.size()] = " << scale_factor_width << " ; " << "x[x.size()] = " << width << "\n";
}