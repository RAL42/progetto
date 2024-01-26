#ifndef PM_HPP
#define PM_HPP
#include "Spazio_vett.hpp"

class PM {  // Punto Materiale
  vec pos;
  vec vel;
  float m;  // massa

  sf::CircleShape s;

 public:
  PM(float p_x, float p_y, float v_x, float v_y, float m_)
      : pos{p_x, p_y}, vel{v_x, v_y}, m(m_) {  // constructor

    s.setRadius(5);
    s.setPosition(pos.get_x(), pos.get_y());
    s.setFillColor(sf::Color::White);
  }

  PM(vec x, vec y, float m_) : pos(x), vel(y), m(m_){
    s.setRadius(5);
    s.setPosition(pos.get_x(), pos.get_y());
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
  PM& operator= (PM ) ;
};

#endif