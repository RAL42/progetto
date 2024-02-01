#ifndef CHAIN_HPP
#define CHAIN_HPP

#include <iostream>

#include "Hooke.hpp"
#include "Pm.hpp"

//--------------------- FREE FUNCTION ---------------------

const float pi = M_PI;  // use an alias
extern float w;

float d(PM, PM);
// distance between two PM

vec x(PM, PM);
// vector coming out of pm1 pointing pm2: pm1=pm_j; pm2=pm_j+1 oppure pm_j-1

vec apply_hooke(PM const &, PM const &, Hooke &);
// calculates the elastic force (it's a vec)

vec apply_CF(PM const &, float const &);
// deve essere un vec perche dopo devo sommarlo per fare la F totale, in solve
// ossia ritorna un vec con componente solo lungo x, controlla se è giusto, ma
// dovrebbe esserlo

vec apply_gravity(PM const &);

//--------------------- CHAIN CLASS ---------------------

class Chain {
  Hooke hooke_;
  std::vector<PM> ch_;

  PM solve(PM, vec, double const &) const;

 public:
  Chain(Hooke const &hooke) : hooke_(hooke){};
  Chain() = default;

  bool empty();

  std::size_t size() const;

  void push_back(PM const &);

  std::vector<PM> const &state() const;

  PM operator[](int);

  void initial_config(
      float const &, float const &, float const &,
      int const &);  // costruisce la catena nella configurazione iniziale

  void evolve(double const &);
};

#endif