#ifndef PM_CPP
#define PM_CPP

#include "Spazio_vett.hpp"
#include <SFML/Window.hpp>
class PM {  // Punto Materiale
  vec pos_;
  vec vel_;
  float m_;  // massa

  sf::CircleShape s_;

 public:
  PM(float, float, float, float, float) {} //first constructor 

  PM(vec, vec, float){} //second constructor

  PM(vec const&) {} //copy constructor

  PM(); //default constructor
  
  void draw(sf::RenderWindow&){}

  float get_m() const { return m_; };

  void update_x(float const&) {};
  void update_y(float const&) {};

  vec get_pos() const {}
  vec get_vel() const {}
 
};


#endif