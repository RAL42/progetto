#ifndef CHAIN_HPP
#define CHAIN_HPP

#include <iostream>

#include "hooke.hpp"
#include "pm.hpp"

//--------------------- FREE FUNCTION ---------------------

const float pi = M_PI;
// uso un alias
extern float w;
// velocita angolare
extern std::vector<float> Kinetic_energies;
// vettore composto dalle energie cinetiche di tutti i punti materiali
extern std::vector<float> Potential_energies;
// vettore composto dalle energie potenziali di tutti i punti materiali

float d(PM, PM);
// distanza tra due PM

vec x(PM, PM);
// vettore che collega i due PM

vec apply_hooke(PM const &, PM const &, Hooke &);
// calcola la forza elastica

vec apply_CF(PM const &, float const &);
// calcola la forza centrifuga

//--------------------- CHAIN CLASS ---------------------

class Chain {
  Hooke hooke_;
  // molla che collega gli elementi della chain
  std::vector<PM> ch_;
  // vettore contenente i punti materiali

  PM solve(PM, vec, double const &) const;
  // risolve le equazioni del moto e aggiorna la posizione e velocità del punto
  // materiale

 public:
  Chain(Hooke const &hooke) : hooke_(hooke){};
  // parametrized constructor
  Chain() = default;
  // default constructor

  std::size_t size() const;
  // restituisce il numero di elementi della chain

  void push_back(PM const &);
  // richiama la funzione push_back dei std::vector

  std::vector<PM> const &state() const;
  // restituisce il vettore contenente gli elementi della chain

  PM operator[](int);
  // per selezionare l'elemento i-esimo della chain

  void initial_config(float const &, float const &, float const &, int const &);
  // costruisce la chain nella configurazione iniziale (circonferenza)

  void evolve(double const &);
  // calcola le varie forze per ogni punto della chain e aggiorna le posizione
  // chiamando la funzione evolve
};

#endif