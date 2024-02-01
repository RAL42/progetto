#include "Hooke.hpp"

float Hooke::get_k() const { return k_; };

vec Hooke::get_lv() const { return lv_; };

float Hooke::get_l() const { return l_; };

void Hooke::update_lv(vec const& lv) { lv_ = lv; };

bool operator==(Hooke const& k1, Hooke const& k2) {
  return k1.get_k() == k2.get_k() && k1.get_l() == k2.get_l();
}