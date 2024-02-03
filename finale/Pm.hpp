#ifndef PM_HPP
#define PM_HPP
#include "Vec.hpp"

class PM {  // Punto Materiale
  vec pos_;
  // vettore posizione
  vec vel_;
  // vettore velocità
  float m_;
  // massa

  sf::CircleShape s;
  // al punto materiale viene assegnata la forma di un cerchio

 public:
  PM(float p_x, float p_y, float v_x, float v_y, float m)
      : pos_{p_x, p_y}, vel_{v_x, v_y}, m_(m) {
    // aggiorna le caratteristiche del punto materiale
    s.setRadius(3);
    s.setPosition(pos_.get_x(), pos_.get_y());
    s.setFillColor(sf::Color::White);
  }  // parametrized constructor date le coordinate di posizione e velocità e
     // massa come argomenti

  PM(vec x, vec y, float m) : pos_(x), vel_(y), m_(m) {
    s.setRadius(3);
    s.setPosition(pos_.get_x(), pos_.get_y());
    s.setFillColor(sf::Color::White);
  }  // parametrized constructor dati i vettori posizione e velocità e massa
     // come argomenti

  PM() = default;
  // default constructor

  bool operator==(PM const &);
  // true se le posizioni sono uguali

  void draw(sf::RenderWindow &);
  // per disegnare il punto materiale

  float get_m() const;
  // restituisce la massa del punto

  void update_x(float const &);
  // aggiorna la componente x
  void update_y(float const &);
  // aggiorna la componente y

  vec get_pos() const;
  // restituisce il vettore posizione
  vec get_vel() const;
  // restituisce il vettore velocità
};

#endif