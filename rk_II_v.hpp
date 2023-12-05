#pragma once
#include <iostream>
#include <vector>

#include "lib_obj.hpp"  //per la catena
/* ormai inutili, li tengo per i commenti
const float t_max{10};  // per definire il dominio della funzione, o almeno fino
a che punto voglio calcolare l'evoluzione const float dt{0.1};  // intervallo,
più è piccolo più è preciso (?) NOTA: se cambi dt devi cambiare il fattore di
moltiplicazione nel ciclo for che disegna i 'point' nel main auto n{t_max / dt};
// numero di step, da mettere nel ciclo for
*/

//std::vector<float> x;
std::vector<float> t;
std::vector<float> dxdt;
float x0{};
float t0{};
float dxdt0{};

//---------------------------------------------------------------------------------------------
// funzioni dell'equazione differenziale per la componente x
//float h_x;
float g_x(float t, float x, float dxdt) {
  float h_x = dxdt;
  return h_x;
}

//float y_x;
float f_x(float t, float x, float dxdt, float w, float k, float m, float l, float cosTheta) {
  auto M = 1 / m;
  float y_x = w * w * x - k * (x -2*l*cosTheta) * M;
  return y_x;
}
//---------------------------------------------------------------------------------------------
// funzioni dell'equazione differenziale per la componente y
//float h_y;
float g_y(float t, float y, float dxdt) {
  float h_y = dxdt;
  return h_y;
}

//float y_y;
float f_y(float t, float y, float dxdt, float k, float m, float l, float cosTheta) {
  auto M = 1 / m;
  float y_y = -k * (y - 2 * l  * cosTheta)* M;
  return y_y;
}
//---------------------------------------------------------------------------------------------

Chain evolved_ch{0,0};
std::vector<Chain> rk4_II(Chain ch, float dt, float t_max, float W, float k, float m, float l) {  // gli do il dt e il t_max e poi dentro definisco il numero di intervalli
  evolved_ch=ch;  
  //x.push_back(x0);
  dxdt.push_back(dxdt0);
  t.push_back(t0);
  float x_{};
  float y_{};

  std::vector<Chain> evolution_of_chains;  // salvo tutti l'evoluzione della catena per ogni dt, la metto qui perche poi devo farne il return
//std::cout<<"size of ch = " <<ch.size() << '\n';  
  float i{t0};            // istante di tempo
  while (i <= t_max) {  // per ogni dt faccio evolvere ogni punto della catena
    for (int j = 0; j < ch.size(); j++) {
      std::cout<<" \n ---------------- \n inizio j = " << j << " ; i = " << i << '\n'; 

// evoluzione delle x
      
      float x{};
      float y{};
      float cosTheta{};

      if (j == 0) {  // poichè un vector ha un inizio e una fine, non è una corda
        x = ch[1].get_x() - ch.back().get_x();
        y = ch[1].get_y() - ch.back().get_y();
       
        float Dx{ch[1].get_x() - ch[0].get_x()}; //Delta x del primo e secondo elemento della catena 
        float Dy{ch[1].get_y() - ch[0].get_y()}; //Delta y
        cosTheta = Dx / sqrt(Dx*Dx+Dy*Dy);

      //std::cout<< " interm0 j = " << j << " ; i = " << i << '\n'; 

      } else if (j == ch.size() - 1) {
        x = (*(ch.end() - 2)).get_x() - ch[0].get_x();
        y = (*(ch.end() - 2)).get_y() - ch[0].get_y();
       //std::cout<< " interm0.01 j = " << j << " ; i = " << i << '\n'; 

        float Dx{(*(ch.end()-1)).get_x() - (*(ch.end()-2)).get_x()};  //Delta x dell'ultimo e penultimo elemento della catena
        float Dy{(ch[1].get_y() - ch[0].get_y())}; //Delta y 
        cosTheta = abs(Dx) / sqrt(Dx*Dx+Dy*Dy);
        
      //std::cout<< " interm0.1 j = " << j << " ; i = " << i << '\n'; 

      }  else{
       x = ch[j + 1].get_x() - ch[j - 1].get_x();
       y = ch[j + 1].get_y() - ch[j - 1].get_y();

        auto Dx{abs( ch[j].get_x() - ch[j+1].get_x())};
        auto Dy{abs( ch[j].get_y() - ch[j+1].get_y())};
        cosTheta = Dx / sqrt(Dx*Dx+Dy*Dy);
        
      //std::cout<< " interm0.2 j = " << j << " ; i = " << i << '\n'; 

      };

      //std::cout<< " interm1 j = " << j << " ; i = " << i << '\n'; 

      float k1_x = dt * g_x(t[i], x, dxdt[i]);
      float l1_x = dt * f_x(t[i], x, dxdt[i], W, k, m, l, cosTheta);

      float k2_x = dt * g_x(t[i] + dt * .5, x + k1_x * .5, dxdt[i] + l1_x * .5);
      float l2_x = dt * f_x(t[i] + dt * .5, x + k1_x * .5, dxdt[i] + l1_x * .5, W, k, m, l, cosTheta);

      float k3_x = dt * g_x(t[i] + dt * .5, x + k2_x * .5, dxdt[i] + l2_x * .5);
      float l3_x = dt * f_x(t[i] + dt * .5, x + k2_x * .5, dxdt[i] + l2_x * .5, W, k, m, l, cosTheta);

      float k4_x = dt * g_x(t[i] + dt, x + k3_x, dxdt[i] + l3_x);
      float l4_x = dt * f_x(t[i] + dt, x + k3_x, dxdt[i] + l3_x, W, k, m, l, cosTheta);

      x_ = x + (k1_x + 2 * k2_x + 2 * k3_x + k4_x) / 6;  // ho calcolato la nuova posizione
      evolved_ch[j].update_x(x_);

    // std::cout<< "x_ = " << x_ <<"\n";
    //  std::cout<< "fine x \n";

// evoluzione delle y

      float k1_y = dt * g_y(t[i], y, dxdt[i]);
      float l1_y = dt * f_y(t[i], y, dxdt[i], k, m, l, cosTheta);

   // std::cout<< "interm y \n";

      float k2_y = dt * g_y(t[i] + dt * .5, y + k1_y * .5, dxdt[i] + l1_y * .5);
      float l2_y = dt * f_y(t[i] + dt * .5, y + k1_y * .5, dxdt[i] + l1_y * .5, k, m, l, cosTheta);

   // std::cout<< "interm1 y \n";

      float k3_y = dt * g_y(t[i] + dt * .5, y + k2_y * .5, dxdt[i] + l2_y * .5);
      float l3_y =dt * f_y(t[i] + dt * .5, y + k2_y * .5, dxdt[i] + l2_y * .5, k, m, l, cosTheta);

   // std::cout<< "interm2 y \n";

      float k4_y = dt * g_y(t[i] + dt, y + k3_y, dxdt[i] + l3_y);
      float l4_y = dt * f_y(t[i] + dt, y + k3_y, dxdt[i] + l3_y, k, m, l, cosTheta);

   // std::cout<< "interm3 y \n";

      y_ = y + (k1_y + 2 * k2_y + 2 * k3_y + k4_y) / 6;  // ho calcolato la nuova posizione

    std::cout<< "j = "<< j <<"\n";
    std::cout<< "i = "<< i <<"\n";
    std::cout<< "x_ = "<< x_ <<"\n";
    std::cout<< "y_ = "<< y_ <<"\n";
      
      evolved_ch[j].update_y(y_);

     // std::cout<< "t[i] = " << t[i] << " oppure i= " << i << "\n";
     // std::cout<< "size of t "<< t.size() << "\n \n";
   
     std::cout<< "X evol_ch = " << evolved_ch[j].get_x() <<"; Y evol_ch = "<< evolved_ch[j].get_y() <<"\n" ;
     //std::cout<< "size del evolved chain " << evolved_ch.size() <<"\n";
     //std::cout<< "fine y \n";
    std::cout<<" fine j = " << j << " ; i = " << i << '\n'; 

    };

    //std::cout<< "fine \n";

    ch = evolved_ch;  // alla fine del ciclo for (che aggiorna le x e le y della catena a un certo istante) aggiorno la catena per poter rifare il processo con la catena allo stato evoluto
    evolution_of_chains.push_back(ch);
    
  i += dt;
  t.push_back(i);
  };
  return evolution_of_chains;
}