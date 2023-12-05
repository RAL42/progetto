#include "lib_obj.hpp"
//#include "lib_phys.hpp"
#include<SFML/Graphics.hpp>
//#include "rk4_II.hpp"
#include "prova_rk_seconda_versione.hpp"

int main(){
     int n_PM{20};
     float m{10};
    Chain corda{n_PM, m};
    
    Hooke spring(10); // solo la costante elastica, la lunghezza a riposo è nella classe chain

    float W{10000}; //velocità angolare

     float dt{.1};
     float t_max{5.};
    
    unsigned const display_width = .7 * sf::VideoMode::getDesktopMode().width;
    unsigned const display_height = .7 * sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(display_width, display_height), "CHAIN EVOLUTION");
    window.setPosition(sf::Vector2i(100,100));
    
    sf::Vector2f window_size (window.getSize()); //getsize prende width e height della window
    sf::View view {sf::Vector2f{0,0}, window_size};    //view permette di cambiare l'origine, il primo vettore è l'origine, il secondo e la size della window
    window.setView(view);
    
    sf::Vertex x_axis[] = {sf::Vertex(sf::Vector2f(-window_size.x, 0)), sf::Vertex(sf::Vector2f(window_size.x, 0))};
    sf::Vertex y_axis[] = {sf::Vertex(sf::Vector2f(0, -window_size.y/2)), sf::Vertex(sf::Vector2f(0, window_size.y/2))};
   
    std::vector<Chain> evolution_of_chains = rk4_II(corda, dt, t_max, W, spring.get_k(), m, corda.l);
        
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
 
 
        window.clear(sf::Color::Black);
        
        for (int j = 0; j < evolution_of_chains.size() - 1; j++){
            for (int i = 0; i < evolution_of_chains[j].size() - 1; i++){
                (evolution_of_chains[j])[i].draw(window);    
            }
        }                     
          
        window.display();

    }
}
