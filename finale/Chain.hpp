#ifndef CHAIN_HPP
#define CHAIN_HPP

#include <iostream>

#include "Hooke.hpp"
#include "Pm.hpp"

//--------------------- FREE FUNCTION ---------------------

const float pi = M_PI;
// uso un alias
extern float w;
// velocita angolare
extern std::vector<float> Kinetic_energies;
//vettore composto dalle energie cinetiche di tutti i punti materiali
extern std::vector<float> Potential_energies;
//vettore composto dalle energie potenziali di tutti i punti materiali

float d(PM, PM);
// distanza tra due PM

vec x(PM, PM);
// vettore che esce da pm1 e indica pm2: pm1=pm_j; pm2=pm_j+1 oppure pm_j-1

vec apply_hooke(PM const &, PM const &, Hooke &);
// calcola la forza elastica

vec apply_CF(PM const &, float const &);
// calcola la forza centrifuga

vec apply_gravity(PM const &);

//--------------------- CHAIN CLASS ---------------------

class Chain {
  Hooke hooke_;
  std::vector<PM> ch_;

  PM solve(PM, vec, double const &) const;
  // risolve le equazioni del moto e aggiorna la posizione e velocità del punto
  // materiale

 public:
  Chain(Hooke const &hooke) : hooke_(hooke){};
  // parametrized constructor
  Chain() = default;

  std::size_t size() const;
  // restituisce il numero di elementi della catena

  void push_back(PM const &);

  std::vector<PM> const &state() const;
  // restituisce il vettore contenente gli elementi della catena

  PM operator[](int);
  // per selezionare l'elemento i-esimo della chain

  void initial_config(float const &, float const &, float const &, int const &);
  // costruisce la catena nella configurazione iniziale (circonferenza)

  void evolve(double const &);
  // calcola le varie forze per ogni punto della catena e aggiorna le posizione
  // chiamando la funzione evolve
};

#endif