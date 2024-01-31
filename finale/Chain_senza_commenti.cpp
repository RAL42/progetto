#include "Chain.hpp"
#include <cassert>
//------------------------------------------------------- FREE FUNCTION -------------------------------------------------------

float w;
bool anticlock = true;

float d(PM pm1, PM pm2)
{ // distanza tra due PM
    vec v = pm1.get_pos() - pm2.get_pos();
    return v.norm();
}

vec x(PM pm1, PM pm2)
{
    return pm2.get_pos() - pm1.get_pos();
} // vettore che esce da pm1 e punta pm2: pm1=pm_j; pm2=pm_j+1 oppure pm_j-1

vec apply_hooke(PM const &pm1, PM const &pm2, Hooke &hooke)
{ // calcola la forza esercitata da pm2 su pm1
    auto temp_x = x(pm1, pm2);
    hooke.update_lv(hooke.get_l() * temp_x / temp_x.norm()); // x è il vettore che esce da PM1 e punta PM2, vedi dopo
    return hooke.get_k() * (temp_x - hooke.get_lv());
}

vec apply_CF(PM const &pm1, float const &omega){ // deve essere un vecc perche dopo devo sommarlo per fare la F totale, in solve
    return vec(pm1.get_m() * omega * omega * pm1.get_pos().get_x(), 0); // ossia ritorna un vec con componente solo lungo x, controlla se è giusto, ma dovrebbe esserlo
}

vec apply_gravity(PM const &pm1) { return vec(0, -pm1.get_m() * 9.81 / (pm1.get_pos().get_y() * pm1.get_pos().get_y())); }

//------------------------------------------------------- CHAIN MEMBER CLASS -------------------------------------------------------

PM Chain::solve(PM pm, vec f, double const &delta_t) const {
    auto const a = f / pm.get_m();
    auto const v = pm.get_vel() + a * delta_t;
    auto const x = pm.get_pos() + (v + 0.5 * a * delta_t) * delta_t;

    return PM(x.get_x(), x.get_y(), v.get_x(), v.get_y(), pm.get_m());
};

bool Chain::empty() { return ch_.empty(); };

std::size_t Chain::size() const { return ch_.size(); };

void Chain::push_back(PM const &pm) { ch_.push_back(pm); }

std::vector<PM> const &Chain::state() const { return ch_; };

PM Chain::operator[](int i) { return ch_[i]; }

void Chain::initial_config(float const &theta, float const &m, float const &r, int const &NoPM) {
    for (int i = 0; i != NoPM / 2; ++i) {                                                                  // con questo ciclo for genero la configurazione iniziale della catena, assegnando la posizioni iniziali utilizzando funzioni di i
        PM pm_temp(r * cos(theta * i), r * sin(theta * i), 0., 0., m); // l'argomento di cos e sin sono in modo tale che i punti, inizialmente, vengano disposti su una circonferenza
        ch_.push_back(pm_temp);
        std::cout << "(" << pm_temp.get_pos().get_x() << ", " << pm_temp.get_pos().get_y() << ")" << '\n';
    };

    PM pm_temp(-r, 0, 0, 0, m);
    ch_.push_back(pm_temp); // metto il polo ovest
    std::cout << "(" << ch_[NoPM / 2].get_pos().get_x() << ", " << ch_[NoPM / 2].get_pos().get_y() << ")" << '\n';

    for (int i = NoPM / 2 + 1; i != NoPM; ++i) {
        PM pm_tempp(r * cos(theta * i), r * sin(theta * i), 0, 0, m); // l'argomento di cos e sin sono in modo tale che i punti, inizialmente, vengano disposti su una circonferenza
        ch_.push_back(pm_tempp);
        std::cout << "(" << pm_tempp.get_pos().get_x() << ", " << pm_tempp.get_pos().get_y() << ")" << '\n';
    }

    std::cout << "size of chain initially = " << ch_.size() << '\n';
}

void Chain::evolve(double const &dt) {
    std::cout << "\nNell'evolve della Chain \n";

    std::vector<PM> ch_copy = ch_;

    if (anticlock) { // integra in senso antiorario
        anticlock = !anticlock;

        std::cout << "\nANTIORARIO \n";

        auto state_it = ch_.begin();
        auto state_it_next = std::next(state_it);
        auto state_last = std::prev(ch_.end());

        auto state_it_copy = ch_copy.begin();
        auto state_it_next_copy = std::next(state_it_copy);
        auto state_last_copy = std::prev(ch_copy.end());

        vec f_prev(apply_hooke(*state_it_copy, *state_last_copy, hooke_) + apply_CF(*state_last_copy, w));

        std::cout << "\nInizio for dei calcoli \n";
        for (; state_it != state_last; ++state_it, ++state_it_next, ++state_it_copy, ++state_it_next_copy) {

            vec f = apply_hooke(*state_it_copy, *state_it_next_copy, hooke_) + apply_CF(*state_it_copy, w);
            *state_it = solve(*state_it_copy, f + f_prev, dt);

            if (std::distance(ch_.begin(), state_it) == 0) { // ri-aggiorno la y del polo est (a dx)
                (*state_it).update_y(0.);
            } else if (static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size() / 2) { // ri-aggiorno la y del polo ovest (a sx)
                (*state_it).update_y(0.);
            } else if (static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size() / 4) { // ri-aggiorno la x del polo nord
                (*state_it).update_x(0.);
            } else if (static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size() / 4 * 3) { // ri-aggiorno la x del polo sud
                (*state_it).update_x(0.);
            }

            f_prev = apply_hooke(*state_it_next_copy, *state_it_copy, hooke_) + apply_CF(*state_it_copy, w);
        }

        vec f = apply_hooke(*ch_copy.begin(), *state_last_copy, hooke_) + apply_CF(*ch_copy.begin(), w);
        *state_last = solve(*state_last_copy, f + f_prev, dt);

    } else { // integra in senso orario
        anticlock = !anticlock;

        std::cout << "\nORARIO \n";

        auto state_it = std::prev(ch_.end());
        auto state_it_next = std::prev(state_it);
        auto state_last = ch_.begin();

        auto state_it_copy = std::prev(ch_copy.end());
        auto state_it_next_copy = std::prev(state_it_copy);
        auto state_last_copy = ch_copy.begin();

        vec f_prev(apply_hooke(*state_it_copy, *state_last_copy, hooke_) + apply_CF(*state_last_copy, w));

        for (; state_it != state_last; --state_it, --state_it_next, --state_it_copy, --state_it_next_copy) {

            vec f = apply_hooke(*state_it_copy, *state_it_next_copy, hooke_) + apply_CF(*state_it_copy, w);
            *state_it = solve(*state_it_copy, f + f_prev, dt);

            if (std::distance(ch_.begin(), state_it) == 0) { // ri-aggiorno la y del polo est (a dx)
                (*state_it).update_y(0.);
            } else if (static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size() / 2) { // ri-aggiorno la y del polo ovest (a sx)
                (*state_it).update_y(0.);
            } else if (static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size() / 4) { // ri-aggiorno la x del polo nord
                (*state_it).update_x(0.);
            } else if (static_cast<long unsigned int>(std::distance(ch_.begin(), state_it)) == ch_.size() / 4 * 3) { // ri-aggiorno la x del polo sud
                (*state_it).update_x(0.);
            }

            f_prev = apply_hooke(*state_it_next_copy, *state_it_copy, hooke_) + apply_CF(*state_it_copy, w);
        }

        vec f = apply_hooke(*std::prev(ch_copy.end()), *state_last_copy, hooke_) + apply_CF(*std::prev(ch_copy.end()), w);
        *state_last = solve(*state_last_copy, f + f_prev, dt);
    }
};
