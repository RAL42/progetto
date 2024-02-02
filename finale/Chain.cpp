#include "Chain.hpp"

#include <cassert>
// --------------------- FREE FUNCTION ---------------------

float w;
bool anticlock = false;
std::vector<float> Kinetic_energies;
std::vector<float> Potential_energies;

float d(PM pm1, PM pm2) { return (pm1.get_pos() - pm2.get_pos()).norm(); }

vec x(PM pm1, PM pm2) { return pm2.get_pos() - pm1.get_pos(); }

vec apply_hooke(PM const& pm1, PM const& pm2, Hooke& hooke) {
  auto temp_x = x(pm1, pm2);
  hooke.update_lv(hooke.get_l() * temp_x / temp_x.norm());
  return hooke.get_k() * (temp_x - hooke.get_lv());
}  // calcola la forza elastica esercitata da pm2 su pm1

vec apply_CF(PM const& pm1, float const& omega) {
  return vec(pm1.get_m() * omega * omega * pm1.get_pos().get_x(), 0);
}

vec apply_gravity(PM const& pm1) { return vec(0, -pm1.get_m() * 9.81); }

// --------------------- CHAIN MEMBER CLASS ---------------------

PM Chain::solve(PM pm, vec f, double const& delta_t) const {
  auto const a = f / pm.get_m();
  auto const v = pm.get_vel() + a * delta_t;
  auto const x = pm.get_pos() + (v + 0.5 * a * delta_t) * delta_t;

  return PM(x.get_x(), x.get_y(), v.get_x(), v.get_y(), pm.get_m());
};

std::size_t Chain::size() const { return ch_.size(); };

void Chain::push_back(PM const& pm) { ch_.push_back(pm); }

std::vector<PM> const& Chain::state() const { return ch_; };

PM Chain::operator[](int i) { return ch_[i]; }

void Chain::initial_config(float const& theta, float const& m, float const& r,
                           int const& NoPM) {
  for (int i = 0; i != NoPM; ++i) {
    // con questo ciclo genero i dei punti della catena e li dispongo su una
    // circoneferenza, assegnando la posizioni iniziali utilizzando funzioni di
    // i

    PM pm_temp(r * cos(theta * i), r * sin(theta * i), 0., 0., m);
    // l'argomento di cos e sin sono in modo tale che i punti vengano disposti
    // su una circonferenza

    ch_.push_back(pm_temp);
    std::cout << "(" << pm_temp.get_pos().get_x() << ", "
              << pm_temp.get_pos().get_y() << ")" << '\n';
  };

  std::cout << "size of chain initially = " << ch_.size() << '\n';
}

void Chain::evolve(double const& dt) {
  // Creo una copia della chain, poi calcolo l'evoluzione passando la copia
  // della catena

  Kinetic_energies.clear();
  Potential_energies.clear();

  std::vector<PM> ch_copy = ch_;

  float Kinetic_energy;
  // energia cinetica del singolo elemento
  float Potential_energy;
  // energia potenziale del singolo elemento

  if (anticlock) {
    // integra in senso antiorario
    anticlock = !anticlock;

    auto state_it = ch_.begin();
    auto state_it_next = std::next(state_it);
    auto state_last = std::prev(ch_.end());

    auto state_it_copy = ch_copy.begin();
    auto state_it_next_copy = std::next(state_it_copy);
    auto state_last_copy = std::prev(ch_copy.end());

    vec f_prev(apply_hooke(*state_it_copy, *state_last_copy, hooke_) +
               apply_CF(*state_last_copy, w));

    for (; state_it != state_last;
         ++state_it, ++state_it_next, ++state_it_copy, ++state_it_next_copy) {
      vec f = apply_hooke(*state_it_copy, *state_it_next_copy, hooke_) +
              apply_CF(*state_it_copy, w);
      *state_it = solve(*state_it_copy, f + f_prev, dt);

      if (static_cast<long unsigned int>(
              std::distance(ch_.begin(), state_it)) == ch_.size() / 4) {
        // ri-aggiorno la x del polo nord
        (*state_it).update_x(0.);

      } else if (static_cast<long unsigned int>(std::distance(
                     ch_.begin(), state_it)) == ch_.size() / 4 * 3) {
        // ri-aggiorno la x del polo sud
        (*state_it).update_x(0.);
      };

      f_prev = apply_hooke(*state_it_next_copy, *state_it_copy, hooke_) +
               apply_CF(*state_it_copy, w);

      Kinetic_energy = 0.5 * (*state_it_copy).get_vel().norm() *
                       (*state_it_copy).get_vel().norm() *
                       (*state_it_copy).get_m();
      Kinetic_energies.push_back(Kinetic_energy);

      Potential_energy =
          0.5 * hooke_.get_k() *
          (x(*state_it_copy, *state_it_next_copy) - hooke_.get_lv()).norm() *
          (x(*state_it_copy, *state_it_next_copy) - hooke_.get_lv()).norm();
      Potential_energies.push_back(Potential_energy);
    }

    vec f = apply_hooke(*state_last_copy, *ch_copy.begin(), hooke_) +
            apply_CF(*ch_copy.begin(), w);
    *state_last = solve(*state_last_copy, f + f_prev, dt);

    Kinetic_energy = 0.5 * (*state_last_copy).get_vel().norm() *
                     (*state_last_copy).get_vel().norm() *
                     (*state_last_copy).get_m();

    Kinetic_energies.push_back(Kinetic_energy);

    Potential_energy =
        0.5 * hooke_.get_k() *
        (x(*state_last_copy, *ch_copy.begin()) - hooke_.get_lv()).norm() *
        (x(*state_it_copy, *ch_copy.begin()) - hooke_.get_lv()).norm();
    Potential_energies.push_back(Potential_energy);

  } else {  // integra in senso orario
    anticlock = !anticlock;

    auto state_it = std::prev(ch_.end());
    auto state_it_next = std::prev(state_it);
    auto state_last = ch_.begin();

    auto state_it_copy = std::prev(ch_copy.end());
    auto state_it_next_copy = std::prev(state_it_copy);
    auto state_last_copy = ch_copy.begin();

    vec f_prev(apply_hooke(*state_it_copy, *state_last_copy, hooke_) +
               apply_CF(*state_last_copy, w));

    for (; state_it != state_last;
         --state_it, --state_it_next, --state_it_copy, --state_it_next_copy) {
      vec f = apply_hooke(*state_it_copy, *state_it_next_copy, hooke_) +
              apply_CF(*state_it_copy, w);
      *state_it = solve(*state_it_copy, f + f_prev, dt);

      if (static_cast<long unsigned int>(
              std::distance(ch_.begin(), state_it)) ==
          ch_.size() / 4) {  // ri-aggiorno la x del polo nord
        (*state_it).update_x(0.);
      } else if (static_cast<long unsigned int>(
                     std::distance(ch_.begin(), state_it)) ==
                 ch_.size() / 4 * 3) {  // ri-aggiorno la x del polo sud
        (*state_it).update_x(0.);
      }

      f_prev = apply_hooke(*state_it_next_copy, *state_it_copy, hooke_) +
               apply_CF(*state_it_copy, w);

      Kinetic_energy = 0.5 * (*state_it_copy).get_vel().norm() *
                       (*state_it_copy).get_vel().norm() *
                       (*state_it_copy).get_m();
      Kinetic_energies.push_back(Kinetic_energy);

      Potential_energy =
          0.5 * hooke_.get_k() *
          (x(*state_it_copy, *state_it_next_copy) - hooke_.get_lv()).norm() *
          (x(*state_it_copy, *state_it_next_copy) - hooke_.get_lv()).norm();
      Potential_energies.push_back(Potential_energy);
    }

    vec f = apply_hooke(*state_last_copy, *std::prev(ch_copy.end()), hooke_) +
            apply_CF(*std::prev(ch_copy.end()), w);
    *state_last = solve(*state_last_copy, f + f_prev, dt);

    Kinetic_energy = 0.5 * (*state_last_copy).get_vel().norm() *
                     (*state_last_copy).get_vel().norm() *
                     (*state_last_copy).get_m();
    Kinetic_energies.push_back(Kinetic_energy);

    Potential_energy =
        0.5 * hooke_.get_k() *
        (x(*state_it_copy, *std::prev(ch_copy.end())) - hooke_.get_lv())
            .norm() *
        (x(*state_it_copy, *std::prev(ch_copy.end())) - hooke_.get_lv()).norm();
    Potential_energies.push_back(Potential_energy);
  }
};
