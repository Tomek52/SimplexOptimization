#include <gtest/gtest.h>
#include "Simplex.hpp"
#include "SimplexTestSuite.hpp"

struct testSimplexFixture : public ::testing::Test
{
    //Given
    Simplex simplex;
    std::vector<double> emptyVector;
    std::vector<double> vectorOf2Doubles = {1.43, 2};
    std::vector<double> vectorOf4Doubles = {3.23, 4, -0.001, 9999999.1234};
};
TEST_F(testSimplexFixture, testGetObjectiveFunctionWhenFunctionIsEmpty)
{   
    //Then 
    ASSERT_EQ(simplex.getObjectiveFunction(), emptyVector);
}

TEST_F(testSimplexFixture, testSetObjectiveFunctionWhenGivenFunctionIsEmpty)
{
    //When
    simplex.setObjectiveFunction(emptyVector);
    //Then
    ASSERT_EQ(simplex.getObjectiveFunction(), emptyVector);
}

TEST_F(testSimplexFixture, testSetObjectiveFunctionWhenGivenFunctionHave2Params)
{
    //When
    simplex.setObjectiveFunction(vectorOf2Doubles);
    //Then
    ASSERT_EQ(simplex.getObjectiveFunction(), vectorOf2Doubles);
}

TEST_F(testSimplexFixture, testGetConstraintFunctionWhenFunctionNumberIsOutOfRange)
{   
    //Then 
    ASSERT_EQ(simplex.getConstraintFunction(0), emptyVector);
    ASSERT_EQ(simplex.getConstraintFunction(5), emptyVector);
}

TEST_F(testSimplexFixture, testAddConstraintFunctionWhenGivenFunctionHave2Params)
{
    //When
    simplex.addConstraintFunction(vectorOf2Doubles);
    //Then
    ASSERT_EQ(simplex.getConstraintFunction(0), vectorOf2Doubles);
}

TEST_F(testSimplexFixture, testAdd2ConstraintFunctionWhenGivenFunctionsHaveParams)
{
    //When
    simplex.addConstraintFunction(vectorOf2Doubles);
    simplex.addConstraintFunction(vectorOf4Doubles);
    //Then
    ASSERT_EQ(simplex.getConstraintFunction(0), vectorOf2Doubles);
    ASSERT_EQ(simplex.getConstraintFunction(1), vectorOf4Doubles);
}

TEST_F(testSimplexFixture, testCheckObjectiveFunctionIsSolvableByDualSimplexWhenFunctionIsEmpty)
{
    //Then
    ASSERT_FALSE(simplex.checkObjectiveFunctionIsSolvableByDualSimplex());
}

TEST_F(testSimplexFixture, testCheckObjectiveFunctionIsSolvableByDualSimplexWhenFunctionParametersAreCorrect)
{
    //When
    simplex.setObjectiveFunction(vectorOf2Doubles);
    //Then
    ASSERT_TRUE(simplex.checkObjectiveFunctionIsSolvableByDualSimplex());
}

TEST_F(testSimplexFixture, testCheckObjectiveFunctionIsSolvableByDualSimplexWhenFunctionParametersAreIncorrect)
{
    //When
    simplex.setObjectiveFunction(vectorOf4Doubles);
    //Then
    ASSERT_FALSE(simplex.checkObjectiveFunctionIsSolvableByDualSimplex());
}

