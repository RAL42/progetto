#include "Pm.hpp"

bool PM::operator==(PM const &pm1) { return pos_ == pm1.get_pos(); }

void PM::draw(sf::RenderWindow &wind) {
  s.setPosition(sf::Vector2f(pos_.get_x(), pos_.get_y()));
  wind.draw(s);
}

float PM::get_m() const { return m_; };

void PM::update_x(float const &z) { pos_.update_x(z); };
void PM::update_y(float const &z) { pos_.update_y(z); };

vec PM::get_pos() const { return pos_; }
vec PM::get_vel() const { return vel_; }
