#ifndef HOOKE_HPP
#define HOOKE_HPP

#include "vec.hpp"

class Hooke {
  const float k_;
  // costante elastica
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
  // default constructor

  float get_k() const;
  // restituisce la costante elastica
  vec get_lv() const;
  // restituisce la lunghezza a riposo vettoriale
  float get_l() const;
  // restituisce la lunghezza a riposo
  void update_lv(vec const &);
  // aggiorna la lunghezza a riposo vettoriale
};

bool operator==(Hooke const &, Hooke const &);
// true se k_ e l_ sono uguali

#endif