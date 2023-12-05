#include<iostream>
#include<SFML/System/Time.hpp>
#include<SFML/System/Clock.hpp>

int main(){
    sf::Clock clock{};
    sf::Time tempo_attuale{};

    if (clock.getElapsedTime().asSeconds() - tempo_attuale.asSeconds() == 1)
    {
        std::cout<< "cacca = " << clock.getElapsedTime().asMilliseconds();
    }
    

}