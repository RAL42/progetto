#include"Spazio_vett.hpp"

float vec::get_x() const {return v.x;};
float vec::get_y() const {return v.y;};
sf::Vector2f vec::state() const {return v;};

float vec::norm() const { return sqrt(v.x * v.x + v.y * v.y); }
/*
vec& vec::operator+=(vec const& other) {
  v.x += other.v.x;
  v.y += other.v.y;
  return *this;
}
*/  
vec& vec::operator-=(vec const& other) {
  v.x -= other.v.x;
  v.y -= other.v.y;
  return *this;
}

vec& vec::operator*=(float const& scalar) {
  v.x *= scalar;
  v.y *= scalar;
  return *this;
}

vec& vec::operator/=(float const& scalar) {
  if (scalar == 0.) {
    throw std::runtime_error{"Cannot divide by zero."};
  }
  v.x /= scalar;
  v.y /= scalar;
  return *this;
}

vec& vec::operator=(vec const& other) {
  v.x = other.v.x;
  v.y = other.v.y; 
  return *this;
}

void vec::update_x(float const& z) {
  v.x= z;
}

void vec::update_y(float const& z) {
  v.y= z;
}

std::ostream& operator<<(std::ostream& os, vec const& v) {
  os << '(' << v.get_x() << ',' << v.get_y() << ')';
  return os;
}

vec operator+(vec const& a, vec const& b) {
  return vec{a.get_x() + b.get_x(), a.get_y() + b.get_y()};
}

vec operator-(vec const& a, vec const& b) {
  return vec{a.get_x() - b.get_x(), a.get_y() - b.get_y()};
}

vec operator*(vec const& a, float const& b) {
  return vec{b * a.get_x(), b * a.get_y()};
}

vec operator*(float const& b, vec const& a) {
  return vec{b * a.get_x(), b * a.get_y()};
}

vec operator/(vec const& a, float const& b) {
  if (b == 0.) {
    throw std::runtime_error{"Cannot divide by zero."};
  }
  return vec{a.get_x() / b, a.get_y() / b};
}

bool operator==(vec const& a, vec const& b) {
  return a.get_x() == b.get_x() && a.get_y() == b.get_y();
}

