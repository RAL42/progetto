#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Chain.hpp"

TEST_CASE("Testing vec")
{
    vec v{};
    vec v1{1., 2.};
    vec v2{3., 4.};
    vec null{0., 0.};

    SUBCASE("Testing default constructor")
    {
        CHECK(v.get_x() == 0.);
        CHECK(v.get_y() == 0.);
    }

    SUBCASE("testin vectorial diff")
    {
        vec v3 = v2 - v1;
        vec t1{2., 2.};
        CHECK(v3 == t1);
        vec v4 = v1 - v2;
        CHECK(v4 == -1*t1);
        vec v6 = v1 - null;
        CHECK(v1 == v6);
        vec v7 = null - v1;
        vec t3(-1., -2.);
        CHECK(v7 == t3);
    }

    SUBCASE("testing vectorial sum")
    {
        vec v3 = v2 + v1;
        vec t1{4., 6.};
        vec t2{2., 3.};
        CHECK(v3 == t1);
        vec v5 = v1 + null;
        CHECK(v1 == v5);
    }
    SUBCASE("testing division by scalar")
    {
        double d{3.};
        vec v3 = v1 / d;
        vec t1{1. / 3., 2. / 3.};
        CHECK(v3 == t1);
        CHECK_THROWS(v1 / 0.);
        CHECK_THROWS(v1 /= 0.);
    }
    SUBCASE("testing norm")
    {
        CHECK(v1.norm() == sqrt(5.));
        CHECK(v2.norm() == 5.);
        CHECK(null.norm() == 0.);
    }
}