#ifndef HOOKE_CPP
#define HOOKE_CPP

#include "Spazio_vett.hpp"

class Hooke {
  const float k_;
  const float l_;//lunghezza a riposo scalare
  vec lv_; //lunghezza a riposo vettoriale. non posso mettrla const perchè dopo devo aggiornarla

 public:
  Hooke(const float k, const float l) : k_(k), l_(l) {};
  Hooke() = default;

  float get_k() const { return k_; }
  vec get_lv() const { return lv_; } //lv stsa per "l vettoriale"
  float get_l() const {return l_;}
  void update_lv(vec const& lv) {lv_ = lv;}

};

#endif