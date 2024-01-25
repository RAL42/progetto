#include "Pm.hpp"
#include<cassert>

int main(){
    PM pm1{1,2,3,4,5};
    PM pm2{6,2,3,7,8};
    
    PM pm3{pm1};
    PM pm4=pm2;

    assert(pm1.get_pos().get_y() == pm2.get_pos().get_y());
    assert(pm1.get_pos().get_x() == pm2.get_pos().get_x()); //must fail
    assert(pm3.get_vel().get_x() == pm4.get_vel().get_x());

}