#ifndef SPAZIO_VETT
#define SPAZIO_VETT

#include <SFML/Graphics.hpp>
#include <cmath>

//spazio vettoriale su SFML

class vec{
sf::Vector2f v;

public:
    vec(float x, float y): v{x, y} {}; //parametrized constructor
    vec() = default; //default constructor

    sf::Vector2f state() const;
    float get_x() const;
    float get_y() const;
    float norm() const;
  
 // template <typename T>
 // void update_pos(T p){ pos = p; };

  vec& operator+=(vec const&);
  vec& operator-=(vec const&);
  vec& operator*=(float const&);
  vec& operator/=(float const&);

  void update_x(float const&);
  void update_y(float const&);
};

std::ostream& operator<<(std::ostream&, vec const&);
vec operator+(vec const&, vec const&);
vec operator-(vec const&, vec const&);
vec operator*(vec const&, float const&);
vec operator*(float const& , vec const&);
vec operator/(vec const&, float const&);
bool operator==(vec const&, vec const&);

#endif 