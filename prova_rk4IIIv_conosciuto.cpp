#include <iostream>
#include <vector>
#include <sstream>

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
  float y_x = x;
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
  float y_y = y;
  return y_y;
}
//---------------------------------------------------------------------------------------------

std::vector<PM> rk4_II(std::vector<PM> ch, float dt, float t_max, float W, float k, float m, float l, float i) {  // i è il tempo, glielo do nel main nel ciclo while
  dxdt.push_back(dxdt0);
  float x_{};
  float y_{};
  std::vector<PM> temp_ch = ch;  
  std::cout<< "capienza dal rk = " << ch.size() << " e " << temp_ch.size() << '\n';

 for (int j = 0; j < ch.size(); j++){
  std::cout << " \n ---------------- \n inizio j = " << j << " ; i = " << i << '\n';

// evoluzione delle x

    float x{};
    float y{};
    float cosTheta{};

    if (j == 0) {  // poichè un vector ha un inizio e una fine, non è una corda
      x = ch[1].get_x() - ch.back().get_x();
      y = ch[1].get_y() - ch.back().get_y();

      auto Dx{abs(ch[1].get_x() - ch[0].get_x())};  // Delta x del primo e secondo elemento della catena
      auto Dy{abs(ch[1].get_y() - ch[0].get_y())};  // Delta y
      cosTheta = Dx / sqrt(Dx * Dx + Dy * Dy);

      // std::cout<< " interm0 j = " << j << " ; i = " << i << '\n';

    } else if (j == ch.size() - 1) {x = (*(ch.end() - 2)).get_x() - ch[0].get_x();
      y = (*(ch.end() - 2)).get_y() - ch[0].get_y();
      // std::cout<< " interm0.01 j = " << j << " ; i = " << i << '\n';

      auto Dx{abs((*(ch.end() - 1)).get_x() -(*(ch.end() - 2)).get_x())};  // Delta x dell'ultimo e penultimo elemento della catena
      auto Dy{abs((ch[1].get_y() - ch[0].get_y()))};  // Delta y
      cosTheta = Dx / sqrt(Dx * Dx + Dy * Dy);

      // std::cout<< " interm0.1 j = " << j << " ; i = " << i << '\n';

    } else {
      x = ch[j + 1].get_x() - ch[j - 1].get_x();
      y = ch[j + 1].get_y() - ch[j - 1].get_y();

      auto Dx{abs(ch[j].get_x() - ch[j + 1].get_x())};
      auto Dy{abs(ch[j].get_y() - ch[j + 1].get_y())};
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
  //temp_ch.push_back(temp_pm);
  temp_ch[j]=temp_pm;
  
    
  //std::cout<< "size of temp ch = " << temp_ch.size() << '\n';
    std::cout << "temp_pm = (" << temp_pm.get_x() << "," << temp_pm.get_y() << ") \n"; 
    std::cout << "CH[i] = (" << ch[i].get_x() << ", " << ch[i].get_y() << ") \n"; 
    std::cout << " fine j = " << j << " ; i = " << i << '\n';
    
};
  return temp_ch;
}

std::string to_string_with_precision(const float a_value, const int n = 2){// https://stackoverflow.com/questions/16605967/set-precision-of-stdto-string-when-converting-floating-point-values
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

int main(){
  PM pm(0,10,1);
  std::vector<PM> corda{pm};
  
  float dt{0.01};
  float t_max{1};

  unsigned const display_width = .7 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = .7 * sf::VideoMode::getDesktopMode().height;
  sf::RenderWindow window(sf::VideoMode(display_width, display_height), "CHAIN EVOLUTION");
  window.setPosition(sf::Vector2i(100, 100));

  sf::Vector2f window_size(window.getSize());  // getsize prende width e height della window
  sf::View view{sf::Vector2f{0, 0}, window_size};  // view permette di cambiare l'origine, il primo vettore è l'origine, il secondo e la size della window
  window.setView(view);

  // sf::Vertex x_axis[] = {sf::Vertex(sf::Vector2f(-window_size.x, 0)),
  // sf::Vertex(sf::Vector2f(window_size.x, 0))}; sf::Vertex y_axis[] =
  // {sf::Vertex(sf::Vector2f(0, -window_size.y/2)), sf::Vertex(sf::Vector2f(0,
  // window_size.y/2))};

  float t {};
  bool start = false;

  while (window.isOpen()) {

 sf::Font font;
    font.loadFromFile("./font/fresco_stamp.ttf");
    sf::Text stringa;
    stringa.setFont(font);
    stringa.setCharacterSize(40);
    stringa.setFillColor(sf::Color::White);
    stringa.setPosition(300, -300);



    sf::Event event;
    
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {start = true;};
     
    }

    
    if (start) {
        while (t <= t_max) {
        std::vector<PM> CH = rk4_II(corda, dt, t_max, 100, 10, 1, 10, t);  // creo la corda evoluta al tempo t
        std::cout << "------------ \n catena all'istante " << t << '\n';

        window.clear(sf::Color::Black);
        for (int i = 0; i < CH.size(); i++) {  // disegno ogni punto della corda appena calcolata
          CH[i].draw(window);

          std::cout << "FUORI CH[i] = (" << CH[i].get_x() << ", " << CH[i].get_y() << ") " << '\n'; 
        }

        stringa.setString(to_string_with_precision(t));
        window.draw(stringa);
        window.display();
        t += dt;
        
      };
    }
  }
}