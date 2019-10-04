#include <gtest/gtest.h>
#include "Simplex.hpp"

struct testSimplex : public ::testing::Test
{
    //Given
    Simplex simplex;
    std::vector<double> emptyVector;
    std::vector<double> vectorOf2Doubles = {1.43, 2};
    std::vector<double> vectorOf4Doubles = {3.23, 4, -0.001, 9999999.1234};
    std::vector<double> vectorOf5Doubles = {1.3, 7.55, -0.001, -0, 0.000000008};
    std::vector<double> vectorOf3Doubles = {-0.5, 6.01, 1};
    
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
    simplex.setObjectiveFunction(vectorOf2Doubles);
    //Then
    ASSERT_EQ(simplex.getObjectiveFunction(), vectorOf2Doubles);
}

TEST_F(testSimplex, testGetConstraintFunctionWhenFunctionNumberIsOutOfRange)
{   
    //Then 
    ASSERT_EQ(simplex.getConstraintFunction(0), emptyVector);
    ASSERT_EQ(simplex.getConstraintFunction(5), emptyVector);
}

TEST_F(testSimplex, testAddConstraintFunctionWhenGivenFunctionHave2Params)
{
    //When
    simplex.addConstraintFunction(vectorOf2Doubles);
    //Then
    ASSERT_EQ(simplex.getConstraintFunction(0), vectorOf2Doubles);
}

TEST_F(testSimplex, testAdd2ConstraintFunctionWhenGivenFunctionsHaveParams)
{
    //When
    simplex.addConstraintFunction(vectorOf2Doubles);
    simplex.addConstraintFunction(vectorOf4Doubles);
    //Then
    ASSERT_EQ(simplex.getConstraintFunction(0), vectorOf2Doubles);
    ASSERT_EQ(simplex.getConstraintFunction(1), vectorOf4Doubles);
}

TEST_F(testSimplex, testCheckObjectiveFunctionIsSolvableByDualSimplexWhenFunctionIsEmpty)
{
    //Then
    ASSERT_FALSE(simplex.checkObjectiveFunctionIsSolvableByDualSimplex());
}

TEST_F(testSimplex, testCheckObjectiveFunctionIsSolvableByDualSimplexWhenFunctionParametersAreCorrect)
{
    //When
    simplex.setObjectiveFunction(vectorOf2Doubles);
    //Then
    ASSERT_TRUE(simplex.checkObjectiveFunctionIsSolvableByDualSimplex());
}

TEST_F(testSimplex, testCheckObjectiveFunctionIsSolvableByDualSimplexWhenFunctionParametersAreIncorrect)
{
    //When
    simplex.setObjectiveFunction(vectorOf4Doubles);
    //Then
    ASSERT_FALSE(simplex.checkObjectiveFunctionIsSolvableByDualSimplex());
}

TEST_F(testSimplex, testCheckSolutionIsOptimalWhenParametersAreCorrect)
{
    //When
    simplex.addConstraintFunction(vectorOf2Doubles);
    simplex.addConstraintFunction(vectorOf4Doubles);
    simplex.addConstraintFunction(vectorOf5Doubles);
    //Then
    ASSERT_TRUE(simplex.checkSolutionIsOptimal());
}

TEST_F(testSimplex, testCheckSolutionIsOptimalWhenParametersAreIncorrect)
{
    //When
    simplex.addConstraintFunction(vectorOf2Doubles);
    simplex.addConstraintFunction(vectorOf4Doubles);
    simplex.addConstraintFunction(vectorOf3Doubles);
    simplex.addConstraintFunction(vectorOf5Doubles);
    //Then
    ASSERT_FALSE(simplex.checkSolutionIsOptimal());
}

TEST_F(testSimplex, testCheckSolutionIsOptimalWhenIsWithoutConstraints)
{
    //Then
    ASSERT_TRUE(simplex.checkSolutionIsOptimal());
}

