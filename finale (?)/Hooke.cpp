#include "Hooke.hpp"

float Hooke::get_k() const {return k_;};

vec Hooke::get_lv() const {return lv_;};

float Hooke::get_l() const {return l_;};

void Hooke::update_lv(vec const& lv) {lv_ = lv;};

