#include "SimplexTestSuite.hpp"

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

TEST_F(testSimplexFixture, testCheckSolutionIsOptimalWhenParametersAreCorrect)
{
    //When
    simplex.addConstraintFunction(vectorOf2Doubles);
    simplex.addConstraintFunction(vectorOf4Doubles);
    simplex.addConstraintFunction(vectorOf5Doubles);
    //Then
    ASSERT_TRUE(simplex.checkSolutionIsOptimal());
}

TEST_F(testSimplexFixture, testCheckSolutionIsOptimalWhenParametersAreIncorrect)
{
    //When
    simplex.addConstraintFunction(vectorOf2Doubles);
    simplex.addConstraintFunction(vectorOf4Doubles);
    simplex.addConstraintFunction(vectorOf3Doubles);
    simplex.addConstraintFunction(vectorOf5Doubles);
    //Then
    ASSERT_FALSE(simplex.checkSolutionIsOptimal());
}

TEST_F(testSimplexFixture, testCheckSolutionIsOptimalWhenIsWithoutConstraints)
{
    //Then
    ASSERT_TRUE(simplex.checkSolutionIsOptimal());
}
