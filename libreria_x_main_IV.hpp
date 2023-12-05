#pragma once

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

const float pi = M_PI;  // usa l'alias
float w {}; //velocità angolare

//---------------------------------------------------------------

class PM {  // Punto Materiale
  sf::Vector2f pos;
  sf::Vector2f vel;
  float m;  // massa

   sf::CircleShape s;

 public:
  PM(float p_x, float p_y, float v_x, float v_y, float m_)
      : pos{p_x, p_y}, vel{v_x, v_y}, m(m_) {  // constructor

    s.setRadius(2.5);
    s.setPosition(pos);
    s.setFillColor(sf::Color::White);
  }

  float get_x() { return pos.x; };
  float get_y() { return pos.y; };
  float get_m() { return m; };

  sf::Vector2f operator-(PM pm1) {  // sottrazione tra due PM dà un sf::Vector2f
    return sf::Vector2f(pos.x - pm1.get_x(), pos.y - pm1.get_y());
  }

  float operator*(sf::Vector2f v) {  // prodotto scalare tra PM e sf::Vector
    return pos.x * v.x + pos.y * v.y;
  }
  float operator*(PM v) {  // prodotto scalare tra due PM
    return pos.x * v.get_x() + pos.y * v.get_y();
  }

  sf::Vector2f get_pos(){ return pos; }

  sf::Vector2f get_vel(){ return vel; }

  void update_pos(sf::Vector2f p){ pos = p; };
  void update_vel(sf::Vector2f v){ vel = v; };
  
};

//---------------------------------------------------------------

class Hooke {
  const float k;
  const float l;

 public:
  Hooke(const float k_, const float l_) : k(k_), l(l_){};

  float get_k() { return k; }
  float get_l() { return l; }
};

//---------------------------------------------------------------

sf::Vector2f operator* (float a, sf::Vector2f v) { //definizione del prodotto tra un float a un vector
    sf::Vector2f temp_v{a * v.x, a * v.y};
    return temp_v;
  }

sf::Vector2f operator+ (sf::Vector2f v1, sf::Vector2f v2) { //definizione della somma tra due vector
    sf::Vector2f temp_v{v1.x + v2.x, v1.y * v2.y};
    return temp_v;
  }

float d(PM pm1, PM pm2) {  // distanza tra due PM
  float dx{pm1.get_x() - pm2.get_x()};
  float dy{pm1.get_y() - pm2.get_y()};
  return sqrt(dx * dx + dy * dy);}

sf::Vector2f x(PM pm1, PM pm2) {return pm2 - pm1;}// vettore che esce da pm1 e punta pm2: pm1=pm_j; pm2=pm_j+1 oppure pm_j-1

std::ostream& operator<<(std::ostream& output, PM pm){
    output << "\nPM:  x = (" << pm.get_pos().x << ", " << pm.get_pos().y << ") " << "\n     v = (" << pm.get_vel().x << ", " << pm.get_vel().y << ") " << '\n' ;
    return output;
  }

//---------------------------------------------------------------

//aggiorna la "fisica" di pm_j
PM update_physics(PM pmj, PM pmP1, PM pmM1, Hooke molla, float dt) { //PM1=PMj e pmP1=PMj+1 pmM1=PMj-1
  PM temp_pm = pmj;
  float M{1 / temp_pm.get_m()};
  float inverse_d1 { 1 / d(temp_pm, pmP1) };
  float inverse_d2 { 1 / d(temp_pm, pmM1) };

  const sf::Vector2f F1 = molla.get_k() * (d(temp_pm, pmP1) - molla.get_l()) * (pmP1 - temp_pm) * inverse_d1; //F dovuta alla massa successiva
  const sf::Vector2f F2 = molla.get_k() * (d(temp_pm, pmM1) - molla.get_l()) * (pmM1 - temp_pm) * inverse_d2; //F dovuta alla massa precedente
  const sf::Vector2f F3 = w * w * sf::Vector2f(pmj.get_x(), 0) ;  //moltiplicando per il vector dovrei dividere per il modulo, che però sarebbe comparso a numeratore per via della formula analtica 
                                                            //Senza massa così evito di moltiplicare e dividere, nella formula di a la metto fuori dalla parentesi
  const sf::Vector2f a = M * (F1 + F2 ) + F3 ;
  
  temp_pm.update_vel( (a * dt) + temp_pm.get_vel() );
  sf::Vector2f v = temp_pm.get_vel();

  temp_pm.update_pos( (v * dt) + temp_pm.get_pos() );
  sf::Vector2f x = temp_pm.get_pos();
  //std::cout<< "temp_pm " <<temp_pm;
  //std::cout<<"     a = (" << a.x << ", " << a.y << ") " << '\n';
  
  return temp_pm;
}


