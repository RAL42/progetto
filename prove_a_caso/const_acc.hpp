#pragma once
#include <iostream>

const float dt{0.001};
const float g{9.81};
const float t_max{20};  // intervallo sulle ascisse, integro fino a t=2

struct particle {
  float x_;
  float vel_;

  void evolve() {
    vel_ += g * dt;
    x_ += vel_ * dt + 0.5 * g * dt * dt;
    
  }
  void print() {
    std::cout << "Posizione = " << x_ << " velocità = " << vel_ << '\n';
  }
};