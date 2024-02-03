#ifndef VEC
#define VEC

#include <SFML/Graphics.hpp>
#include <cmath>

// spazio vettoriale su SFML

class vec {
  sf::Vector2f v_;

 public:
  vec(float x, float y) : v_{x, y} {};
  // parametrized constructor
  vec() = default;
  // default constructor

  sf::Vector2f state() const;
  // restituisce v_

  // overload degli operatori
  vec &operator+=(vec const &);
  vec &operator-=(vec const &);
  vec &operator*=(float const &);
  vec &operator/=(float const &);

  float get_x() const;
  // restituisce la componente x
  float get_y() const;
  // restituisce la componente y
  float norm() const;
  // calcola la norma del vettore
  void update_x(float const &);
  // aggiorna la componente x
  void update_y(float const &);
  // aggiorna la componente y
};

// overload degli operatori
std::ostream &operator<<(std::ostream &, vec const &);
vec operator+(vec const &, vec const &);
vec operator-(vec const &, vec const &);
vec operator*(vec const &, float const &);
vec operator*(float const &, vec const &);
vec operator/(vec const &, float const &);
bool operator==(vec const &, vec const &);

#endif