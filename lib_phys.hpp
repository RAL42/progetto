#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<vector>

const double g = 9.81;  // accelerazione gravitazionale da applicare a ogni PM

template <typename T> //perche chain è un vector di tipo PM, che pero non ho definito qui.
void apply_gravity(g, std::vector<T> chain){
  for (int i = 0; i < chain.size(); i++){
   //applico RK4 a ogni PM i-esima (ossia chain[i])

  }
  
}


void apply_CF(double w, float R,std::vector<T> chain){ //funzione che applica a ogni [qualcosa] (n: numero di [qualcosa]) la forza centrifuga
    for (int i = 0; i < chain.size(); i++){
     //applico RK4 a ogni PM i-esima (ossia chain[i])
    }
    
};
