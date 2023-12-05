#include<iostream>

int main(){
    float t{};
    int t_max{5};
    float dt{1};
    int i_max{10};

    while (t <= t_max)
    {
        std::cout<< "---------------------- \n inizio ciclo while j = " << t << '\n';
        for (int i = 0; i < i_max; i++)
        {
            std::cout<< "inizio ciclo for (j = " << t << ") " << " i = " << i << '\n';
        }
        std::cout<<"uscita dal ciclo for"<<'\n';
        t += dt;
    }
    
}