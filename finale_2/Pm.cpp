#include "Pm.hpp"

bool PM::operator==(PM const& pm1){
    return pos == pm1.get_pos();
}

void PM::draw(sf::RenderWindow& wind){
    s.setPosition(sf::Vector2f(pos.get_x(), pos.get_y())); //poichè pos è un vec e c'è bisogno di un vector2f
    wind.draw(s);
}

float PM::get_m() const { return m; };

void PM::update_x(float const& z) {pos.update_x(z);};
void PM::update_y(float const& z) {pos.update_y(z);};

vec PM::get_pos() const { return pos; }
vec PM::get_vel() const { return vel; }

PM& PM::operator= (PM other_pm){
    pos = other_pm.get_pos();
    vel = other_pm.get_vel();
    return *this;
    }