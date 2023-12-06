#include "libreria_x_main_IV-copia.hpp"

int main(){
    Hooke spring(1, 2);
    std::cout<< "lv = (" << spring.get_lv().get_x() << ", " << spring.get_lv().get_y() << ") \n";
    spring.update_lv(vec(10, 12));
    std::cout<< "lv = (" << spring.get_lv().get_x() << ", " << spring.get_lv().get_y() << ") \n";

}