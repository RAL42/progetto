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
  PM(float p_x, float p_y, float v_x, float v_y, float m) : pos_{p_x, p_y}, vel_{v_x, v_y}, m_(m) {//first constructor 
    s_.setRadius(5);
    s_.setPosition(pos_.get_x(), pos_.get_y());
    s_.setFillColor(sf::Color::White);

  }; 

  PM(vec x, vec y, float m) : pos_(x), vel_(y), m_(m) { //second constructor
    s_.setRadius(5);
    s_.setPosition(pos_.get_x(), pos_.get_y());
    s_.setFillColor(sf::Color::White);
  };

  PM(PM const& other) : pos_{other.get_pos()}, vel_{other.get_vel()} {}; //copy constructor

  PM() = default; //default constructor

  bool operator==(PM const&);

  void draw(sf::RenderWindow&);

  float get_m() const;

  void update_x(float const&);
  void update_y(float const&);

  vec get_pos() const; 
  vec get_vel() const;

 
};


#endif