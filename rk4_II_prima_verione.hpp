#pragma once
#include <vector>
#include<iostream>

const double t_max{10};  // per definire il dominio della funzione, o almeno fino a che punto voglio calcolare l'evoluzione
const double dt{0.1};  // intervallo, più è piccolo più è preciso (?) NOTA: se cambi dt devi cambiare il fattore di moltiplicazione nel ciclo for che disegna i 'point' nel main
auto n{t_max / dt};   // numero di step, da mettere nel ciclo for

std::vector<double> x;
std::vector<double> t;
std::vector<double> dxdt;
double x0{};
double t0{};
double dxdt0{};


double h;
double g(double t, double x, double dxdt){
    h = dxdt;
    return h;
}

double y;
double f(double t, double x, double dxdt){
    y = 2*x + t;
    return y;
}

void rk4_II() {  // RK4 per edo al secondo ordine del tipo d^2 x/dt^2 = f(t,x,dx/dt)
  x.push_back(x0);
  dxdt.push_back(dxdt0);
  t.push_back(t0);
  double x_{};
  
  for (int i = 0; i < n; i++) {
    //std::cout << "inizio" << i << '\n';
    double k1 = dt * g(t[i], x[i], dxdt[i]);
    double l1 = dt * f(t[i], x[i], dxdt[i]);

    double k2 = dt * g(t[i] + dt*.5, x[i] + k1*.5, dxdt[i] + l1*.5 );
    double l2 = dt * f(t[i] + dt*.5, x[i] + k1*.5, dxdt[i] + l1*.5 );

    double k3 = dt * g(t[i] + dt*.5, x[i] + k2*.5, dxdt[i] + l2*.5);
    double l3 = dt * f(t[i] + dt*.5, x[i] + k2*.5, dxdt[i] + l2*.5);

    double k4 = dt * g(t[i] + dt, x[i] + k3, dxdt[i] + l3);
    double l4 = dt * f(t[i] + dt, x[i] + k3, dxdt[i] + l3);
   
    double t_ = t[i] + dt;
    t.push_back(t_);
 
   x_ = x[i] + (k1 + 2 * k2 + 2 * k3 + k4)/6;
    x.push_back(x_);
  }

  double j{};
  while (j <= t_max) {
    std::cout << x[j] << "\n";
    j += dt;
  };
}

 /*int main (){
   rk4_II();
 }*/