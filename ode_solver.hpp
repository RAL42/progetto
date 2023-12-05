#pragma once
#include <math.h>
#include <iostream>
#include <vector>

// fourth order runge kutta method
// https://stackoverflow.com/questions/45724065/runge-kutta-method-on-c

//numerical recipes par(17.1), formula (17.1.3). Functor a slide 45, rk a slide 931

// voglio applicare rk4 a una funzione, ossia rk4(x, t, h, f(x,t)), e dentro c'è
// l'algoritmo che risolve l'ode e mi restituisce i due vector contenenti gli insiemi di punti per x(t) e t

//per vedere un esempio di FUNCTOR guarda "FUNCTOR_square" 

//esempio di funzione. ATTTENZIONE, NON è UNA FUNZIONE TIPO y=x^2, è LA FUNZIONE CHE STA A DESTRA DELL'EQUAZIONE DIFFERENEZIALE dx/dt = f(x,t) !!
float h;
float f(float x, float t) {  // define a function f, i'm gonna put in the li_phys.hpp and define one for each force, i hope
  h = x + t;
  return h;
}

double k1{};
double k2{};
double k3{};
double k4{};

std::vector<float> vec_x;  // sono gli insiemi di punti finali, quelli in cui memorizzo i risultati dati da rk4
std::vector<float> vec_t;
float x0{};  // initial value
float t0{};
// nel main chiedo di metterli in input ?? oppure vengo qui a metterli ogni
// volta (forse è meglio / piu normale)

const float t_max{10};     //per definire il dominio della funzione, o almeno fino a che punto voglio calcolare l'evoluzione 
const float dt{0.1};        //intervallo, più è piccolo più è preciso (?)
auto n {t_max / dt};     // numero di step, da mettere nel ciclo for


void rk4_I(float f(float x, float t)) {  //risolve ODE al PRIMO ORDINE del tipo dx/dt=f(x,t)
  float x;
  float t;
  vec_x.push_back(x0);
  vec_t.push_back(t0);

  for (int i = 1; i < n; i++) { //i=1 perche la posizione 0 è occupata dalla pos iniz
    x=vec_x[i];
    t=vec_t[i];
    
    k1 = dt * f(x, t);                       //formula (17.1.3) numerical recipes
    k2 = dt * f(t + 0.5 * dt, x + 0.5 * k1);
    k3 = dt * f(t + 0.5 * dt, x + 0.5 * k2);
    k4 = dt * f(t + dt, x + k3);

    vec_t[i+1]=vec_t[i]+dt;
    vec_x[i+1]=vec_x[i]+ 1/6 * (k1 + 2*k2 + 2*k3 + k4);

  }

}

  void print(){
    for (int i = 0; i < n; i++)
    {
      std::cout<<"t_"<< i << " = " << vec_t[i] << "    ";
      std::cout<<"x_"<< i << " = " << vec_x[i] << std::endl;
    };
    
  }
