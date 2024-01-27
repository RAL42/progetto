#ifndef PM_HPP
#define PM_HPP
#include "Spazio_vett.hpp"

class PM {  // Punto Materiale
  vec pos_;
  vec vel_;
  float m;  // massa

  sf::CircleShape s;

 public:
  PM(float p_x, float p_y, float v_x, float v_y, float m_)
      : pos_{p_x, p_y}, vel_{v_x, v_y}, m(m_) {  // constructor

    s.setRadius(5);
    s.setPosition(pos_.get_x(), pos_.get_y());
    s.setFillColor(sf::Color::White);
  }

  PM(vec x, vec y, float m_) : pos_(x), vel_(y), m(m_){
    s.setRadius(5);
    s.setPosition(pos_.get_x(), pos_.get_y());
    s.setFillColor(sf::Color::White);
  };
  PM() = default;
  
  bool operator==(PM const&);

  void draw(sf::RenderWindow&) ;

  float get_m() const ;

  void update_x(float const&) ;
  void update_y(float const&) ;

  vec get_pos() const ;
  vec get_vel() const ;
  
};

#endif