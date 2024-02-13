#include<iostream>
#include<vector>
#include "FUNCTOR_square.hpp"

int main() {
  const float t_max{10};
  const float dt{0.5};
  auto n{t_max / dt};

  std::cout << "numero di punti: " << n << "\n";

  std::vector<float> vec_x;
  square x;

  float i{};
  while (i <= n) {
    double y = x(i);
    vec_x.push_back(y);
    std::cout << "(" << i << ", " << y << ") \n";

    i += dt;
  };
}