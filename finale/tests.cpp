#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Chain.hpp"
#include "doctest.h"

TEST_CASE("Testing vec") {
  vec v{};
  vec v1{1., 2.};
  vec v2{3., 4.};
  vec null{0., 0.};

  SUBCASE("Testing default constructor") {
    CHECK(v.get_x() == 0.);
    CHECK(v.get_y() == 0.);
  }

  SUBCASE("testin vectorial diff") {
    vec v3 = v2 - v1;
    vec t1{2., 2.};
    CHECK(v3 == t1);
    vec v4 = v1 - v2;
    CHECK(v4 == -1 * t1);
    vec v6 = v1 - null;
    CHECK(v1 == v6);
    vec v7 = null - v1;
    vec t3(-1., -2.);
    CHECK(v7 == t3);
  }

  SUBCASE("testing vectorial sum") {
    vec v3 = v2 + v1;
    vec t1{4., 6.};
    vec t2{2., 3.};
    CHECK(v3 == t1);
    vec v5 = v1 + null;
    CHECK(v1 == v5);
  }
  SUBCASE("testing division by scalar") {
    double d{3.};
    vec v3 = v1 / d;
    vec t1{1. / 3., 2. / 3.};
    CHECK(v3 == t1);
    CHECK_THROWS(v1 / 0.);
    CHECK_THROWS(v1 /= 0.);
  }
  SUBCASE("testing norm") {
    CHECK(v1.norm() == doctest::Approx(sqrt(5.)));
    CHECK(v2.norm() == 5.);
    CHECK(null.norm() == 0.);
  }
}

TEST_CASE("Testing Pm") {
  SUBCASE("testing default constructor") {
    PM pm1{};
    PM t1(0., 0., 0., 0., 0.);
    CHECK(pm1 == t1);
  }
}

TEST_CASE("Testing Chain") {
  PM pm1{1., 2., 3., 4., 5.};
  PM pm2{10., 11., 12., 13., 14.};

  SUBCASE("testing distance") {
    CHECK(d(pm1, pm2) == doctest::Approx(sqrt(2) * 9));
    CHECK(d(pm1, pm2) == d(pm2, pm1));
  }
  SUBCASE("testing versor") {
    vec a = x(pm1, pm2);
    vec b = x(pm2, pm1);
    vec null(0., 0.);

    vec t1(9., 9.);
    CHECK(a == t1);
    CHECK(a == -1 * b);
    CHECK(x(pm1, pm1) == null);
  }
  SUBCASE("testing apply_hooke") {
    Hooke k(10., 2.);
    vec f = apply_hooke(pm1, pm2, k);
    vec t1(10 * (9. - sqrt(2.)), 10 * (9. - sqrt(2.)));
    CHECK(f == t1);
  }
  SUBCASE("testing apply_CF") {
    float w{11};
    vec f = apply_CF(pm1, w);
    vec t1(5. * 11. * 11., 0.);
    CHECK(f == t1);
  }
  SUBCASE("testing apply_gravity") {
    vec f = apply_gravity(pm1);
    vec t1(0, -5. * 9.81);
    CHECK(f == t1);
  }
}