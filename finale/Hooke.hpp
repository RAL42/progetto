#ifndef HOOKE_HPP
#define HOOKE_HPP

#include "Vec.hpp"

class Hooke {
  const float k_;
  const float l_;
  // lunghezza a riposo scalare
  vec lv_;
  // lunghezza a riposo "vettoriale" per i calcoli della forza elastica

 public:
  Hooke(const float k, const float l) : k_(k), l_(l) {
    if (k_ <= 0.) {
      throw std::runtime_error{"La costante elastica deve essere >0"};
    }
    if (l_ < 0.) {
      throw std::runtime_error{"La lunghezza a riposo deve essere >=0"};
    }
  }  // parametrized constructor

  Hooke() : k_{}, l_{} {};
  // default constructor. Ho dovuto inizializzare esplicitamente k_ e l_ perché
  // sono const

  float get_k() const;
  vec get_lv() const;  
  float get_l() const;
  void update_lv(vec const &);
};

bool operator==(Hooke const &, Hooke const &);
// per i test

#endif