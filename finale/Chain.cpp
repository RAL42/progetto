#include "Chain.hpp"
#include <cassert>
//------------------------------------------------------- FREE FUNCTION -------------------------------------------------------

float w;
bool anticlock = true;

float d(PM pm1, PM pm2) {  // distanza tra due PM
  vec v = pm1.get_pos() - pm2.get_pos();
  return v.norm();
}

vec x(PM pm1, PM pm2) {
  std::cout<<"  vettore che esce da pm1 e punta pm2 " << pm2.get_pos() - pm1.get_pos() << '\n';
  return pm2.get_pos() - pm1.get_pos();
}  // vettore che esce da pm1 e punta pm2: pm1=pm_j; pm2=pm_j+1 oppure pm_j-1

auto apply_hooke(PM const& pm1, PM const& pm2, Hooke& hooke) { // calcola la forza (è un vec)
  auto temp_x = x(pm1, pm2);
  hooke.update_lv(hooke.get_l() * temp_x / temp_x.norm()); //x è il vettore che esce da PM1 e punta PM2, vedi dopo
  return hooke.get_k() * (temp_x - hooke.get_lv()); 
}

auto apply_CF (PM const& pm1, float const& omega){ //deve essere un vecc perche dopo devo sommarlo per fare la F totale, in solve
  return vec(pm1.get_m()*omega*omega*pm1.get_pos().get_x(), 0);     //ossia ritorna un vec con componente solo lungo x, controlla se è giusto, ma dovrebbe esserlo
}

auto apply_gravity(PM const& pm1){return vec(0, -pm1.get_m()*9.81);}

//------------------------------------------------------- CHAIN MEMBER CLASS ------------------------------------------------------- 

PM Chain::solve(PM pm, vec f, double const& delta_t) const {
    auto const a = f / pm.get_m();
    auto const v = pm.get_vel() + a * delta_t;
    auto const x = pm.get_pos() + (v + 0.5 * a * delta_t) * delta_t;

    return PM(x.get_x(), x.get_y(), v.get_x(), v.get_y(), pm.get_m());
};

bool Chain::empty() { return ch_.empty(); };

std::size_t Chain::size() const { return ch_.size(); };

void Chain::push_back(PM const &pm) { ch_.push_back(pm); }

std::vector<PM> const &Chain::state() const {return ch_;};

PM Chain::operator[] (int i) {return ch_[i];}

void Chain::initial_config(float const& theta, float const& m ,float const& r ,int const& NoPM){
  for (int i = 0; i != NoPM/2; ++i) {  // con questo ciclo for genero la configurazione iniziale della catena, assegnando la posizioni iniziali utilizzando funzioni di i
      PM pm_temp(r *cos(theta*i), r * sin(theta*i), 0, 0, m);  // l'argomento di cos e sin sono in modo tale che i punti, inizialmente, vengano disposti su una circonferenza
      ch_.push_back(pm_temp);
      std::cout<< "("<< pm_temp.get_pos().get_x() << ", " << pm_temp.get_pos().get_y() << ")" << '\n';
  };

  PM pm_temp(-r, 0,0, 0, m);
  ch_.push_back(pm_temp); //metto il polo ovest
  std::cout<< "("<< ch_[NoPM/2].get_pos().get_x() << ", " << ch_[NoPM/2].get_pos().get_y() << ")" << '\n';
    
  for (int i = NoPM/2 + 1; i != NoPM; ++i){
    PM pm_tempp(r *cos(theta*i), r * sin(theta*i), 0, 0, m);  // l'argomento di cos e sin sono in modo tale che i punti, inizialmente, vengano disposti su una circonferenza
    ch_.push_back(pm_tempp);
    std::cout<< "("<< pm_tempp.get_pos().get_x() << ", " << pm_tempp.get_pos().get_y() << ")" << '\n';
  }
    
  /*for (int i = 0; i < ch_.size(); i++){
    std::cout<< "x_"<<i<<"=(" << x(ch_[i], ch_[i+1]).get_x() << ", " << x(ch_[i], ch_[i+1]).get_y() << ")" <<'\n';
  }*/
    
  std::cout<<"size of chain initially = " << ch_.size() << '\n'; 
}


void Chain::evolve(double const& dt) {
  std::cout<<"\nNell'evolve della Chain \n";   
  
   /*creo una copia della chain, poi calcolo l'evoluzione (ciclo for) e invece di fare *state_it = f(*state_it) faccio
  *state_it = f(*state_it_copia)
  */

  std::vector<PM> ch_copy = ch_;
//  assert(ch_copy.size() == ch_.size());  

  if (anticlock){//integra in senso antiorario
    anticlock = !anticlock;
  
  std::cout << "\nANTIORARIO \n";

  auto state_it = ch_.begin();
  auto state_it_next = std::next(state_it);
  auto state_last = std::prev(ch_.end());

  auto state_it_copy = ch_copy.begin();
  auto state_it_next_copy = std::next(state_it_copy);
  auto state_last_copy = std::prev(ch_copy.end());

//auto state_it_prov = ch_.begin(), state_it_copy_prov = ch_copy.begin()
/*  
  for (; state_it <= state_last; ++state_it, ++state_it_copy) {
    std::cout<<"\nelemento " << std::distance(ch_.begin(), state_it) << '\n';   
    std::cout<<"ch_copy  "<< (*state_it_copy).get_pos() << '\n';
    std::cout<<"  ch_  "<<(*state_it).get_pos() << '\n';
    assert((*state_it_copy) == (*state_it));
  };  
  std::cout << "fuori dal for\n";

  state_it_copy = ch_copy.begin();
  state_it = ch_.begin();
  std::cout<<"\n state_it_copy = " << std::distance(ch_copy.begin(), state_it_copy) << '\n';   
  std::cout<<"\n state_it = " << std::distance(ch_.begin(), state_it) << '\n';   
*/
  std::cout<<"\npos_copy: "<< (*state_last_copy).get_pos() << '\n';
  std::cout<<"pos: "<< (*state_last).get_pos() << '\n';

  vec f_prev((-1)*(apply_hooke(*state_last, *state_it, hooke_) + apply_CF(*state_last,w))); 
  
  std::cout<<"  f_prev data da pm1 e punta pm2 " << f_prev << '\n';

  /*ossia f_prev è la forza di hooke esercitata dall'ultimo elemento della catena sul primo 
  (ricordo che la catena è chiusa e il primo elemento è quello che giace sull'asse x, l'ultimo sarebbe quello appena sotto).
  Questo poichè nel ciclo for sotto inizio a calcolare le forze a partire dal primo elemento, questo è soggetto alla 
  forza data dall'elemento precedente (f_prev) e dall'elemento successivo, che calcolo dopo (f) (guarda il commento nella chain.hpp in /lab5) 
  */
  /*per rendere costanti i poli, faccio una copia delle loro coordinate x o y e ogni volta che aggiorno lo stato poi le rimetto in posizione
  Non sono sicuro al 100%: se faccio muovere il PM e poi gli cambio la coordinata, nel calcolo dell'evoluzione del punto successivo 
  la forza che rientra in quest'ultimo calcolo sarà quella calcolata con la "coordinata non spostata", si aggiusterà nell'iterazione 
  successiva no? Provo. 
  */

  std::cout << "\nInizio for dei calcoli \n";
  for (; state_it != state_last; ++state_it, ++state_it_next, ++state_it_copy, ++state_it_next_copy) {
    std::cout<<"\npos_copy: "<< (*state_it_copy).get_pos() << '\n';
    std::cout<<"pos: "<< (*state_it).get_pos() << '\n';
    
    /*if (x(*state_it, *state_it_next).norm() >= (hooke_.get_l() + 1) ) //vincolo delle distanze
    {
      (*state_it).update_x(*state_it_copy);
    }*/
    
    vec f = apply_hooke(*state_it_copy, *state_it_next_copy, hooke_) + apply_CF(*state_it_copy, w);
    *state_it = solve(*state_it_copy, f - f_prev, dt);

  if(std::distance(ch_.begin(), state_it) == 0){ //ri-aggiorno la y del polo est (a dx)
      (*state_it).update_y(0);
    }
    else if(static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size()/2){ //ri-aggiorno la y del polo ovest (a sx)
      (*state_it).update_y(0);
    }
    else if(static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size()/4){ //ri-aggiorno la x del polo nord
      (*state_it).update_x(0);
    }
    else if(static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size()/4*3){ //ri-aggiorno la x del polo sud
      (*state_it).update_x(0);
    }

     std::cout<<"  f data da pm1 su pm2 " << f << '\n';
     std::cout<<"  f - f_prev = " << f - f_prev << '\n';

    f_prev = (-1)*f;
  }
  std::cout << "\n Fine dal for dei calcoli \n";

  vec f = apply_hooke(*ch_copy.begin(), *state_last_copy, hooke_) + apply_CF(*ch_copy.begin(), w);
  *state_last = solve(*state_last_copy, f - f_prev, dt);

  std::cout<<"\npos_copy: "<< (*state_it_copy).get_pos() << '\n';
  std::cout<<"pos: "<< (*state_it).get_pos() << '\n';
  std::cout<<"  f data da pm1 su pm2 " << f << '\n';
  std::cout<<"  f - f_prev = " << f - f_prev << '\n';

  std::cout << "\nFine evolve della Chain \n";



  }else{//integra in senso orario
   anticlock = !anticlock;
  
  std::cout << "\nORARIO \n";

  auto state_it = std::prev(ch_.end());
  auto state_it_next = std::prev(state_it);
  auto state_last =  ch_.begin();

  auto state_it_copy = std::prev(ch_copy.end());
  auto state_it_next_copy = std::prev(state_it_copy);
  auto state_last_copy =  ch_copy.begin();

  std::cout<<"\npos_copy: "<< (*state_last_copy).get_pos() << '\n';
  std::cout<<"pos: "<< (*state_last).get_pos() << '\n';

  vec f_prev((-1)*((apply_hooke(*state_last, *state_it, hooke_) + apply_CF(*state_last,w)))); 
  
  std::cout<<"  f_prev data da pm1 e punta pm2 " << f_prev << '\n';
  std::cout << "\nInizio for dei calcoli \n";

  for (; state_it != state_last; --state_it, --state_it_next, --state_it_copy, --state_it_next_copy) {
  
    std::cout<<"\npos_copy: "<< (*state_it_copy).get_pos() << '\n';
    std::cout<<"pos: "<< (*state_it).get_pos() << '\n';
    
    /*if (x(*state_it, *state_it_next).norm() >= (hooke_.get_l() + 1) ) //vincolo delle distanze
    {
      (*state_it).update_x(*state_it_copy);
    }*/
    
    vec f = apply_hooke(*state_it_copy, *state_it_next_copy, hooke_) + apply_CF(*state_it_copy, w);
    *state_it = solve(*state_it_copy, f - f_prev, dt);

    if(std::distance(ch_.begin(), state_it) == 0){ //ri-aggiorno la y del polo est (a dx)
      (*state_it).update_y(0);
    }
    else if(static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size()/2){ //ri-aggiorno la y del polo ovest (a sx)
      (*state_it).update_y(0);
    }
    else if(static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size()/4){ //ri-aggiorno la x del polo nord
      (*state_it).update_x(0);
    }
    else if(static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size()/4*3){ //ri-aggiorno la x del polo sud
      (*state_it).update_x(0);
    }

     std::cout<<"  f data da pm1 su pm2 " << f << '\n';
     std::cout<<"  f - f_prev = " << f - f_prev << '\n';

    f_prev = (-1)*f;
  }
  std::cout << "\n Fine dal for dei calcoli \n";

  vec f = apply_hooke(*std::prev(ch_.end()), *state_last_copy, hooke_) + apply_CF(*std::prev(ch_.end()), w);
  *state_last = solve(*state_last_copy, f - f_prev, dt);

  std::cout<<"\npos_copy: "<< (*state_it_copy).get_pos() << '\n';
  std::cout<<"pos: "<< (*state_it).get_pos() << '\n';
  std::cout<<"  f data da pm1 su pm2 " << f << '\n';
  std::cout<<"  f - f_prev = " << f - f_prev << '\n';

  std::cout << "\nFine evolve della Chain \n";


  }



};


