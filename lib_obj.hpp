#pragma once

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include<cmath>
#include<SFML/Graphics.hpp>

const float pi = M_PI; //usa l'alias

class PM { // Punto Materiale
  sf::Vector2f pos;
  //sf::Vector2f vel;
  float m;  // massa

  sf::CircleShape s;

 public:
  PM(float p_x, float p_y,float m_): pos(p_x, p_y), m(m_) {  // constructor

    s.setRadius(2.5);
    s.setPosition(pos);
    s.setFillColor(sf::Color::White);
  }
  PM() = default;

  void draw(sf::RenderWindow& wind){
    s.setPosition(pos);
    wind.draw(s);
  }
  float get_x(){
    return pos.x;
  };
  float get_y(){
    return pos.y;
  }

/*void operator= (PM pm1) {
  pos.x = pm1.get_x();
  pos.y = pm1.get_y();
}*/

void update_x(float x_){
  pos.x = x_;
}
void update_y(float y_){
  pos.y = y_;
}

};

//-------------------------------------------------------------------------------------------------------------------

class Hooke {
  float k;
  float l;  // lunghezza a riposo, deve essere la stessa di quella nella classe chain, quindi la tolgo, è inutile

 public:
  Hooke(float k_, float l_): k(k_), l(l_) {
    if (k <= 0. || l < 0) {
      throw std::runtime_error{"La costante elastica deve essere > 0, oppure la lunghezza a riposo >= 0"};
    };
  };
  Hooke() = default;

  void update_k(float k_){k = k_;};
  void update_l(float l_){l = l_;};
  float get_k(){return k;};
  float get_l(){return l;};
  
  //float operator() (PM pm1_, PM pm2_) ;
};

//-------------------------------------------------------------------------------------------------------------------

class Chain {
  std::vector<PM> ch;  // catena inestensibile come insieme discreto di PM a distanza fissa;
  float m;
  int NoPM; //sta per Number of PM
  
 public:

  Chain(const int number_of_PM, const float mass): NoPM(number_of_PM), m(mass) {};
  Chain() = default;
  
  void initial_config(float l){ //costruisce la catena nella configurazione iniziale
      for (int i = 0; i < NoPM; i++) {  // con questo ciclo for genero la configurazione iniziale della catena, assegnando la posizioni iniziali utilizzando funzioni di i
      PM pm_temp(100 *cos(l*i) /l, 100*sin(l*i) / l, m);  // l'argomento di cos e sin sono in modo tale che i punti, inizialmente, vengano disposti su una circonferenza
      ch.push_back(pm_temp);

      std::cout<< "("<< pm_temp.get_x() << ", " << pm_temp.get_y() << ")" << '\n';
    };
    std::cout<<"size of chain initially = " << ch.size() << '\n'; 
  }

  std::vector<PM> state() {
    return ch;
  }



 void push_back(PM pm){ch.push_back(pm);};

 int size(){return ch.size();}

 PM operator[] ( int i){return ch[i];}

 void operator= (Chain evolved_ch){
  if (ch.size() <= evolved_ch.size()){
    for (int i = 0; i < ch.size(); i++){ //quelli che ci sono gia li aggiorna
      ch[i]=evolved_ch[i];
    };  
    for (int i = ch.size(); i < evolved_ch.size(); i++){//se il secondo vettore ha elementi in piu, semplicemente li pusha dentro
      ch.push_back(evolved_ch[i]);
    }; 

  }else{  //ossia se la chain a sinistra dell'uguale ha size maggiore di quella a destra dell'uguale

    for (int i = 0; i < ch.size(); i++){ //aggiorno solo i primi ch.size() membri della "chain a sinistra"
      ch[i]=evolved_ch[i];
    };
    
  }
}

 PM back(){return ch.back();}

 auto end(){return ch.end();}; //restituisce un iterator che punta all'(ultimo +1) elemento del vector [quindi *(vector.end() -1) da  l'ultimo elemento] quindi va dereferenziato

 void empty(){ch.empty();}

//void resize(int n){ch.resize(n);};
/*void evolve(){
  std::vector<Chain> evolution_of_chains = rk4_II(ch, 0.1, 10);
}*/
};

//float W; //velocità angolare