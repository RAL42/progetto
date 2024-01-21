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

std::vector<float> dxdt;
float dxdt0{};

//---------------------------------------------------------------------------------------------
// funzioni dell'equazione differenziale per la componente x
// float h_x;
float g_x(float t, float x, float dxdt) {
  float h_x = dxdt;
  return h_x;
}

// float y_x;
float f_x(float t, float x, float dxdt, float w, float k, float m, float l, float cosTheta) {
  auto M = 1 / m;
  float y_x = w * w * x - k * (x - 2 * l * cosTheta) * M;
  return y_x;
}
//---------------------------------------------------------------------------------------------
// funzioni dell'equazione differenziale per la componente y
// float h_y;
float g_y(float t, float y, float dxdt) {
  float h_y = dxdt;
  return h_y;
}

// float y_y;
float f_y(float t, float y, float dxdt, float k, float m, float l, float cosTheta) {
  auto M = 1 / m;
  float y_y = -k * (y - 2 * l * cosTheta) * M;
  return y_y;
}
//---------------------------------------------------------------------------------------------

std::vector<PM> rk4_II(Chain ch, float dt, float t_max, float W, float k, float m, float l, float i) {  // i è il tempo, glielo do nel main nel ciclo while
  dxdt.push_back(dxdt0);
  float x_{};
  float y_{};
  std::vector<PM> temp_ch = ch.state();  

  for (int j = 0; j < ch.size(); j++){
  //std::cout << " \n ---------------- \n inizio j = " << j << " ; i = " << i << '\n';

// evoluzione delle x

    float x{};
    float y{};
    float cosTheta{};

    if (j == 0) {  // poichè un vector ha un inizio e una fine, non è una corda
      x = temp_ch[1].get_x() - temp_ch.back().get_x();
      y = temp_ch[1].get_y() - temp_ch.back().get_y();

      auto Dx{abs(temp_ch[1].get_x() - temp_ch[0].get_x())};  // Delta x del primo e secondo elemento della catena
      auto Dy{abs(temp_ch[1].get_y() - temp_ch[0].get_y())};  // Delta y
      cosTheta = Dx / sqrt(Dx * Dx + Dy * Dy);

      // std::cout<< " interm0 j = " << j << " ; i = " << i << '\n';

    } else if (j == ch.size() - 1) {x = (*(temp_ch.end() - 2)).get_x() - temp_ch[0].get_x();
      y = (*(temp_ch.end() - 2)).get_y() - temp_ch[0].get_y();
      // std::cout<< " interm0.01 j = " << j << " ; i = " << i << '\n';

      auto Dx{abs((*(temp_ch.end() - 1)).get_x() -(*(temp_ch.end() - 2)).get_x())};  // Delta x dell'ultimo e penultimo elemento della catena
      auto Dy{abs((temp_ch[1].get_y() - temp_ch[0].get_y()))};  // Delta y
      cosTheta = Dx / sqrt(Dx * Dx + Dy * Dy);

      // std::cout<< " interm0.1 j = " << j << " ; i = " << i << '\n';

    } else {
      x = temp_ch[j + 1].get_x() - temp_ch[j - 1].get_x();
      y = temp_ch[j + 1].get_y() - temp_ch[j - 1].get_y();

      auto Dx{abs(temp_ch[j].get_x() - temp_ch[j + 1].get_x())};
      auto Dy{abs(temp_ch[j].get_y() - temp_ch[j + 1].get_y())};
      cosTheta = Dx / sqrt(Dx * Dx + Dy * Dy);

      // std::cout<< " interm0.2 j = " << j << " ; i = " << i << '\n';
    };

    float k1_x = dt * g_x(i, x, dxdt[i]);
    float l1_x = dt * f_x(i, x, dxdt[i], W, k, m, l, cosTheta);

    float k2_x = dt * g_x(i + dt * .5, x + k1_x * .5, dxdt[i] + l1_x * .5);
    float l2_x = dt * f_x(i + dt * .5, x + k1_x * .5, dxdt[i] + l1_x * .5, W, k, m, l, cosTheta);

    float k3_x = dt * g_x(i + dt * .5, x + k2_x * .5, dxdt[i] + l2_x * .5);
    float l3_x = dt * f_x(i + dt * .5, x + k2_x * .5, dxdt[i] + l2_x * .5, W, k, m, l, cosTheta);

    float k4_x = dt * g_x(i + dt, x + k3_x, dxdt[i] + l3_x);
    float l4_x = dt * f_x(i + dt, x + k3_x, dxdt[i] + l3_x, W, k, m, l, cosTheta);

    x_ = x + (k1_x + 2 * k2_x + 2 * k3_x + k4_x) /6;  // ho calcolato la nuova posizione  
    //ch[j].update_x(x_);

// evoluzione delle y

    float k1_y = dt * g_y(i, y, dxdt[i]);
    float l1_y = dt * f_y(i, y, dxdt[i], k, m, l, cosTheta);

    float k2_y = dt * g_y(i + dt * .5, y + k1_y * .5, dxdt[i] + l1_y * .5);
    float l2_y = dt * f_y(i + dt * .5, y + k1_y * .5, dxdt[i] + l1_y * .5, k, m, l, cosTheta);

    float k3_y = dt * g_y(i + dt * .5, y + k2_y * .5, dxdt[i] + l2_y * .5);
    float l3_y = dt * f_y(i + dt * .5, y + k2_y * .5, dxdt[i] + l2_y * .5, k, m, l, cosTheta);

    float k4_y = dt * g_y(i + dt, y + k3_y, dxdt[i] + l3_y);
    float l4_y = dt * f_y(i + dt, y + k3_y, dxdt[i] + l3_y, k, m, l, cosTheta);

    y_ = y + (k1_y + 2 * k2_y + 2 * k3_y + k4_y) / 6;  // ho calcolato la nuova posizione

  PM temp_pm(x_, y_, m);
  ch[j] = temp_pm;
  //temp_ch[j]=temp_pm;
  
  std::cout << "x_ = " << x_ << "; y_ = " << y_ << '\n'; 
  //std::cout << "ch[j].x = " << ch[j].get_x() << "; ch[j].y = " << ch[j].get_y() << '\n'; 

    
  /*std::cout<< "size of temp ch = " << temp_ch.size() << '\n';
    std::cout << "temp_pm x = " << temp_pm.get_x() << "\n";
    std::cout << "temp_pm y = " << temp_pm.get_y() << "\n";
    std::cout << "temp_ch.x = " << ch[j].get_x() << "\n"; 
    std::cout << "temp_ch.y = " << ch[j].get_y() << "\n";
    std::cout << " fine j = " << j << " ; i = " << i << '\n';
    */
};
  return ch.state();
}