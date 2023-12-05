#include"SFML/Graphics.hpp"
#include<iostream>
#include<cmath>

class PM { // Punto Materiale
  sf::Vector2f pos;
  float m;  // massa

 
 public:
  PM(float p_x, float p_y,float m_) {  // constructor
    pos.x = p_x;
    pos.y = p_y;
    m = m_;
  }
  float get_x(){
    return pos.x;
  };
  float get_y(){
    return pos.y;
  }

void operator= (PM pm1) {
  pos.x = pm1.get_x();
  pos.y = pm1.get_y();
}

void update_x(float x_){
  pos.x = x_;
}
void update_y(float y_){
  pos.y = y_;
}

};


class Chain {
  std::vector<PM> ch;  // catena inestensibile come insieme discreto di PM a distanza fissa;
 
 public:
 const float pi=3.1415926;//53589793
 
 float l{}; //IMPORTANTE!!  è LA lunghezza a riposo, la uso nel main quando la do in pasto al rk4_II()

  Chain(const int number_of_PM, const float mass) { //costruisce la catena nella configurazione iniziale
    l=2*pi/number_of_PM; //lunghezza dell'arco tra un PM e il successivo, OSSIA LA LUNGHEZA A RIPOSO
      for (int i = 0; i < number_of_PM; i++) {  // con questo ciclo for genero la configurazione iniziale della catena, assegnando la posizioni iniziali utilizzando funzioni di i
      PM pm_temp(200*cos(l*i), 200*sin(l*i), mass);  // l'argomento di cos e sin sono in modo tale che i punti, inizialmente, vengano disposti su una circonferenza
      ch.push_back(pm_temp);

      //std::cout<< "("<< pm_temp.get_x() << ", " << pm_temp.get_y() << ")" << '\n';
    };
  };

  void push_back(PM pm){
    ch.push_back(pm);
  };

int size(){
  return ch.size();
}

PM operator[] (const int i){
  return ch[i];
}

void operator= (Chain evolved_ch){
  if (ch.size() < evolved_ch.size()){
    for (int i = 0; i <= evolved_ch.size() - ch.size(); i++){ //quelli che ci sono gia li aggiorna
      ch[i]=evolved_ch[i];
    };  
    for (int i = ch.size(); i < evolved_ch.size(); i++){//se il secondo vettore ha elementi in piu, semplicemente li pusha dentro
      ch.push_back(evolved_ch[i]);
    }; 
  };
}

PM back(){
  return ch.back();
}

auto end(){  //restituisce un iterator che punta all'(ultimo +1) elemento del vector [quindi *(vector.end() -1) da  l'ultimo elemento]
  return ch.end(); //quindi va dereferenziato
}

/*void evolve(){
  std::vector<Chain> evolution_of_chains = rk4_II(ch, 0.1, 10);
}*/
};


int main(){
/* //controllo sulle operazioni della classe PM

    PM pm1(1, 2.3, 67.2);
    PM pm2(33. ,45., 12.);

    std::cout<<"PRIMA" << '\n';
    std::cout<<"pm1 : " << pm1.get_x() << ", " << pm1.get_y() <<"\n";
    std::cout<<"pm2 : " << pm2.get_x() << ", " << pm2.get_y() <<"\n";

    //pm2.update_x(pm1.get_x());
    
    pm1=pm2;

    std::cout<<"DOPO" << '\n';
    std::cout<<"pm1 : " << pm1.get_x() << ", " << pm1.get_y() <<"\n";
    std::cout<<"pm2 : " << pm2.get_x() << ", " << pm2.get_y() <<"\n";
*/

   //controllo sulle operazioni della classe Chain

   Chain ch1{20, 1}; //20 elementi
   Chain ch2(10,9); //10 elementi

 std::cout<<"PRIMA" << '\n';
    std::cout<<"ch1 : " << ch1.size() << "\n";
    std::cout<<"ch2 : " << ch2.size() << "\n";

std::cout<< "CHAIN 1 \n";
for (int i = 0; i < ch1.size(); i++){
    std::cout<<"(" << ch1[i].get_x() << " , "<< ch1[i].get_y()<< ")" << '\n';    
}

std::cout<< "CHAIN 2 \n";
for (int i = 0; i < ch2.size(); i++){
    std::cout<<"(" << ch2[i].get_x() << " , "<< ch2[i].get_y()<< ")" << '\n'; 
}

    ch2=ch1;

 std::cout<<"DOPO" << '\n';
    std::cout<<"ch1 SIZE : " << ch1.size() << "\n";
    std::cout<<"ch2 SIZE : " << ch2.size() << "\n";


std::cout<< "CHAIN 1 \n";
for (int i = 0; i < ch1.size(); i++){
    std::cout<<"(" << ch1[i].get_x() << " , "<< ch1[i].get_y() << ")" << '\n';    
}

std::cout<< "CHAIN 2 \n";
for (int i = 0; i < ch2.size(); i++){
    std::cout<<"(" << ch2[i].get_x() << " , "<< ch2[i].get_y() << ")" << '\n'; 
}


}