#include "PM.hpp"

PM::PM(float p_x, float p_y, float v_x, float v_y, float m) : pos_{p_x, p_y}, vel_{v_x, v_y}, m_(m)
{ // first constructor
  s_.setRadius(5);
  s_.setPosition(pos_.get_x(), pos_.get_y());
  s_.setFillColor(sf::Color::White);
};

PM::PM(vec x, vec y, float m) : pos_(x), vel_(y), m_(m)
{ //second constructor
  s_.setRadius(5);
  s_.setPosition(pos_.get_x(), pos_.get_y());
  s_.setFillColor(sf::Color::White);
};

PM::PM(PM const& other) : pos_{other.get_pos()}, vel_{other.get_vel()} {}; //copy constructor

PM::PM() = default; //default constructor

void PM::draw(sf::RenderWindow& wind){
    s_.setPosition(sf::Vector2f(pos_.get_x(), pos_.get_y())); //poichè pos è un vec e c'è bisogno di un vector2f
    wind.draw(s_);
  }

void PM::update_x(float const& z) {pos_.update_x(z);};
void PM::update_y(float const& z) {pos_.update_y(z);};

vec PM::get_pos() const { return pos_; }
vec PM::get_vel() const { return vel_; }
