#pragma once
#include <iostream>
#include <vector>

/*
Function y=t*t*; //voglio creare un oggetto che mantiene le operazioni che
scrivo in y e poi tramite l'operatore() applico, ossia calcolo, la funzione al
punto x double y(x);
*/

// double t{};
// double y{}; //lo fa letteralmente questo, ogni volta che gli do un t in pasto
// questo calcola la funzione

const float dt{0.1};
const float t_max{20};
const auto n{t_max / dt};  // numero di punti(vertici)
// const int n1 = static_cast<int>(n); //(size del vettore "function") devo
// convertirlo in const int perche la dimensione del vettore è tale

std::vector<double> function{};
double i{};  // devo definirla fuori così nel main posso scrivere "double y=f(i)",
auto draw_function(double y) {
  while (i < t_max) {
    y = 2 * i * i;    //per ora devo inserire qui la funzione
    function.push_back(y);
    i += dt;
  }
  return function;
}

//void print_car(double* ptr_y) { std::cout << "posizione: " << *ptr_y << '\n'; }

template <typename T>
auto print_fun(std::vector<T> function) {
  for (int i = 0; i < function.size(); i++) {
    std::cout << "Elemento " << i << " = " << function[i] << '\n';
  }
}