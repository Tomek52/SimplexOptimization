#include <gtest/gtest.h>
#include "Simplex.hpp"

struct testSimplex : public ::testing::Test
{
    //Given
    Simplex simplex;
    std::vector<double> emptyVector;
    std::vector<double> objectiveFunction = {1.43, -2};
};

TEST_F(testSimplex, testGetObjectiveFunctionWhenFunctionIsEmpty)
{   
    //Then 
    ASSERT_EQ(simplex.getObjectiveFunction(), emptyVector);
}

TEST_F(testSimplex, testSetObjectiveFunctionWhenGivenFunctionIsEmpty)
{
    //When
    simplex.setObjectiveFunction(emptyVector);
    //Then
    ASSERT_EQ(simplex.getObjectiveFunction(), emptyVector);
}

TEST_F(testSimplex, testSetObjectiveFunctionWhenGivenFunctionHave2Params)
{
    //When
    simplex.setObjectiveFunction(objectiveFunction);
    //Then
    ASSERT_EQ(simplex.getObjectiveFunction(), objectiveFunction);
}