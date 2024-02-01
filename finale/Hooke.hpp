#ifndef HOOKE_HPP
#define HOOKE_HPP

#include "Vec.hpp"

class Hooke {
  const float k_;
  const float l_;  // lunghezza a riposo scalare
  vec lv_;  // lunghezza a riposo vettoriale. non posso mettrla const perchè
            // dopo devo aggiornarla

 public:
  Hooke(const float k, const float l) : k_(k), l_(l) {
    if (k_ <= 0.) {
      throw std::runtime_error{"La costante elastica deve essere >0"};
    }
    if (l_ < 0.) {
      throw std::runtime_error{"La lunghezza a riposo deve essere >=0"};
    }
  };

  Hooke()
      : k_{}, l_{} {};  // default constructor. Had to explicitely initialize k_
                        // and l_ because they are const

  float get_k() const;
  vec get_lv() const;  // lv sta per "l vettoriale"
  float get_l() const;
  void update_lv(vec const &);
};

bool operator==(Hooke const &, Hooke const &);
// per i test

#endif