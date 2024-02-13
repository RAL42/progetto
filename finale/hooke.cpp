#include "hooke.hpp"

double Hooke::get_k() const { return k_; }

vec Hooke::get_lv() const { return lv_; }

double Hooke::get_l() const { return l_; }

void Hooke::update_lv(vec const& lv) { lv_ = lv; }

bool Hooke::operator==(Hooke const& k1) {
  return k_ == k1.get_k() && l_ == k1.get_l();
}