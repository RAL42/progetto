#pragma once
#include <iostream>
#include <vector>

/*
Function y=t*t*; //voglio creare un oggetto che mantiene le operazioni che scrivo in y e poi tramite l'operatore() applico, ossia calcolo, la funzione al punto x
double y(x);
*/

double t{};
double y{2 * t * t}; //lo fa letteralmente questo, ogni volta che gli do un t in pasto questo calcola la funzione 

const float dt{0.001};
const float t_max{20};
auto n{t_max / dt};  // numero di punti(vertici)

auto ddy(double function, double variable_of_derivation, double t_0) {
  std::vector<double> ddt_function{};
  while (double i=0 <= t_max) {
    ddt_function[i] ;
    i += dt;
  }
  return ddt_function;
};



int main() {}