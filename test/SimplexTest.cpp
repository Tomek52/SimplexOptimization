#include <gtest/gtest.h>
#include "Simplex.hpp"

struct testSimplex : public ::testing::Test
{
    //Given
    Simplex simplex;
};

TEST_F(testSimplex, testingTestFunction)
{
    ASSERT_EQ(simplex.SimplexTest(), "Simplex test");
}