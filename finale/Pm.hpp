#ifndef PM_HPP
#define PM_HPP
#include "Vec.hpp"

class PM {  // Punto Materiale
  vec pos_;
  vec vel_;
  float m_;

  sf::CircleShape s;

 public:
  PM(float p_x, float p_y, float v_x, float v_y, float m)
      : pos_{p_x, p_y}, vel_{v_x, v_y}, m_(m) {
    s.setRadius(3);
    s.setPosition(pos_.get_x(), pos_.get_y());
    s.setFillColor(sf::Color::White);
  }  // parametrized constructor

  PM(vec x, vec y, float m) : pos_(x), vel_(y), m_(m) {
    s.setRadius(3);
    s.setPosition(pos_.get_x(), pos_.get_y());
    s.setFillColor(sf::Color::White);
  }  // parametrized constructor

  PM() = default;

  bool operator==(PM const &);

  void draw(sf::RenderWindow &);
  // per disegnare il punto materiale

  float get_m() const;

  void update_x(float const &);
  void update_y(float const &);

  vec get_pos() const;
  vec get_vel() const;
};

#endif