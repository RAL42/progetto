#ifndef CHAIN_HPP
#define CHAIN_HPP

#include <iostream>

#include "hooke.hpp"
#include "pm.hpp"
//--------------------- FREE FUNCTION ---------------------

double d(PM const &, PM const &);
// distanza tra due PM

vec x(PM const &, PM const &);
// vettore che collega i due PM

vec apply_hooke(PM const &, PM const &, Hooke &);
// calcola la forza elastica

vec apply_CF(PM const &, double const &);
// calcola la forza centrifuga

//--------------------- CHAIN CLASS ---------------------

class Chain {
  Hooke hooke_;
  // molla che collega gli elementi della chain
  std::vector<PM> ch_;
  // vettore contenente i punti materiali

  PM solve(PM, vec, double const) const;
  // risolve le equazioni del moto e aggiorna la posizione e velocità del punto
  // materiale

 public:
  Chain(Hooke const &, double const, double const, int const);
  // parametrized constructor

  double kin_energy() const;
  // restituisce l'energia cinetica totale della corda
  double pot_energy() const;
  // restituisce l'energia potenziale totale della corda

  size_t size() const;
  // restituisce il numero di elementi della chain

  void push_back(PM const &);
  // richiama la funzione push_back dei std::vector

  std::vector<PM> const &state() const;
  // restituisce il vettore contenente gli elementi della chain

  PM operator[](int);
  // per selezionare l'elemento i-esimo della chain

  void evolve(double const, double const);
  // calcola le varie forze per ogni punto della chain e aggiorna le posizione
  // chiamando la funzione evolve
};

#endif