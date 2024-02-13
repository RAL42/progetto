#ifndef VEC
#define VEC

#include <SFML/Graphics.hpp>
#include <cmath>
// spazio vettoriale su SFML

class vec {
  sf::Vector2<double> v_;

 public:
  vec(double x, double y) : v_{x, y} {};
  // parametrized constructor
  vec() = default;
  // default constructor

  sf::Vector2<double> state() const;
  // restituisce v_

  // overload degli operatori
  vec &operator+=(vec const &);
  vec &operator-=(vec const &);
  vec &operator*=(double const);
  vec &operator/=(double const);

  double get_x() const;
  // restituisce la componente x
  double get_y() const;
  // restituisce la componente y
  double norm() const;
  // calcola la norma del vettore
  void update_x(double const);
  // aggiorna la componente x
  void update_y(double const);
  // aggiorna la componente y
};

// overload degli operatori
std::ostream &operator<<(std::ostream &, vec const &);
vec operator+(vec const &, vec const &);
vec operator-(vec const &, vec const &);
vec operator*(vec const &, double const);
vec operator*(double const, vec const &);
vec operator/(vec const &, double const);
bool operator==(vec const &, vec const &);

#endif