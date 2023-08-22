#include <gtest/gtest.h>
#include <tuple>
#include <iostream>

#include "matrix.h"

TEST(Matrix, Creation)
{
    matrix<int, -1> m;
    ASSERT_EQ(m.size(), 0);
}

TEST(Matrix, DefaultValue)
{
    matrix<int, -1> m;

    auto a = m[0][0];

    ASSERT_EQ(a, -1);
    ASSERT_EQ(m.size(), 0);
}

TEST(Matrix, Assignment)
{
    matrix<int, -1> m;
    m[100][100] = 314;
    ASSERT_EQ(m[100][100], 314);
    ASSERT_EQ(m.size(), 1);
}

TEST(Matrix, Tie)
{
    matrix<int, -1> m;
    m[100][100] = 314;

    for (auto c: m)
    {
        int x, y, v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
}
