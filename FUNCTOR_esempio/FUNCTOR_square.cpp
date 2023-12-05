#include<iostream>
#include<vector>
#include "FUNCTOR_square.hpp"

int main() {
  const float t_max{10};
  const float dt{0.1};
  auto n{t_max / dt};

  std::cout << n << "\n";

  std::vector<float> vec_x;
  square x;

  float i;
  while (i <= n) {
    x(i);
    vec_x.push_back(x(i));
    std::cout << "(" << i << ", " << x(i) << ") \n";

    i += dt;
  };

}